#include "ServerManager.hpp"
#include <errno.h>

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

int ServerManager::error_fd = -1;
int ServerManager::access_fd = -1;
int ServerManager::stdin_fd = dup(0);
int ServerManager::stdout_fd = dup(1);

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::ServerManager()
{
    this->m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);
    ft::fdZero(&m_error_copy_set);
}

ServerManager::ServerManager(const ServerManager& obj)
{
	m_servers = obj.m_servers;
	m_server_fdset = obj.m_server_fdset;
	m_config = obj.m_config;
	m_max_fd = obj.m_max_fd;
	m_read_set = obj.m_read_set;
	m_read_copy_set = obj.m_read_copy_set;
	m_write_set = obj.m_write_set;
	m_write_copy_set = obj.m_write_copy_set;
	m_error_copy_set = obj.m_error_copy_set;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::~ServerManager()
{
    this->m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);
    ft::fdZero(&m_error_copy_set);
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ServerManager& ServerManager::operator=(const ServerManager& obj)
{
	if (this == &obj)
		return (*this);
	m_servers = obj.m_servers;
	m_server_fdset = obj.m_server_fdset;
	m_config = obj.m_config;
	m_max_fd = obj.m_max_fd;
	m_read_set = obj.m_read_set;
	m_read_copy_set = obj.m_read_copy_set;
	m_write_set = obj.m_write_set;
	m_write_copy_set = obj.m_write_copy_set;
	m_error_copy_set = obj.m_error_copy_set;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const ServerManager&) {
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const std::vector<Server>& ServerManager::get_m_servers() const { return (this->m_servers); }
const std::set<int>& ServerManager::get_m_server_fdset() const { return (this->m_server_fdset); }
Config ServerManager::get_m_config() const { return (this->m_config); }
int ServerManager::get_m_max_fd() const { return (this->m_max_fd); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void ServerManager::set_m_max_fd(int max_fd) { this->m_max_fd = max_fd; }
void ServerManager::set_m_config(const Config& config) { this->m_config = config; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------- FUNCTIONS FOR PARSE CONFIGURATION FILE ------------------ */
/* ************************************************************************** */

namespace {
	enum IncludeMode { INCLUDE_START, INCLUDE_END, INCLUDE_BOTH, INCLUDE_NOT, };

	std::vector<std::string> groupLineWithCondition(std::vector<std::string>& lines, \
	const std::string& start_line, const std::string& end_line, IncludeMode mode = INCLUDE_BOTH)
	{
		bool is_group_line = false;
		std::vector<std::string> ret;
		std::vector<std::string> remain;
		for (size_t i = 0; i < lines.size(); ++i)
		{
			std::string line = lines[i];
			if (line.empty())
				continue ;
			if (is_group_line == true)
			{
				if (line.size() >= end_line.size() && line.substr(0, end_line.size()) == end_line)
				{
					if (mode == INCLUDE_BOTH || mode == INCLUDE_END)
						ret[ret.size() - 1].append(line + "\n");
					is_group_line = false;
				}
				else
					ret[ret.size() - 1].append(line + "\n");
			}
			else if (line.size() >= start_line.size() && line.substr(0, start_line.size()) == start_line)
			{
				is_group_line = true;
				if (mode == INCLUDE_BOTH || mode == INCLUDE_START)
					ret.push_back(line + "\n");
				else
					ret.push_back("");
			}
			else
				remain.push_back(line);
		}
		lines = remain;
		return (ret);
	}

	bool isValidIpByte(std::string s) { return ((ft::stoi(s) >= 0) && (ft::stoi(s) <= 255)); }
	bool isValidCgi(std::string data) { return (data[0] == '.'); }
	bool isDigit(char c) { return (c >= '0' && c <= '9'); }
}

bool
ServerManager::splitConfigString(std::string config_string, std::string& config_block, \
std::vector<std::string>& server_strings)
{
	std::vector<std::string> lines = ft::split(config_string);
	for (size_t i = 0; i < lines.size(); ++i)
		lines[i] = ft::rtrim(lines[i], " \t");
	server_strings = groupLineWithCondition(lines, "server {", "}", INCLUDE_NOT);
	config_block = ft::containerToString(lines, "\n");

	return (!config_block.empty() && server_strings.size() != 0);
}

bool
ServerManager::splitServerString(std::string server_string, std::string& server_block, \
std::vector<std::string>& location_blocks)
{
	std::vector<std::string> lines = ft::split(server_string);
	for (size_t i = 0; i < lines.size(); ++i)
		lines[i] = ft::trim(lines[i], " \t");
	location_blocks = groupLineWithCondition(lines, "location ", "}", INCLUDE_START);
	server_block = ft::containerToString(lines, "\n");

	return (!server_block.empty() && location_blocks.size() != 0);
}

/*
** function: isValidConfigBlock
** 1. check every entity without duplicate
** 2. check 'SOFTWARE_NAME' and 'SOFTWARE_VERSION' NOT EMPTY
** 3. check 'HTTP_VERSION' and 'CGI_VERSION' is 1.1
*/

bool
ServerManager::isValidConfigBlock(std::string& config_block)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(config_block, '\n'), ' ');
	std::string key[4] = {"SOFTWARE_NAME", "SOFTWARE_VERSION", "HTTP_VERSION", "CGI_VERSION"};
	if (map_block.size() != 4)
		return (false);
	for (int i = 0; i < 4; ++i) {
		if (!ft::hasKey(map_block, key[i]))
			return (false);
	}
	if (map_block[key[0]].empty())
		return (false);
	if (map_block[key[1]].empty())
		return (false);
	if (map_block[key[2]] != "1.1")
		return (false);
	if (map_block[key[3]] != "1.1")
		return (false);
	return (true);
}

/*
** function: isValidServerBlock
** 1. check entity count without duplicate
** 2. check ip range ([0~255] * 4)
** 3. check port range (80, 443, 1024 ~ 49151)
** 4. check uri limit size
** 5. check header limit size
** 6. check body limit size
*/

bool
ServerManager::isValidServerBlock(std::string& server_block)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(server_block, '\n'), ' ');
	std::string key[6] = {"host", "port", "REQUEST_URI_LIMIT_SIZE", "REQUEST_HEADER_LIMIT_SIZE", \
	"DEFAULT_ERROR_PAGE", "LIMIT_CLIENT_BODY_SIZE"};

	if (map_block.size() < 6 || map_block.size() > 7)
		return (false);
	for (int i = 0; i < 6; ++i) {
		if (!ft::hasKey(map_block, key[i]))
			return (false);
	}
	if (map_block.size() == 7 && !ft::hasKey(map_block, "server_name"))
		return (false);

	std::vector<std::string> ip_tokens = ft::split(map_block.find(key[0])->second, '.');
	if (ip_tokens.size() != 4 || !std::all_of(ip_tokens.begin(), ip_tokens.end(), isValidIpByte))
		return (false);

	int port = std::atoi(map_block.find(key[1])->second.c_str());
	if (port != 80 && port != 443 && (port < 1024 || port > 49151))
		return (false);

	int uri_limit = std::atoi(map_block.find(key[2])->second.c_str());
	if (uri_limit < REQUEST_URI_LIMIT_SIZE_MIN || uri_limit > REQUEST_URI_LIMIT_SIZE_MAX)
		return (false);

	int header_limit = std::atoi(map_block.find(key[3])->second.c_str());
	if (header_limit < REQUEST_HEADER_LIMIT_SIZE_MIN || header_limit > REQUEST_HEADER_LIMIT_SIZE_MAX)
		return (false);

	int fd;
	if ((fd = open(map_block.find(key[4])->second.c_str(), O_RDONLY)) == -1)
		return (false);
	close(fd);

	int body_limit = std::atoi(map_block.find(key[5])->second.c_str());
	if (body_limit < 0 || body_limit > LIMIT_CLIENT_BODY_SIZE_MAX)
		return (false);

	return (true);
}

/*
** function: isValidLocationBlock
** 1. check entity count without duplicate or empty value
** 2. check location expression count and start with '/'
** 3. check root path is valid directory and end without '/'
** 4. check auth file path is valid file with realm string
** 5. check header limit size
** 6. check body limit size
*/

bool
ServerManager::isValidLocationBlock(std::string& location_block)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(location_block, '\n'), ' ');
	std::string key[] = {"location", "root", "allow_method", "auth_basic_realm", \
	"auth_basic_file", "index", "cgi", "autoindex", "limit_client_body_size"};
	std::set<std::string> key_set(key, key + sizeof(key) / sizeof(key[0]));

	if (map_block.size() < 2 || map_block.size() > 9)
		return (false);
	if (!ft::hasKey(map_block, "location") || !ft::hasKey(map_block, "root"))
		return (false);
	for (std::map<std::string, std::string>::iterator it = map_block.begin(); it != map_block.end(); ++it) {
		if (!ft::hasKey(key_set, it->first) || it->second.empty())
			return (false);
	}

	std::vector<std::string> location = ft::split(ft::rtrim(map_block[key[0]], " \t{"), ' ');
	if (location.size() != 1 || location[0].empty() || location[0][0] != '/')
		return (false);

	struct stat buf;
	std::string root = map_block[key[1]];
	stat(root.c_str(), &buf);
	if (!S_ISDIR(buf.st_mode) || root.empty() || (root != "/" && root.size() > 1 && root[root.size() - 1] == '/'))
		return (false);

	if ((ft::hasKey(map_block, key[3]) && !ft::hasKey(map_block, key[4]))
	|| (!ft::hasKey(map_block, key[3]) && ft::hasKey(map_block, key[4])))
		return (false);
	if (ft::hasKey(map_block, key[4]))
	{
		stat(map_block[key[4]].c_str(), &buf);
		if (!S_ISREG(buf.st_mode))
			return (false);
	}

	if (ft::hasKey(map_block, key[2]))
	{
		std::set<std::string> data_set = ft::stringVectorToSet(ft::split(map_block[key[2]], ' '));
		std::string method[] = {"GET", "POST", "HEAD", "PUT", "DELETE", "TRACE", "OPTIONS"};
		std::set<std::string> method_set(method, method + sizeof(method) / sizeof(method[0]));
		if (data_set.empty())
			return (false);
		for (std::set<std::string>::iterator it = data_set.begin(); it != data_set.end(); ++it) {
			if ((*it).empty() || !ft::hasKey(method_set, *it))
				return (false);
		}
	}

	if (ft::hasKey(map_block, key[6])) {
		std::set<std::string> cgi_set = ft::stringVectorToSet(ft::split(map_block[key[6]], ' '));
		if (cgi_set.empty() || !std::all_of(cgi_set.begin(), cgi_set.end(), isValidCgi))
			return (false);
	}

	if (ft::hasKey(map_block, key[7])) {
		std::string autoindex = map_block[key[7]];
		if (autoindex != "on" && autoindex != "off")
			return (false);
	}

	if (ft::hasKey(map_block, key[8])) {
		std::string size = map_block[key[8]];
		if (size.empty() || !std::all_of(size.begin(), size.end(), isDigit))
			return (false);
	}

	return (true);
}


/* ************************************************************************** */
/* ------------------------------ FD FUNCTION ------------------------------- */
/* ************************************************************************** */

void
ServerManager::fdSet(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdSet(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdSet(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdSet(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdSet(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_COPY_SET)
		ft::fdSet(fd, &this->m_error_copy_set);
}

void
ServerManager::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdZero(&this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdZero(&this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdZero(&this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdZero(&this->m_read_copy_set);
	else if (fdset == ERROR_COPY_SET)
		ft::fdZero(&this->m_error_copy_set);
}

void
ServerManager::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdClr(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdClr(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdClr(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdClr(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_COPY_SET)
		ft::fdClr(fd, &this->m_error_copy_set);
}

bool
ServerManager::fdIsset(int fd, SetType fdset)
{
	bool ret = false;

	if (fdset == WRITE_SET)
		ret = ft::fdIsset(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ret = ft::fdIsset(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ret = ft::fdIsset(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ret = ft::fdIsset(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_COPY_SET)
		ret = ft::fdIsset(fd, &this->m_error_copy_set);
	return (ret);
}

void
ServerManager::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_write_copy_set);
		this->m_write_copy_set = this->m_write_set;
	}
	if (fdset == READ_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_read_copy_set);
		this->m_read_copy_set = this->m_read_set;
	}
	if (fdset == ERROR_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_error_copy_set);
		this->m_error_copy_set = this->m_read_set;
	}
}

void
ServerManager::resetMaxFd(int new_max_fd)
{
	if (new_max_fd != -1)
		set_m_max_fd(new_max_fd);
	else
	{
		for (int i = get_m_max_fd(); i >= 0; --i)
		{
			if (fdIsset(i, READ_SET) || fdIsset(i, WRITE_SET))
			{
				m_max_fd = i;
				break ;
			}
		}
	}
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
ServerManager::createServer(const std::string& configuration_file_path, char **env)
{
	std::string config_string = ft::getStringFromFile(configuration_file_path);
	std::string config_block;
	std::vector<std::string> server_strings;

	if (!splitConfigString(config_string, config_block, server_strings))
		throw (std::invalid_argument("Failed to split configuration string"));
	if (!isValidConfigBlock(config_block))
		throw (std::invalid_argument("Config block is not valid."));
	m_config = Config(config_block, env);
	for (size_t i = 0; i < server_strings.size(); ++i)
	{
		std::string server_block;
		std::vector<std::string> location_blocks;
		if (!splitServerString(server_strings[i], server_block, location_blocks))
			throw (std::invalid_argument("Failed to split Sever string(" + ft::to_string(i) + ")"));
		if (!isValidServerBlock(server_block))
			throw (std::invalid_argument("Server block(" + ft::to_string(i) + ") is not valid."));
		for (size_t j = 0; j < location_blocks.size(); ++j) {
			if (!isValidLocationBlock(location_blocks[j]))
				throw (std::invalid_argument("Location block(" + ft::to_string(i) \
				+ "-" + ft::to_string(j) + ") is not valid."));
		}
		m_servers.push_back(Server(this, server_block, location_blocks, &this->m_config));
		m_server_fdset.insert(m_servers.back().get_m_fd());
	}
	writeCreateServerLog();
}

bool g_live;

void
changeSignal(int sig)
{
	ft::log(ServerManager::access_fd, -1, "signal execute");
	(void)sig;
	g_live = false;
}

void
ServerManager::closeOldConnection(std::vector<Server>::iterator server_it)
{
	std::map<int, Connection>::const_iterator it = server_it->get_m_connections().begin();
	while (it != server_it->get_m_connections().end())
	{
		int fd = it->first;
		if (!ft::hasKey(m_server_fdset, fd) && it->second.isOverTime())
		{
			++it;
			// std::cout << "close connection because connection old" << std::endl;
			server_it->closeConnection(fd);
		} else
			++it;
	}
}

void
ServerManager::runServer()
{
	signal(SIGINT, changeSignal);

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	g_live = true;
	while (g_live)
	{
		int cnt;
		fdCopy(ALL_SET);

		if ((cnt = select(this->m_max_fd + 1, &this->m_read_copy_set, &this->m_write_copy_set, \
		&this->m_error_copy_set, &timeout)) == -1)
		{
			perror("why?");
			ft::log(ServerManager::access_fd, ServerManager::error_fd, "[Failed][Function]Select function failed(return -1)");
			throw std::runtime_error("select error");
		}
		else if (cnt == 0)
			continue ;
		writeServerHealthLog();
		for (std::vector<Server>::iterator it = m_servers.begin() ; it != m_servers.end() ; ++it)
		{
			it->run();
			closeOldConnection(it);
		}
	}
	exitServer("server exited.\n");
}

void
ServerManager::exitServer(const std::string& error_msg)
{
	std::cout << error_msg << std::endl;
	close(ServerManager::access_fd);
	close(ServerManager::error_fd);
	for (int i = 0; i < m_max_fd; ++i)
	{
		if (fdIsset(i, READ_SET))
			close(i);
	}
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
ServerManager::openLog()
{
	if ((ServerManager::access_fd = open(ACCESS_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
		return ;
	if ((ServerManager::error_fd = open(ERROR_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755)) == -1)
		return ;
}

void
ServerManager::writeCreateServerLog()
{
	std::string text = "[Created][Servers]" + ft::to_string(m_servers.size()) + " servers created successfully.\n";
	ft::log(ServerManager::access_fd, -1, text);
	return ;
}

void
ServerManager::writeServerHealthLog(bool ignore_interval)
{
	if (ignore_interval == false && !ft::isRightTime(SERVER_HEALTH_LOG_SECOND))
		return ;
	(void)ignore_interval;
	int fd = ServerManager::access_fd;
	std::string text = "[HealthCheck][Server][Max_fd:" + ft::to_string(m_max_fd) \
	+ "][Connection:" + ft::getSetFdString(m_max_fd, &m_read_set) + "][Response:" + ft::getSetFdString(m_max_fd, &m_write_set) + "]\n";
	ft::log(fd, -1, text);
	return ;
}
