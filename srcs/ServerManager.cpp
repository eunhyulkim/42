#include "ServerManager.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::ServerManager()
{
    this->m_max_fd = 0;
    FD_ZERO(&m_read_set);
    FD_ZERO(&m_read_copy_set);
    FD_ZERO(&m_write_set);
    FD_ZERO(&m_write_copy_set);
    FD_ZERO(&m_error_set);
    FD_ZERO(&m_error_copy_set);
}

ServerManager::ServerManager(const ServerManager& copy) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ServerManager::~ServerManager()
{
    this->m_max_fd = 0;
    FD_ZERO(&m_read_set);
    FD_ZERO(&m_read_copy_set);
    FD_ZERO(&m_write_set);
    FD_ZERO(&m_write_copy_set);
    FD_ZERO(&m_error_set);
    FD_ZERO(&m_error_copy_set);
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ServerManager& ServerManager::operator=(const ServerManager& obj)
{
	if (this == &obj)
		return (*this);
	return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

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
		for (int i = 0; i < lines.size(); ++i)
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
	
	bool isValidIpByte(std::string s) { return ((std::stoi(s) >= 0) && (std::stoi(s) <= 255)); }
	bool isValidCgi(std::string data) { return (!data.empty() && data[0] == '.'); }
}

bool
ServerManager::splitConfigString(std::string config_string, std::string& config_block, \
std::vector<std::string>& server_strings)
{
	std::vector<std::string> lines = ft::split(config_string);
	for (int i = 0; i < lines.size(); ++i)
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
	for (int i = 0; i < lines.size(); ++i)
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
	"auth_basic_file", "index", "cgi", "autoindex"};
	std::set<std::string> key_set(key, key + sizeof(key) / sizeof(key[0]));
	
	if (map_block.size() < 2 || map_block.size() > 8)
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
		for (std::set<std::string>::iterator it = data_set.begin(); it != data_set.end(); ++it) {
			if ((*it).empty() || !ft::hasKey(method_set, *it))
				return (false);
		} 
	}

	if (ft::hasKey(map_block, key[6])) {
		std::set<std::string> cgi_set = ft::stringVectorToSet(ft::split(map_block[key[6]], ' '));
		if (!std::all_of(cgi_set.begin(), cgi_set.end(), isValidCgi))
			return (false);
	}
	
	if (ft::hasKey(map_block, key[7])) {
		std::string autoindex = map_block[key[7]];
		if (autoindex != "on" && autoindex != "off")
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
		FD_SET(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_SET(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_SET(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_SET(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_SET(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_SET(fd, &this->m_error_copy_set);
}

void
ServerManager::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET)
		FD_ZERO(&this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_ZERO(&this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_ZERO(&this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_ZERO(&this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_ZERO(&this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_ZERO(&this->m_error_copy_set);
}

void
ServerManager::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		FD_CLR(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		FD_CLR(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		FD_CLR(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		FD_CLR(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		FD_CLR(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		FD_CLR(fd, &this->m_error_copy_set);
}

bool
ServerManager::fdIsset(int fd, SetType fdset)
{
	bool ret = false;

	if (fdset == WRITE_SET)
		ret = FD_ISSET(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ret = FD_ISSET(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ret = FD_ISSET(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ret = FD_ISSET(fd, &this->m_read_copy_set);
	else if (fdset == ERROR_SET)
		ret = FD_ISSET(fd, &this->m_error_set);
	else if (fdset == ERROR_COPY_SET)
		ret = FD_ISSET(fd, &this->m_error_copy_set);
	return (ret);
}

void
ServerManager::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET) {
		FD_ZERO(&this->m_write_copy_set);
		this->m_write_copy_set = this->m_write_set;
	} else if (fdset == READ_SET) {
		FD_ZERO(&this->m_read_copy_set);
		this->m_read_copy_set = this->m_read_set;
	} else if (fdset == ERROR_SET) {
		FD_ZERO(&this->m_error_copy_set);
		this->m_error_copy_set = this->m_error_set;
	}
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

namespace
{
	void
	printFdSet(fd_set s, int max_fd)
	{
		bool first = true;
		for (int i = 0; i <= max_fd; ++i)
		{
			if (FD_ISSET(i, &s))
			{
				if (!first) {
					std::cout << " ";
				}
				first = false;
				std::cout << i;
			}
		}
	}
}

void
ServerManager::printFdSets()
{
	std::cout << "MAX_FD: " << this->m_max_fd << std::endl;
	std::cout << "[SET_ERROR_FD]" << std::endl;
	printFdSet(this->m_error_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_ERROR_COPY_FD]" << std::endl;
	printFdSet(this->m_error_copy_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_READ_FD]" << std::endl;
	printFdSet(this->m_read_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_READ_COPY_FD]" << std::endl;
	printFdSet(this->m_read_copy_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_WRITE_FD]" << std::endl;
	printFdSet(this->m_write_set, this->m_max_fd); std::cout << std::endl;
	std::cout << "[SET_WRITE_COPY_FD]" << std::endl;
	printFdSet(this->m_write_copy_set, this->m_max_fd); std::cout << std::endl;
	return ;
}

void
ServerManager::createServer(const std::string& configuration_file_path)
{
	std::string config_string = ft::getStringFromFile(configuration_file_path);
	std::string config_block;
	std::vector<std::string> server_strings;

	if (splitConfigString(config_string, config_block, server_strings))
		throw (std::invalid_argument("Failed to split configuration string"));
	if (!isValidConfigBlock(config_block))
		throw (std::invalid_argument("Config block is not valid."));
	for (int i = 0; i < server_strings.size(); ++i)
	{
		std::string server_block;
		std::vector<std::string> location_blocks;
		if (!splitServerString(server_strings[i], server_block, location_blocks))
			throw (std::invalid_argument("Failed to split Sever string(" + std::to_string(i) + ")"));
		if (!isValidServerBlock(server_block))
			throw (std::invalid_argument("Server block(" + std::to_string(i) + ") is not valid."));
		for (int j = 0; j < location_blocks.size(); ++j) {
			if (!isValidLocationBlock(location_blocks[j]))
				throw (std::invalid_argument("Location block(" + std::to_string(i) \
				+ "-" + std::to_string(j) + ") is not valid."));
		}
		m_servers.push_back(Server(this, server_block, location_blocks, &this->m_config));
	}
}

bool g_live;

void
changeSignal(int sig)
{
	(void)sig;
	g_live = false;
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
		this->m_read_copy_set = this->m_read_set;
		this->m_write_copy_set = this->m_write_set;
		this->m_error_copy_set = this->m_error_set;

		int n = select(this->m_max_fd, &this->m_read_copy_set, &this->m_write_copy_set, &this->m_error_copy_set, &timeout);
		if (n == -1)
		{
			throw std::runtime_error("select error");
		}
		else if (n == 0)
		{
			continue ;
		}
		for (std::vector<Server>::iterator it = m_servers.begin() ; it != m_servers.end() ; ++it)
		{
			it->run();

			std::map<int, Connection>::const_iterator it2 = it->get_m_connections().begin();
			while (it2 != it->get_m_connections().end())
			{
				int fd = it2->first;
				
				if (it2->second.isOverTime())
					it->closeConnection(fd);
			}
		}
	}
}

void
ServerManager::exitServer(const std::string& error_msg)
{
	std::cout << error_msg << std::endl;
	exit(EXIT_FAILURE);
}
