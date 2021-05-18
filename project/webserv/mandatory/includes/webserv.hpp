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

# include <cstdlib>
# include <cstring>
# include <iostream>
# include <algorithm>

# include <string>
# include <vector>
# include <queue>
# include <set>
# include <map>

# include "base64.hpp"
# include "HtmlWriter.hpp"
# include "libft.hpp"

# define DEFAULT_CONFIG_FILE_PATH "config/default.conf"
# define HEALTH_LOG_PATH "log/health.log"
# define PROXY_LOG_PATH "log/proxy.log"
# define SERVER_ALLOW_METHODS "GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE"

# define REQUEST_URI_LIMIT_SIZE_MIN 64
# define REQUEST_URI_LIMIT_SIZE_MAX 8192
# define REQUEST_HEADER_LIMIT_SIZE_MIN 64
# define REQUEST_HEADER_LIMIT_SIZE_MAX 8192
# define LIMIT_CLIENT_BODY_SIZE_MAX 200000000

# define CONNECTION_OLD_SECOND 500
# define REQUEST_TIMEOVER_SECOND 30
# define SEND_RESPONSE_AT_ONCE 5
# define CGI_SUCCESS_CODE 299
# define CGI_META_VARIABLE_COUNT 15
# define STACKED_RESPONSE_COUNT 20

# define BUFFER_SIZE 65536
# define CHUNKED_TRANSFER_BUFFER_SIZE 65536
# define GENERAL_TRANSFER_BUFFER_SIZE 65536

# define SERVER_HEALTH_LOG_SECOND 5

typedef std::vector<std::string> headers_t;

#endif
