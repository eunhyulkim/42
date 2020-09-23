#ifndef CONNECTION_HPP
# define CONNECTION_HPP

# include "webserv.hpp"

class Connection
{
	private:
		int m_client_fd;
		timeval m_last_request_at;
		std::string m_client_ip;
		int m_client_port;
		Connection();
	public:
		Connection(int fd, const std::string& client_ip, int client_port);
		Connection(const Connection& copy);
		Connection& operator=(const Connection& obj);
		virtual ~Connection();

		/* getter function */
		int get_m_client_fd() const;
		timeval get_m_last_request_at() const;
		std::string get_m_client_ip() const;
		int get_m_client_port() const;

		/* setter function */
		void set_m_last_request_at();

		bool isOverTime() const;
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Connection& connection);

#endif
