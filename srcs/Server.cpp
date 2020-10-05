#include "Server.hpp"
#include "ServerManager.hpp"

timeval g_start;

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

std::map<std::string, std::string> makeMimeType ()
{
	std::map<std::string, std::string> type_map;

	type_map["avi"] = "video/x-msvivdeo";
	type_map["bin"] = "application/octet-stream";
	type_map["bmp"] = "image/bmp";
	type_map["css"] = "text/css";
	type_map["csv"] = "text/csv";
	type_map["doc"] = "application/msword";
	type_map["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	type_map["gz"] = "application/gzip";
	type_map["gif"] = "image/gif";
	type_map["htm"] = "text/html";
	type_map["html"] = "text/html";
	type_map["ico"] = "image/vnd.microsoft.icon";
	type_map["jepg"] = "image/jepg";
	type_map["jpg"] = "image/jepg";
	type_map["js"] = "text/javascript";
	type_map["json"] = "application/json";
	type_map["mp3"] = "audio/mpeg";
	type_map["mpeg"] = "video/mpeg";
	type_map["png"] = "image/png";
	type_map["pdf"] = "apllication/pdf";
	type_map["php"] = "application/x-httpd-php";
	type_map["ppt"] = "application/vnd.ms-powerpoint";
	type_map["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	type_map["rar"] = "application/vnd.rar";
	type_map["sh"] = "application/x-sh";
	type_map["svg"] = "image/svg+xml";
	type_map["tar"] = "application/x-tar";
	type_map["tif"] = "image/tiff";
	type_map["txt"] = "text/plain";
	type_map["wav"] = "audio/wav";
	type_map["xls"] = "application/xhtml+xml";
	type_map["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	type_map["zip"] = "application/zip";
	type_map["bad_extension"] = "application/bad";
	type_map["bla"] = "application/42cgi";
	type_map["pouic"] = "application/pouic";
	return (type_map);
}
std::map<std::string, std::string> Server::mime_types = makeMimeType();

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::Server() {}

Server::Server(ServerManager* server_manager, const std::string& server_block, std::vector<std::string>& location_blocks, Config* config)
{
	std::map<std::string, std::string> server_map = ft::stringVectorToMap(ft::split(server_block, '\n'), ' ');
	struct sockaddr_in server_addr;
	std::string uri;
	std::string block;
	std::string error_page;
	std::string line;

	m_manager = server_manager;
	m_config = config;
	if (ft::hasKey(server_map, "server_name"))
		m_server_name = server_map["server_name"];
	else
		m_server_name = "noname";
	m_host = server_map["host"];
	m_port = std::stoi(server_map["port"]);
	m_request_uri_limit_size = std::stoi(server_map["REQUEST_URI_LIMIT_SIZE"]);
	m_request_header_limit_size = std::stoi(server_map["REQUEST_HEADER_LIMIT_SIZE"]);
	m_limit_client_body_size = std::stoi(server_map["LIMIT_CLIENT_BODY_SIZE"]);
	m_default_error_page = ft::getStringFromFile(server_map["DEFAULT_ERROR_PAGE"]);

	//socket 생성
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
	m_manager->fdSet(m_fd, ServerManager::READ_SET);
	if (m_manager->get_m_max_fd() < m_fd)
		m_manager->set_m_max_fd(m_fd);
	for (std::vector<std::string>::iterator it = location_blocks.begin(); it != location_blocks.end(); ++it)
	{
		uri = ft::split(ft::split(*it).front(), ' ')[1];
		block = *it;
		block = block.substr(block.find('\n') + 1);
		m_locations.push_back(Location(uri, block, m_limit_client_body_size));
	}
}

Server::Server(const Server& copy)
{
	m_manager = copy.m_manager;
	m_server_name = copy.m_server_name;
	m_host = copy.m_host;
	m_port = copy.m_port;
	m_fd = copy.m_fd;
	m_request_uri_limit_size = copy.m_request_uri_limit_size;
	m_request_header_limit_size = copy.m_request_header_limit_size;
	m_limit_client_body_size = copy.m_limit_client_body_size;
	m_default_error_page = copy.m_default_error_page;
	m_config = copy.m_config;
	m_locations = copy.m_locations;
	m_connections = copy.m_connections;
	m_responses = copy.m_responses;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Server::~Server(){}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Server& Server::operator=(const Server& obj)
{
	if (this == &obj)
		return (*this);
	m_manager = obj.m_manager;
	m_server_name = obj.m_server_name;
	m_host = obj.m_host;
	m_port = obj.m_port;
	m_fd = obj.m_fd;
	m_request_uri_limit_size = obj.m_request_uri_limit_size;
	m_request_header_limit_size = obj.m_request_header_limit_size;
	m_limit_client_body_size = obj.m_limit_client_body_size;
	m_default_error_page = obj.m_default_error_page;
	m_config = obj.m_config;
	m_locations = obj.m_locations;
	m_connections = obj.m_connections;
	m_responses = obj.m_responses;
	/* overload= code */
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Server& server)
{

	out << "server_name: " << server.get_m_server_name() << std::endl;
	out << "host: " << server.get_m_host() << std::endl;
	out << "port: " << server.get_m_port() << std::endl;
	out << "server_fd: " << server.get_m_fd() << std::endl;
	out << "request_uri_limit_size: " << server.get_m_request_uri_limit_size() << std::endl;
	out << "request_header_limit_size: " << server.get_m_request_header_limit_size() << std::endl;
	out << "limit_client_body_size: " << server.get_m_limit_client_body_size() << std::endl;
	out << "default_error_page: " << server.get_m_default_error_page() << std::endl;
	out << "--------CONFIG----------" << std::endl;
	out << *(server.get_m_config()) << std::endl;
	out << "--------LOCATIONS----------" << std::endl;
	for (std::vector<Location>::const_iterator it = server.get_m_locations().begin(); it != server.get_m_locations().end(); ++it) {
		out << *it << std::endl;
	}
	std::cout << "--------CONNECTIONS----------" << std::endl;
	for (std::map<int, Connection>::const_iterator it = server.get_m_connections().begin(); it != server.get_m_connections().end(); ++it) {
		out << it->second << std::endl;
	}
	std::cout << "--------NEXT RESPONSE----------" << std::endl;
	if (server.get_m_responses().size() > 0)
		out << server.get_m_responses().front() << std::endl;
	else
		out << "Response is not exist." << std::endl;
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const std::string& Server::get_m_server_name() const { return (this->m_server_name); }
const std::string& Server::get_m_host() const { return (this->m_host); }
int Server::get_m_port() const { return (this->m_port); }
int Server::get_m_fd() const { return (this->m_fd); }
size_t Server::get_m_request_uri_limit_size() const { return (this->m_request_uri_limit_size); }
size_t Server::get_m_request_header_limit_size() const { return (this->m_request_header_limit_size); }
size_t Server::get_m_limit_client_body_size() const { return (this->m_limit_client_body_size); }
const std::string& Server::get_m_default_error_page() const { return (this->m_default_error_page); }
Config* Server::get_m_config() const { return (this->m_config); }
const std::vector<Location>& Server::get_m_locations() const { return (this->m_locations); }
const std::map<int, Connection>& Server::get_m_connections() const { return (this->m_connections); }
const std::queue<Response>& Server::get_m_responses() const { return (this->m_responses); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------------- UTIL ---------------------------------- */
/* ************************************************************************** */

/*
** function: solveRequest
** 1. check request method is allowed
** 2. Check authentication is required
** 3. If uri is directory, executeAutoindex
** 4. If uri is file, executeMethod
*/

void basic_decode(std::string data, std::string& key, std::string& value)
{
	std::string decodedData = ft::containerToString(ft::base64_decode(data), "");
	if (decodedData.find(":") == std::string::npos || decodedData.find(":") == decodedData.size() - 1)
		return ;
	int idx = decodedData.find(":");
	key = decodedData.substr(0, idx);
    std::vector<unsigned char> value_base(decodedData.begin() + idx + 1, decodedData.end());
    value = ft::base64_encode(&value_base[0], value_base.size());
}

std::string
Server::inet_ntoa(unsigned int address)
{
	std::string ret;

	ret = std::to_string(address & 0xFF) + ".";
	ret.append(std::to_string((address >> 8) & 0xFF) + ".");
	ret.append(std::to_string((address >> 16) & 0xFF) + ".");
	ret.append(std::to_string((address >> 24) & 0xFF));
	return (ret);
}

/* ************************************************************************** */
/* ----------------------------- SEND OPERATION ----------------------------- */
/* ************************************************************************** */

bool
Server::hasSendWork(Connection& connection)
{
	Connection::Status status = connection.get_m_status();
	int fd = connection.get_m_client_fd();
	if (status != Connection::TO_SEND && status != Connection::ON_SEND)
		return (false);
	return (m_manager->fdIsset(fd, ServerManager::WRITE_COPY_SET));
}

bool
Server::runSend(Connection& connection)
{
	Connection::Status status = connection.get_m_status();
	if (status == Connection::TO_SEND)
	{
		connection.set_m_wbuf_for_send();
		connection.set_m_status(Connection::ON_SEND);
	}

	int fd = connection.get_m_client_fd();
	const std::string& data = connection.get_m_wbuf();
	int count = (data.size() > BUFFER_SIZE) ? BUFFER_SIZE : data.size();
	count = send(fd, data.c_str(), count, 0);
	connection.decreaseWbuf(count);
	bool ret = connection.get_m_wbuf().empty();
	if (ret)
	{
		connection.set_m_status(Connection::ON_WAIT);
		m_manager->fdClear(fd, ServerManager::WRITE_SET);
		writeSendResponseLog(connection.get_m_response());
		if (connection.get_m_response().get_m_status_code() / 100 != 2)
			closeConnection(connection.get_m_client_fd());
		else
			connection.clear();
		// m_manager->writeServerHealthLog(true);
	}
	return (ret);
}

/* ************************************************************************** */
/* ---------------------------- EXECUTE OPERATION --------------------------- */
/* ************************************************************************** */


namespace {
	bool isMethodHasBody(const Request::Method& method) {
		return (method == Request::POST || method == Request::PUT || method == Request::TRACE);
	}
	int getChunkedSize(std::string& buf, std::string& len)
	{
		int content_length;
		if (!ft::getline(buf, len))
			return (-1);
		try {
			content_length = std::stoi(len, 0, 16);
		} catch (std::exception& e) {
			throw (40017);
		}
		if (content_length < 0)
			throw (40016);
		if (content_length == 0)
		{
			if (len[0] != '0')
				throw (40017);
		}
		return (content_length);
	}
}


bool
Server::hasExecuteWork(Connection& connection)
{
	Connection::Status status = connection.get_m_status();
	int from_child_fd = connection.get_m_from_child_fd();
	int to_child_fd = connection.get_m_to_child_fd();
	int stat;
	bool select_from = false;
	bool select_to = false;

	if (status != Connection::ON_EXECUTE)
		return (false);
	if (from_child_fd == -1 && to_child_fd == -1)
		return (false);
	if (from_child_fd != -1 && (select_from = m_manager->fdIsset(from_child_fd, ServerManager::READ_COPY_SET)))
		return (true);
	if (to_child_fd != -1 && m_manager->fdIsset(to_child_fd, ServerManager::WRITE_COPY_SET))
		return (true);
	select_to = !connection.get_m_wbuf().empty();
	waitpid(connection.get_m_child_pid(), &stat, WNOHANG);
	if (WIFEXITED(stat) && !select_from && !select_to)
		return (true);
	return (false);
}

bool
Server::runExecute(Connection& connection)
{
	int from_child_fd = connection.get_m_from_child_fd();
	int to_child_fd = connection.get_m_to_child_fd();
	int client_fd = connection.get_m_client_fd();
	int stat;
	bool select_from = true;
	bool select_to = false;
	char buff[BUFFER_SIZE];
	int count;
	const Request& request = connection.get_m_request();

	ft::log(ServerManager::access_fd, -1, "[MAIN][0]\n");
	if (to_child_fd != -1 && m_manager->fdIsset(to_child_fd, ServerManager::WRITE_COPY_SET))
	{
		
		ft::log(ServerManager::access_fd, -1, "[MAIN][1-1]\n");
		if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
		{
			ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WRITE][START]\n");
			std::string& buf = const_cast<std::string&>(connection.get_m_rbuf());
			if (m_manager->fdIsset(client_fd, ServerManager::READ_COPY_SET))
			{
				ft::log(ServerManager::access_fd, -1, "[MAIN][1-1-1]\n");
				ft::log(ServerManager::access_fd, -1, "RBUF SIZE: " + std::to_string(buf.size()) + "\n");
				if ((count = recv(client_fd, buff, sizeof(buff), 0)) > 0)
					connection.addRbuf(buff, count);
				ft::log(ServerManager::access_fd, -1, "READ FROM COUNT: " + std::to_string(count) + "\n");
				if (count > 0)
					ft::log(ServerManager::access_fd, -1, "READ CONTENT: " + std::string(buff, count) + " with " + std::to_string((int)buff[0]) + "\n");
			}
			std::string len;
			int content_length = getChunkedSize(buf, len);
			ft::log(ServerManager::access_fd, -1, "Content-Length: " + std::to_string(content_length));
			if (content_length == -1)
				;
			else if (content_length == 0)
			{
				if (buf.find("\r\n") == std::string::npos)
					buf.insert(0, len + "\r\n");
				else if (buf.size() >= 2 && buf[0] == '\r' && buf[1] == '\n')
				{
					connection.decreaseRbuf(2);
					close(to_child_fd);
					m_manager->fdClear(to_child_fd, ServerManager::WRITE_SET);
					m_manager->resetMaxFd();
				}
			}
			else if (static_cast<int>(buf.size()) < content_length + 2)
			{
				buf.insert(0, len + "\r\n");
				return (false);
			}
			else
			{
				count = write(to_child_fd, buf.c_str(), count);
				ft::log(ServerManager::access_fd, -1, std::to_string(count) + " writed.\n");
				connection.decreaseRbuf(content_length + 2);
			}
		}
		else
		{
			ft::log(ServerManager::access_fd, -1, "[MAIN][1-2]\n");
			const std::string& data = connection.get_m_wbuf();
			if (!data.empty())
			{
				ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WRITE][CASE: NOT EMPTY][START]\n");
				int count = (data.size() > BUFFER_SIZE) ? BUFFER_SIZE : data.size();
				ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WRITE][CASE: NOT EMPTY][STEP 1]\n");
				count = write(to_child_fd, data.c_str(), count);
				ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WRITE][CASE: NOT EMPTY][STEP 2]\n");
				connection.decreaseWbuf(count);
				ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WRITE][CASE: NOT EMPTY][END]\n");
			}
			else
			{
				close(to_child_fd);
				m_manager->fdClear(to_child_fd, ServerManager::WRITE_SET);
				m_manager->resetMaxFd();
			}
		}
		
		ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][WIRTE][END]\n");
	}

	if (from_child_fd != -1 && m_manager->fdIsset(from_child_fd, ServerManager::READ_COPY_SET))
	{
		ft::log(ServerManager::access_fd, -1, "[MAIN][2-1]\n");
		ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[OPERATION][READ][START]\n");
		count = read(from_child_fd, buff, sizeof(buff));
		if (count == 0)
			select_from = false;
		else
			connection.addCgiRbuf(buff, count);
	}

	select_to = !connection.get_m_wbuf().empty();
	waitpid(connection.get_m_child_pid(), &stat, WNOHANG);
	if (WIFEXITED(stat) && !select_from && !select_to)
	{
		ft::log(ServerManager::access_fd, -1, "[MAIN][3-1]\n");
		if (from_child_fd != -1)
		{
			close(from_child_fd);
			m_manager->fdClear(from_child_fd, ServerManager::READ_SET);
		}
		std::string body = connection.get_m_cgi_rbuf();
		connection.clearCgiRbuf();
		connection.clearWbuf();
		if (connection.get_m_request().get_m_uri_type() == Request::CGI_PROGRAM)
			createResponse(connection, CGI_SUCCESS_CODE, headers_t(), body);
		else
			createResponse(connection, 200, headers_t(), body);
		connection.set_m_status(Connection::TO_SEND);
		m_manager->resetMaxFd();
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/* -------------------------- CONNECTION MANAGEMENT ------------------------- */
/* ************************************************************************** */

bool
Server::hasException(int client_fd) {
	return (m_manager->fdIsset(client_fd, ServerManager::ERROR_COPY_SET));
}

void
Server::closeConnection(int client_fd)
{
	writeCloseConnectionLog(client_fd);
	// Connection& connection = m_connections[client_fd];
	if (close(client_fd) == -1)
		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
		"[Failed][Function] close function failed in closeConnection method");
	m_manager->fdClear(client_fd, ServerManager::READ_SET);
	m_connections.erase(client_fd);
	if (m_manager->get_m_max_fd() == client_fd)
		m_manager->resetMaxFd();
}

int
Server::getUnuseConnectionFd()
{
	std::map<int, Connection>::iterator it = m_connections.begin();
	for (; it != m_connections.end(); ++it) {
		if (it->second.get_m_status() == Connection::ON_WAIT)
			return (it->first);
	}
	return (-1);
}

bool
Server::hasNewConnection()
{
	return (m_manager->fdIsset(m_fd, ServerManager::READ_COPY_SET));
}

bool
Server::acceptNewConnection()
{
	struct sockaddr_in	client_addr;
	socklen_t			client_addr_size = sizeof(struct sockaddr);
	int 				client_fd;
	std::string			client_ip;
	int					client_port;

	ft::bzero(&client_addr, client_addr_size);

	if ((client_fd = accept(m_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1) {
		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
		"[Failed][Function]failed to cerate client_fd by accept function");
		return (false);
	}
	if (m_manager->get_m_max_fd() < client_fd)
		m_manager->set_m_max_fd(client_fd);
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	client_ip = inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	m_manager->fdSet(client_fd, ServerManager::READ_SET);
	// writeCreateNewConnectionLog(client_fd, client_ip, client_port);
	return (true);
}

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

bool Server::hasRequest(Connection& connection)
{
	Connection::Status status = connection.get_m_status();
	// Request::Phase phase = connection.get_m_request().get_m_phase();
	int fd = connection.get_m_client_fd();

	if (status != Connection::ON_WAIT && status != Connection::ON_RECV)
		return (false);
	if (!m_manager->fdIsset(fd, ServerManager::READ_COPY_SET))
		return (false);
	return (true);
}

bool
Server::parseStartLine(Connection& connection, Request& request)
{
	size_t new_line;

	if ((new_line = connection.get_m_rbuf().find("\r\n")) != std::string::npos)
	{
		std::string start_line = connection.get_m_rbuf().substr(0, new_line);
		connection.decreaseRbuf(start_line.size() + 2);
		request.addOrigin(start_line + "\r\n");
		request = Request(&connection, this, start_line);
		return (true);
	} else if (connection.get_m_rbuf().size() > REQUEST_URI_LIMIT_SIZE_MAX)
		throw (40006);
	return (false);
}

bool
Server::parseHeader(Connection& connection, Request& request)
{
	std::string& rbuf = const_cast<std::string&>(connection.get_m_rbuf());
	std::string line;

	while (ft::getline(rbuf, line, REQUEST_HEADER_LIMIT_SIZE_MAX) >= 0)
	{
		if (line == "")
		{
			if (!ft::hasKey(request.get_m_headers(), "Host"))
				throw (40011);
			return (true);
		}
		if (!request.isValidHeader(line))
			throw (40010);
		request.addHeader(line);
	}
	return (false);
}

bool
Server::parseBody(Connection& connection, Request& request)
{
	if (!isMethodHasBody(request.get_m_method()))
		return (true);
	if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
		return (true);
	std::string& buf = const_cast<std::string&>(connection.get_m_rbuf());

	if (request.get_m_transfer_type() == Request::GENERAL)
	{
		if (!ft::hasKey(request.get_m_headers(), "Content-Length"))
			throw (41101);
		connection.set_m_token_size(std::stoi(request.get_m_headers().find("Content-Length")->second));
		if (connection.get_m_readed_size() + static_cast<int>(buf.size()) <= connection.get_m_token_size())
		{
			request.addContent(buf);
			request.addOrigin(buf);
			connection.set_m_readed_size(connection.get_m_readed_size() + buf.size());
			connection.decreaseRbuf(buf.size());
		}
		else
		{
			std::string part = buf.substr(0, connection.get_m_token_size() - connection.get_m_readed_size());
			request.addContent(part);
			request.addOrigin(part);
			connection.decreaseRbuf(part.size());
			connection.set_m_readed_size(connection.get_m_token_size());
		}
		return (connection.get_m_readed_size() == connection.get_m_token_size());
	}
	while (request.get_m_transfer_type() == Request::CHUNKED)
	{
		std::string len;
		int content_length = getChunkedSize(buf, len);
		if (content_length == -1)
			return (false);
		if (content_length == 0)
		{
			if (buf.find("\r\n") == std::string::npos)
			{
				buf.insert(0, len + "\r\n");
				return (false);
			}
			if (buf.size() >= 2 && buf[0] == '\r' && buf[1] == '\n')
			{
				connection.decreaseRbuf(2);
				return (true);
			}
			throw (40018);
		}
		if (static_cast<int>(buf.size()) < content_length + 2)
		{
			buf.insert(0, len + "\r\n");
			return (false);
		}
		if (buf.substr(content_length, 2) != "\r\n")
			throw (40021);
		request.addContent(buf.substr(0, content_length));
		request.addOrigin(len + "\r\n");
		request.addOrigin(buf.substr(0, content_length + 2));
		connection.decreaseRbuf(content_length + 2);
	}
	return (false);
}

namespace {
	int recvWithoutBody(const Connection& connection, char*buf, int buf_size)
	{
		int count;
		int i = 0;
		if ((count = recv(connection.get_m_client_fd(), buf, buf_size, MSG_PEEK)) > 0)
		{
			while (i < count)
			{
				if (buf[i] == '\r' && i + 3 < count && buf[i + 1] == '\n' && buf[i + 2] == '\r' && buf[i + 3] == '\n')
					break ;
				++i;
			}
			if (i == count)
				return (0);
			else
			{
				recv(connection.get_m_client_fd(), buf, i + 4, 0);
				ft::log(ServerManager::access_fd, -1, connection.get_m_request().get_m_method_to_string()
				+ "read(1) : " + std::to_string(i) + " : " + std::to_string(i + 4)
				+ std::string(buf, i + 4) + "\n");
				return (i + 4);
			}
		}
		else
			return (-1);
	}
	int recvBody(const Connection& connection, char*buf, int buf_size)
	{
		int count;
		const Request& request = connection.get_m_request();

		if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
			return (0);
		if (!isMethodHasBody(request.get_m_method()))
			return (0);
	
		if ((count = recv(connection.get_m_client_fd(), buf, buf_size, MSG_PEEK)) > 0)
		{
			recv(connection.get_m_client_fd(), buf, count, 0);
			return (count);
		}
		else
			return (-1);
	}
}

void
Server::recvRequest(Connection& connection, const Request& const_request)
{
	char buf[BUFFER_SIZE];
	int count = BUFFER_SIZE - connection.get_m_rbuf().size();
	Request& request = const_cast<Request&>(const_request);
	Request::Phase phase = request.get_m_phase();
	if (connection.get_m_status() == Connection::ON_WAIT)
	{
		gettimeofday(&g_start, NULL);
		ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + ft::getSpeed(g_start) + "[REQUEST HEADER READ][START]\n");
	}
	connection.set_m_status(Connection::ON_RECV);
	if (phase == Request::READY && hasRequest(connection) && (count = recvWithoutBody(connection, buf, sizeof(buf))) > 0)
		connection.addRbuf(buf, count);
	if (phase == Request::READY && parseStartLine(connection, request))
		phase = Request::ON_HEADER;
	if (phase == Request::ON_HEADER && parseHeader(connection, request))
	{
		request.set_m_phase(phase = Request::ON_BODY);
		if (isMethodHasBody(request.get_m_method()))
			return ;
	}
	if (phase == Request::ON_BODY && (count = recvBody(connection, buf, sizeof(buf))) > 0)
		connection.addRbuf(buf, count);
	if (phase == Request::ON_BODY && parseBody(connection, request))
	{
		phase = Request::COMPLETE;
		ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[REQUEST HEADER READ][END]\n");
	}
	if (phase == Request::COMPLETE)
		connection.set_m_last_request_at();
	request.set_m_phase(phase);
}

bool
Server::runRecvAndSolve(Connection& connection)
{
	try {
		recvRequest(connection, connection.get_m_request());
	} catch (int status_code) {
		createResponse(connection, status_code);
		return (true);
	} catch (std::exception& e) {
		ft::log(ServerManager::access_fd, ServerManager::error_fd, std::string("[Failed][Request] Failed to create request because ") + e.what());
		createResponse(connection, 50001);
		return (true);
	}
	// if (m_responses.size() > STACKED_RESPONSE_COUNT) {
	// 	createResponse(connection, 50301);
	// 	return (true);
	// }
	const Request& request = connection.get_m_request();
	if (request.get_m_phase() == Request::COMPLETE)
	{
		// writeCreateNewRequestLog(request);
		connection.set_m_status(Connection::ON_EXECUTE);
		solveRequest(connection, connection.get_m_request());
		return (true);
	}
	return (false);
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

std::string
Server::getExtension(std::string path)
{
	std::string ret;

	if (path.find(".") != std::string::npos)
	{
		size_t idx = path.rfind(".");
		if (idx != path.size() - 1)
			ret = path.substr(idx + 1);
	}
	return (ret);
}

std::string
Server::getMimeTypeHeader(std::string path)
{
	std::string extension = getExtension(path);
	std::string ret;
	if (!extension.empty() && ft::hasKey(mime_types, extension))
		ret = "Content-type:" + mime_types[extension];
	else
		ret = "Content-type:test-for-evaluation";
	return (ret);
}

time_t
Server::getLastModified(std::string path)
{
	struct stat buf;
	ft::bzero(&buf, sizeof(struct stat));
	stat(path.c_str(), &buf);
	return (buf.st_mtimespec.tv_sec);
}

std::string
Server::getLastModifiedHeader(std::string path)
{
	time_t modified = getLastModified(path);
	struct tm t;
	char buff[1024];

	ft::convertTimespecToTm(modified, &t);
	strftime(buff, sizeof(buff), "%a, %d %b %Y %X GMT", &t);
	return ("Last-Modified:" + std::string(buff));
}

void
Server::run()
{
	std::map<int, Connection>::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		std::map<int, Connection>::iterator it2 = it++;
		int fd = it2->first;

		if (m_fd == fd)
			continue ;
		if (hasException(fd)) {
			closeConnection(fd);
			continue ;
		}
		if (hasSendWork(it2->second) && !runSend(it2->second))
			continue ;
		if (hasExecuteWork(it2->second))
		{
			runExecute(it2->second);
			continue ;
		}
		if (hasRequest(it2->second) || !it2->second.get_m_rbuf().empty())
			runRecvAndSolve(it2->second);
	}
	if (hasNewConnection())
	{
		writeDetectNewConnectionLog();
		if (m_connections.size() >= (1024 / m_manager->get_m_servers().size()))
		{
			int fd = getUnuseConnectionFd();
			if (fd == -1)
				return ;
			closeConnection(fd);
		}
		if (!acceptNewConnection())
			reportCreateNewConnectionLog();
	}
}

namespace {
	bool isAuthorizationRequired(Location* location) { return (!location->get_m_auth_basic_realm().empty()); }
	bool hasCredential(const Request& request) { return (ft::hasKey(request.get_m_headers(), "Authorization")); }
	bool isValidCredentialForm(std::vector<std::string> credential) {
		return (credential.size() == 2 && credential[0] != "basic");
	}
	bool isValidCredentialContent(Location* location, std::vector<std::string>& credential)
	{
		std::string key, value;
		basic_decode(credential[1], key, value);
		return (key.empty() || value.empty() || !ft::hasKey(location->get_m_auth_basic_file(), key)
		|| location->get_m_auth_basic_file().find(key)->second != value);
	}
	void makeResponse401(Server* server, const Request& request, Connection& connection) {
		std::string header = "WWW-Authenticate:Basic realm=\"";
		header.append(request.get_m_location()->get_m_auth_basic_realm());
		header.append("\", charset=\"UTF-8\"");
		return (server->createResponse(connection, 40101, headers_t(1, header)));
	}
}

void
Server::solveRequest(Connection& connection, const Request& request)
{
	Location* location = request.get_m_location();
	Request::Method method = request.get_m_method();
	std::string methodString = request.get_m_method_to_string();

	if (!ft::hasKey(location->get_m_allow_method(), methodString)) {
		headers_t headers(1, "Allow:" + ft::containerToString(location->get_m_allow_method(), ", "));
		return (createResponse(connection, 40501, headers));
	}
	if (isAuthorizationRequired(location)) {
		if (!hasCredential(request)) {
			return (makeResponse401(this, request, connection));
		} else {
			std::vector<std::string> credential = ft::split(request.get_m_headers().find("Authorization")->second, ' ');
			if (!isValidCredentialForm(credential))
				return (createResponse(connection, 40022));
			else if (!isValidCredentialContent(location, credential))
				return (createResponse(connection, 40301));
		}
	}
	if (method == Request::TRACE)
		executeTrace(connection, request);
	else if (request.get_m_uri_type() == Request::DIRECTORY)
		return (executeAutoindex(connection, request));
	else if (request.get_m_uri_type() == Request::CGI_PROGRAM)
		return (executeCGI(connection, request));
	else if (method == Request::GET)
		executeGet(connection, request);
	else if (method == Request::HEAD)
		executeHead(connection, request);
	else if (method == Request::POST)
		executePost(connection, request);
	else if (method == Request::PUT)
		executePut(connection, request);
	else if (method == Request::DELETE)
		executeDelete(connection, request);
	else if (method == Request::OPTIONS)
		executeOptions(connection, request);
	else
		throw (400);
}

/*
** function: executeAutoindex
** d_type(4) : DIRECTORY
** d_type(8) : REGULAR_FILE
*/

namespace {
	bool makeAutoindexContent(HtmlWriter& html, std::string cwd)
	{
		DIR *dir = NULL;
		struct dirent *de = NULL;
		char buff[1024];
		int idx = 7;

		if ((dir = opendir(cwd.c_str())) == NULL)
			return (false);
		while ((de = readdir(dir)) != NULL) {
			std::string name = de->d_name;
            if (name == "." || (name != ".." && name[0] == '.'))
                continue ;
			if (de->d_type == 4 || de->d_type == 8) // 4 dir, 8 file
			{
				std::string content;
				content.append(html.makeLink(name));
				content.append(std::string(51 - std::string(name).size(), ' '));

				struct stat buf;
            	struct tm t;
				ft::bzero(&buf, sizeof(struct stat));
				stat((std::string(cwd) + "/" + name).c_str(), &buf);
				ft::convertTimespecToTm(buf.st_mtimespec.tv_sec, &t);
				strftime(buff, sizeof(buff), "%d-%h-%G %H:%M", &t);

				content.append(std::string(buff));
				content.append(std::string(20 - std::to_string(de->d_reclen).size(), ' '));
				content.append(std::to_string(de->d_reclen));
				html.add_line(idx++, content);
			}
		}
		closedir(dir);
		return (true);
	}
	void makeAutoindexForm(HtmlWriter& html, const Request& request)
	{
		std::string title = "Index of " + request.get_m_uri();
		html.add_title(title);
		html.add_bgcolor("white");
		html.add_tag("\"white\">\n", "h1", title, false);
		html.add_tag("/h1>\n", "hr", "", true);
		html.add_tag("hr>\n", "pre", "", true);
	}
	int getValidIndexFd(const Request& request)
	{
		std::set<std::string> index = request.get_m_location()->get_m_index();
		std::set<std::string>::iterator it = index.begin();
		struct stat buf;
		int fd = -1;
		std::string path, body;
		for (; it != index.end(); ++it)
		{
			path = request.get_m_script_translated();
			if (path[path.size() - 1] != '/')
				path.push_back('/');
			path.append(*it);
			stat(path.c_str(), &buf);
			if (S_ISREG(buf.st_mode) && (fd = open(path.c_str(), O_RDONLY)) > -1)
				break ;
		}
		return (fd);
	}
}

void
Server::executeAutoindex(Connection& connection, const Request& request)
{
	char cwd[BUFFER_SIZE];
	getcwd(cwd, sizeof(cwd));

	if (request.get_m_location()->get_m_autoindex())
	{
		HtmlWriter html;
		makeAutoindexForm(html, request);
		if (!makeAutoindexContent(html, request.get_m_location()->get_m_root_path()))
			return (createResponse(connection, 50002));
		return (createResponse(connection, 200, headers_t(), html.get_m_body()));
	}
	else
	{
		int fd = getValidIndexFd(request);
		if (fd == -1)
			return (createResponse(connection, 40403));
		return (createResponse(connection, 200, headers_t(), ft::getStringFromFd(fd)));
	}
}

void
Server::executeGet(Connection& connection, const Request& request)
{
	std::string path = request.get_m_path_translated();
	std::string body;

	try {
		body = ft::getStringFromFile(path, m_limit_client_body_size);
	} catch (std::overflow_error& e) {
		return (createResponse(connection, 41304));
	}
	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(connection, 41501));
	headers.push_back(getLastModifiedHeader(path));
	return (createResponse(connection, 200, headers, body));
}

void
Server::executeHead(Connection& connection, const Request& request)
{
	std::string path = request.get_m_path_translated();
	std::string body;

	try {
		body = ft::getStringFromFile(path, m_limit_client_body_size);
	} catch (std::overflow_error& e) {
		return (createResponse(connection, 41305));
	}

	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(connection, 41502));
	headers.push_back(getLastModifiedHeader(path));
	headers.push_back("content-length:" + std::to_string(body.size()));
	return (createResponse(connection, 200, headers));
}

void
Server::executeTrace(Connection& connection, const Request& request)
{
	createResponse(connection, 200, headers_t(1, "Content-Type:text/plain"), request.get_m_origin());
}

void
Server::executePost(Connection& connection, const Request& request)
{
	if (request.get_m_headers().find("Content-Length")->second == "0")
		return (executeGet(connection, request));
	else
		return (createResponse(connection, 40023));
}

void
Server::executeOptions(Connection& connection, const Request& request) {
	if (request.get_m_uri() == "*")
		return (createResponse(connection, 200, headers_t(1, std::string("Allow:") + SERVER_ALLOW_METHODS)));
	headers_t headers(1, "Allow:" + ft::containerToString(request.get_m_location()->get_m_allow_method(), ", "));
	return (createResponse(connection, 200, headers));
}

void
Server::executePut(Connection& connection, const Request& request)
{
	int fd;
	struct stat buf;

	stat(request.get_m_script_translated().c_str(), &buf);
	headers_t headers(1, getMimeTypeHeader(request.get_m_path_translated()));
	// if (headers[0].empty())
	// 	return (createResponse(request.get_m_connection(), 41503));
	if ((fd = open(request.get_m_script_translated().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		return (createResponse(connection, 50003));
	if (write(fd, request.get_m_content().c_str(), request.get_m_content().size()) == -1)
		return (createResponse(connection, 50004));
	close(fd);
	if (S_ISREG(buf.st_mode))
		return (createResponse(connection, 204));
	headers.push_back("Location:" + m_host + "/" + request.get_m_uri());
	return (createResponse(connection, 201, headers, request.get_m_content()));
}

void
Server::executeDelete(Connection& connection, const Request& request) {
	if (unlink(request.get_m_path_translated().c_str()) == -1)
		createResponse(connection, 204);
	else
		return (createResponse(connection, 204));
}

namespace {
	int	setEnv(char **env, int idx, std::string key, std::string val)
	{
		char	*item;

		if (key.empty())
			return (0);
		item = ft::strsjoin(key, std::string("="), val);
		env[idx] = item;
		return (1);
	}
	char **dupBaseEnvWithExtraSpace(Config *config, const Request& request)
	{
		char **base_env = config->get_m_base_env();
		char **cgi_env = NULL;
		int idx = 0;
		int base_len = ft::lenDoubleStr(base_env);
		int custom_len = request.get_m_special_header_count();

		if ((cgi_env = reinterpret_cast<char **>(malloc(sizeof(char *) * (base_len + custom_len + CGI_META_VARIABLE_COUNT + 1)))) == 0)
			return (NULL);
		while (base_env[idx] != NULL) {
			cgi_env[idx] = ft::strdup(base_env[idx]);
			++idx;
		}
		while (idx < base_len + custom_len + CGI_META_VARIABLE_COUNT + 1)
			cgi_env[idx++] = NULL;
		return (cgi_env);
	}
	std::string getCGIEnvValue(const Request& request, std::string token, Server *server = NULL, Config config = Config())
	{
		if (token == "CONTENT_LENGTH") {
			if (ft::hasKey(request.get_m_headers(), "Content-Length"))
				return (request.get_m_headers().find("Content-Length")->second);
			// if (request.get_m_method() == Request::POST)
				// return (std::to_string(request.get_m_content().size()));
			return (std::string("-1"));
		}
		else if (token == "CONTENT_TYPE") {
			if (ft::hasKey(request.get_m_headers(), "Content-Type"))
				return (request.get_m_headers().find("Content-Type")->second);
			return (std::string());
		}
		else if (token == "AUTH_TYPE")
			return (config.get_m_cgi_version());
		else if (token == "PATH_INFO")
			return (request.get_m_path_info());
		else if (token == "PATH_TRANSLATED")
			return (request.get_m_path_translated());
		else if (token == "QUERY_STRING")
			return (request.get_m_query());
		else if (token == "REMOTE_ADDR")
			return (request.get_m_connection()->get_m_client_ip());
		else if (token == "REQUEST_METHOD")
			return (request.get_m_method_to_string());
		else if (token == "REQUEST_URI")
			return (request.get_m_uri());
		else if (token == "SCRIPT_NAME")
			return (request.get_m_script_translated());
		else if (token == "SERVER_NAME")
			return (server->get_m_server_name());
		else if (token == "SERVER_PORT")
			return (std::to_string(server->get_m_port()));
		else if (token == "SERVER_PROTOCOL")
			return ("HTTP/" + config.get_m_http_version());
		else if (token == "SERVER_SOFTWARE")
			return (config.get_m_software_name() + "/" + config.get_m_software_version());
		else if (token == "GATEWAY_INTERFACE")
			return (config.get_m_cgi_version());
		return (NULL);
	}
}

char**
Server::createCGIEnv(const Request& request)
{
	char **env = dupBaseEnvWithExtraSpace(m_config, request);
	int idx = ft::lenDoubleStr(m_config->get_m_base_env());
	setEnv(env, idx++, "AUTH_TYPE", "");
	setEnv(env, idx++, "CONTENT_LENGTH", getCGIEnvValue(request, "CONTENT_LENGTH"));
	setEnv(env, idx++, "CONTENT_TYPE", getCGIEnvValue(request, "CONTENT_TYPE"));
	setEnv(env, idx++, "GATEWAY_INTERFACE", getCGIEnvValue(request, "GATEWAY_INTERFACE", NULL, m_manager->get_m_config()));
	setEnv(env, idx++, "PATH_INFO", getCGIEnvValue(request, "PATH_INFO"));
	setEnv(env, idx++, "PATH_TRANSLATED", getCGIEnvValue(request, "PATH_TRANSLATED"));
	setEnv(env, idx++, "QUERY_STRING", getCGIEnvValue(request, "QUERY_STRING"));
	setEnv(env, idx++, "REMOTE_ADDR", getCGIEnvValue(request, "REMOTE_ADDR"));
	setEnv(env, idx++, "REQUEST_METHOD", getCGIEnvValue(request, "REQUEST_METHOD"));
	setEnv(env, idx++, "REQUEST_URI", getCGIEnvValue(request, "REQUEST_URI"));
	setEnv(env, idx++, "SCRIPT_NAME", getCGIEnvValue(request, "SCRIPT_NAME"));
	setEnv(env, idx++, "SERVER_NAME", getCGIEnvValue(request, "SERVER_NAME", this));
	setEnv(env, idx++, "SERVER_PORT", getCGIEnvValue(request, "SERVER_PORT", this));
	setEnv(env, idx++, "SERVER_PROTOCOL", getCGIEnvValue(request, "SERVER_PROTOCOL", NULL, m_manager->get_m_config()));
	setEnv(env, idx++, "SERVER_SOFTWARE", getCGIEnvValue(request, "SERVER_SOFTWARE", NULL, m_manager->get_m_config()));

	std::map<std::string, std::string>::const_iterator it = request.get_m_headers().begin();
	for (; it != request.get_m_headers().end(); ++it)
	{
		if (it->first[0] == 'X')
		{
			std::string new_header = "HTTP_";
			for (std::string::const_iterator it2 = it->first.begin(); it2 != it->first.end(); ++it2)
				new_header.push_back(std::toupper(*it2));
				// new_header.push_back((*it2 == '-') ? '_' : std::toupper(*it2));
			setEnv(env, idx++, new_header, it->second);
		}
	}
	return (env);
}

void Server::revertStdInOut()
{
	if (close(0) == -1 || close(1) == -1)
		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
		"[Failed][function] close function failed in revertStdInOut.");
	if (dup2(ServerManager::stdin_fd, 0) == -1 || dup2(ServerManager::stdin_fd, 1) == -1)
		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
		"[Failed][function] dup2 function failed in revertStdInOut method.");
}

void
Server::executeCGI(Connection& connection, const Request& request)
{
	pid_t	pid;
	int parent_write_fd[2];
	int child_write_fd[2];
	char **env;
	Request::Method method = request.get_m_method();
	std::string body;

	if ((env = createCGIEnv(request)) == NULL)
		return (createResponse(connection, 50005));
	pipe(parent_write_fd);
	pipe(child_write_fd);
	pid = fork();
	if (pid == 0) {
		close(parent_write_fd[1]);
		close(child_write_fd[0]);
		dup2(parent_write_fd[0], 0);
		dup2(child_write_fd[1], 1);
		/* child process */
		char *arg[2] = { const_cast<char *>(request.get_m_script_translated().c_str()), NULL };
		std::string script_name = getCGIEnvValue(request, "SCRIPT_NAME");
		std::string ext = script_name.substr(script_name.rfind(".") + 1);
		if (ext == "php" && execve("./php-cgi", arg, env) == -1)
			exit(EXIT_FAILURE);
		else if (execve(arg[0], arg, env) == -1)
			exit(EXIT_FAILURE);
		ft::log(-1, ServerManager::error_fd, "if this is found, error");
		exit(EXIT_FAILURE);
	} else if (pid < 0) {
		close(parent_write_fd[0]);
		close(parent_write_fd[1]);
		close(child_write_fd[0]);
		close(child_write_fd[1]);
		return (createResponse(connection, 50006, headers_t()));
	}

	close(parent_write_fd[0]);
	close(child_write_fd[1]);
	if (fcntl(parent_write_fd[1], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("write fnctl error");
	if (fcntl(child_write_fd[0], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("read fnctl error");
	connection.set_m_status(Connection::ON_EXECUTE);
	if (method == Request::POST)
	{
		connection.set_m_to_child_fd(parent_write_fd[1]);
		if (request.get_m_transfer_type() == Request::GENERAL)
			connection.set_m_wbuf_for_execute();
		m_manager->fdSet(connection.get_m_to_child_fd(), ServerManager::WRITE_SET);
	}
	else
		close(parent_write_fd[1]);
	connection.set_m_from_child_fd(child_write_fd[0]);
	m_manager->fdSet(connection.get_m_from_child_fd(), ServerManager::READ_SET);
	m_manager->resetMaxFd(std::max(parent_write_fd[1], child_write_fd[0]));
}

namespace {
	std::string getDateHeader()
	{
		char buff[1024];
		struct tm t;
		timeval now;

		gettimeofday(&now, NULL);
		ft::convertTimespecToTm(now.tv_sec, &t);
		strftime(buff, sizeof(buff), "%a, %d %b %Y %X GMT", &t);
		return ("Last-Modified:" + std::string(buff));
	}
	std::string getServerHeader(Server* server) {
		return ("Server:" + server->get_m_server_name());
	}
}

void Server::createCGIResponse(int& status, headers_t& headers, std::string& body)
{
	status = 200;
	headers_t headers_in_body = ft::split(ft::rtrim(body.substr(0, body.find("\r\n\r\n")), "\r\n"), '\n');
	std::string key, value;
	for (headers_t::iterator it = headers_in_body.begin(); it != headers_in_body.end(); it++)
	{
		key = ft::trim(it->substr(0, it->find(":")), " \t");
		value = ft::trim(it->substr(it->find(":") + 1), " \r\n\t");
		if (key == "Status" || key == "status")
			status = std::stoi(value);
		else if (!key.empty() && !value.empty())
			headers.push_back(key + ":" + value);
	}
	// headers.push_back("Connection:close");
	if (body.find("\r\n\r\n") != std::string::npos)
		body = body.substr(body.find("\r\n\r\n") + 4);
	else if (body.find("\n\n") != std::string::npos)
		body = body.substr(body.find("\n\n") + 2);
	else
		body = "";
	if (body.size() == 0)
		return ;

	headers.push_back("Transfer-Encoding:chunked");
}

void
Server::createResponse(Connection& connection, int status, headers_t headers, std::string body)
{
	ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[FUNCTION][START]createResponse\n");
	if (status >= 40000) {
		reportCreateNewRequestLog(connection, status);
		status /= 100;
	}

	headers.push_back(getDateHeader());
	headers.push_back(getServerHeader(this));

	ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[FUNCTION][START]createCGIResponse\n");
	if (status == CGI_SUCCESS_CODE)
		createCGIResponse(status, headers, body);
	ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[FUNCTION][END]createCGIResponse\n");
	if (status >= 400 && status <= 599) {
		body = m_default_error_page;
		body.replace(body.find("#ERROR_CODE"), 11, std::to_string(status));
		body.replace(body.find("#ERROR_CODE"), 11, std::to_string(status));
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
	}
	if (!ft::hasKey(ft::stringVectorToMap(headers), "Transfer-Encoding"))
		headers.push_back("Content-Length:" + std::to_string(body.size()));
	if (!body.empty())
		headers.push_back("Content-Language:ko-KR");
	if (status / 100 != 2)
		headers.push_back("Connection:close");
	if (status / 100 == 3)
		headers.push_back("Location:/");
	if (status == 504)
		headers.push_back("Retry-After:3600");
	if (connection.get_m_request().get_m_method() == Request::HEAD)
		body = "";
	ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[FUNCTION][START]Response Generator\n");
	Response& response = const_cast<Response&>(connection.get_m_response());
	response = Response(&connection, status, body);
	ft::log(ServerManager::access_fd, -1, ft::getTimestamp() + "[FUNCTION][END]Response Generator\n");
	headers_t::iterator it = headers.begin();
	for (; it != headers.end(); ++it) {
		std::string key = ft::rtrim((*it).substr(0, (*it).find(":")), " ");
		std::string value = ft::ltrim((*it).substr((*it).find(":") + 1), " ");
		response.addHeader(key, value);
	}
	writeCreateNewResponseLog(response);
	const_cast<Request&>(connection.get_m_request()).set_m_phase(Request::COMPLETE);
	connection.set_m_status(Connection::TO_SEND);
	m_manager->fdSet(response.get_m_connection()->get_m_client_fd(), ServerManager::WRITE_SET);
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Server::writeDetectNewConnectionLog()
{
	std::string text = "[Detected][Connection][Server:" + m_server_name + "][Host:" + m_host \
	+ "] New connection detected.\n";
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
Server::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{
	std::string text = "[Created][Connection][Server:" + m_server_name + "][CFD:" \
	+ std::to_string(client_fd) + "][IP:" + client_ip + "][Port:" + std::to_string(client_port) + "]\n";
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
Server::reportCreateNewConnectionLog()
{
	std::string text = "[Failed][Connection][Server:" + m_server_name + "][Host:" + m_host \
	+ "] Failed to create new connection.\n";
	ft::log(ServerManager::access_fd, ServerManager::error_fd, text);
	return ;
}

void
Server::writeDetectNewRequestLog(const Connection& connection)
{
	std::string text = "[Detected][Request][Server:" + m_server_name + "][CIP:"
	+ connection.get_m_client_ip() + "][CFD:" + std::to_string(connection.get_m_client_fd()) + "]"
	+ " New request detected.\n";
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
Server::writeCreateNewRequestLog(const Request& request)
{
	std::string text = "[Created][Request][Server:" + m_server_name + "][Method:" \
	+ request.get_m_method_to_string() + "][URI:" + request.get_m_uri() + "][Path:" + request.get_m_script_translated() + "]";
	if (request.get_m_method() == Request::GET)
		text.append("[Query:" + request.get_m_query() + "]");
	text.append(" New request created.\n");
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
Server::reportCreateNewRequestLog(const Connection& connection, int status)
{
	std::string text = "[Failed][Request][Server:" + m_server_name + "][CIP:"
	+ connection.get_m_client_ip() + "][CFD:" + std::to_string(connection.get_m_client_fd()) + "]["
	+ std::to_string(status) + "][" + Response::status[status] + "] Failed to create new Request.\n";
	ft::log(ServerManager::access_fd, ServerManager::error_fd, text);
	return ;
}

void
Server::writeCreateNewResponseLog(const Response& response)
{
	std::string text = ft::getTimestamp() + "[Created][Response][Server:" + m_server_name + "][" \
	+ std::to_string(response.get_m_status_code()) + "][" + response.get_m_status_description() + "][CFD:" \
	+ std::to_string(response.get_m_connection()->get_m_client_fd()) + "][headers:" \
	+ std::to_string(response.get_m_headers().size()) + "][body:" + std::to_string(response.get_m_content().size()) + "]";
	text.append(" New response created.\n");
	ft::log(ServerManager::access_fd, -1, text);
	// ft::log(ServerManager::access_fd, -1, "[Detected][Response][Message][↓]" + response.getString().substr(0, 500) + "\n\n");
	return ;
}

void
Server::writeSendResponseLog(const Response& response)
{
	std::string text = ft::getTimestamp() + "[Sended][Response][Server:" + m_server_name + "][" \
	+ std::to_string(response.get_m_status_code()) + "][" + response.get_m_status_description() + "][CFD:" \
	+ std::to_string(response.get_m_connection()->get_m_client_fd()) + "][headers:" \
	+ std::to_string(response.get_m_headers().size()) + "][body:" + std::to_string(response.get_m_content().size()) + "]";
	text.append(" Response sended\n");
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
Server::writeCloseConnectionLog(int client_fd)
{
	std::string text = "[Deleted][Connection][Server:" + m_server_name + "][CFD:" \
	+ std::to_string(client_fd) + "] Connection closed.\n";
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}
