#include "Server.hpp"
#include "ServerManager.hpp"

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
	if(listen(m_fd, 64) == -1)
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
		m_locations.push_back(Location(uri, block));
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

// void Server::set_m_server_name(std::string server_name) { this->m_server_name = server_name; }
// void Server::set_m_host(std::string host) { this->m_host = host; }
// void Server::set_m_port(int port) { this->m_port = port; }
// void Server::set_m_fd(int fd) { this->m_fd = fd; }
// void Server::set_m_request_uri_limit_size(int request_uri_limit_size) { this->m_request_uri_limit_size = request_uri_limit_size; }
// void Server::set_m_request_header_limit_size(int request_header_limit_size) { this->m_request_header_limit_size = request_header_limit_size; }
// void Server::set_m_limit_client_body_size(int limit_client_body_size) { this->m_limit_client_body_size = limit_client_body_size; }
// void Server::set_m_default_error_page(std::string default_error_page) { this->m_default_error_page = default_error_page; }

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
Server::isSendable(int client_fd)
{
	if (m_manager->fdIsset(client_fd, ServerManager::ERROR_COPY_SET))
		return (false);
	else if (!m_manager->fdIsset(client_fd, ServerManager::READ_SET))
		return (false);
	else if (m_manager->fdIsset(client_fd, ServerManager::WRITE_COPY_SET))
		return (true);
	return (false);
}

void
Server::sendResponse(Response response)
{
	int fd = response.get_m_connection()->get_m_client_fd();
	std::string data = response.getString();
	int size = data.size();
	int count = 0;
	bool log = false;

	if (size >= 100000 && size <= 110000)
		log = true;
	while (size > 0)
	{
		if (size > CHUNKED_TRANSFER_BUFFER_SIZE)
			count = CHUNKED_TRANSFER_BUFFER_SIZE;
		else
			count = size;
		count = send(fd, data.c_str(), count, 0);
		if (log == true)
			write(ServerManager::access_fd, data.c_str(), count);
		ft::log(ServerManager::access_fd, -1, std::to_string(count) + " is sended.\n");
		if (count > 0) {
			data.erase(0, count);
			size -= count;
		}
		usleep(2000);
	}
	m_manager->fdClear(fd, ServerManager::WRITE_SET);
	writeSendResponseLog(response);
}

bool
Server::runSend()
{
	Response response(m_responses.front());
	int fd = response.get_m_connection()->get_m_client_fd();
	if (isSendable(fd))
	{
		sendResponse(response);
		if (response.get_m_connection_type() == Response::CLOSE)
			closeConnection(fd);
		m_responses.pop();
	}
	else if (!m_manager->fdIsset(fd, ServerManager::ERROR_COPY_SET) \
	&& m_manager->fdIsset(fd, ServerManager::READ_SET)) {
		m_manager->fdSet(fd, ServerManager::WRITE_SET);
		return (false);
	}
	else
		m_responses.pop();
	return (true);
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
	
	// if (lseek(client_fd, 0, SEEK_END) == -1)
	// 	ft::log(ServerManager::access_fd, ServerManager::error_fd, \
	// 	"[Failed][Function] lseek function failed in closeConnection method");

	char buff[GENERAL_TRANSFER_BUFFER_SIZE];
	while (read(client_fd, buff, GENERAL_TRANSFER_BUFFER_SIZE) > 0)
		;

	if (close(client_fd) == -1)
		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
		"[Failed][Function] close function failed in closeConnection method");
	m_manager->fdClear(client_fd, ServerManager::READ_SET);
	m_manager->fdClear(client_fd, ServerManager::WRITE_SET);
	m_connections.erase(client_fd);
	if (m_manager->get_m_max_fd() == client_fd) {
		m_manager->set_m_max_fd(client_fd - 1);
		for (int i = client_fd - 1; i > 0; i--) {
			if (m_manager->fdIsset(i, ServerManager::READ_SET)) {
				m_manager->set_m_max_fd(i);
				break ;
			}
		}
	}
}

int
Server::getUnuseConnectionFd()
{
	std::map<int, Connection>::iterator it = m_connections.begin();
	for (; it != m_connections.end(); ++it) {
		if (!m_manager->fdIsset(it->first, ServerManager::WRITE_SET))
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
	writeCreateNewConnectionLog(client_fd, client_ip, client_port);
	return (true);
}

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

bool Server::hasRequest(int client_fd, Request::Method& method) {
	if (!m_manager->fdIsset(client_fd, ServerManager::READ_COPY_SET))
		return (false);
	char *buffer;
	if ((buffer = (char *)malloc(sizeof(char) * LIMIT_CLIENT_BODY_SIZE_MAX)) == 0)
		throw (50000);
	int idx = 3;
	int len = -1;
	if ((len = recv(client_fd, buffer, LIMIT_CLIENT_BODY_SIZE_MAX, MSG_PEEK)) == -1)
	{
		free(buffer);
		return (false);
	}
	if (len >= 4 && std::string(buffer, buffer + 4) == "HEAD")
		method = Request::HEAD;
	else if (len >= 4 && std::string(buffer, buffer + 4) == "POST")
		method = Request::POST;
	else if (len >= 3 && std::string(buffer, buffer + 3) == "GET")
		method = Request::GET;

	while (idx < len) {
		if (buffer[idx - 3] == '\r' && buffer[idx - 2] == '\n' && buffer[idx - 1] == '\r' && buffer[idx] == '\n')
		{
			free(buffer);
			return (true);
		}
		++idx;
	}
	free(buffer);

	// bool chunked = false;
	// std::string compare;

	// while (idx < len) {
	// 	if (buffer[idx] == 'T' && idx + 17 < len \
	// 	&& std::string(buffer + idx, buffer + idx + 17) == "Transfer-Encoding")
	// 	{
	// 		int cidx = idx + 17;
	// 		while (cidx < len && buffer[cidx] != '\r')
	// 		{
	// 			compare.push_back(buffer[cidx]);
	// 			++cidx;
	// 		}
	// 		if (compare.find("chunked") != std::string::npos) {
	// 			ft::log(ServerManager::access_fd, -1, "\nchunked detected\n");
	// 			chunked = true;
	// 		}
	// 	}
	// 	if (chunked == false && buffer[idx - 3] == '\r' \
	// 	&& buffer[idx - 2] == '\n' && buffer[idx - 1] == '\r' && buffer[idx] == '\n')
	// 	{
	// 		free(buffer);
	// 		return (true);
	// 	}
	// 	if (chunked == true && buffer[idx] == '\n' && idx + 3 < len 
	// 	&& buffer[idx + 1] == '0' && buffer[idx + 2] == '\r' && buffer[idx + 3] == '\n')
	// 	{
	// 		free(buffer);
	// 		return (true);
	// 	}
	// ++idx;
	// }
	// free(buffer);
	return (false);
}

std::string
Server::getStartLine(int client_fd)
{
	char buff[REQUEST_URI_LIMIT_SIZE_MAX];
	int ret = -1;
	
	ft::bzero(buff, sizeof(buff));
	if ((ret = ft::getline(client_fd, buff, this->get_m_request_uri_limit_size())) <= 0) {
		if (ret == 0)
			return (std::string(""));
		if (ret < -1)
			throw (40006);
		throw (40007);
	}
	return (std::string(buff, buff + ret));
}
	
int
Server::getHeaderLine(int client_fd, std::string& line)
{
	char buff[REQUEST_HEADER_LIMIT_SIZE_MAX];
	int ret = -1;

	ft::bzero(buff, sizeof(buff));
	if ((ret = ft::getline(client_fd, buff, this->get_m_request_header_limit_size())) <= 0) {
		if (ret == 0) {
			line = "";
			return (0);
		}
		if (ret < -1)
			throw (40008);
		throw (40009);
	}
	line = std::string(buff, buff + ret);
	return (ret);
}

void
Server::headerParsing(Request &request, std::string &origin_message, int client_fd)
{
	std::string line;

	while (getHeaderLine(client_fd, line) >= 0)
	{
		origin_message += (line + "\n");
		if (line == "\r" || line == "")
			break ;
		line = ft::rtrim(line, "\r");
		if (!request.isValidHeader(line))
			throw (40010);
		request.add_header(line);
	}
	if (!ft::hasKey(request.get_m_headers(), "Host"))
		throw (40011);
	return ;
}

namespace {
	bool isMethodHasBody(const Request::Method& method) {
		return (method == Request::POST || method == Request::PUT || method == Request::TRACE);
	}
	std::string readBodyMessageGeneral(Request& request, int client_fd)
	{
		char buffer[GENERAL_TRANSFER_BUFFER_SIZE] = { '\0', };
		int content_length = std::stoi(request.get_m_headers().find("Content-Length")->second);
		int read_len;
		std::string body;

		while (content_length > GENERAL_TRANSFER_BUFFER_SIZE)
		{
			if ((read_len = read(client_fd, buffer, sizeof(buffer) - 1)) < 0)
				throw (40012);
			body.append(buffer, read_len);
			content_length -= read_len;
		}
		if ((read_len = read(client_fd, buffer, content_length)) < 0)
			throw (40013);
		if (read_len != content_length)
			throw (40014);
		body.append(buffer, read_len);
		return (body);
	}
	int getChunkedSize(int client_fd, char *buffer, int buffer_size)
	{
		int content_length;
		int ret;
		if ((ret = ft::getline(client_fd, buffer, buffer_size)) == -1)
			throw (40015);
		try {
			content_length = std::stoi(std::string(buffer), 0, 16);
		} catch (std::exception& e) {
			throw (40017);
		}
		if (content_length < 0)
			throw (40016);
		if (content_length == 0)
		{
			if (buffer[0] != '0')
				throw (40017);
			else if (!(buffer[1] == '\0' || (buffer[1] == '\r' && buffer[2] == '\0')))
				throw (40017);
		}
		return (content_length);
	}
	bool isValidateLineEnd(int client_fd, char* buffer, int buffer_size)
	{
		int read_len = ft::getline(client_fd, buffer, buffer_size);
		if (read_len < 0 || read_len > 1 || (read_len == 1 && buffer[0] != '\r'))
			throw (40018);
		return (true);
	}
	std::string readBodyMessageChunked(int client_fd, std::string& origin_message)
	{
		char buffer[CHUNKED_TRANSFER_BUFFER_SIZE] = { '\0', };
		int content_length = 0;
		int total_length = 0;
		int read_len;
		std::string body;

		while (true)
		{
			content_length = getChunkedSize(client_fd, buffer, sizeof(buffer));
			origin_message.append(buffer + std::string("\n"));
			if (content_length == 0 && isValidateLineEnd(client_fd, buffer, sizeof(buffer)))
				break ;
			if (content_length > 0)
				total_length += content_length;
			// while (content_length > CHUNKED_TRNASFER_BUFFER_SIZE)
			while (content_length > CHUNKED_TRANSFER_BUFFER_SIZE)
			{
				usleep(2000);
				if ((read_len = read(client_fd, buffer, CHUNKED_TRANSFER_BUFFER_SIZE)) > 0)
				{
						// throw (40019);
					body.append(buffer, read_len);
					origin_message.append(buffer, read_len);
					content_length -= read_len;
				}
			}
			while (content_length > 0)
			{
				usleep(2000);
				if ((read_len = read(client_fd, buffer, content_length)) > 0)
				{
						// throw (40019);
					body.append(buffer, read_len);
					origin_message.append(buffer, read_len);
					content_length -= read_len;
				}
			}
			// if ((read_len = read(client_fd, buffer, content_length)) < 0)
			// 	throw (40020);
			// if (read_len != content_length)
			// 	throw (40021);
			// body.append(buffer, read_len);
			// origin_message.append(buffer, content_length);
			if (isValidateLineEnd(client_fd, buffer, sizeof(buffer)))
				origin_message.append(buffer + std::string("\n"));
			
		}
		return (body);
	}
}

std::string
Server::readBodyMessage(Request &request, std::string &origin_message, int client_fd)
{
	std::string message_body;

	if (!isMethodHasBody(request.get_m_method()))
		return (std::string(""));
	else if (request.get_m_transfer_type() == Request::CHUNKED)
		message_body = readBodyMessageChunked(client_fd, origin_message);
	else if (ft::hasKey(request.get_m_headers(), "Content-Length"))
	{
		message_body = readBodyMessageGeneral(request, client_fd);
		origin_message.append(message_body);
	}
	else
		throw (41101);
	if (request.get_m_method() == Request::POST && request.get_m_uri().find("post_body") != std::string::npos 
	&& message_body.size() > 100)
		throw (41307);
	return (message_body);
}

Request
Server::recvRequest(int client_fd, Connection* connection)
{
	std::string start_line;

	start_line = getStartLine(client_fd);
	std::string origin_message = start_line + "\n";
	start_line = ft::rtrim(start_line, "\r");
	Request request(connection, this, start_line);
	headerParsing(request, origin_message, client_fd);
	std::string message_body = readBodyMessage(request, origin_message, client_fd);
	request.add_content(message_body);
	ft::log(ServerManager::access_fd, -1, "size: " + std::to_string(request.get_m_content().size()));
	if (request.get_m_method() == Request::TRACE)
		request.add_origin(origin_message);
	connection->set_m_last_request_at();
	ft::log(ServerManager::access_fd, -1, "[Detected][Request][Message][↓]\n\n" + origin_message.substr(0, 300) + "\n");
	return (request);
}

bool
Server::runRecvAndSolve(std::map<int, Connection>::iterator it, Request::Method method)
{
	Request request;
	int fd = it->first;
	writeDetectNewRequestLog(it->second);
	try {
		request = recvRequest(fd, &it->second);
	} catch (int status_code) {
		createResponse(&(it->second), status_code, headers_t(), "", method);
		return (false);
	} catch (std::exception& e) {
		ft::log(ServerManager::access_fd, ServerManager::error_fd, std::string("[Failed][Request] Failed to create request because ") + e.what());
		createResponse(&(it->second), 50001, headers_t(), "", method);
		return (false);
	}
	if (m_responses.size() > STACKED_RESPONSE_COUNT) {
		createResponse(&(it->second), 50301, headers_t(), "", method);
		return (false);
	}
	writeCreateNewRequestLog(request);
	solveRequest(request);
	return (true);
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
	int response_count = 0;
	while (!m_responses.empty() && response_count < SEND_RESPONSE_AT_ONCE) {
		if (!runSend())
			break ;
		++response_count;
	}
	
	std::map<int, Connection>::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		std::map<int, Connection>::iterator it2 = it++;
		int fd = it2->first;
		Request::Method method = Request::DEFAULT;

		if (m_fd == fd)
			continue ;
		else if (hasException(fd)) {
			closeConnection(fd);
			continue ;
		}
		else if (hasRequest(fd, method))
			runRecvAndSolve(it2, method);
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
	usleep(10000);
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
	void makeResponse401(Server* server, const Request& request, Request::Method method) {
		std::string header = "WWW-Authenticate:Basic realm=\"";
		header.append(request.get_m_location()->get_m_auth_basic_realm());
		header.append("\", charset=\"UTF-8\"");
		return (server->createResponse(request.get_m_connection(), 40101, headers_t(1, header), "", method));
	}
}

void
Server::solveRequest(const Request& request)
{
	Location* location = request.get_m_location();
	Request::Method method = request.get_m_method();
	std::string methodString = request.get_m_method_to_string();

	if (!ft::hasKey(location->get_m_allow_method(), methodString)) {
		headers_t headers(1, "Allow:" + ft::containerToString(location->get_m_allow_method(), ", "));
		return (createResponse(request.get_m_connection(), 40501, headers, "", method));
	}
	if (isAuthorizationRequired(location)) {
		if (!hasCredential(request)) {
			return (makeResponse401(this, request, method));
		} else {
			std::vector<std::string> credential = ft::split(request.get_m_headers().find("Authorization")->second, ' ');
			if (!isValidCredentialForm(credential))
				return (createResponse(request.get_m_connection(), 40022, headers_t(), "", method));
			else if (!isValidCredentialContent(location, credential))
				return (createResponse(request.get_m_connection(), 40301, headers_t(), "", method));
		}
	}
	if (method == Request::TRACE)
		executeTrace(request);
	else if (request.get_m_uri_type() == Request::DIRECTORY)
		return (executeAutoindex(request));
	else if (request.get_m_uri_type() == Request::CGI_PROGRAM)
		return (executeCGI(request));
	else if (method == Request::GET)
		executeGet(request);
	else if (method == Request::HEAD)
		executeHead(request);
	else if (method == Request::POST)
		executePost(request);
	else if (method == Request::PUT)
		executePut(request);
	else if (method == Request::DELETE)
		executeDelete(request);
	else if (method == Request::OPTIONS)
		executeOptions(request);
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
Server::executeAutoindex(const Request& request)
{
	Request::Method method = request.get_m_method();
	
	if (method != Request::GET)
		return (createResponse(request.get_m_connection(), 40502, headers_t(1, "Allow:GET"), "", method));

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	if (request.get_m_location()->get_m_autoindex())
	{
		HtmlWriter html;
		makeAutoindexForm(html, request);
		if (!makeAutoindexContent(html, request.get_m_location()->get_m_root_path()))
			return (createResponse(request.get_m_connection(), 50002));
		return (createResponse(request.get_m_connection(), 200, headers_t(), html.get_m_body(), method));
	}
	else
	{
		int fd = getValidIndexFd(request);
		if (fd == -1)
			return (createResponse(request.get_m_connection(), 40403));
		return (createResponse(request.get_m_connection(), 200, headers_t(), ft::getStringFromFd(fd), method));
	}
}

void
Server::executeGet(const Request& request)
{
	std::string path = request.get_m_path_translated();
	std::string body;

	try {
		body = ft::getStringFromFile(path, m_limit_client_body_size);
	} catch (std::overflow_error& e) {
		return (createResponse(request.get_m_connection(), 41304));
	}

	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(request.get_m_connection(), 41501));
	headers.push_back(getLastModifiedHeader(path));
	return (createResponse(request.get_m_connection(), 200, headers, body));
}

void
Server::executeHead(const Request& request)
{
	std::string path = request.get_m_path_translated();
	std::string body;

	try {
		body = ft::getStringFromFile(path, m_limit_client_body_size);
	} catch (std::overflow_error& e) {
		return (createResponse(request.get_m_connection(), 41305, headers_t(), "", Request::HEAD));
	}

	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(request.get_m_connection(), 41502, headers_t(), "", Request::HEAD));
	headers.push_back(getLastModifiedHeader(path));
	headers.push_back("content-length:" + std::to_string(body.size()));
	return (createResponse(request.get_m_connection(), 200, headers, "", Request::HEAD));
}

void
Server::executeTrace(const Request& request) {
	createResponse(request.get_m_connection(), 200, headers_t(1, "Content-Type:text/plain"), request.get_m_origin());
}

void
Server::executePost(const Request& request)
{
	if (request.get_m_headers().find("Content-Length")->second == "0")
		return (executeGet(request));
	else
		return (createResponse(request.get_m_connection(), 40023));
}

void
Server::executeOptions(const Request& request) {
	if (request.get_m_uri() == "*")
		return (createResponse(request.get_m_connection(), 200, headers_t(1, std::string("Allow:") + SERVER_ALLOW_METHODS)));
	headers_t headers(1, "Allow:" + ft::containerToString(request.get_m_location()->get_m_allow_method(), ", "));
	return (createResponse(request.get_m_connection(), 200, headers));
}

void
Server::executePut(const Request& request)
{
	int fd;
	struct stat buf;

	stat(request.get_m_script_translated().c_str(), &buf);
	headers_t headers(1, getMimeTypeHeader(request.get_m_path_translated()));
	// if (headers[0].empty())
	// 	return (createResponse(request.get_m_connection(), 41503));
	if ((fd = open(request.get_m_script_translated().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		return (createResponse(request.get_m_connection(), 50003));
	if (write(fd, request.get_m_content().c_str(), request.get_m_content().size()) == -1)
		return (createResponse(request.get_m_connection(), 50004));
	close(fd);
	if (S_ISREG(buf.st_mode))
		return (createResponse(request.get_m_connection(), 204));
	headers.push_back("Location:" + m_host + "/" + request.get_m_uri());
	return (createResponse(request.get_m_connection(), 201, headers, request.get_m_content()));
}

void
Server::executeDelete(const Request& request) {
	if (unlink(request.get_m_path_translated().c_str()) == -1)
		createResponse(request.get_m_connection(), 204);
	else
		return (createResponse(request.get_m_connection(), 204));
}

namespace {
	int	setEnv(char **env, int idx, std::string key, std::string val)
	{
		char	*item;

		if (key.empty())
			return (0);
		item = ft::strsjoin(key, std::string("="), val);
		std::cout << item << std::endl;
		env[idx] = item;
		return (1);
	}
	char **dupBaseEnvWithExtraSpace(Config *config)
	{
		char **base_env = config->get_m_base_env();
		char **cgi_env = NULL;
		int idx = 0;
		int len = ft::lenDoubleStr(base_env);

		if ((cgi_env = reinterpret_cast<char **>(malloc(sizeof(char *) * (len + CGI_META_VARIABLE_COUNT + 1 + 1)))) == 0)
			return (NULL);
		while (base_env[idx] != NULL) {
			cgi_env[idx] = ft::strdup(base_env[idx]);
			++idx;
		}
		while (idx < len + CGI_META_VARIABLE_COUNT + 1 + 1)
			cgi_env[idx++] = NULL;
		return (cgi_env);
	}
	std::string getCGIEnvValue(const Request& request, std::string token, Server *server = NULL, Config config = Config())
	{
		if (token == "CONTENT_LENGTH") {
			if (request.get_m_method() == Request::POST)
				return (std::to_string(request.get_m_content().size()));
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
	char **env = dupBaseEnvWithExtraSpace(m_config);
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
	if (ft::hasKey(request.get_m_headers(), "X-Secret-Header-For-Test"))
		setEnv(env, idx, "HTTP_X-SECRET-HEADER-FOR-TEST", request.get_m_headers().find("X-Secret-Header-For-Test")->second);
	return (env);
}


// void Server::redirectStdInOut(int* parent_write_fd, int* child_write_fd) {
// 	if (dup2(parent_write_fd[0], 0) == -1 || dup2(child_write_fd[1], 1) == -1)
// 		ft::log(ServerManager::access_fd, ServerManager::error_fd, \
// 		"[Failed][function] dup2 function failed in redirectStdInOut method.");
// }

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
Server::executeCGI(const Request& request)
{
	ft::log(-1, ServerManager::error_fd, "\n\n[CGI START]\n\n");
	pid_t	pid;
	int parent_write_fd[2];
	int child_write_fd[2];
	char **env;
	Request::Method method = request.get_m_method();
	std::string body;
	int status = 0;

	if ((env = createCGIEnv(request)) == NULL)
		return (createResponse(request.get_m_connection(), 50005, headers_t(), "", method));
	pipe(parent_write_fd);
	pipe(child_write_fd);
	pid = fork();
	if (pid == 0) {
		dup2(parent_write_fd[0], 0);
		dup2(child_write_fd[1], 1);
		close(parent_write_fd[1]);
		close(child_write_fd[0]);
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
		return (createResponse(request.get_m_connection(), 50006, headers_t(), "", method));
	}
	
	usleep(1000);
	ft::log(ServerManager::access_fd, -1, "TEST 1\n");
	close(parent_write_fd[0]);
	close(child_write_fd[1]);
	if (fcntl(parent_write_fd[1], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("write fnctl error");
	if (fcntl(child_write_fd[0], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("read fnctl error");

	ft::log(ServerManager::access_fd, -1, "TEST 2\n");
	int size = 0;
	int count = 0;
	std::string data;
	char buff[CHUNKED_TRANSFER_BUFFER_SIZE];

	// if (ft::hasKey(request.get_m_headers(), "X-Secret-Header-For-Test"))
	// 	body = "HTTP_X-Secret-Header-For-Test: " + request.get_m_headers().find("X-Secret-Header-For-Test")->second + "\r\n";
	if (method == Request::POST) {
		data = request.get_m_content();
		size = request.get_m_content().size();
	}
	if (method == Request::GET)
		close(parent_write_fd[1]);
	ft::log(ServerManager::access_fd, -1, "TEST 3\n");
	waitpid(pid, &status, WNOHANG);
	while (!WIFEXITED(status) || (method == Request::POST && size > 0))
	{
		if (method == Request::POST && size > 0)
		{
			if (size > CHUNKED_TRANSFER_BUFFER_SIZE)
				count = CHUNKED_TRANSFER_BUFFER_SIZE;
			else
				count = size;
			count = write(parent_write_fd[1], data.c_str(), count);
			ft::log(-1, ServerManager::error_fd, "written:" + std::to_string(count) + "\n");
			if (count > 0) {
				data.erase(0, count);
				size -= count;
			}
			ft::log(-1, ServerManager::error_fd, "size:" + std::to_string(size) + "\n");
			usleep(2000);
		}
		count = read(child_write_fd[0], buff, sizeof(buff));
		ft::log(-1, ServerManager::error_fd, "ing readed:" + std::to_string(count) + "\n");
		if (count > 0) {
			body.append(buff, count);
		}
		if (body.size() > m_limit_client_body_size) {
			close(child_write_fd[0]);
			return (createResponse(request.get_m_connection(), 41306, headers_t(), "", method));
		}
		if (count < 0)
			usleep(2000);
		if (request.isOverTime()) {
			close(child_write_fd[0]);
			return (createResponse(request.get_m_connection(), 50401, headers_t(), "", method));
		}
		waitpid(pid, &status, WNOHANG);
	}
	usleep(10000);
	if (method == Request::POST)
		close(parent_write_fd[1]);
	while ((count = read(child_write_fd[0], buff, sizeof(buff))) > 0)
	{
		ft::log(-1, ServerManager::error_fd, "after readed:" + std::to_string(count) + "\n");
		if (count > 0)
			body.append(buff, count);
		if (body.size() > m_limit_client_body_size) {
			close(child_write_fd[0]);
			return (createResponse(request.get_m_connection(), 41306, headers_t(), "", method));
		}
	}
	close(child_write_fd[0]);
	return (createResponse(request.get_m_connection(), CGI_SUCCESS_CODE, headers_t(), body));
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
		std::cout << key << "::" << value << std::endl;
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

	int size = body.size();
	std::string new_body;
	headers.push_back("Transfer-Encoding:chunked");
	ft::log(ServerManager::access_fd, -1, "response size is origin: " + std::to_string(size) + "\n");
	while (size > 0)
	{
		if (size > CHUNKED_TRANSFER_BUFFER_SIZE)
		{
			new_body.append(ft::itos(std::to_string(CHUNKED_TRANSFER_BUFFER_SIZE), 10, 16) + "\r\n");
			new_body.append(body.begin(), body.begin() + CHUNKED_TRANSFER_BUFFER_SIZE);
			new_body.append("\r\n");
			body.erase(body.begin(), body.begin() + CHUNKED_TRANSFER_BUFFER_SIZE);
			size -= CHUNKED_TRANSFER_BUFFER_SIZE;
		} else
		{
			new_body.append(ft::itos(std::to_string(size), 10, 16) + "\r\n");
			new_body.append(body.begin(), body.end());
			new_body.append("\r\n");
			body.clear();
			size = 0;
		}
	}
	new_body.append("0\r\n\r\n");
	body = new_body;
}

void
Server::createResponse(Connection* connection, int status, headers_t headers, std::string body, Request::Method method)
{
	if (status >= 40000) {
		reportCreateNewRequestLog(connection, status);
		status /= 100;
	}
	
	headers.push_back(getDateHeader());
	headers.push_back(getServerHeader(this));

	if (status == CGI_SUCCESS_CODE)
		createCGIResponse(status, headers, body);
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
	if (method == Request::HEAD)
		body = "";
	
	Response response(connection, status, body);
	headers_t::iterator it = headers.begin();
	for (; it != headers.end(); ++it) {
		std::string key = ft::rtrim((*it).substr(0, (*it).find(":")), " ");
		std::string value = ft::ltrim((*it).substr((*it).find(":") + 1), " ");
		response.addHeader(key, value);
	}
	writeCreateNewResponseLog(response);
	m_responses.push(response);
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
Server::reportCreateNewRequestLog(Connection* connection, int status)
{
	std::string text = "[Failed][Request][Server:" + m_server_name + "][CIP:"
	+ connection->get_m_client_ip() + "][CFD:" + std::to_string(connection->get_m_client_fd()) + "]["
	+ std::to_string(status) + "][" + Response::status[status] + "] Failed to create new Request.\n";
	ft::log(ServerManager::access_fd, ServerManager::error_fd, text);
	return ;
}

void
Server::writeCreateNewResponseLog(const Response& response)
{
	std::string text = "[Created][Response][Server:" + m_server_name + "][" \
	+ std::to_string(response.get_m_status_code()) + "][" + response.get_m_status_description() + "][CFD:" \
	+ std::to_string(response.get_m_connection()->get_m_client_fd()) + "][headers:" \
	+ std::to_string(response.get_m_headers().size()) + "][body:" + std::to_string(response.get_m_content().size()) + "]";
	text.append(" New response created.\n");
	ft::log(ServerManager::access_fd, -1, text);
	ft::log(ServerManager::access_fd, -1, "[Detected][Response][Message][↓]" + response.getString().substr(0, 500) + "\n\n");
	return ;
}

void
Server::writeSendResponseLog(const Response& response)
{
	std::string text = "[Sended][Response][Server:" + m_server_name + "][" \
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
