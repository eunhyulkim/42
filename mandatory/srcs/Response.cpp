#include "Response.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

std::map<int, std::string> Response::status = make_status();

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Response::Response() {}

Response::Response(Connection* connection, int status_code, std::string body)
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

Response::~Response() {}

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

void Response::clear()
{
	m_status_code = -1;
	m_status_description.clear();
	m_headers.clear();
	m_trasfer_type = GENERAL;
	m_content.clear();
}
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

void Response::addContent(const std::string& body) { m_content += body; }

void Response::set_m_status_code(int status_code) { m_status_code = status_code; }

std::string Response::getString() const
{	
	std::string message;
	std::map<std::string, std::string>::const_iterator it = this->m_headers.begin();

	message = "HTTP/1.1 " + ft::to_string(this->m_status_code) + " " + this->m_status_description + "\r\n";
	for (; it != this->m_headers.end(); ++it)
		message += it->first + ": " + it->second + "\r\n";
	if (m_connection_type == CLOSE || m_status_code < 200 || m_status_code > 299)
		message += "Connection: close\r\n";
	else
		message += "Connection: Keep-Alive\r\n";
	if (m_trasfer_type == CHUNKED) {
		message += "Transfer-Encoding: chunked\r\n\r\n";
		int size = this->m_content.size();
		int count;
		std::string data = m_content;
		int added = 0;
		while (size > 0)
		{
			if (size > BUFFER_SIZE)
				count = BUFFER_SIZE;
			else
				count = size;
			message += ft::itos(ft::to_string(count), 10, 16) + "\r\n";
			message += data.substr(added, count) + "\r\n";
			size -= count;
			added += count;
		}
		data.clear();
		message += "0\r\n\r\n";
	}
	else
	{
		message += "\r\n";
		message += this->m_content;
	}
	return (message);
}

std::map<int, std::string>
make_status ()
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

	status_map[40000] = "Bad Request: start line element count is not 3";
	status_map[40001] = "Bad Request: Method is not normal";
	status_map[40002] = "Bad Request: URI parse failed(translated-path is empty)";
	status_map[40003] = "Bad Request: failed to add request header to map(maybe: duplicate header)";
	status_map[40004] = "Bad Request: Content-Length header value is less than 0";
	status_map[40005] = "Bad Request: header size is greater than request header limit size";
	status_map[40006] = "Bad Request: start line size is greater than request uri limit size";
	status_map[40007] = "Bad Request: Failed to get start line(recv function failure)";
	status_map[40008] = "Bad Request: header line size is greater than request header limit size";
	status_map[40009] = "Bad Request: Failed to get header line(recv function failure)";
	status_map[40010] = "Bad Request: Unvalid Header(maybe not found ':')";
	status_map[40011] = "Bad Request: Not Found host header";
	status_map[40012] = "Bad Request: In general request, failed to read content by large content-length";
	status_map[40013] = "Bad Request: In general request, failed to read content by normal content-length";
	status_map[40014] = "Bad Request: In general request, readed-size and content-length value is not equal";
	status_map[40015] = "Bad Request: In chunked request, failed to read trnasfer-size";
	status_map[40016] = "Bad Request: In chunked request, failed to convert trnasfer-size(maybe negative number)";
	status_map[40017] = "Bad Request: In chunked request, failed to convert trnasfer-size(maybe not number)";
	status_map[40018] = "Bad Request: In chunked request, for of end-line is not '\\r\\n'";
	status_map[40019] = "Bad Request: In chunked request, failed to read content by large content-length";
	status_map[40020] = "Bad Request: In chunked request, failed to read content by normal content-length";
	status_map[40021] = "Bad Request: In chunked request, readed-size and content-length value is not equal";
	status_map[40022] = "Bad Request: Credential Form unvalid";
	status_map[40023] = "Bad Request: Not CGI-prgoram, POST method, Content-Length is not 0";
	
	status_map[40101] = "Unauthorized";
	status_map[40301] = "Forbidden: Credential Content unvalid";	
	status_map[40401] = "Not Found: No suitable location";
	status_map[40402] = "Not Found: Requested uri is not in server";
	status_map[40403] = "Not Found: Autoindex off, index file is not found";
	status_map[40404] = "Not Found: CGI file is not found";
	status_map[40501] = "Method Not Allowed";
	status_map[40502] = "Bad Request: Access Directory other than GET method";
	status_map[41101] = "Length Required";
	status_map[41301] = "Payload Too Large: Failed to add content in request";
	status_map[41302] = "Payload Too Large: Failed to add origin in request";
	status_map[41303] = "Payload Too Large: Content length header value is over than body limit size";
	status_map[41304] = "Payload Too Large: File size is too large in GET method";
	status_map[41305] = "Payload Too Large: File size is too large in HEAD method";
	status_map[41306] = "Payload Too Large: CGI output size is too large";
	status_map[41307] = "Payload Too Large: LOCATION SIZE OVER";
	status_map[41401] = "Bad Request: uri size is greater than request uri limit size";
	status_map[41501] = "Unsupported Media Type: in GET method";
	status_map[41502] = "Unsupported Media Type: in HEAD method";
	status_map[41503] = "Unsupported Media Type: in PUT method";

	status_map[50001] = "Internal Server Error: recvRequest function throw std::exception";
	status_map[50002] = "Internal Server Error: MakeAutoindex function failed";
	status_map[50003] = "Internal Server Error: in PUT method, failed to create or open file";
	status_map[50004] = "Internal Server Error: in PUT method, failed to write content";
	status_map[50005] = "Internal Server Error: createCGIEnv function return NULL";
	status_map[50006] = "Internal Server Error: Failed to fork process for executeCGI";
	status_map[50301] = "Internal Server Error: Too many Stacked Response exists";
	status_map[50401] = "Gateway Timeout";
	status_map[50501] = "HTTP Version Not Supported";

	return (status_map);
}
