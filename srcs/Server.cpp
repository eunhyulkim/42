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
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
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

bool
Server::hasException(int client_fd) {
	return (m_manager->fdIsset(client_fd, ServerManager::ERROR_COPY_SET));
}

void
Server::closeConnection(int client_fd)
{
	close(client_fd);
	m_manager->fdClear(client_fd, ServerManager::READ_SET);
	m_connections.erase(client_fd);
	if (m_manager->get_m_max_fd() == client_fd) {
		m_manager->set_m_max_fd(m_manager->get_m_max_fd() - 1);
	}
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
	socklen_t			client_addr_size = sizeof(struct sockaddr_in);
	int 				client_fd;
	std::string			client_ip;
	int					client_port;

	ft::bzero(&client_addr, client_addr_size);

	if ((client_fd = accept(m_fd, (struct sockaddr *)&client_addr, &client_addr_size)) == -1)
		return (false);
	if (m_manager->get_m_max_fd() < client_fd)
		m_manager->set_m_max_fd(client_fd);
	if (fcntl(client_fd, F_SETFL, O_NONBLOCK) == -1)
		return (false);
	client_ip = inet_ntoa(client_addr.sin_addr.s_addr);
	client_port = static_cast<int>(client_addr.sin_port);
	m_connections[client_fd] = Connection(client_fd, client_ip, client_port);
	m_manager->fdSet(client_fd, ServerManager::READ_SET);
	if (client_fd > m_manager->get_m_max_fd())
		m_manager->set_m_max_fd(client_fd);
	writeCreateNewConnectionLog(client_fd, client_ip, client_port);
	return (true);
}

void
Server::run()
{
	int response_count = 0;
	while (!m_responses.empty() && response_count < SEND_RESPONSE_AT_ONCE)
	{
		++response_count;
		Response response(m_responses.front());
		m_responses.pop();
		if (isSendable(response.get_m_connection()->get_m_client_fd()))
			sendResponse(response);
		if (response.get_m_connection_type() == Response::CLOSE)
			closeConnection(response.get_m_connection()->get_m_client_fd());
	}

	std::map<int, Connection>::iterator it = m_connections.begin();
	while (it != m_connections.end())
	{
		Request request;
		std::map<int, Connection>::iterator it2 = it++;
		int fd = it2->first;

		if (m_fd == fd)
			continue ;
		else if (hasException(fd)) {
			closeConnection(fd);
			continue ;
		}
		else if (hasRequest(fd))	{
			writeDetectNewRequestLog(it2->second);
			try {
				request = recvRequest(fd, it2->second);
			} catch (int status_code) {
				createResponse(&(it2->second), status_code);
				reportCreateNewRequestLog(it2->second, status_code);
				continue ;
			} catch (std::exception& e) {
				createResponse(&(it2->second), 500);
				reportCreateNewRequestLog(it2->second, 500);
				continue ;
			}
			if (m_responses.size() > RESPONSE_OVERLOAD_COUNT) {
				createResponse(&(it2->second), 503);
				reportCreateNewRequestLog(it2->second, 503);
				closeConnection(fd);
				continue ;
			}
			writeCreateNewRequestLog(request);
			solveRequest(request);
			m_manager->writeServerHealthLog(true);
		}
	}
	if (hasNewConnection())
	{
		writeDetectNewConnectionLog();
		if (m_connections.size() >= (1024 / m_manager->get_m_servers().size()))
		{
			std::map<int, Connection>::iterator it = m_connections.begin();
			for (; it != m_connections.end(); ++it) {
				if (!m_manager->fdIsset(it->first, ServerManager::WRITE_SET))
					break ;
			}
			if (it == m_connections.end())
				return ;
			closeConnection(it->first);
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
	void makeResponse401(Server* server, const Request& request) {
		std::string header = "WWW-Authenticate:Basic realm=\"";
		header.append(request.get_m_location()->get_m_auth_basic_realm());
		header.append("\", charset=\"UTF-8\"");
		return (server->createResponse(request.get_m_connection(), 401, HEADERS(1, header)));
	}
}

void
Server::solveRequest(const Request& request)
{
	Location* location = request.get_m_location();
	std::string methodString = request.get_m_method_to_string();

	if (!ft::hasKey(location->get_m_allow_method(), methodString)) {
		HEADERS headers(1, "Allow:" + ft::containerToString(location->get_m_allow_method(), ", "));
		return (createResponse(request.get_m_connection(), 405, headers, ""));
	}
	if (isAuthorizationRequired(location)) {
		if (!hasCredential(request)) {
			return (makeResponse401(this, request));
		} else {
			std::vector<std::string> credential = ft::split(request.get_m_headers().find("Authorization")->second, ' ');
			if (!isValidCredentialForm(credential))
				return (createResponse(request.get_m_connection(), 400));
			else if (!isValidCredentialContent(location, credential))
				return (createResponse(request.get_m_connection(), 403));
		}
	}
	Request::Method method = request.get_m_method();
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
	bool makeAutoindexContent(HtmlWriter& html, char *cwd)
	{
		DIR *dir = NULL;
		struct dirent *de = NULL;
		char buff[1024];
		int idx = 7;

		if ((dir = opendir(cwd)) == NULL)
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
	int getValidIndexFd(const Request& request, char *cwd)
	{
		std::set<std::string> index = request.get_m_location()->get_m_index();
		std::set<std::string>::iterator it = index.begin();
		struct stat buf;
		int fd = -1;
		std::string path, body;
		for (; it != index.end(); ++it)
		{
			path = std::string(cwd) + "/" + *it;
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
	if (request.get_m_method() != Request::GET)
		return (createResponse(request.get_m_connection(), 405, HEADERS(1, "Allow:GET")));

	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	if (request.get_m_location()->get_m_autoindex())
	{
		HtmlWriter html;
		makeAutoindexForm(html, request);
		if (!makeAutoindexContent(html, cwd))
			return (createResponse(request.get_m_connection(), 500));
		createResponse(request.get_m_connection(), 200, HEADERS(), html.get_m_body());
	}
	else
	{
		int fd = getValidIndexFd(request, cwd);
		if (fd == -1)
			return (createResponse(request.get_m_connection(), 404));
		return (createResponse(request.get_m_connection(), 200, HEADERS(), ft::getStringFromFd(fd)));
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
		return (createResponse(request.get_m_connection(), 413));
	}

	HEADERS headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(request.get_m_connection(), 415));
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
		return (createResponse(request.get_m_connection(), 413));
	}

	HEADERS headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(request.get_m_connection(), 415));
	headers.push_back(getLastModifiedHeader(path));
	headers.push_back("content-length:" + std::to_string(body.size()));
	return (createResponse(request.get_m_connection(), 200, headers));
}

void
Server::executeTrace(const Request& request) {
	createResponse(request.get_m_connection(), 200, HEADERS(1, "Content-Type:text/plain"), request.get_m_origin());
}

void
Server::executePost(const Request& request)
{
	if (request.get_m_headers().find("Content-Length")->second == "0")
		return (executeGet(request));
	else
		return (createResponse(request.get_m_connection(), 400));
}

void
Server::executeOptions(const Request& request) {
	if (request.get_m_uri() == "*")
		return (createResponse(request.get_m_connection(), 200, HEADERS(1, std::string("Allow:") + SERVER_ALLOW_METHODS)));
	HEADERS headers(1, "Allow:" + ft::containerToString(request.get_m_location()->get_m_allow_method(), ", "));
	return (createResponse(request.get_m_connection(), 200, headers));
}

void
Server::executePut(const Request& request)
{
	int fd;
	struct stat buf;

	stat(request.get_m_path_translated().c_str(), &buf);
	HEADERS headers(1, getMimeTypeHeader(request.get_m_path_translated()));
	if (headers[0].empty())
		return (createResponse(request.get_m_connection(), 415));
	if ((fd = open(request.get_m_path_translated().c_str(), O_RDWR | O_CREAT)) == -1)
		createResponse(request.get_m_connection(), 500);
	if (write(fd, request.get_m_content().c_str(), request.get_m_content().size() + 1) == -1)
		createResponse(request.get_m_connection(), 500);
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
}

namespace {
	void closeFd(int *fd) {
		close(fd[0]);
		close(fd[1]);
	}
	int	setEnv(char **env, int idx, std::string key, std::string val)
	{
		char	*item;

		if (key.empty())
			return (0);
		item = ft::strsjoin(key, std::string("="), val);
		env[idx] = item;
		return (1);
	}
	char **dupBaseEnvWithExtraSpace(Config *config)
	{
		char **base_env = config->get_m_base_env();
		char **cgi_env = NULL;
		int idx = 0;
		int len = ft::lenDoubleStr(base_env);

		if ((cgi_env = reinterpret_cast<char **>(malloc(sizeof(char *) * (len + CGI_META_VARIABLE_COUNT + 1)))) == 0)
			return (NULL);
		while (base_env[idx] != NULL) {
			cgi_env[idx] = base_env[idx];
			++idx;
		}
		while (idx < len + CGI_META_VARIABLE_COUNT + 1)
			cgi_env[idx++] = NULL;
		return (cgi_env);
	}
	char *getCGIEnvValue(const Request& request, std::string token, Server *server = NULL, Config config = Config())
	{
		if (token == "CONTENT_LENGH") {
			if (request.get_m_method() == Request::POST)
				return (const_cast<char *>(std::to_string(request.get_m_content().size()).c_str()));
			return (const_cast<char *>(std::string("-1").c_str()));
		}
		else if (token == "CONTENT_TYPE") {
			if (ft::hasKey(request.get_m_headers(), "Content-Type"))
				return (const_cast<char *>(request.get_m_headers().find("Content-Type")->second.c_str()));
			return (const_cast<char *>(std::string().c_str()));
		}
		else if (token == "AUTH_TYPE")
			return (const_cast<char *>(config.get_m_cgi_version().c_str()));
		else if (token == "PATH_INFO")
			return (const_cast<char *>(request.get_m_path_info().c_str()));
		else if (token == "PATH_TRANSLATED")
			return (const_cast<char *>(request.get_m_path_translated().c_str()));
		else if (token == "QUERY_STRING")
			return (const_cast<char *>(request.get_m_query().c_str()));
		else if (token == "REMOTE_ADDR")
			return (const_cast<char *>(request.get_m_connection()->get_m_client_ip().c_str()));
		else if (token == "REQUEST_METHOD")
			return (const_cast<char *>(request.get_m_method_to_string().c_str()));
		else if (token == "REQUEST_URI") {
			std::string request_uri = request.get_m_uri();
			request_uri.append(request.get_m_query());
			request_uri.append(request.get_m_path_info());
			return (const_cast<char *>(request_uri.c_str()));
		}
		else if (token == "SCRIPT_NAME")
			return (const_cast<char *>(request.get_m_uri().c_str()));
		else if (token == "SERVER_NAME")
			return (const_cast<char *>(server->get_m_server_name().c_str()));
		else if (token == "SERVER_PORT")
			return (const_cast<char *>(std::to_string(server->get_m_port()).c_str()));
		else if (token == "SERVER_PROTOCOL")
			return (const_cast<char *>(config.get_m_cgi_version().c_str()));
		else if (token == "SERVER_SOFTWARE")
			return (const_cast<char *>((config.get_m_software_name() + config.get_m_software_version()).c_str()));
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
	return (env);
}

void
Server::executeCGI(const Request& request)
{
	pid_t	pid;
	int parent_write_fd[2];
	int child_write_fd[2];
	char **env;

	if ((env = createCGIEnv(request)) == NULL)
		return (createResponse(request.get_m_connection(), 500));
	pipe(parent_write_fd);
	pipe(child_write_fd);
	pid = fork();
	if (pid == 0) {
		/* child process */
		close(parent_write_fd[1]);
		close(child_write_fd[0]);
		dup2(child_write_fd[1], STDOUT_FILENO);
		dup2(parent_write_fd[0], STDIN_FILENO);
		close(child_write_fd[1]);
		close(parent_write_fd[0]);
		char *arg[2] = { const_cast<char *>(request.get_m_path_translated().c_str()), NULL };
		if (execve("./php-cgi", arg, env) == -1)
			exit(EXIT_FAILURE);
	} else if (pid > 0) {
		close(child_write_fd[1]);
		close(parent_write_fd[0]);
		if (request.get_m_method() == Request::POST)
			write(parent_write_fd[1], request.get_m_content().c_str(), request.get_m_content().size() + 1);
		close(parent_write_fd[1]);

	} else {
		perror("Failed to Create Process for executeCGI");
		closeFd(parent_write_fd);
		closeFd(child_write_fd);
		return (createResponse(request.get_m_connection(), 500));
	}

	int status;
	int readed = 0;
	std::string body;
	char buff[1024];
	if (fcntl(child_write_fd[0], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("FCNTL ERROR");

	while (true)
	{
		waitpid(pid, &status, WNOHANG);
		if ((readed = read(child_write_fd[0], buff, sizeof(buff))) > 0) {
			body.append(buff, readed);
			if (body.size() > m_limit_client_body_size) {
				close(child_write_fd[0]);
				return (createResponse(request.get_m_connection(), 413));
			}
		}
		if (WIFEXITED(status)) {
			close(child_write_fd[0]);
			break ;
		}
		if (request.isOverTime()) {
			close(child_write_fd[0]);
			return (createResponse(request.get_m_connection(), 504));
		}
		usleep(100000);
	}
	return (createResponse(request.get_m_connection(), 200, HEADERS(), body));
}

bool
Server::isSendable(int client_fd)
{
	if (m_manager->fdIsset(client_fd, ServerManager::ERROR_COPY_SET))
		return (false);
	else if (m_manager->fdIsset(client_fd, ServerManager::WRITE_COPY_SET))
		return (true);
	return (false);
}

void
Server::sendResponse(Response response)
{
	int fd = response.get_m_connection()->get_m_client_fd();

	send(fd, response.c_str(), ft::strlen(response.c_str()), 0);
	m_manager->fdClear(fd, ServerManager::WRITE_SET);
}

bool Server::hasRequest(int client_fd)
{
	return (m_manager->fdIsset(client_fd, ServerManager::READ_COPY_SET));
}

namespace {
	int headerParsing(Server *server, Request &request, std::string &origin_message, Request::TransferType &transfer_type, int &content_length)
	{
		std::string buf;
		bool host_header = false;

		while (!std::cin.eof()) //header parsing
		{
			std::getline(std::cin, buf);
			origin_message = buf + "\n";
			if (buf == "\r" || buf == "")
				break;
			if (!request.isValidHeader(buf))
				throw (400);
			buf = ft::rtrim(buf, "\r");
			size_t pos = buf.find(':');
			std::string key = ft::trim(buf.substr(0, pos));
			std::string value = ft::trim(buf.substr(pos + 1));
			for (size_t i = 0 ; i < key.length() ; ++i) // capitalize
				key[i] = (i == 0 || key[i - 1] == '-') ? std::toupper(key[i]) : std::tolower(key[i]);
			if (key == "Content-Type" && value.find("chunked") != std::string::npos)
				transfer_type = Request::CHUNKED;
			if (key == "Content-Length")
			{
				content_length = std::stoi(value);
				if (content_length > static_cast<int>(server->get_m_limit_client_body_size()))
					throw (413);
				if (content_length < 0)
					throw 400;
			}
			if (key == "Host")
				host_header = true;
			request.add_header(key, value);
		}
		return (host_header);
	}
	std::string readBodyMessage(Server *server, Request &request, std::string &origin_message, Request::TransferType &transfer_type, int &content_length, int client_fd)
	{
		std::string buf;
		std::string message_body;
		char		buffer[LIMIT_CLIENT_BODY_SIZE_MAX];
		ssize_t		read_len = 0;

		if (request.get_m_method() == Request::POST || request.get_m_method() == Request::PUT)
		{
			if (transfer_type == Request::CHUNKED)
			{
				if (content_length)
					throw 400;
				while (1)
				{
					std::getline(std::cin, buf);
					origin_message += buf + "\n";
					buf = ft::rtrim(buf, "\r");
					if (buf == "0")
					{
						if ((read_len = read(client_fd, buffer, 2)) != 2 || std::strncmp(buffer, "\r\n", 2))
							throw 400;
						origin_message += "\r\n";
						break;
					}
					content_length = std::stoi(buf);
					if (content_length > static_cast<int>(server->get_m_limit_client_body_size()))
						throw (413);
					if (content_length < 0)
						throw 400;
					read_len = read(client_fd, buffer, content_length);
					if (read_len != content_length)
						throw 400;
					message_body.append(buffer, read_len);
					origin_message += buffer;
					if ((read_len = read(client_fd, buffer, 2)) != 2 || std::strncmp(buffer, "\r\n", 2))
						throw 400;
					origin_message += "\r\n";
				}
			}
			else
			{
				read_len = read(client_fd, buffer, content_length);
				if (read_len != content_length)
					throw 400;
				message_body.append(buffer, read_len);
				origin_message += buffer;
			}
		}
		else
		{
			if ((read_len = read(client_fd, buffer, 1024)) != -1)
				throw 400;
		}
		return (message_body);
	}
}

Request Server::recvRequest(int client_fd, Connection connection)
{
	std::string start_line;
	Request::TransferType transfer_type = Request::GENERAL;
	int content_length = 0;

	dup2(client_fd, 0);
	std::getline(std::cin, start_line);
	std::string origin_message = start_line + "\n";
	start_line = ft::rtrim(start_line, "\r");
	Request request(&connection, this, start_line);
	if (!headerParsing(this, request, origin_message, transfer_type, content_length))
		throw 400;
	std::string message_body = readBodyMessage(this, request, origin_message, transfer_type, content_length, client_fd);
	origin_message += message_body;
	request.add_content(message_body);
	if (request.get_m_method() == Request::TRACE)
		request.add_origin(origin_message);
	return (request);
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

void
Server::createResponse(Connection* connection, int status, HEADERS headers, std::string body)
{
	headers.push_back(getDateHeader());
	headers.push_back(getServerHeader(this));
	if (status == CGI_SUCCESS_CODE) {
		HEADERS headers_in_body = ft::split(ft::rtrim(body.substr(0, body.find("\n\n")), "\r\n"), '\n');
		headers.insert(headers.end(), headers_in_body.begin(), headers_in_body.end());
		headers.push_back("Transfer-Encoding:chunked; UTF-8");
		headers.push_back("Connection:close");
		body = body.substr(body.find("\n\n") + 2);
		status = 200;
	} else if (!body.empty()) {
		headers.push_back("Content-Length:" + std::to_string(body.size()));
	} else if (status >= 400 && status <= 599) {
		body = m_default_error_page;
		body.replace(body.find("#ERROR_CODE"), 11, std::to_string(status));
		body.replace(body.find("#ERROR_CODE"), 11, std::to_string(status));
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
		headers.push_back("Content-Length:" + std::to_string(body.size()));
	}
	if (!body.empty())
		headers.push_back("Content-Language:ko-KR");
	if (status / 100 != 2)
		headers.push_back("Connection:close");
	if (status / 100 == 3)
		headers.push_back("Location:/");
	if (status == 504)
		headers.push_back("Retry-After:3600");

	Response response(connection, status, body);
	HEADERS::iterator it = headers.begin();
	for (; it != headers.end(); ++it) {
		std::string key = (*it).substr(0, (*it).find(":"));
		std::string value = (*it).substr((*it).find(":") + 1);
		response.addHeader(key, value);
	}
	writeCreateNewResponseLog(response);
	m_responses.push(response);
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Server::writeDetectNewConnectionLog()
{
	std::string text = "[Detected][Connection][Server:" + m_server_name + "][Host:" + m_host \
	+ "] New connection detected.\n";
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port)
{
	std::string text = "[Created][Connection][Server:" + m_server_name + "][CFD:" \
	+ std::to_string(client_fd) + "][IP:" + client_ip + "][Port:" + std::to_string(client_port) + "]\n";
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::reportCreateNewConnectionLog()
{
	std::string text = "[Failed][Connection][Server:" + m_server_name + "][Host:" + m_host \
	+ "] Failed to create new connection.\n";
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::writeDetectNewRequestLog(const Connection& connection)
{
	std::string text = "[Detected][Request][Server:" + m_server_name + "][CIP:"
	+ connection.get_m_client_ip() + "][CFD:" + std::to_string(connection.get_m_client_fd()) + "]"
	+ " New request detected.\n";
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::writeCreateNewRequestLog(const Request& request)
{
	std::string text = "[Created][Request][Server:" + m_server_name + "][Method:" \
	+ request.get_m_method_to_string() + "][URI:" + request.get_m_uri() + "][Path:" + request.get_m_path_translated() + "]";
	if (request.get_m_method() == Request::GET)
		text.append("[Query:" + request.get_m_query() + "]");
	text.append(" New request created.\n");
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::reportCreateNewRequestLog(const Connection& connection, int status)
{
	std::string text = "[Failed][Request][Server:" + m_server_name + "][CIP:"
	+ connection.get_m_client_ip() + "][CFD:" + std::to_string(connection.get_m_client_fd()) + "]["
	+ std::to_string(status) + "] Failed to create new connection.\n";
	ft::log(ServerManager::access_fd, text);
	return ;
}

void
Server::writeCreateNewResponseLog(const Response& response)
{
	std::string text = "[Created][Response][Server:" + m_server_name + "][" \
	+ std::to_string(response.get_m_status_code()) + "][" + response.get_m_status_description() + "][headers:" \
	+ response.get_m_headers().size() + "][body" + response.get_m_content().size();
	text.append(" New response created.\n");
	ft::log(ServerManager::access_fd, text);
	return ;
}

// void
// Server::writeServerHealthLog(bool ignore_interval)
// {
// 	if (ignore_interval == false && !ft::isRightTime(SERVER_HEALTH_LOG_TIME))
// 		return ;
// 	int fd = ServerManager::access_fd;
// 	std::string text = "[HealthCheck][Server][Max_fd:" + std::to_string(m_max_fd) \
// 	+ "][ReadFD:" + ft::getSetFdString(m_max_fd, &m_read_set) + "][RequestFD:" + ft::getSetFdString(m_max_fd, &m_read_copy_set) \
// 	+ "][WriteFD:" + ft::getSetFdString(m_max_fd, &m_write_set) + "]\n";
// 	ft::log(fd, text);
// 	return ;
// }
