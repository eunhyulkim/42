#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"
# include "Config.hpp"
# include "Connection.hpp"
# include "Location.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Worker.hpp"

// class Request;
class ServerManager;

class Server
{
	public:
	private:
		static std::map<std::string, std::string> mime_types;
		ServerManager* m_manager;
		std::string m_server_name;
		std::string m_host;
		int m_port;
		int m_fd;
		size_t m_request_uri_limit_size;
		size_t m_request_header_limit_size;
		size_t m_limit_client_body_size;
		std::string m_default_error_page;
		Config* m_config;
		std::vector<Location> m_locations;
		std::map<int, Connection> m_connections;
		std::queue<Response> m_responses;
		
		bool* m_server_live;
		std::queue<Job>* m_job_queue;
		pthread_mutex_t m_job_mutex;
		pthread_mutex_t m_live_mutex;
		std::map<std::string, pthread_mutex_t> m_uri_mutex;
		std::vector<Worker *> m_workers;
		int m_worker_count;
		int m_health_check_interval;
	private:
		/* connection management */
		// bool hasException(int client_fd);
		// int getUnuseConnectionFd();
		bool hasNewConnection();
		Job acceptNewConnection();
	public:
		Server();
		Server(ServerManager* server_manager, const std::string& server_block, std::vector<std::string>& location_blocks, Config* config);
		Server(const Server& copy);
		Server& operator=(const Server& obj);
		virtual ~Server();

		/* getter function */
		const std::string& get_m_server_name() const;
		const std::string& get_m_host() const;
		int get_m_port() const;
		int get_m_fd() const;
		size_t get_m_request_uri_limit_size() const;
		size_t get_m_request_header_limit_size() const;
		size_t get_m_limit_client_body_size() const;
		const std::string& get_m_default_error_page() const;
		Config* get_m_config() const;
		const std::vector<Location>& get_m_locations() const;
		const std::map<int, Connection>& get_m_connections() const;
		const std::queue<Response>& get_m_responses() const;
		int getFreeWorkerCount() const;
		bool get_m_server_live() const;
		std::queue<Job>* get_m_job_queue() const;
		int get_m_worker_count() const;
		int get_m_health_check_interval() const;

		Server *clone();

		/* declare member function */
		void createWorkers();
		void runWorkers();
		bool isExistFreeWorker();
		void run();
		bool work(int client_fd, Worker *worker);
		void exit();

		/* log function */
		void writeCreateServerLog(std::string, int port);
		void writeDetectNewConnectionLog();
		void writeCreateNewConnectionLog(int client_fd, std::string client_ip, int client_port);
		void reportCreateNewConnectionLog();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Server& server);

#endif
