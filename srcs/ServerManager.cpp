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

void ServerManager::printFdSets()
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
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool
ServerManager::splitConfigString(std::string config_string, std::string& config_block, \
std::vector<std::string>& server_strings)
{
	std::cout << config_string << std::endl;
	std::vector<std::string> lines = ft::split(config_string);
	bool is_server_line = false;
	bool is_first_server_line = false;
	int server_index = 0;
	
	for (int i = 0; i < lines.size(); ++i)
	{
		std::string line = ft::rtrim(lines[i], " \t");
		if (line.empty())
			continue ;
		if (is_server_line == false)
		{
			if (line != "server {")
				config_block.append(line + "\n");
			else
			{
				is_server_line = true;
				is_first_server_line = true;
			}
		}
		else
		{
			if (line != "}")
			{
				if (is_first_server_line)
				{
					server_strings.push_back(line + "\n");
					is_first_server_line = false;
				}
				else
					server_strings[server_index].append(line + "\n");
			}
			else
			{
				is_server_line = false;
				++server_index;
			}
		}
	}
	return (!config_block.empty() && server_strings.size() != 0);
}

bool
ServerManager::splitServerString(std::string server_string, std::string& server_block, \
std::vector<std::string>& location_blocks)
{
	std::vector<std::string> lines = ft::split(server_string);
	bool is_location_line = false;
	int location_index = 0;
	
	for (int i = 0; i < lines.size(); ++i)
	{
		std::string line = ft::trim(lines[i], " \t");
		if (line.empty())
			continue ;
		if (is_location_line == false)
		{
			if (line.substr(0, 9) != "location ")
				server_block.append(line + "\n");
			else {
				is_location_line = true;
				location_blocks.push_back(line + "\n");
			}
		}
		else
		{
			if (line != "}")
				location_blocks[location_index].append(line + "\n");
			else
			{
				is_location_line = false;
				++location_index;
			}
		}
	}
	return (!server_block.empty() && location_blocks.size() != 0);
}

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
	if (map_block.find(key[0])->second.empty())
		return (false);
	if (map_block.find(key[1])->second.empty())
		return (false);
	if (map_block.find(key[2])->second != "1.1")
		return (false);
	if (map_block.find(key[3])->second != "1.1")
		return (false);
	return (true);
}

/*
** 1. check entity count without duplicate
** 2. check ip range ([0~255] * 4)
** 3. check port range (80, 443, 1024 ~ 49151)
** 4. check uri limit size
** 5. check header limit size
** 6. check body limit size
*/

namespace {
	bool isValidPort(std::string s) { return ((std::atoi(s.c_str()) >= 0) && (std::atoi(s.c_str()) <= 255)); }
	bool isValidCgi(std::string data) { return (!data.empty() && data[0] == '.'); }
}

bool
ServerManager::isValidServerBlock(std::string& server_block)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(server_block, '\n'), ' ');
	std::string key[6] = {"host", "port", "REQUEST_URI_LIMIT_SIZE", "REQUEST_HEADER_LIMIT_SIZE", \
	"DEFAULT_ERROR_PAGE", "LIMIT_CLIENT_BODY_SIZE"};
	
	std::cout << server_block << std::endl;
	std::cout << 1 << std::endl;
	if (map_block.size() < 6 || map_block.size() > 7)
		return (false);
	
	std::cout << 2 << std::endl;
	for (int i = 0; i < 6; ++i) {
		if (!ft::hasKey(map_block, key[i]))
			return (false);
	}
	
	std::cout << 3 << std::endl;
	if (map_block.size() == 7 && !ft::hasKey(map_block, "server_name"))
		return (false);

	std::cout << 4 << std::endl;
	std::vector<std::string> port_tokens = ft::split(map_block.find(key[0])->second, '.');
	if (port_tokens.size() != 4 || !std::all_of(port_tokens.begin(), port_tokens.end(), isValidPort))
		return (false);

	std::cout << 5 << std::endl;
	int port = std::atoi(map_block.find(key[1])->second.c_str());
	if (port < 0 || (port != 80 && port != 443 && port < 1024 && port > 49151))
		return (false);
	
	std::cout << 6 << std::endl;
	int uri_limit = std::atoi(map_block.find(key[2])->second.c_str());
	if (uri_limit < REQUEST_URI_LIMIT_SIZE_MIN || uri_limit > REQUEST_URI_LIMIT_SIZE_MAX)
		return (false);
	
	std::cout << 7 << std::endl;
	int header_limit = std::atoi(map_block.find(key[3])->second.c_str());
	if (header_limit < REQUEST_HEADER_LIMIT_SIZE_MIN || header_limit > REQUEST_HEADER_LIMIT_SIZE_MAX)
		return (false);
	
	std::cout << 8 << std::endl;
	int fd;
	if ((fd = open(map_block.find(key[4])->second.c_str(), O_RDONLY)) == -1)
		return (false);
	close(fd);
	
	std::cout << 9 << std::endl;
	int body_limit = std::atoi(map_block.find(key[5])->second.c_str());
	if (body_limit < 0 || body_limit > LIMIT_CLIENT_BODY_SIZE_MAX)
		return (false);

	return (true);
}

bool
ServerManager::isValidLocationBlock(std::string& location_block)
{
	std::cout << location_block << std::endl;
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(location_block, '\n'), ' ');
	
	std::cout << "a" << std::endl;
	if (map_block.size() < 2 || map_block.size() > 8)
		return (false);

	std::cout << "b" << std::endl;
	std::set<std::string>set_block;
	for (std::map<std::string, std::string>::iterator it = map_block.begin(); it != map_block.end(); ++it)
		set_block.insert(it->first);
	std::string key[8] = {"location", "root", "allow_method", "auth_basic_realm", \
	"auth_basic_file", "index", "cgi", "autoindex"};
	std::set<std::string> key_set;
	for (int i = 0; i < 8; ++i)
		key_set.insert(key[i]);

	std::cout << "c" << std::endl;
	if (!ft::hasKey(map_block, "location") || !ft::hasKey(map_block, "root"))
		return (false);
	for (std::set<std::string>::iterator it = set_block.begin(); it != set_block.end(); ++it) {
		if (!ft::hasKey(key_set, *it) || map_block.find(*it)->second.empty())
			return (false);
	} 

	std::cout << "d" << std::endl;
	std::vector<std::string> location = ft::split(ft::rtrim(map_block.find(key[0])->second, " \t{"), ' ');
	if (location.size() != 1 || location[0].empty() || location[0][0] != '/')
		return (false);
	
	std::cout << "e" << std::endl;
	struct stat buf;
	std::string root = map_block.find(key[1])->second;
	stat(root.c_str(), &buf);
	if (!S_ISDIR(buf.st_mode) || root.empty() || (root != "/" && root.size() > 1 && root[root.size() - 1] == '/'))
		return (false);
	
	std::cout << "f" << std::endl;
	if (ft::hasKey(map_block, key[4]))
	{
		stat(map_block.find(key[4])->second.c_str(), &buf);
		if (!S_ISREG(buf.st_mode))
			return (false);
	}

	std::cout << "g" << std::endl;
	if (ft::hasKey(map_block, key[2]))
	{
		std::set<std::string> data_set = ft::stringVectorToSet(ft::split(map_block.find(key[2])->second, ' '));
		std::string method[7] = {"GET", "POST", "HEAD", "PUT", "DELETE", "TRACE", "OPTIONS"};
		std::set<std::string> method_set;
		for (int i = 0; i < 7; ++i)
			method_set.insert(method[i]);
	
		for (std::set<std::string>::iterator it = data_set.begin(); it != data_set.end(); ++it) {
			std::cout << "[" << *it << "]" << std::endl;
			if ((*it).empty() || !ft::hasKey(method_set, *it))
				return (false);
			std::cout << "[" << *it << "]" << std::endl;
		} 
	}

	std::cout << "h" << std::endl;
	if (ft::hasKey(map_block, key[6])) {
		std::set<std::string> cgi_set = ft::stringVectorToSet(ft::split(map_block.find(key[6])->second, ' '));
		if (!std::all_of(cgi_set.begin(), cgi_set.end(), isValidCgi))
			return (false);
	}
	
	if (ft::hasKey(map_block, key[7])) {
		std::string autoindex = map_block.find(key[7])->second;
		if (autoindex != "on" && autoindex != "off")
			return (false);
	}

	return (true);
}

void
parseConfigBlock(std::string& config_block)
{

}

void
parseServerBlock(std::string& server_block)
{

}

void
parseLocationBlock(std::string& location_block)
{

}

void ServerManager::fdSet(int fd, SetType fdset)
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

void ServerManager::fdZero(SetType fdset)
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

void ServerManager::fdClear(int fd, SetType fdset)
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

bool ServerManager::fdIsset(int fd, SetType fdset)
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

void ServerManager::fdCopy(SetType fdset)
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
