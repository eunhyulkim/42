#include "Proxy.hpp"
#include "ServerManager.hpp"

timeval g_now;

namespace {
	void timeflag(std::string flag) {
		ft::log(ServerManager::proxy_fd, -1, flag + ": " + ft::getSpeed(g_now) + "\n");
	}
}
/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Proxy::Proxy() {}

Proxy::Proxy(ServerManager* server_manager, const std::string& proxy_block)
{
	std::map<std::string, std::string> proxy_map = ft::stringVectorToMap(ft::split(proxy_block, '\n'), ' ');
	struct sockaddr_in server_addr;

    m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);

	m_manager = server_manager;
	m_host = proxy_map["host"];
	m_port = ft::stoi(proxy_map["port"]);
	// std::string type = proxy_map["type"];
	// if (type == "cache" || type == "Cache")
	// 	m_type = CACHE_PROXY;
	// else if (type == "LoadBalance" || type == "loadBalance")
	// 	m_type = LOADBALANCE_PROXY;
	// else if (type == "filter" || type == "Filter")
	// 	m_type = FILTER_PROXY;
	// else
	// 	throw (std::invalid_argument("filter type invalid."));

	/* parse for filter proxy */
	std::string rawFilter = proxy_map["filter"].substr(1, proxy_map["filter"].length() - 2);
	std::vector<std::string> rawFilterSplit = ft::split(rawFilter, ',');
	for (std::vector<std::string>::iterator it = rawFilterSplit.begin() ; it != rawFilterSplit.end() ; ++it)
		*it = ft::trim(*it, " []");
	for (std::vector<std::string>::iterator it = rawFilterSplit.begin() ; it != rawFilterSplit.end() ; ++it)
	{
		std::string key = it->substr(0, it->find(":"));
		std::string rawVals = it->substr(it->find(":") + 1);
		std::vector<std::string> vals = ft::split(rawVals, '|');

		for (std::vector<std::string>::iterator it2 = vals.begin() ; it2 != vals.end() ; ++it2)
			m_filter.insert(std::pair<std::string, std::string>(key, *it2));
	}

	std::vector<std::string> servers = ft::split(ft::trim(proxy_map["server"], "[]"), ',');
	std::vector<std::string>::iterator it = servers.begin();
	for (; it != servers.end(); ++it)
	{
		std::vector<std::string> server_url = ft::split(*it, ':');
		std::string host = ft::trim(server_url[0], " ");
		int port = ft::stoi(ft::trim(server_url[1], " "));
		connectServer(host, port);
	}

	if((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("SOCKET ERROR");
	int value = true;
	if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(m_host.c_str());
	server_addr.sin_port = ft::ws_htons(m_port);
	if(bind(m_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(struct sockaddr)) == -1)
		throw std::runtime_error("BIND ERROR");
	if(listen(m_fd, 256) == -1)
		throw std::runtime_error("LISTEN ERROR");
	if (fcntl(m_fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("FCNTL ERROR");
	ft::fdSet(m_fd, &m_read_set);
}

Proxy::Proxy(const Proxy& copy)
{
	m_manager = copy.m_manager;
	// m_type = copy.m_type;
	m_filter = copy.m_filter;
	m_host = copy.m_host;
	m_port = copy.m_port;
	m_fd = copy.m_fd;
	m_max_fd = copy.m_max_fd;
	m_read_set = copy.m_read_set;
	m_read_copy_set = copy.m_read_copy_set;
	m_write_set = copy.m_write_set;
	m_write_copy_set = copy.m_write_copy_set;
	m_server_connections = copy.m_server_connections;
	m_client_connections = copy.m_client_connections;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Proxy::~Proxy()
{
	m_manager = NULL;
	// m_type = UNDEFINED_PROXY;
	m_filter.clear();
	m_host.clear();
	m_port = 0;
	m_fd = -1;
	m_max_fd = 0;
	ft::fdZero(&m_read_set);
	ft::fdZero(&m_read_copy_set);
	ft::fdZero(&m_write_set);
	ft::fdZero(&m_write_copy_set);
	m_server_connections.clear();
	m_client_connections.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Proxy& Proxy::operator=(const Proxy& obj)
{
	if (this == &obj)
		return (*this);
	m_manager = obj.get_m_manager();
	// m_type = obj.get_m_type();
	m_filter = obj.get_m_filter();
	m_host = obj.get_m_host();
	m_port = obj.get_m_port();
	m_fd = obj.get_m_fd();
	m_max_fd = obj.get_m_max_fd();
	m_read_set = obj.get_m_read_set();
	m_read_copy_set = obj.get_m_read_copy_set();
	m_write_set = obj.get_m_write_set();
	m_write_copy_set = obj.get_m_write_copy_set();
	m_server_connections = obj.get_m_server_connections();
	m_client_connections = obj.get_m_client_connections();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Proxy&)
{
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

ServerManager* Proxy::get_m_manager() const { return (m_manager); }
// Proxy::ProxyType Proxy::get_m_type() const { return (m_type); }
// std::string Proxy::get_type_to_string() const
// {
// 	if (m_type == CACHE_PROXY)
// 		return ("CACHE_PROXY");
// 	else if (m_type == LOADBALANCE_PROXY)
// 		return ("LOADBALANCE_PROXY");
// 	else if (m_type == FILTER_PROXY)
// 		return ("FILTER_PROXY");
// 	return ("UNDEFINED_PROXY");
// }
const std::multimap<std::string, std::string>& Proxy::get_m_filter() const { return (m_filter); }
const std::string& Proxy::get_m_host() const { return (m_host); }
int Proxy::get_m_port() const { return (m_port); }
int Proxy::get_m_fd() const { return (m_fd); }
int Proxy::get_m_max_fd() const { return (m_max_fd); }
fd_set Proxy::get_m_read_set() const { return (m_read_set); }
fd_set Proxy::get_m_read_copy_set() const { return (m_read_copy_set); }
fd_set Proxy::get_m_write_set() const { return (m_write_set); }
fd_set Proxy::get_m_write_copy_set() const { return (m_write_copy_set); }
const std::map<int, Proxy::ServerConnection>& Proxy::get_m_server_connections() const { return (m_server_connections); }
const std::map<int, Connection>& Proxy::get_m_client_connections() const { return (m_client_connections); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Proxy::set_m_max_fd(int new_max_fd) { m_max_fd = new_max_fd; }

namespace {
	std::string methodToString(Request::Method method)
	{
		if (method == Request::GET) return ("GET");
		if (method == Request::HEAD) return ("HEAD");
		if (method == Request::PUT) return ("PUT");
		if (method == Request::POST) return ("POST");
		if (method == Request::DELETE) return ("DELETE");
		if (method == Request::OPTIONS) return ("OPTIONS");
		if (method == Request::TRACE) return ("TRACE");
		return ("");
	}
}

void Proxy::add_m_cache(Connection &connection)
{
	std::string request = methodToString(connection.get_m_request().get_m_method()) + " " + connection.get_m_request().get_m_uri() + "?" + connection.get_m_request().get_m_query();
	std::string response = connection.get_m_rbuf_from_server();

	m_cache.insert(std::pair<std::string, std::string>(request, response));
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------------- UTIL ---------------------------------- */
/* ************************************************************************** */

namespace
{
	int
	parseStatusCode(const std::string& responseString)
	{
		if (responseString.size() < 10)
			return (400);
		int status_code = ft::stoi(responseString.substr(9, 3));
		if (status_code < 200 || status_code > 599)
			return (500);
		return (status_code);
	}

	bool
	isMethodHasBody(const Request::Method& method) {
		return (method == Request::POST || method == Request::PUT || method == Request::TRACE);
	}

	int
	getContentLengthValue(const std::string& requestString, size_t length_header_idx)
	{
		while (requestString[length_header_idx] != ':')
			++length_header_idx;
		int from_at = ++length_header_idx;
		while (requestString[length_header_idx] != '\n')
			++length_header_idx;
		int to_at = length_header_idx;
		return (ft::stoi(ft::trim(requestString.substr(from_at, to_at - from_at + 1), "\r\n ")));
	}

	bool
	isTraceHasBody(const std::string& requestString)
	{
		size_t header_end_ldx = requestString.find("\r\n\r\n");

		size_t length_header_idx = requestString.find("Content-Length");
		if (length_header_idx == std::string::npos)
			length_header_idx = requestString.find("content-length");
		if (length_header_idx > header_end_ldx)
			length_header_idx = std::string::npos;

		size_t encoding_header_idx = requestString.find("Chunked");
		if (encoding_header_idx == std::string::npos)
			encoding_header_idx = requestString.find("chunked");
		if (encoding_header_idx > header_end_ldx)
			encoding_header_idx = std::string::npos;

		if (length_header_idx == std::string::npos && encoding_header_idx == std::string::npos)
			return (false);
		if (length_header_idx != std::string::npos)
			return (getContentLengthValue(requestString, length_header_idx) > 0);
		return (true);
	}

    bool
    parseRequestHeader(Connection& connection, Request& request, const std::string& requestString)
    {
        size_t header_end_idx;
        size_t length_header_idx;
        size_t encoding_header_idx;

        if (requestString.size() > 7 && (header_end_idx = requestString.find("\r\n\r\n")) != std::string::npos)
        {
			std::string firstLine = requestString.substr(0, requestString.find("\r\n"));
            std::string method = ft::split(firstLine, ' ')[0];
            if (method == "GET")
                request.set_m_method(Request::GET);
            if (method == "HEAD")
                request.set_m_method(Request::HEAD);
            if (method == "POST")
                request.set_m_method(Request::POST);
            if (method == "TRACE")
                request.set_m_method(Request::TRACE);
            if (method == "PUT")
                request.set_m_method(Request::PUT);
            if (method == "DELETE")
                request.set_m_method(Request::DELETE);
            if (method == "OPTIONS")
                request.set_m_method(Request::OPTIONS);

			std::string rawUri = ft::split(firstLine, ' ')[1];
			if (rawUri.find('?') != std::string::npos)
			{
				request.set_m_query(rawUri.substr(rawUri.find('?') + 1));
				request.set_m_uri(rawUri.substr(0, rawUri.find('?')));
			}
			else
			{
				request.set_m_uri(rawUri);
			}

			if (!isMethodHasBody(request.get_m_method()))
                connection.set_m_token_size(0);
            else if (request.get_m_method() == Request::TRACE && !isTraceHasBody(requestString))
                connection.set_m_token_size(0);
            else if ((((length_header_idx = requestString.find("Content-Length")) != std::string::npos)
            || (length_header_idx = requestString.find("content-length")) != std::string::npos)
			&& length_header_idx < header_end_idx)
			{
                connection.set_m_token_size(getContentLengthValue(requestString, length_header_idx));
			}
            else if (((encoding_header_idx = requestString.find("Chunked")) != std::string::npos ||
			(encoding_header_idx = requestString.find("chunked")) != std::string::npos)
			&& encoding_header_idx < header_end_idx)
			{
                request.set_m_transfer_type(Request::CHUNKED);
			}
            else
                connection.set_m_token_size(0);
            return (true);
        }
        return (false);
    }

    bool
    parseRequestBody(Connection& connection, Request& request, const std::string& requestString)
    {
        Request::Method method = request.get_m_method();
        int token_size;
        size_t header_end_idx = requestString.find("\r\n\r\n");
        size_t body_end_idx;

        if (!isMethodHasBody(method))
		{
			connection.set_m_token_size(requestString.size());
            return (true);
		}
        if (request.get_m_transfer_type() == Request::GENERAL)
        {
            if ((token_size = connection.get_m_token_size()) <= 0)
                connection.set_m_token_size(header_end_idx + 4);
            else if (requestString.size() >= header_end_idx + 4 + token_size)
                connection.set_m_token_size(header_end_idx + 4 + token_size);
            else
                return (false);
            return (true);
        }
        body_end_idx = requestString.find("0\r\n\r\n");
        if (body_end_idx == std::string::npos)
		{
			int count = requestString.size() - 5;
			count = (count <= 0) ? 0 : count;
			request.addOrigin(requestString.substr(0, count));
			connection.decreaseRbufFromClient(count);
            return (false);
		}
		request.addOrigin(requestString.substr(0, body_end_idx + 5));
		connection.decreaseRbufFromClient(body_end_idx + 5);
        return (true);
    }

    bool
    parseResponseHeader(Connection& connection, Response& response, const std::string& responseString)
    {
        size_t header_end_idx;
        size_t length_header_idx;
        size_t encoding_header_idx;

        if ((header_end_idx = responseString.find("\r\n\r\n")) != std::string::npos)
        {
            if ((length_header_idx = responseString.find("Content-Length")) != std::string::npos
			|| (length_header_idx = responseString.find("content-length")) != std::string::npos)
			{
				if (connection.get_m_request().get_m_method() != Request::HEAD)
                	connection.set_m_token_size(getContentLengthValue(responseString, length_header_idx));
				else
					connection.set_m_token_size(0);
			}
            else if ((encoding_header_idx = responseString.find("Chunked")) != std::string::npos
			|| (encoding_header_idx = responseString.find("chunked")) != std::string::npos)
                response.set_m_transfer_type(Response::CHUNKED);
            else
                connection.set_m_token_size(0);
            return (true);
        }
        return (false);
    }

    bool
    parseResponseBody(Connection& connection, Response& response, const std::string& responseString)
    {
        int token_size;
        size_t header_end_idx = responseString.find("\r\n\r\n");
        size_t body_end_idx;

        if (response.get_m_transfer_type() == Response::GENERAL)
        {
            if ((token_size = connection.get_m_token_size()) <= 0)
				return (true);
            else if (responseString.size() >= header_end_idx + 4 + token_size)
                return (true);
            return (false);
        }
        body_end_idx = responseString.find("0\r\n\r\n");
        if (body_end_idx == std::string::npos)
            return (false);
        return (true);
    }
}

void
Proxy::resetConnectionsFd(int from_fd, int to_fd)
{
	std::map<int, Connection>::iterator it = m_client_connections.begin();
	for (; it != m_client_connections.end(); ++it)
	{
		if (it->second.get_m_server_fd() == from_fd)
			it->second.set_m_server_fd(to_fd);
	}
	return ;
}

void
Proxy::resetConnectionServer(Connection& client_connection)
{
	Connection& connection = client_connection;
	int server_fd = client_connection.get_m_server_fd();

	std::string host = m_server_connections[server_fd].host;
	int port = m_server_connections[server_fd].port;
	ft::fdClr(server_fd, &m_write_set);
	ft::fdClr(server_fd, &m_read_set);
	close(server_fd);
	m_server_connections.erase(server_fd);
	connection.set_m_server_fd(connectServer(host, port));
	resetConnectionsFd(server_fd, connection.get_m_server_fd());
}

/* ************************************************************************** */
/* ----------------------------- SEND OPERATION ----------------------------- */
/* ************************************************************************** */

bool
Proxy::hasSendWorkToClient(Connection& client_connection)
{
	Connection::Status client_status = client_connection.get_m_status();
	int client_fd = client_connection.get_m_client_fd();

	if (client_status != Connection::TO_SEND && client_status != Connection::ON_SEND)
		return (false);
	return (ft::fdIsset(client_fd, &m_write_copy_set));
}

bool
Proxy::runSendToClient(Connection& client_connection)
{
	Connection& connection = client_connection;
	Connection::Status status = connection.get_m_status();
	int client_fd = client_connection.get_m_client_fd();

	if (status == Connection::TO_SEND)
	{
		timeflag("5. Start Send To Client");
		Response& response = const_cast<Response&>(connection.get_m_response());
		response.set_m_status_code(parseStatusCode(connection.get_m_rbuf_from_server()));
		connection.set_m_wbuf_for_send(connection.get_m_rbuf_from_server());
		if (!connection.get_m_is_cached() && (connection.get_m_request().get_m_method() == Request::GET || connection.get_m_request().get_m_method() == Request::HEAD))
			add_m_cache(connection);
		connection.set_m_is_cached(false);
		connection.set_m_is_filtered(false);

		connection.clearRbufFromServer();
		connection.set_m_status(Connection::ON_SEND);
	}

	if (!ft::fdIsset(client_fd, &m_write_set) || !connection.sendFromWbuf(client_fd))
	{
		closeClientConnection(client_fd);
		return (false);
	}

	bool ret = connection.isSendCompleted();
	if (ret)
	{
		connection.set_m_status(Connection::ON_WAIT);
		ft::fdClr(client_fd, &m_write_set);
		writeSendResponseLog(connection);
		if (connection.get_m_response().get_m_status_code() / 100 != 2)
		{
			resetConnectionServer(connection);
			closeClientConnection(client_fd);
		}
		else
		{
			ft::fdSet(client_fd, &m_read_set);
			connection.clear();
		}
		timeflag("6. End Send To Client");
	}
	return (ret);
}

bool
Proxy::hasSendWorkToServer(Connection& client_connection)
{
	Connection::Status client_status = client_connection.get_m_status();
	int server_fd = client_connection.get_m_server_fd();
	if (server_fd == -1)
		return (false);
	Proxy::ServerConnectionStatus server_status = m_server_connections[server_fd].status;

	if (client_status != Connection::TO_EXECUTE && client_status != Connection::ON_EXECUTE)
		return (false);
	if (client_status == Connection::TO_EXECUTE && server_status == RUN)
		return (false);
	return (ft::fdIsset(server_fd, &m_write_copy_set));
}

bool
Proxy::runSendToServer(Connection& client_connection)
{
	Connection& connection = client_connection;
	Connection::Status status = connection.get_m_status();
	int server_fd = client_connection.get_m_server_fd();
	bool disconnect = false;

	if (status == Connection::TO_EXECUTE || (disconnect = !connection.sendFromWbuf(server_fd)))
	{
		timeflag("2. Start Send To Server");

		resetConnectionServer(connection);
		server_fd = connection.get_m_server_fd();
		ft::fdSet(server_fd, &m_write_set);
		if (connection.get_m_is_filtered())
		{
			std::string origin = connection.get_m_request().get_m_origin();

			origin.erase(0, origin.find(" "));
			origin.insert(0, "FAIL");
			Request request = const_cast<Request&>(connection.get_m_request());
			request.set_m_origin(origin);
		}

		connection.set_m_wbuf_for_send(connection.get_m_request().get_m_origin());
		ft::log(ServerManager::proxy_fd, -1, "\nSEND MESSAGE TO SERVER:\n" + connection.get_m_wbuf());
		connection.set_m_status(Connection::ON_EXECUTE);
		m_server_connections[server_fd].status = RUN;
	}
	if (disconnect)
	{
		resetConnectionServer(connection);
		ft::fdSet(connection.get_m_server_fd(), &m_write_set);
		return (false);
	}

	bool ret = connection.isSendCompleted();
	if (ret)
	{
		ft::fdClr(server_fd, &m_write_set);
		ft::fdSet(server_fd, &m_read_set);
		writeSendRequestLog(connection);
		timeflag("3. End Send To Server");
	}
	return (ret);
}

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

bool
Proxy::hasRecvWorkFromServer(Connection& client_connection)
{
	Connection::Status client_status = client_connection.get_m_status();
	int server_fd = client_connection.get_m_server_fd();

	if (client_status != Connection::ON_EXECUTE || server_fd == -1)
		return (false);
	return (ft::fdIsset(server_fd, &m_read_copy_set));
}

bool
Proxy::runRecvFromServer(Connection& client_connection)
{
	Connection& connection = client_connection;
	Response& response = const_cast<Response&>(client_connection.get_m_response());
	Response::Phase phase = response.get_m_phase();
	int server_fd = connection.get_m_server_fd();
	char buff[BUFFER_SIZE];
	int count;

	if ((count = recv(server_fd, buff, sizeof(buff), 0)) > 0)
		connection.addRbufFromServer(buff, count);
	if (phase == Response::READY && parseResponseHeader(connection, response, connection.get_m_rbuf_from_server()))
		phase = Response::ON_BODY;
	if (phase == Response::ON_BODY && parseResponseBody(connection, response, connection.get_m_rbuf_from_server()))
		phase = Response::COMPLETE;
	if (phase == Response::COMPLETE)
	{
		connection.set_m_status(Connection::TO_SEND);
		m_server_connections[server_fd].status = WAIT;
		ft::fdClr(server_fd, &m_read_set);
		ft::fdSet(client_connection.get_m_client_fd(), &m_write_set);
		timeflag("4. End Recv From Server");
	}
	response.set_m_phase(phase);
    return (phase == Response::COMPLETE);
}

bool
Proxy::hasRecvWorkFromClient(Connection& client_connection)
{
	Connection::Status client_status = client_connection.get_m_status();
	int client_fd = client_connection.get_m_client_fd();

	if (client_status != Connection::ON_WAIT && client_status != Connection::ON_RECV)
		return (false);
	return (ft::fdIsset(client_fd, &m_read_copy_set));
}

bool
Proxy::runRecvFromClient(Connection& client_connection)
{
	Connection& connection = client_connection;
	Request& request = const_cast<Request&>(client_connection.get_m_request());
	Request::Phase phase = request.get_m_phase();
	int client_fd = connection.get_m_client_fd();
	char buff[BUFFER_SIZE];
	int count;

	if (connection.get_m_status() == Connection::ON_WAIT)
	{
		gettimeofday(&g_now, NULL);
		timeflag("1. Start Recv From Client");
	}
	connection.set_m_status(Connection::ON_RECV);
	if (hasRecvWorkFromClient(client_connection) && (count = recv(client_fd, buff, sizeof(buff), 0)) > 0)
		connection.addRbufFromClient(buff, count);
	if (phase == Request::READY && parseRequestHeader(connection, request, connection.get_m_rbuf_from_client()))
		phase = Request::ON_BODY;
	if (phase == Request::ON_BODY && parseRequestBody(connection, request, connection.get_m_rbuf_from_client()))
		phase = Request::COMPLETE;
	if (phase == Request::COMPLETE)
	{
		if (!isMethodHasBody(request.get_m_method()) || request.get_m_transfer_type() == Request::GENERAL)
		{
			request.addOrigin(connection.get_m_rbuf_from_client().substr(0, connection.get_m_token_size()));
			ft::log(ServerManager::proxy_fd, -1, "\nREQUEST MESSAGE FROM CLIENT:\n" + request.get_m_origin());
			connection.decreaseRbufFromClient(request.get_m_origin().size());
		}
		connection.set_m_status(Connection::TO_EXECUTE);
        connection.set_m_token_size(-1);
		connection.set_m_server_fd(m_server_connections.begin()->first);
		ft::fdSet(connection.get_m_server_fd(), &m_write_set);
		ft::fdClr(client_fd, &m_read_set);
	}
	request.set_m_phase(phase);
    return (phase == Request::COMPLETE);
}

/* ************************************************************************** */
/* ----------------------------- PROXY OPERATION ---------------------------- */
/* ************************************************************************** */

void Proxy::runProxyAction(Connection& client_connection)
{
	runFiltering(client_connection);
	if (client_connection.get_m_request().get_m_method() == Request::GET || client_connection.get_m_request().get_m_method() == Request::HEAD)
		runCaching(client_connection);
	runLoadBalancing(client_connection);
}


void Proxy::runFiltering(Connection& client_connection)
{
	if (client_connection.get_m_request().get_m_query() == "")
		return ;
	std::map<std::string, std::string> query = \
		ft::stringVectorToMap(ft::split(client_connection.get_m_request().get_m_query(), '&'), '=');
	for (std::map<std::string, std::string>::iterator it = query.begin() ; it != query.end() ; ++it)
	{
		std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> ret;
		ret = m_filter.equal_range(it->first);
		for (std::multimap<std::string, std::string>::iterator it2 = ret.first ; it2 != ret.second ; ++it2)
		{
			if (it->second == it2->second)
			{
				std::cout << "[filter] same key, same value" << std::endl;
				client_connection.set_m_is_filtered(true);
			}
		}
	}
}

void Proxy::runCaching(Connection& client_connection)
{
	for (std::map<std::string, std::string>::iterator it = m_cache.begin() ; it != m_cache.end() ; ++it)
	{
		std::string s = methodToString(client_connection.get_m_request().get_m_method()) + " " + client_connection.get_m_request().get_m_uri() + "?" + client_connection.get_m_request().get_m_query();
		if (s == it->first)
		{
			std::cout << "[cache] same request in cache" << std::endl;
			client_connection.set_m_is_cached(true);

			client_connection.set_m_rbuf_from_server(it->second);
			ft::fdSet(client_connection.get_m_client_fd(), &m_write_set);
			client_connection.set_m_status(Connection::TO_SEND);
		}
	}
}

void Proxy::runLoadBalancing(Connection& client_connection)
{
	(void)client_connection;

	// int newFd;
	// int max = 0;

	// for (std::map<int, ServerConnection>::iterator it = m_server_connections.begin() ; it != m_server_connections.end() ; ++it)
	// {
	// 	for (std::vector<Server>::iterator it2 = m_manager->get_m_servers().begin() ; it2 != m_manager->get_m_servers.end() ; ++it2)
	// 	{
	// 		if (it2->get_m_host() == it->second.host
	// 			&& it2->get_m_port() == it->second.port
	// 			&& it2->getFreeWorkerCount() > max)
	// 		{
	// 			max = it2->getFreeWorkerCount();
	// 			newFd = it->first;
	// 		}
	// 	}
	// }
	// client_connection.set_m_server_fd(newFd);
}

/* ************************************************************************** */
/* -------------------------- CONNECTION MANAGEMENT ------------------------- */
/* ************************************************************************** */

int
Proxy::connectServer(std::string host, int port)
{
	struct sockaddr_in server_addr;
	std::string key = host + ":" + ft::to_string(port);
	int fd;

	if((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("SOCKET ERROR");
	int value = true;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(host.c_str());
	server_addr.sin_port = ft::ws_htons(port);
	if (connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect error:");
        close(fd);
		reportConnectServerLog(host, port);
        exit(EXIT_FAILURE);
    }
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("SERVER_CONNECT ERROR");
	ServerConnection server_connection;
	server_connection.socket_fd = fd;
	server_connection.key = key;
	server_connection.host = host;
	server_connection.port = port;
	server_connection.status = Proxy::WAIT;
	m_server_connections.insert(std::pair<int, Proxy::ServerConnection>(fd, server_connection));
	writeConnectServerLog(host, port);
	return (fd);
}

bool
Proxy::hasNewConnection() {
	return (ft::fdIsset(m_fd, &m_read_copy_set));
}

int
Proxy::getUnusedConnectionFd()
{
	std::map<int, Connection>::iterator it = m_client_connections.begin();
	for (; it != m_client_connections.end(); ++it) {
		if (it->second.get_m_status() == Connection::ON_WAIT)
			return (it->first);
	}
	return (-1);
}

void
Proxy::closeClientConnection(int fd)
{
	writeCloseConnectionLog(fd);
	if (close(fd) == -1)
		ft::log(ServerManager::proxy_fd, -1,
		"[Failed][Function] close function failed in closeConnection method");
	ft::fdClr(fd, &m_read_set);
	ft::fdClr(fd, &m_write_set);
	m_client_connections.erase(fd);
}

bool
Proxy::acceptNewConnection()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size = sizeof(struct sockaddr);
	int 				client_fd;
	std::string			client_ip;
	int					client_port;

	ft::bzero(&client_addr, client_addr_size);

	if ((client_fd = accept(m_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1) {
		ft::log(ServerManager::proxy_fd, -1, "[Failed][Function]failed to cerate client_fd by accept function");
		return (false);
	}
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	client_ip = ft::inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_client_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	writeCreateNewConnectionLog(client_fd, client_ip, client_port);
	ft::fdSet(client_fd, &m_read_set);
	return (true);
}

void
Proxy::resetMaxFd()
{
	for (int fd = 512; fd >= 0; --fd)
	{
		if (ft::fdIsset(fd, &m_read_set) || ft::fdIsset(fd, &m_write_set))
		{
			m_max_fd = fd;
			break ;
		}
	}
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Proxy::run()
{
	std::map<int, Connection>::iterator it = m_client_connections.begin();
	while (it != m_client_connections.end())
	{
		std::map<int, Connection>::iterator it2 = it++;
		int fd = it2->first;
		Connection& connection = it2->second;

		if (m_fd == fd)
			continue ;
		if (hasSendWorkToClient(connection) && !runSendToClient(connection))
			continue ;
		if (hasRecvWorkFromServer(connection) && !runRecvFromServer(connection))
			continue ;
		if (hasSendWorkToServer(connection) && !runSendToServer(connection))
			continue ;
		if (hasRecvWorkFromClient(connection) || !(connection.get_m_rbuf_from_client().empty()))
		{
			if (runRecvFromClient(connection))
				runProxyAction(connection);
		}
	}
	if (hasNewConnection())
	{
		if (m_client_connections.size() >= 512)
		{
			int fd = getUnusedConnectionFd();
			if (fd == -1)
				return ;
			closeClientConnection(fd);
		}
		if (!acceptNewConnection())
			reportCreateNewConnectionLog();
	}
}

void
Proxy::runProxy()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	while (true)
	{
		m_read_copy_set = m_read_set;
		m_write_copy_set = m_write_set;
		int cnt;

		resetMaxFd();
		if ((cnt = select(this->m_max_fd + 1, &this->m_read_copy_set, &this->m_write_copy_set, \
		NULL, &timeout)) == -1)
		{
			ft::log(ServerManager::access_fd, ServerManager::error_fd, "[Failed][Function]Select function failed(return -1)");
			throw std::runtime_error("select error");
		}
		else if (cnt == 0)
			continue ;
		writeProxyHealthLog();
		run();
	}
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Proxy::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{
	int fd = ServerManager::proxy_fd;
	std::string text = "[Created][Connection][Proxy][CFD:" \
	+ ft::to_string(client_fd) + "][IP:" + client_ip + "][Port:" + ft::to_string(client_port)
	+ "] Connection Created.\n\n";
	ft::log(fd, -1, text);
	return ;
}

void
Proxy::reportCreateNewConnectionLog()
{
	int fd = ServerManager::proxy_fd;
	std::string text = "[Failed][Connection][Proxy][Host:" + m_host \
	+ ":" + ft::to_string(m_port) + "] Failed to create new connection.\n";
	ft::log(fd, -1, text);
	return ;
}

void
Proxy::writeProxyHealthLog()
{
	if (!ft::isRightTime(SERVER_HEALTH_LOG_SECOND))
		return ;
	int fd = ServerManager::proxy_fd;
	std::string text = "[HealthCheck][Proxy][Max_fd:" + ft::to_string(m_max_fd) \
	+ "][Connection:" + ft::getSetFdString(m_max_fd, &m_read_set) + "]\n";
	ft::log(fd, -1, text);
	return ;
}

void
Proxy::writeCloseConnectionLog(int client_fd)
{
	int fd = ServerManager::proxy_fd;
	std::string text = "[Deleted][Connection][Proxy][CFD:" \
	+ ft::to_string(client_fd) + "] Connection closed.\n";
	ft::log(fd, -1, text);
	return ;

}

void
Proxy::writeConnectServerLog(std::string host, int port)
{
	int fd = ServerManager::proxy_fd;
	std::string text = "[Created][ServerConnection][Proxy][ServerInfo:" \
	+ host + ":" + ft::to_string(port) + "] Connection Created.\n";
	ft::log(fd, -1, text);
}

void
Proxy::reportConnectServerLog(std::string host, int port)
{
	int fd = ServerManager::proxy_fd;
	std::string text = "[Failed][ServerConnection][Proxy][ServerInfo:" \
	+ host + ":" + ft::to_string(port) + "] Connect Failed.\n";
	ft::log(fd, -1, text);
}

void
Proxy::writeSendRequestLog(const Connection& connection)
{
	std::string text = ft::getTimestamp() + "[Sended][Request][Proxy][CFD:" \
	+ ft::to_string(connection.get_m_client_fd()) + "] Request sended\n";
	ft::log(ServerManager::proxy_fd, -1, text);
	return ;
}

void
Proxy::writeSendResponseLog(const Connection& connection)
{
	std::string text = ft::getTimestamp() + "[Sended][Response][Proxy][CFD:" \
	+ ft::to_string(connection.get_m_client_fd()) + "] Response sended\n";
	ft::log(ServerManager::proxy_fd, -1, text);
	return ;

}
