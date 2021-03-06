#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <fcntl.h>
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <dirent.h>
# include <fcntl.h>
# include <unistd.h>
# include <pthread.h>

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <algorithm>

# include <string>
# include <vector>
# include <queue>
# include <set>
# include <map>
# include <random>

# include <regex>

# include "base64.hpp"
# include "HtmlWriter.hpp"
# include "libft.hpp"

# define DEFAULT_CONFIG_FILE_PATH "config/default.conf"
# define BONUS_CONFIG_FILE_PATH "config/bonus.conf"
# define SERVER_LOG_PATH "log/health_check.log"
# define PROXY_LOG_PATH "log/proxy.log"
# define SERVER_ALLOW_METHODS "GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE"

# define REQUEST_URI_LIMIT_SIZE_MIN 64
# define REQUEST_URI_LIMIT_SIZE_MAX 8192
# define REQUEST_HEADER_LIMIT_SIZE_MIN 64
# define REQUEST_HEADER_LIMIT_SIZE_MAX 8192
# define LIMIT_CLIENT_BODY_SIZE_MAX 200000000

# define CONNECTION_OLD_SECOND 2 // 10 // 60000
# define REQUEST_TIMEOVER_SECOND 30 // 30 // 45000
# define SEND_RESPONSE_AT_ONCE 5
# define CGI_SUCCESS_CODE 299
# define CGI_META_VARIABLE_COUNT 15
# define STACKED_RESPONSE_COUNT 5

# define BUFFER_SIZE 65536
# define CACHE_SIZE 20
# define CHUNKED_TRANSFER_BUFFER_SIZE 65536
# define GENERAL_TRANSFER_BUFFER_SIZE 65536

# define SERVER_HEALTH_LOG_SECOND 3

/// BONUS

# define WORKER_COUNT 2


typedef std::vector<std::string> headers_t;

struct Job
{
    int client_fd;
    std::string ip;
    int port;
};

#endif
