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
# define ACCESS_LOG_PATH "log/access.log"
# define ERROR_LOG_PATH "log/error.log"
# define SERVER_ALLOW_METHODS "GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE"

# define CONNECTION_OLD 30
# define REQUEST_TIMEOVER 10
# define SEND_RESPONSE_AT_ONCE 5
# define RESPONSE_OVERLOAD_COUNT 20
# define CGI_META_VARIABLE_COUNT 15
# define CGI_SUCCESS_CODE 299
# define HEADERS std::vector<std::string>
# define REQUEST_URI_LIMIT_SIZE_MIN 64
# define REQUEST_URI_LIMIT_SIZE_MAX 8192
# define REQUEST_HEADER_LIMIT_SIZE_MIN 64
# define REQUEST_HEADER_LIMIT_SIZE_MAX 8192
# define LIMIT_CLIENT_BODY_SIZE_MAX 8192

# define SERVER_HEALTH_LOG_TIME 5
#endif
