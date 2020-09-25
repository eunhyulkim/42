#include "Response.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

std::map<int, std::string> Response::status = make_status();

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Response::Response()
{

}

Response::Response(Connection *connection, int status_code, std::string body)
{
	this->m_connection = connection;
	this->m_connection_type = KEEP_ALIVE;
	this->m_status_code = status_code;
	this->m_status_description = Response::status[status_code];
	this->m_content = body;
	this->m_trasfer_type = GENERAL;
}

Response::Response(const Response& copy)
{
	this->m_connection = copy.get_m_connection();
	this->m_connection_type = copy.get_m_connection_type();
	this->m_status_code = copy.get_m_status_code();
	this->m_status_description = copy.get_m_status_description();
	this->m_trasfer_type = copy.get_m_transfer_type();
	this->m_content = copy.get_m_content();
	this->m_headers = copy.get_m_headers();
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Response::~Response()
{
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Response&
Response::operator=(const Response& obj)
{
	if (this == &obj)
		return (*this);
	this->m_connection = obj.get_m_connection();
	this->m_connection_type = obj.get_m_connection_type();
	this->m_status_code = obj.get_m_status_code();
	this->m_status_description = obj.get_m_status_description();
	this->m_trasfer_type = obj.get_m_transfer_type();
	this->m_content = obj.get_m_content();
	this->m_headers = obj.get_m_headers();
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Response& Response)
{
	size_t len = 0;
	std::map<std::string, std::string>::const_iterator it = Response.get_m_headers().begin();
	out << "STATUS_CODE: " << Response.get_m_status_code() << std::endl
	<< "STATUS_DESCRIPTION: " << Response.get_m_status_description() << std::endl
	<< "TRANSFER_TYPE: " << Response.get_m_transfer_type() << std::endl
	<< "CONTENT: " << Response.get_m_content() << std::endl;
	std::cout << "size :" << Response.get_m_headers().size() << std::endl;
	for (; len < Response.get_m_headers().size(); ++len)
	{
		out << "HEADER KEY: " << it->first << " VALUE : " << it->second << std::endl;
		++it;
	}
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

Connection *Response::get_m_connection() const { return (this->m_connection); }
Response::ConnectionType Response::get_m_connection_type() const { return (this->m_connection_type); }
int Response::get_m_status_code() const { return (this->m_status_code); }
std::string Response::get_m_status_description() const { return (this->m_status_description); }
const std::map<std::string, std::string>& Response::get_m_headers() const { return (this->m_headers); }
Response::TransferType Response::get_m_transfer_type() const { return (this->m_trasfer_type); }
std::string Response::get_m_content() const { return (this->m_content); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void Response::addHeader(std::string header_key, std::string header_value)
{
	if (header_key == "Transfer-Encoding" && header_value.find("chunked") != std::string::npos)
		this->m_trasfer_type = CHUNKED;
	else if (header_key == "Connection" && header_value == "close")
		this->m_connection_type = CLOSE;
	else
		this->m_headers[header_key] = header_value;
}

std::string Response::getString()
{
	std::string message;
	std::map<std::string, std::string>::iterator it = this->m_headers.begin();

	message = "HTTP/1.1 " + std::to_string(this->m_status_code) + " " + this->m_status_description + "\r\n";
	for (; it != this->m_headers.end(); ++it)
		message += it->first + ": " + it->second + "\r\n";
	if (m_connection_type == CLOSE || m_status_code < 200 || m_status_code > 299)
		message += "Connection: close\r\n";
	else
		message += "Connection: Keep-Alive\r\n";
	if (m_trasfer_type == CHUNKED)
		message += "transfer-encoding: chunked\r\n";
	message += "\r\n";
	message += this->m_content;
	return (message);
}

std::map<int, std::string> make_status ()
{
	std::map<int, std::string> status_map;

	status_map[100] = "Continue";
	status_map[200] = "OK";
	status_map[201] = "Created";
	status_map[202] = "Accepted";
	status_map[204] = "No Content";
	status_map[205] = "Reset Content";
	status_map[206] = "Partial Content";
	status_map[299] = "CGI OK";
	status_map[300] = "Multiple Choice";
	status_map[301] = "Moved Permanently";
	status_map[303] = "See Other";
	status_map[305] = "Use Proxy";
	status_map[307] = "Temporary Redirect";
	status_map[400] = "Bad Request";
	status_map[401] = "Unauthorized";
	status_map[403] = "Forbidden";
	status_map[404] = "Not Found";
	status_map[405] = "Method Not Allowed";
	status_map[406] = "Not Acceptable";
	status_map[407] = "Proxy Authentication Required";
	status_map[408] = "Request Timeout";
	status_map[409] = "Conflict";
	status_map[410] = "Gone";
	status_map[411] = "Length Required";
	status_map[412] = "Precondition Failed";
	status_map[413] = "Payload Too Large";
	status_map[414] = "URI Too Long";
	status_map[415] = "Unsupported Media Type";
	status_map[416] = "Requested Range Not Satisfiable";
	status_map[417] = "Expectation Failed";
	status_map[500] = "Internal Server Error";
	status_map[501] = "Not Implemented";
	status_map[503] = "Service Unavailable";
	status_map[504] = "Gateway Timeout";
	status_map[505] = "HTTP Version Not Supported";

	status_map[4000] = "Bad Request: Unvalid Header";
	status_map[4001] = "Bad Request: Content-Length header value is less than 0";
	status_map[4002] = "Bad Request: Not Found host header";
	status_map[4003] = "Bad Request: Found Content-Length header in chunked transfer-encoding";
	status_map[4004] = "Bad Request: In chunked request, last read operation is failed";
	status_map[4005] = "Bad Request: In chunked request, failed to convert trnasfer-size";
	status_map[4006] = "Bad Request: In chunked request, readed-size and treansfer-size is not equal";
	status_map[4007] = "Bad Request: In chunked request, not found '\\r\\n' at end of line.";
	status_map[4008] = "Bad Request: In chunked request, not found '\\r\\n' at end of line.";
	status_map[4009] = "Bad Request: found body in method other than GET, POST, TRACE.";
	status_map[4010] = "Bad Request: start line element count is not 3";
	status_map[4010] = "Bad Request: Method is not normal.";
	return (status_map);
}
