#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "webserv.hpp"
# include "Request.hpp"
# include "Response.hpp"

class Request;
class Response;

class Connection
{
	public:
		enum Status { ON_WAIT, TO_SEND, ON_SEND, ON_EXECUTE, ON_RECV };
	private:
		Status m_status;
		int m_client_fd;
		int m_child_pid;
		int m_from_child_fd;
		int m_to_child_fd;
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
	public:
		Connection();
		Connection(int fd, const std::string& client_ip, int client_port);
		Connection(const Connection& copy);
		Connection& operator=(const Connection& obj);
		virtual ~Connection();

		/* getter function */
		Status get_m_status() const;
		int get_m_client_fd() const;
		int get_m_child_pid() const;
		int get_m_from_child_fd() const;
		int get_m_to_child_fd() const;
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

		/* setter function */
		void set_m_child_pid(int pid);
		void set_m_from_child_fd(int fd);
		void set_m_to_child_fd(int fd);
		void set_m_last_request_at();
		void set_m_status(Status status);
		void set_m_token_size(int token_size);
		void set_m_readed_size(int readed_size);
		void set_m_wbuf_for_execute();
		void set_m_wbuf_for_send();
		void addRbuf(const char* str, int count);
		void addCgiRbuf(const char* str, int count);
		void decreaseRbuf(int size);
		void decreaseWbuf(int size);
		void clearRbufFromClient();
		void clearRbufFromServer();
		void clearWbuf();
		void clear();

		/* member function */
		bool isOverTime() const;
		void responseSend();
		bool isSendCompleted();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Connection& connection);

#endif
