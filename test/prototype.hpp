#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>

#define DEFAULT_CONFIG_FILE_PATH "/default/error_file"

class Config {
    private:
        std::string m_software_name;
        std::string m_software_version;
        std::string m_http_version;
        std::string m_cgi_version;
        char** m_base_env;
    public:
        Config(const std::string& config_block);

        const std::string& get_m_software_name() const;
        const std::string& get_m_software_version() const;
        const std::string& get_m_http_version() const;
        const std::string& get_m_cgi_version() const;
        const char** get_m_base_env() const;
};

class Location {
    private:
        std::string m_root_path;
        std::set<std::string> m_allow_method;
        std::string m_auth_basic_realm;
        std::string m_auth_basic_file;
        std::set<std::string> m_index;
        std::set<std::string> m_cgi;
        bool m_autoindex;
    public:
        Location(const std::string& location_block);

        const std::string& get_m_root_path() const;
        const std::set<std::string>& get_m_allow_method() const;
        const std::string& get_m_auth_basic_realm() const;
        const std::string& get_m_auth_basic_file() const;
        const std::set<std::string>& get_m_index() const;
        const std::set<std::string>& get_m_cgi() const;
        const bool& get_m_autoindex() const;
};

class Connection {
    private:
        int m_fd;
        timeval m_last_request_at;
        std::string m_client_ip;
        int m_clinet_port;

        const int& get_m_fd() const;
        const int& get_m_last_requested_at() const;
        void set_m_last_requested_at();
        const std::string& get_m_client_ip() const;
        const int& get_m_client_port() const;

        Connection(int fd, std::string client_ip, int client_port);
};

class Request {
    private:
        enum Method { GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
        enum URIType { DIRECTORY, FILE, CGI_PROGRAM };
        enum TransferType { GENERAL, CHUNKED };

        Connection* m_connection;
        Server* m_server;
        Location* m_location;
        timeval m_start_at;

        Method m_method;
        std::string m_uri;
        URIType m_uri_type;
        std::map<std::string, std::string> m_headers;
        TransferType m_transfer_type;
        std::string m_content;
        std::string m_origin;
    public:
        void add_content(std::string added_content);
        void add_origin(std::string added_origin);
        void add_header(std::string header);
        bool isValidHeader(std::string header);
        bool isOverTime();
        const Connection& get_m_connection() const;
        Server* get_m_server() const;
        const Location& get_m_location() const;
        const Method& get_m_method() const;
        const std::string& get_m_uri() const;
        const URIType& get_m_uri_type() const;
        const std::map<std::string, std::string>& get_m_headers() const;
        const TransferType& get_m_transfer_type() const;
        const std::string& get_m_content() const;
        const std::string& get_m_origin() const;

        Request(Connection* connection, Server* server, std::string start_line);
};

class Response {
    private:
        enum TransferType { GENERAL, CHUNKED };
        Connection* m_connection;
        static std::map<int, std::vector<std::string> > status;
        int m_status_code;
        std::string m_status_description;
        std::map<std::string, std::string> m_headers;
        TransferType m_transfer_type;
        std::string m_content;
    public:
        void addHeader(std::string key, std::string value = "");
        char* c_str();
        Connection* get_m_connection() const;
        const int& get_m_status_code() const;
        const TransferType& get_m_transfer_type() const;
        const std::string& get_m_content() const;
        
        Response(int status_code, std::string va_arg = "");
};

class Server {
    private:
        ServerManager* m_manager;
        std::string m_server_name;
        std::string m_host;
        int m_port;
        int m_fd;

        int m_request_uri_limit_size;
        int m_request_header_limit_size;
        int m_limit_client_body_size;
        std::string m_default_error_page;

        std::vector<Location> m_locations;
        std::map<int, Connection> m_connections;
        std::queue<Response> m_responses;
    private:
        bool hasException(int client_fd);
        void closeConnection(int client_fd);
        bool isSendable();
        void sendResponse(Response& response);
        bool hasRequest(int client_fd);
        Request recvRequest(int client_fd);
        void solveRequest(Request& request);
        void executeGet(Request& request);
        void executeHead(Request& request);
        void executePut(Request& request);
        void executePost(Request& request);
        void executeDelete(Request& request);
        void executeOptions(Request& request);
        void executeTrace(Request& request);
        char **createCGIEnv();
        void exeucuteCGI(Request& request);
        void createResponse(int status_code);
        void removeOldConnection();
        bool hasNewConnection();
        void acceptNewConnection();
    public:
        Server(const std::string& server_block, const std::vector<std::string>& location_blocks);
        void run();
};

class ServerManager {
    private:
        std::vector<Server> m_servers;
        Config m_config;
        int m_max_fd;
        fd_set m_read_set;
        fd_set m_read_copy_set;
        fd_set m_write_set;
        fd_set m_write_copy_set;
        fd_set m_error_set;
        fd_set m_error_copy_set;
    private:
        bool splitConfigString(std::string config_string, std::string& config_block, std::string*& server_strings);
        bool splitServerString(std::string server_string, std::string& server_block, std::string*& location_blocks);
        bool isValidConfigBlock(std::string& config_block);
        bool isValidServerBlock(std::string& server_block);
        bool isValidLocationBlock(std::string& location_block);
        void parseConfigBlock(std::string& config_block);
        void parseServerBlock(std::string& server_block);
        void parseLocationBlock(std::string& location_block);
    public:
        void set_m_max_fd(int max_fd);
        void set_m_read_set(int fd);
        void unset_m_read_set(int fd);

        const fd_set& get_m_read_set() const;
        const fd_set& get_m_read_copy_set() const;
        const fd_set& get_m_write_set() const;
        const fd_set& get_m_error_set() const;

        void exitServer(std::string error_msg);
        void createServer(const char* config_file_path = DEFAULT_CONFIG_FILE_PATH);
        void runServer();

        ServerManager();
};
