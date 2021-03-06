#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "Response.hpp"

class Request;
class Response;
class Worker;

class Connection
{
	public:
		enum Status { ON_WAIT, ON_RECV_CLIENT, TO_SEND_SERVER, ON_SEND_SERVER, ON_RECV_SERVER, ON_EXECUTE, TO_SEND_CLIENT, ON_SEND_CLIENT };
	private:
		Status m_status;
		int m_client_fd;
		int m_server_fd;
		int m_read_from_server_fd;
		int m_write_to_server_fd;
		Request m_request;
		int m_token_size;
		int m_readed_size;
		Response m_response;
		std::string m_rbuf_from_client;
		std::string m_rbuf_from_server;
		std::string m_wbuf;
		int m_wbuf_data_size;
		int m_send_data_size;
		timeval m_last_request_at;
		std::string m_client_ip;
		int m_client_port;
		Worker *m_worker;
		bool m_is_cached;
		bool m_is_filtered;
	public:
		Connection();
		Connection(int fd, const std::string& client_ip, int client_port);
		Connection(const Connection& copy);
		Connection& operator=(const Connection& obj);
		virtual ~Connection();

		/* getter function */
		Status get_m_status() const;
		int get_m_client_fd() const;
		int get_m_server_fd() const;
		int get_m_read_from_server_fd() const;
		int get_m_write_to_server_fd() const;
		const Request& get_m_request() const;
		int get_m_token_size() const;
		int get_m_readed_size() const;
		const Response& get_m_response() const;
		const std::string& get_m_rbuf_from_client() const;
		const std::string& get_m_rbuf_from_server() const;
		const std::string& get_m_wbuf() const;
		timeval get_m_last_request_at() const;
		std::string get_m_client_ip() const;
		int get_m_client_port() const;
		Worker *get_m_worker() const;
		bool get_m_is_cached() const;
		bool get_m_is_filtered() const;

		/* setter function */
		void set_m_client_fd(int fd);
		void set_m_server_fd(int fd);
		void set_m_read_from_server_fd(int fd);
		void set_m_write_to_server_fd(int fd);
		void set_m_last_request_at();
		void set_m_status(Status status);
		void set_m_token_size(int token_size);
		void set_m_readed_size(int readed_size);
		void set_m_wbuf_for_execute();
		void set_m_wbuf_for_send(std::string wbuf_string = "");
		void set_m_worker(Worker *worker);
		void set_m_is_cached(bool is_cached);
		void set_m_is_filtered(bool is_filtered);
		void set_m_rbuf_from_server(std::string rbuf_from_server);
		void addRbufFromClient(const char* str, int count);
		void addRbufFromServer(const char* str, int count);
		void decreaseRbufFromClient(int size);
		void decreaseWbuf(int size);
		void clearRbufFromClient();
		void clearRbufFromServer();
		void clearWbuf();
		void clear();

		/* member function */
		bool isOverTime() const;
		bool sendFromWbuf(int fd);
		bool isSendCompleted();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Connection& connection);

#endif
