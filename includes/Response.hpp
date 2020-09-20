#ifndef Response_HPP
# define Response_HPP

# include <string>
# include <vector>
# include <map>
# include <iostream>
# include "libft.hpp"
# include "Connection.hpp"

class Response
{
	private:
		enum TransferType { GENERAL, CHUNKED };
		static std::map<int, std::string> status; // 확인
		Connection* m_connection;
		int m_status_code;
		std::string m_status_description;
		std::map<std::string, std::string> m_headers;
		TransferType m_trasfer_type;
		std::string m_content;
		Response();
	public:
		Response(Connection *connection, int status_code, std::string body = "");
		Response(const Response& copy);
		Response& operator=(const Response& obj);
		virtual ~Response();

		/* getter function */
		Connection *get_m_connection() const;
		int get_m_status_code() const;
		std::string get_m_status_description() const;
		const std::map<std::string, std::string>& get_m_headers() const;
		TransferType get_m_transfer_type() const;
		std::string get_m_content() const;
		void addHeader(std::string header_key, std::string header_value);
		const char* c_str();
};

/* global operator overload */
std::ostream&	operator<<(std::ostream& out, const Response& Response);

std::map<int, std::string> make_status ();

#endif
