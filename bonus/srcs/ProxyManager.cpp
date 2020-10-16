#include "ProxyManager.hpp"

bool g_proxy_live;

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

int ProxyManager::log_fd = -1;

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

ProxyManager::ProxyManager()
{
    this->m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);
}

ProxyManager::ProxyManager(const ProxyManager& obj)
{
	m_proxys = obj.m_proxys;
	m_proxy_fdset = obj.m_proxy_fdset;
	m_config = obj.m_config;
	m_max_fd = obj.m_max_fd;
	m_read_set = obj.m_read_set;
	m_read_copy_set = obj.m_read_copy_set;
	m_write_set = obj.m_write_set;
	m_write_copy_set = obj.m_write_copy_set;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

ProxyManager::~ProxyManager()
{
    this->m_max_fd = 0;
    ft::fdZero(&m_read_set);
    ft::fdZero(&m_read_copy_set);
    ft::fdZero(&m_write_set);
    ft::fdZero(&m_write_copy_set);
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

ProxyManager& ProxyManager::operator=(const ProxyManager& obj)
{
	if (this == &obj)
		return (*this);
	m_proxys = obj.m_proxys;
	m_proxy_fdset = obj.m_proxy_fdset;
	m_config = obj.m_config;
	m_max_fd = obj.m_max_fd;
	m_read_set = obj.m_read_set;
	m_read_copy_set = obj.m_read_copy_set;
	m_write_set = obj.m_write_set;
	m_write_copy_set = obj.m_write_copy_set;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const ProxyManager&) {
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const std::vector<Proxy>& ProxyManager::get_m_proxys() const { return (this->m_proxys); }
const std::set<int>& ProxyManager::get_m_proxy_fdset() const { return (this->m_proxy_fdset); }
Config ProxyManager::get_m_config() const { return (this->m_config); }
int ProxyManager::get_m_max_fd() const { return (this->m_max_fd); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void ProxyManager::set_m_max_fd(int max_fd) { this->m_max_fd = max_fd; }
void ProxyManager::set_m_config(const Config& config) { this->m_config = config; }

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
}

bool
ProxyManager::splitConfigString(std::string config_string, std::string& config_block, \
std::vector<std::string>& proxy_blocks)
{
	std::vector<std::string> lines = ft::split(config_string);
	for (size_t i = 0; i < lines.size(); ++i)
		lines[i] = ft::trim(lines[i], " \t");
	proxy_blocks = groupLineWithCondition(lines, "proxy {", "}", INCLUDE_NOT);
	config_block = ft::containerToString(lines, "\n");

	return (!config_block.empty() && proxy_blocks.size() != 0);
}

/*
** function: isValidConfigBlock
** 1. check every entity without duplicate
** 2. check 'SOFTWARE_NAME' and 'SOFTWARE_VERSION' NOT EMPTY
** 3. check 'HTTP_VERSION' and 'CGI_VERSION' is 1.1
*/

bool
ProxyManager::isValidConfigBlock(std::string& config_block)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(config_block, '\n'), ' ');
	std::string key[4] = {"SOFTWARE_NAME", "SOFTWARE_VERSION", "HTTP_VERSION", "CGI_VERSION"};
	if (map_block.size() < 4)
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

bool
ProxyManager::isValidProxyBlock(std::string& proxy_block, Config& config)
{
	std::map<std::string, std::string>map_block = ft::stringVectorToMap(ft::split(proxy_block, '\n'), ' ');
	std::string key[] = {"host", "port", "server", "cache", "filter", "log-if"};
	std::set<std::string> key_set(key, key + 6);
	if (map_block.size() < 3 || map_block.size() > 6)
		return (false);
	for (int i = 0; i < 3; ++i) {
		if (!ft::hasKey(map_block, key[i]))
			return (false);
	}
	for (std::map<std::string, std::string>::iterator it = map_block.begin(); it != map_block.end(); ++it) {
		if (!ft::hasKey(key_set, it->first))
			return (false);
	}

	std::vector<std::string> ip_tokens = ft::split(map_block.find(key[0])->second, '.');
	if (ip_tokens.size() != 4 || !std::all_of(ip_tokens.begin(), ip_tokens.end(), isValidIpByte))
		return (false);

	std::vector<std::string> ports = ft::split(ft::trim(map_block["port"], "[]"), ',');
	if (ports.size() > 1)
		return (false);
	int port = std::atoi(ft::trim(ports[0], " ").c_str());
	if (port != 80 && port != 443 && (port < 1024 || port > 49151))
		return (false);

	std::string server_tokens = ft::trim(map_block["server"], "[]");
	std::string server_host = server_tokens.substr(0, server_tokens.find(":"));
	std::vector<std::string> server_ports = ft::split(server_tokens.substr(server_tokens.find(":") + 1), '|');
	if (!config.is_on_plugin_array_var() && server_ports.size() > 1)
		return (false);
	for (size_t i = 0; i < server_ports.size(); ++i)
	{
		int port = std::atoi(ft::trim(server_ports[i], " ").c_str());
		if (port != 80 && port != 443 && (port < 1024 || port > 49151))
			return (false);
	}
	if (ft::hasKey(map_block, "cache")) {
		if (!m_config.is_on_plugin_cache())
			return (false);
		std::string cache = map_block["cache"];
		if (cache != "on" && cache != "On" && cache != "off" && cache != "Off")
			return (false);
	}
	if (ft::hasKey(map_block, "filter")) {
		if (!m_config.is_on_plugin_filter())
			return (false);
		std::vector<std::string> filter_querys = ft::split(ft::trim(map_block["filter"], "{} \t\n"), ',');
		if (filter_querys.size() < 1 || (!config.is_on_plugin_array_var() && filter_querys.size() > 1))
			return (false);

		for (size_t i = 0; i < filter_querys.size(); ++i)
		{
			std::vector<std::string> query = ft::split(ft::trim(filter_querys[i], " []\t\n"), ':');
			if (query.size() != 2)
				return (false);
			std::string key = query[0];
			query = ft::split(ft::trim(query[1], " "), '|');
			if (query.size() < 1)
				return (false);
			if (!config.is_on_plugin_array_var() && filter_querys.size() > 1)
				return (false);
		}
	}
	if (ft::hasKey(map_block, "log-if")) {
		if (!m_config.is_on_plugin_log_if())
			return (false);
		std::vector<std::string> log_querys = ft::split(ft::trim(map_block["log-if"], "{} \t\n"), ',');
		if (log_querys.size() < 1 || (!config.is_on_plugin_array_var() && log_querys.size() > 1))
			return (false);
		for (size_t i = 0; i < log_querys.size(); ++i)
		{
			std::vector<std::string> query = ft::split(ft::trim(log_querys[i], " []\t\n"), '|');
			if (!config.is_on_plugin_array_var() && query.size() > 1)
				return (false);
			for (size_t j = 0; j < query.size(); ++j)
			{
				if (ft::split(query[j], ':').size() != 2)
					return (false);
			}
		}
	}
	return (true);
}

/* ************************************************************************** */
/* ------------------------------ FD FUNCTION ------------------------------- */
/* ************************************************************************** */

void
ProxyManager::fdSet(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdSet(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdSet(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdSet(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdSet(fd, &this->m_read_copy_set);
}

void
ProxyManager::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdZero(&this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdZero(&this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdZero(&this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdZero(&this->m_read_copy_set);
}

void
ProxyManager::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdClr(fd, &this->m_write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdClr(fd, &this->m_write_copy_set);
	else if (fdset == READ_SET)
		ft::fdClr(fd, &this->m_read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdClr(fd, &this->m_read_copy_set);
}

bool
ProxyManager::fdIsset(int fd, SetType fdset)
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
	return (ret);
}

void
ProxyManager::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_write_copy_set);
		this->m_write_copy_set = this->m_write_set;
	}
	if (fdset == READ_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_read_copy_set);
		this->m_read_copy_set = this->m_read_set;
	}
}

void
ProxyManager::resetMaxFd(int new_max_fd)
{
	if (new_max_fd != -1)
		set_m_max_fd(new_max_fd);
	else
	{
		for (int i = 512; i >= 0; --i)
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
ProxyManager::createServer(const std::string& configuration_file_path, char **env)
{
	std::string config_string = ft::getStringFromFile(configuration_file_path);
	std::string config_block;
	std::vector<std::string> proxy_blocks;

	if (!splitConfigString(config_string, config_block, proxy_blocks))
		throw (std::invalid_argument("Failed to split configuration string"));
	if (config_block.find("server {") != std::string::npos)
		config_block = config_block.substr(0, config_block.find("server {"));
	if (!isValidConfigBlock(config_block))
		throw (std::invalid_argument("Config block is not valid."));
	m_config = Config(config_block, env);
	for (size_t i = 0; i < proxy_blocks.size(); ++i)
	{
		if (!isValidProxyBlock(proxy_blocks[i], m_config))
			throw (std::invalid_argument("Proxy block(" + ft::to_string(i) + ") is not valid."));
		m_proxys.push_back(Proxy(this, proxy_blocks[i]));
		m_proxy_fdset.insert(m_proxys.back().get_m_fd());
		fdSet(m_proxys.back().get_m_fd(), READ_SET);
	}
}

namespace {
	void
	changeSignal(int sig)
	{
		ft::log(ProxyManager::log_fd, ft::getTimestamp() + "[Detected] Exit Signal detected.\n");
		g_proxy_live = false;
		(void)sig;
	}
}

void
ProxyManager::runServer()
{
	g_proxy_live = true;
	signal(SIGINT, changeSignal);

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	while (g_proxy_live)
	{
		int cnt;
		fdCopy(ALL_SET);
		resetMaxFd();

		if ((cnt = select(this->m_max_fd + 1, &this->m_read_copy_set, &this->m_write_copy_set, NULL, &timeout)) == -1)
		{
			perror("select fail:");
			ft::log(ProxyManager::log_fd, "[Failed][Function]Select function failed(return -1)");
			throw std::runtime_error("select error");
		}
		else if (cnt == 0)
			continue ;
		for (std::vector<Proxy>::iterator it = m_proxys.begin() ; it != m_proxys.end() ; ++it)
			it->run();
	}
	exitServer("proxy exited.\n");
}

void
ProxyManager::exitServer(const std::string& error_msg)
{
	close(ProxyManager::log_fd);
	std::cout << error_msg << std::endl;
	exit(EXIT_FAILURE);
}

/* ************************************************************************** */
/* ------------------------------- LOG FUNCTION ----------------------------- */
/* ************************************************************************** */

void
ProxyManager::openLog() {
	ProxyManager::log_fd = open(PROXY_LOG_PATH, O_WRONLY | O_CREAT | O_TRUNC, 0755);
}
