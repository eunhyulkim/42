#include "Proxy.hpp"
#include "ProxyManager.hpp"

timeval g_now;

namespace {
	void timeflag(std::string flag) {
		ft::log(ProxyManager::log_fd, flag + ": " + ft::getSpeed(g_now) + "\n");
	}
}
/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Proxy::Proxy() {}

Proxy::Proxy(ProxyManager* proxy_manager, const std::string& proxy_block)
{
	std::map<std::string, std::string> proxy_map = ft::stringVectorToMap(ft::split(proxy_block, '\n'), ' ');
	struct sockaddr_in server_addr;

	m_manager = proxy_manager;
	m_host = proxy_map["host"];
	m_port = ft::stoi(proxy_map["port"]);

	m_plugin_filter = false;
	m_plugin_log_if = false;
	m_plugin_cache = false;

	/* parse for filter proxy */
	if (ft::hasKey(proxy_map, "filter"))
	{
		m_plugin_filter = true;
		std::string rawFilter = ft::trim(proxy_map["filter"], " {}\t\n");
		std::vector<std::string> rawFilterSplit = ft::split(rawFilter, ',');
		for (std::vector<std::string>::iterator it = rawFilterSplit.begin() ; it != rawFilterSplit.end() ; ++it)
			*it = ft::trim(*it, " []");
		for (std::vector<std::string>::iterator it = rawFilterSplit.begin() ; it != rawFilterSplit.end() ; ++it)
		{
			std::string key = it->substr(0, it->find(":"));
			std::string rawVals = it->substr(it->find(":") + 1);
			std::vector<std::string> vals = ft::split(rawVals, '|');

			for (std::vector<std::string>::iterator it2 = vals.begin() ; it2 != vals.end() ; ++it2)
				m_filters.insert(std::pair<std::string, std::string>(key, *it2));
		}
	}

	if (ft::hasKey(proxy_map, "log-if"))
	{
		m_plugin_log_if = true;
		std::string rawLogQuerys = ft::trim(proxy_map["log-if"], " {}\t\n");
		std::vector<std::string> rawQuerySplit = ft::split(rawLogQuerys, ',');
		for (std::vector<std::string>::iterator it = rawQuerySplit.begin() ; it != rawQuerySplit.end() ; ++it)
			*it = ft::trim(*it, " []");
		for (std::vector<std::string>::iterator it = rawQuerySplit.begin() ; it != rawQuerySplit.end() ; ++it)
		{
			LogQuery log_query;
			std::vector<std::string> querys = ft::split(ft::trim(*it, " "), '|');
			for (size_t i = 0; i < querys.size(); ++i) {
				Query query;
				query.condition = querys[i].substr(0, querys[i].find(":"));
				querys[i] = querys[i].substr(querys[i].find(":") + 1);
				if (querys[i].find("=") != std::string::npos) {
					query.value = querys[i].substr(querys[i].find("=") + 1);
					querys[i] = querys[i].substr(0, querys[i].find("="));
				}
				query.key = querys[i];
				log_query.querys.push_back(query);
			}
			m_log_querys.push_back(log_query);
		}
	}

	if (ft::hasKey(proxy_map, "cache") && (proxy_map["cache"] == "on" || proxy_map["cache"] == "On"))
		m_plugin_cache = true;

	std::vector<std::string> server_tokens = ft::split(ft::trim(proxy_map["server"], "[] \t\n"), ':');
	std::string server_ip = ft::trim(server_tokens[0], " ");
	std::vector<std::string> ports = ft::split(server_tokens[1], '|');
	for (size_t i = 0; i < ports.size(); ++i)
		connectServer(server_ip, ft::stoi(ft::trim(ports[i], " ")));

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
	m_manager->fdSet(m_fd, ProxyManager::READ_SET);
	writeCreateNewProxyLog(m_host, m_port);
}

Proxy::Proxy(const Proxy& copy)
{
	m_manager = copy.m_manager;
	m_filters = copy.m_filters;
	m_log_querys = copy.m_log_querys;
	m_caches = copy.m_caches;
	m_plugin_filter = copy.m_plugin_filter;
	m_plugin_log_if = copy.m_plugin_log_if;
	m_plugin_cache = copy.m_plugin_cache;
	m_host = copy.m_host;
	m_port = copy.m_port;
	m_fd = copy.m_fd;
	m_server_connections = copy.m_server_connections;
	m_client_connections = copy.m_client_connections;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Proxy::~Proxy()
{
	m_manager = NULL;
	m_filters.clear();
	m_log_querys.clear();
	m_caches.clear();
	m_plugin_filter = false;
	m_plugin_log_if = false;
	m_plugin_cache = false;
	m_host.clear();
	m_port = 0;
	m_fd = -1;
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
	m_filters = obj.get_m_filters();
	m_log_querys = obj.get_m_log_querys();
	m_caches = obj.get_m_caches();
	m_plugin_filter = obj.is_on_plugin_filter();
	m_plugin_log_if = obj.is_on_plugin_log_if();
	m_plugin_cache = obj.is_on_plugin_cache();
	m_host = obj.get_m_host();
	m_port = obj.get_m_port();
	m_fd = obj.get_m_fd();
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

ProxyManager* Proxy::get_m_manager() const { return (m_manager); }
const std::multimap<std::string, std::string>& Proxy::get_m_filters() const { return (m_filters); }
const std::vector<Proxy::LogQuery>& Proxy::get_m_log_querys() const { return (m_log_querys); }
const std::map<std::string, std::string>& Proxy::get_m_caches() const { return (m_caches); }
bool Proxy::is_on_plugin_filter() const { return (m_plugin_filter); }
bool Proxy::is_on_plugin_log_if() const { return (m_plugin_log_if); }
bool Proxy::is_on_plugin_cache() const { return (m_plugin_cache); }
const std::string& Proxy::get_m_host() const { return (m_host); }
int Proxy::get_m_port() const { return (m_port); }
int Proxy::get_m_fd() const { return (m_fd); }
const std::map<int, Proxy::ServerConnection>& Proxy::get_m_server_connections() const { return (m_server_connections); }
const std::map<int, Connection>& Proxy::get_m_client_connections() const { return (m_client_connections); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

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

	m_caches.insert(std::pair<std::string, std::string>(request, response));
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
	m_manager->fdClear(server_fd, ProxyManager::READ_SET);
	m_manager->fdClear(server_fd, ProxyManager::WRITE_SET);
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

	if (client_status != Connection::TO_SEND_CLIENT && client_status != Connection::ON_SEND_CLIENT)
		return (false);
	return (m_manager->fdIsset(client_fd, ProxyManager::WRITE_COPY_SET));
}

bool
Proxy::runSendToClient(Connection& client_connection)
{
	Connection& connection = client_connection;
	Connection::Status status = connection.get_m_status();
	int client_fd = client_connection.get_m_client_fd();

	if (status == Connection::TO_SEND_CLIENT)
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
		connection.set_m_status(Connection::ON_SEND_CLIENT);
	}

	
	if (!m_manager->fdIsset(client_fd, ProxyManager::WRITE_SET) || !connection.sendFromWbuf(client_fd))
	{
		closeClientConnection(client_fd);
		return (false);
	}

	bool ret = connection.isSendCompleted();
	if (ret)
	{
		connection.set_m_status(Connection::ON_WAIT);
		m_manager->fdClear(client_fd, ProxyManager::WRITE_SET);
		writeSendResponseLog(connection);
		if (connection.get_m_response().get_m_status_code() / 100 != 2)
			closeClientConnection(client_fd);
		else
		{
			m_manager->fdSet(client_fd, ProxyManager::READ_SET);
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

	if (client_status != Connection::TO_SEND_SERVER && client_status != Connection::ON_SEND_SERVER)
		return (false);
	if (client_status == Connection::TO_SEND_SERVER && server_status == RUN)
		return (false);
	return (m_manager->fdIsset(server_fd, ProxyManager::WRITE_COPY_SET));
}

bool
Proxy::runSendToServer(Connection& client_connection)
{
	Connection& connection = client_connection;
	Connection::Status status = connection.get_m_status();
	int server_fd = client_connection.get_m_server_fd();

	if (status == Connection::TO_SEND_SERVER)
	{
		timeflag("2. Start Send To Server");

		resetConnectionServer(connection);
		server_fd = connection.get_m_server_fd();
		m_manager->fdSet(server_fd, ProxyManager::WRITE_SET);
		if (connection.get_m_is_filtered())
		{
			std::string origin = connection.get_m_request().get_m_origin();

			origin.erase(0, origin.find(" "));
			origin.insert(0, "FAIL");
			Request request = const_cast<Request&>(connection.get_m_request());
			request.set_m_origin(origin);
		}

		connection.set_m_wbuf_for_send(connection.get_m_request().get_m_origin());
		ft::log(ProxyManager::log_fd, "[WBUF]\n" + connection.get_m_wbuf() + "\n");
		connection.set_m_status(Connection::ON_SEND_SERVER);
		m_server_connections[server_fd].status = RUN;
		return (false);
	}

	connection.sendFromWbuf(server_fd);
	bool ret = connection.isSendCompleted();
	if (ret)
	{
		m_manager->fdClear(server_fd, ProxyManager::WRITE_SET);
		std::cout << "clear server fd " << server_fd << std::endl;
		m_manager->fdSet(server_fd, ProxyManager::READ_SET);
		connection.set_m_status(Connection::ON_RECV_SERVER);
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

	if (client_status != Connection::ON_RECV_SERVER || server_fd == -1)
		return (false);
	return (m_manager->fdIsset(server_fd, ProxyManager::READ_COPY_SET));
}

bool
Proxy::runRecvFromServer(Connection& client_connection)
{
	ft::log(ProxyManager::log_fd, "hasRecvWorkFromServer return true\n");
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
		connection.set_m_status(Connection::TO_SEND_CLIENT);
		m_server_connections[server_fd].status = WAIT;
		m_manager->fdClear(server_fd, ProxyManager::READ_SET);
		m_manager->fdSet(client_connection.get_m_client_fd(), ProxyManager::WRITE_SET);
		writeRecvResponseLog(connection);
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

	if (client_status != Connection::ON_WAIT && client_status != Connection::ON_RECV_CLIENT)
		return (false);
	return (m_manager->fdIsset(client_fd, ProxyManager::READ_COPY_SET));
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
	connection.set_m_status(Connection::ON_RECV_CLIENT);
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
			connection.decreaseRbufFromClient(request.get_m_origin().size());
		}
		writeRecvRequestLog(connection);
		connection.set_m_status(Connection::TO_SEND_SERVER);
        connection.set_m_token_size(-1);
		m_manager->fdClear(client_fd, ProxyManager::READ_SET);
	}
	request.set_m_phase(phase);
    return (phase == Request::COMPLETE);
}

/* ************************************************************************** */
/* ----------------------------- PROXY OPERATION ---------------------------- */
/* ************************************************************************** */

void
Proxy::runFiltering(Connection& client_connection)
{
	if (client_connection.get_m_request().get_m_query() == "")
		return ;
	std::map<std::string, std::string> query = \
		ft::stringVectorToMap(ft::split(client_connection.get_m_request().get_m_query(), '&'), '=');
	for (std::map<std::string, std::string>::iterator it = query.begin() ; it != query.end() ; ++it)
	{
		std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> ret;
		ret = m_filters.equal_range(it->first);
		for (std::multimap<std::string, std::string>::iterator it2 = ret.first ; it2 != ret.second ; ++it2)
		{
			if (it->second == it2->second)
			{
				client_connection.set_m_is_filtered(true);
				std::string text = ft::getTimestamp() + "[Filter]";
				text += "[" + client_connection.get_m_client_ip() + ":";
				text += ft::to_string(client_connection.get_m_client_port()) + "]";
				const Request& request = client_connection.get_m_request();
				text += "[Method:" + request.get_m_method_to_string() + "]";
				text += "[URI:" + request.get_m_uri() + "]";
				text += "[Query:" + request.get_m_query() + "]";
				text += " Request Filterd.\n";
				ft::log(ProxyManager::log_fd, text);
			}
		}
	}
}

bool
Proxy::runCaching(Connection& client_connection)
{
	for (std::map<std::string, std::string>::iterator it = m_caches.begin() ; it != m_caches.end() ; ++it)
	{
		std::string s = methodToString(client_connection.get_m_request().get_m_method()) + " " + client_connection.get_m_request().get_m_uri() + "?" + client_connection.get_m_request().get_m_query();
		if (s == it->first)
		{
			client_connection.set_m_is_cached(true);
			std::string text = ft::getTimestamp() + "[Cache]";
			text += "[" + client_connection.get_m_client_ip() + ":";
			text += ft::to_string(client_connection.get_m_client_port()) + "]";
			const Request& request = client_connection.get_m_request();
			text += "[Method:" + request.get_m_method_to_string() + "]";
			text += "[URI:" + request.get_m_query() + "]";
			text += "[Query:" + request.get_m_uri() + "]";
			text += " Request return cached data\n";
			ft::log(ProxyManager::log_fd, text);
			client_connection.set_m_rbuf_from_server(it->second);
			m_manager->fdSet(client_connection.get_m_client_fd(), ProxyManager::WRITE_SET);
			client_connection.set_m_status(Connection::TO_SEND_CLIENT);
			return (true);
		}
	}
	return (false);
}

bool
Proxy::isSatisfiedQuery(Connection& client_connection, const Query& query)
{
	const Request& request = client_connection.get_m_request();

	if (query.condition == "METHOD")
	{
		std::string method = request.get_m_method_to_string();
		for (size_t i = 0; i < method.length(); ++i)
			method[i] = static_cast<char>(toupper(method[i]));
		return (method == query.key);
	}
	else if (query.condition == "QUERY")
		return (request.get_m_query().find(query.key + "=" + query.value) != std::string::npos);
	else if (query.condition == "URI")
		return (request.get_m_uri() == query.key);
	return (false);
}

void
Proxy::writeLogIfCase(Connection& client_connection)
{
	std::string text = ft::getTimestamp() + "[Log-If]";
	text += "[" + client_connection.get_m_client_ip() + ":";
	text += ft::to_string(client_connection.get_m_client_port()) + "]";
	const Request& request = client_connection.get_m_request();
	text += "[Method:" + request.get_m_method_to_string() + "]";
	text += "[URI:" + request.get_m_uri() + "]";
	text += "[Query:" + request.get_m_query() + "]";
	text += " Request return cached data\n";
	ft::log(ProxyManager::log_fd, text);
}

void
Proxy::runLogIf(Connection& client_connection)
{
	std::vector<LogQuery>::iterator it = m_log_querys.begin();
	for (; it != m_log_querys.end(); ++it)
	{
		bool query_satisfied = true;
		std::vector<Query>::iterator it2 = it->querys.begin();
		for (; it2 != it->querys.end(); ++it2)
		{
			if (!isSatisfiedQuery(client_connection, *it2)) {
				query_satisfied = false;
				break ;
			}
		}
		if (query_satisfied == true) {
			writeLogIfCase(client_connection);	
			return ;
		}
	}
}

int
getRandomServerIdx(int option_size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> function_name_dis(0, option_size);
	return (function_name_dis(gen));
}

void
Proxy::runLoadBalancing(Connection& client_connection)
{
	int server_fd = client_connection.get_m_server_fd();

	if (server_fd > 0)
		;
	else if (m_server_connections.size() == 1)
		server_fd = m_server_connections.begin()->first;
	else {
		int idx = getRandomServerIdx(m_server_connections.size() - 1);
		std::cout << "idx:" << idx << std::endl;
		std::map<int, Proxy::ServerConnection>::iterator it = m_server_connections.begin();
		while (idx-- > 0)
			++it;
		server_fd = it->first;
	}
	std::cout << "server_fd: " << server_fd << std::endl;
	client_connection.set_m_server_fd(server_fd);
	m_manager->fdSet(server_fd, ProxyManager::WRITE_SET);
}

void
Proxy::runProxyAction(Connection& client_connection)
{
	// if (m_plugin_log_if)
	// 	runLogIf(client_connection);
	// if (m_plugin_filter)
	// 	runFiltering(client_connection);
	// Request::Method method = client_connection.get_m_request().get_m_method();
	// if (m_plugin_cache && (method == Request::GET || method == Request::HEAD)) {
	// 	if (runCaching(client_connection))
	// 		return ;
	// }
	runLoadBalancing(client_connection);
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
	std::cout << "create server: " << fd << std::endl;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(int)) == -1)
		throw std::runtime_error("SOCKET_OPTION ERROR");
	ft::bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(host.c_str());
	server_addr.sin_port = ft::ws_htons(port);
	if (connect(fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect error:");
        close(fd);
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
	return (fd);
}

bool
Proxy::hasNewConnection() {
	return (m_manager->fdIsset(m_fd, ProxyManager::READ_COPY_SET));
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
		ft::log(ProxyManager::log_fd,
		"[Failed][Function] close function failed in closeConnection method");
	m_manager->fdClear(fd, ProxyManager::READ_SET);
	m_manager->fdClear(fd, ProxyManager::WRITE_SET);
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
		ft::log(ProxyManager::log_fd, "[Failed][Function]failed to cerate client_fd by accept function");
		return (false);
	}
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	client_ip = ft::inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_client_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	writeCreateNewConnectionLog(client_fd, client_ip, client_port);
	m_manager->fdSet(client_fd, ProxyManager::READ_SET);
	return (true);
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Proxy::run()
{
	writeProxyHealthLog();
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

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Proxy::writeCreateNewProxyLog(std::string host, int port)
{	
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Proxy][" + host + ":" + ft::to_string(port) + "]";
	text += " proxy created successfully.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Connection][Proxy:" + m_host + ":" + ft::to_string(m_port) + "] ";
	text += "[Client:" + client_ip + ":" + ft::to_string(client_port) + "] new connection(client fd:" + ft::to_string(client_fd);
	text += ") new connection created.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::reportCreateNewConnectionLog()
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Failed][Connection][Proxy:" + m_host + ":" + ft::to_string(m_port) + "] ";
	text += "failed to create new connection.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeProxyHealthLog()
{
	if (!m_manager->get_m_config().is_on_plugin_health_check() || !ft::isRightTime(1))
		return ;
	std::string text = ft::getTimestamp() + "[HealthCheck]";
	text += "[HealthCheck][Proxy:" + m_host + ":" + ft::to_string(m_port) + "]";
	text += " proxy is live healthy.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeCloseConnectionLog(int client_fd)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Deleted][Connection][Proxy][CFD:" \
	+ ft::to_string(client_fd) + "] Connection closed.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeRecvRequestLog(const Connection& connection)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Readed][Request][Proxy:" + m_host + ":" + ft::to_string(m_port) + "]";
	text += "[Client:" + ft::to_string(connection.get_m_client_fd()) + "]";
	const Request& request = connection.get_m_request();
	text += "[Method:" + request.get_m_method_to_string() + "]";
	text += "[URI:" + request.get_m_uri() + "]";
	text += "[Query:" + request.get_m_query() + "]";
	text += " new request readed.\n";
	text += request.get_m_origin().substr(0, 200);
	text += "\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeSendRequestLog(const Connection& connection)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Sended][Request][Proxy:" + m_host + ":" + ft::to_string(m_port) + "]";
	text += "[Client:" + ft::to_string(connection.get_m_client_fd()) + "]";
	text += "[Server:" + ft::to_string(connection.get_m_server_fd()) + "]";
	const Request& request = connection.get_m_request();
	text += "[Method:" + request.get_m_method_to_string() + "]";
	text += "[URI:" + request.get_m_uri() + "]";
	text += "[Query:" + request.get_m_query() + "]";
	text += " request sended.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeRecvResponseLog(const Connection& connection)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Readed][Response][Proxy:" + m_host + ":" + ft::to_string(m_port) + "]";
	text += "[Client:" + ft::to_string(connection.get_m_client_fd()) + "]";
	text += " new response readed.\n";
	text += connection.get_m_rbuf_from_server().substr(0, 200);
	text += "\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}

void
Proxy::writeSendResponseLog(const Connection& connection)
{
	if (!m_manager->get_m_config().is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Sended][Response][Proxy:" + m_host + ":" + ft::to_string(m_port) + "]";
	text += "[Client:" + ft::to_string(connection.get_m_client_fd()) + "]";
	text += " response sended.\n";
	ft::log(ProxyManager::log_fd, text);
	return ;
}
