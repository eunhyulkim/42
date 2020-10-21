#include "Server.hpp"
#include "Worker.hpp"
#include "ServerManager.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* static variable code */

std::map<std::string, std::string> makeMimeType ()
{
	std::map<std::string, std::string> type_map;

	type_map["avi"] = "video/x-msvivdeo";
	type_map["bin"] = "application/octet-stream";
	type_map["bmp"] = "image/bmp";
	type_map["css"] = "text/css";
	type_map["csv"] = "text/csv";
	type_map["doc"] = "application/msword";
	type_map["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	type_map["gz"] = "application/gzip";
	type_map["gif"] = "image/gif";
	type_map["htm"] = "text/html";
	type_map["html"] = "text/html";
	type_map["ico"] = "image/vnd.microsoft.icon";
	type_map["jepg"] = "image/jepg";
	type_map["jpg"] = "image/jepg";
	type_map["js"] = "text/javascript";
	type_map["json"] = "application/json";
	type_map["mp3"] = "audio/mpeg";
	type_map["mpeg"] = "video/mpeg";
	type_map["png"] = "image/png";
	type_map["pdf"] = "apllication/pdf";
	type_map["php"] = "application/x-httpd-php";
	type_map["ppt"] = "application/vnd.ms-powerpoint";
	type_map["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	type_map["rar"] = "application/vnd.rar";
	type_map["sh"] = "application/x-sh";
	type_map["svg"] = "image/svg+xml";
	type_map["tar"] = "application/x-tar";
	type_map["tif"] = "image/tiff";
	type_map["txt"] = "text/plain";
	type_map["wav"] = "audio/wav";
	type_map["xls"] = "application/xhtml+xml";
	type_map["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	type_map["zip"] = "application/zip";
	type_map["bad_extension"] = "application/bad";
	type_map["bla"] = "application/42cgi";
	type_map["pouic"] = "application/pouic";
	return (type_map);
}
std::map<std::string, std::string> Worker::mime_types = makeMimeType();

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Worker::Worker() {}
Worker::Worker(ServerManager* server_manager, Server* server, pthread_mutex_t* job_mutex, pthread_mutex_t* live_mutex, std::map<std::string, pthread_mutex_t> *uri_mutex, int idx)
{
	m_idx = idx;
	m_manager = m_param.manager = server_manager;
	m_config = m_manager->configClone();
	m_server = m_param.server = server->clone();
	m_worker = m_param.worker = this;
	m_job_mutex = m_param.job_mutex = job_mutex;
	m_live_mutex = m_param.live_mutex = live_mutex;
	m_uri_mutex = m_param.uri_mutex = uri_mutex;
	m_work_status = false;
	ft::fdZero(&m_fdset.read_set);
	ft::fdZero(&m_fdset.read_copy_set);
	ft::fdZero(&m_fdset.write_set);
	ft::fdZero(&m_fdset.write_copy_set);
	m_client_fd = -1;
	m_child_pid = -1;
}

Worker::Worker(const Worker& copy)
{
	m_idx = copy.m_idx;
	m_param.manager = copy.m_param.manager;
	m_config = copy.m_config;
	m_server = m_param.server = copy.m_param.server;
	m_worker = m_param.worker = copy.m_param.worker;
	m_job_mutex = m_param.job_mutex = copy.m_param.job_mutex;
	m_live_mutex = m_param.live_mutex = copy.m_param.live_mutex;
	m_uri_mutex = m_param.uri_mutex = copy.m_param.uri_mutex;
	m_work_status = copy.m_work_status;
	m_fdset.read_set = copy.m_fdset.read_set;
	m_fdset.read_copy_set = copy.m_fdset.read_copy_set;
	m_fdset.write_set = copy.m_fdset.write_set;
	m_fdset.write_copy_set = copy.m_fdset.write_copy_set;
	m_client_fd = copy.m_client_fd;
	m_child_pid = copy.m_child_pid;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Worker::~Worker()
{
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Worker& Worker::operator=(const Worker& obj)
{
	if (this == &obj)
		return (*this);
	m_idx = obj.m_idx;
	m_param.manager = obj.m_param.manager;
	m_config = obj.m_config;
	m_server = m_param.server = obj.m_param.server;
	m_worker = m_param.worker = obj.m_param.worker;
	m_job_mutex = m_param.job_mutex = obj.m_param.job_mutex;
	m_live_mutex = m_param.live_mutex = obj.m_param.live_mutex;
	m_uri_mutex = m_param.uri_mutex = obj.m_param.uri_mutex;
	m_work_status = obj.m_work_status;
	m_fdset.read_set = obj.m_fdset.read_set;
	m_fdset.read_copy_set = obj.m_fdset.read_copy_set;
	m_fdset.write_set = obj.m_fdset.write_set;
	m_fdset.write_copy_set = obj.m_fdset.write_copy_set;
	m_client_fd = obj.m_client_fd;
	m_child_pid = obj.m_child_pid;
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Worker&)
{
	/* ostream output overload code */
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

const Connection& Worker::get_m_connection() const { return (m_connection); }
bool Worker::isFree() const { return (m_work_status == false); }
int Worker::get_m_idx() const { return (m_idx); }
Config* Worker::get_m_config() const { return (m_config); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void Worker::set_m_work_status(bool status) { m_work_status = status; }
void Worker::set_m_client_fd(int fd) { m_client_fd = fd; }

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

Worker::IOError::IOError() throw () : std::exception(){}
Worker::IOError::IOError(const char *msg) throw () : std::exception(){ m_msg = std::string(msg); }
Worker::IOError::IOError(const IOError& copy) throw () : std::exception(){ m_msg = copy.m_msg; }
Worker::IOError& Worker::IOError::operator=(const Worker::IOError& obj) throw() { m_msg = obj.m_msg; return (*this); }
Worker::IOError::~IOError() throw (){}
const char* Worker::IOError::what() const throw () { return ("read/write operation return fail:"); }
std::string Worker::IOError::location() const throw () { return ("read/write operation return fail:" + m_msg); }


/* ************************************************************************** */
/* ---------------------------------- UTIL ---------------------------------- */
/* ************************************************************************** */

void
Worker::fdSet(int fd, SetType fdset)
{
	if (fdset == WRITE_SET)
		ft::fdSet(fd, &this->m_fdset.write_set);
	else if (fdset == WRITE_COPY_SET)
		ft::fdSet(fd, &this->m_fdset.write_copy_set);
	else if (fdset == READ_SET)
		ft::fdSet(fd, &this->m_fdset.read_set);
	else if (fdset == READ_COPY_SET)
		ft::fdSet(fd, &this->m_fdset.read_copy_set);
}

void
Worker::fdZero(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.write_set);
	if (fdset == WRITE_COPY_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.write_copy_set);
	if (fdset == READ_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.read_set);
	if (fdset == READ_COPY_SET || fdset == ALL_SET)
		ft::fdZero(&this->m_fdset.read_copy_set);
}

void
Worker::fdClear(int fd, SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.write_set);
	if (fdset == WRITE_COPY_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.write_copy_set);
	if (fdset == READ_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.read_set);
	if (fdset == READ_COPY_SET || fdset == ALL_SET)
		ft::fdClr(fd, &this->m_fdset.read_copy_set);
}

bool
Worker::fdIsset(int fd, SetType fdset)
{
	bool ret = false;

	if (fdset == WRITE_SET || (fdset == false && fdset == ALL_SET))
		ret = ft::fdIsset(fd, &this->m_fdset.write_set);
	if (fdset == WRITE_COPY_SET || (fdset == false && fdset == ALL_SET))
		ret = ft::fdIsset(fd, &this->m_fdset.write_copy_set);
	if (fdset == READ_SET || (fdset == false && fdset == ALL_SET))
		ret = ft::fdIsset(fd, &this->m_fdset.read_set);
	if (fdset == READ_COPY_SET || (fdset == false && fdset == ALL_SET))
		ret = ft::fdIsset(fd, &this->m_fdset.read_copy_set);
	return (ret);
}

void
Worker::fdCopy(SetType fdset)
{
	if (fdset == WRITE_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_fdset.write_copy_set);
		this->m_fdset.write_copy_set = this->m_fdset.write_set;
	}
	if (fdset == READ_SET || fdset == ALL_SET) {
		ft::fdZero(&this->m_fdset.read_copy_set);
		this->m_fdset.read_copy_set = this->m_fdset.read_set;
	}
}

int
Worker::get_max_fd()
{
	for (int i = 512; i >= 0; --i)
	{
		if (ft::fdIsset(i, &m_fdset.read_set) || ft::fdIsset(i, &m_fdset.write_set))
			return (i);
	}
	return (-1);
}

/* ************************************************************************** */
/* ----------------------------- SEND OPERATION ----------------------------- */
/* ************************************************************************** */

/*
** function: solveRequest
** 1. check request method is allowed
** 2. Check authentication is required
** 3. If uri is directory, executeAutoindex
** 4. If uri is file, executeMethod
*/

namespace {
	void basic_decode(std::string data, std::string& key, std::string& value)
	{
		std::string decodedData = ft::containerToString(ft::base64_decode(data), "");
		if (decodedData.find(":") == std::string::npos || decodedData.find(":") == decodedData.size() - 1)
			return ;
		int idx = decodedData.find(":");
		key = decodedData.substr(0, idx);
		std::vector<unsigned char> value_base(decodedData.begin() + idx + 1, decodedData.end());
		value = ft::base64_encode(&value_base[0], value_base.size());
	}

	std::string getDateHeader()
	{
		char buff[1024];
		struct tm t;
		timeval now;

		gettimeofday(&now, NULL);
		ft::convertTimespecToTm(now.tv_sec, &t);
		strftime(buff, sizeof(buff), "%a, %d %b %Y %X GMT", &t);
		return ("Last-Modified:" + std::string(buff));
	}

	std::string getServerHeader(Server* server) {
		return ("Server:" + server->get_m_server_name());
	}
}

void
Worker::createCGIResponse(int& status, headers_t& headers, std::string& body)
{
	status = 200;
	headers_t headers_in_body = ft::split(ft::rtrim(body.substr(0, body.find("\r\n\r\n")), "\r\n"), '\n');
	std::string key, value;
	for (headers_t::iterator it = headers_in_body.begin(); it != headers_in_body.end(); it++)
	{
		key = ft::trim(it->substr(0, it->find(":")), " \t");
		value = ft::trim(it->substr(it->find(":") + 1), " \r\n\t");
		if (key == "Status" || key == "status")
			status = ft::stoi(value);
		else if (!key.empty() && !value.empty())
			headers.push_back(key + ":" + value);
	}
	if (body.find("\r\n\r\n") != std::string::npos)
		body = body.substr(body.find("\r\n\r\n") + 4);
	else if (body.find("\n\n") != std::string::npos)
		body = body.substr(body.find("\n\n") + 2);
	else
		body = "";
	if (body.size() == 0)
		return ;

	headers.push_back("Transfer-Encoding:chunked");
}

void
Worker::createResponse(Connection& connection, int status, headers_t headers, std::string body)
{
	if (status >= 40000) {
		reportCreateNewRequestLog(status);
		status /= 100;
	}

	headers.push_back(getDateHeader());
	headers.push_back(getServerHeader(m_server));

	if (status == CGI_SUCCESS_CODE)
		createCGIResponse(status, headers, body);
	if (status >= 400 && status <= 599) {
		body = m_server->get_m_default_error_page();
		body.replace(body.find("#ERROR_CODE"), 11, ft::to_string(status));
		body.replace(body.find("#ERROR_CODE"), 11, ft::to_string(status));
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
		body.replace(body.find("#ERROR_DESCRIPTION"), 18, Response::status[status]);
	}
	if (!ft::hasKey(ft::stringVectorToMap(headers), "Transfer-Encoding"))
		headers.push_back("Content-Length:" + ft::to_string(body.size()));
	if (!body.empty())
		headers.push_back("Content-Language:ko-KR");
	if (status / 100 != 2)
		headers.push_back("Connection:close");
	if (status / 100 == 3)
		headers.push_back("Location:/");
	if (status == 504)
		headers.push_back("Retry-After:3600");
	if (connection.get_m_request().get_m_method() == Request::HEAD)
		body = "";

	Response& response = const_cast<Response&>(connection.get_m_response());
	response = Response(&connection, status, body);
	headers_t::iterator it = headers.begin();
	for (; it != headers.end(); ++it) {
		std::string key = ft::rtrim((*it).substr(0, (*it).find(":")), " ");
		std::string value = ft::ltrim((*it).substr((*it).find(":") + 1), " ");
		response.addHeader(key, value);
	}
	writeCreateNewResponseLog(response);
	const_cast<Request&>(connection.get_m_request()).set_m_phase(Request::COMPLETE);
	connection.set_m_status(Connection::TO_SEND_CLIENT);
	this->fdSet(response.get_m_connection()->get_m_client_fd(), Worker::WRITE_SET);
}

bool
Worker::hasSendWork()
{
	Connection::Status status = m_connection.get_m_status();
	int fd = m_connection.get_m_client_fd();
	if (status != Connection::TO_SEND_CLIENT&& status != Connection::ON_SEND_CLIENT)
		return (false);
	return (this->fdIsset(fd, Worker::WRITE_COPY_SET));
}

bool
Worker::runSend()
{
	Connection& connection = m_connection;

	Connection::Status status = connection.get_m_status();
	if (status == Connection::TO_SEND_CLIENT)
	{
		connection.set_m_wbuf_for_send();
		connection.set_m_status(Connection::ON_SEND_CLIENT);
	}

	connection.sendFromWbuf(connection.get_m_client_fd());
	bool ret = connection.isSendCompleted();
	if (ret)
	{
		connection.set_m_status(Connection::ON_WAIT);
		this->fdClear(connection.get_m_client_fd(), Worker::WRITE_SET);
		writeSendResponseLog(connection.get_m_response());
		if (connection.get_m_response().get_m_status_code() / 100 != 2)
			return (false);
		else
			connection.clear();
		connection.set_m_last_request_at();
	}
	return (true);
}

/* ************************************************************************** */
/* ---------------------------- EXECUTE OPERATION --------------------------- */
/* ************************************************************************** */

bool
Worker::hasExecuteWork()
{
	Connection::Status status = m_connection.get_m_status();
	int from_child_fd = m_connection.get_m_read_from_server_fd();
	int to_child_fd = m_connection.get_m_write_to_server_fd();

	if (status != Connection::ON_EXECUTE)
		return (false);
	if (from_child_fd == -1 && to_child_fd == -1)
		return (false);
	if (from_child_fd != -1 && this->fdIsset(from_child_fd, Worker::READ_COPY_SET))
		return (true);
	if (to_child_fd != -1 && this->fdIsset(to_child_fd, Worker::WRITE_COPY_SET))
		return (true);
	return (false);
}

namespace
{
	int
	getChunkedSize(std::string& buf, std::string& len)
	{
		int content_length;
		if (!ft::getline(buf, len))
			return (-1);
		try {
			content_length = ft::stoi(len, 16);
		} catch (std::exception& e) {
			throw (40017);
		}
		if (content_length < 0)
			throw (40016);
		if (content_length == 0)
		{
			if (len[0] != '0')
				throw (40017);
		}
		return (content_length);
	}

	void
	writeChunkedBodyToCGIScript(Worker* worker, Connection& connection)
	{
		std::string& rbuf = const_cast<std::string&>(connection.get_m_rbuf_from_client());
		int client_fd = connection.get_m_client_fd();
		int to_child_fd = connection.get_m_write_to_server_fd();
		char buff[BUFFER_SIZE];
		int count;

		if (rbuf.size() < 70000 && worker->fdIsset(client_fd, Worker::READ_COPY_SET))
		{
			if ((count = recv(client_fd, buff, sizeof(buff), 0)) > 0)
				connection.addRbufFromClient(buff, count);
			else if (count == -1)
				throw (Worker::IOError((("IO error detected to read reqeust message without body for client ") + ft::to_string(connection.get_m_client_fd())).c_str()));
			else
				throw (Worker::IOError((("Connection close detected by client ") + ft::to_string(connection.get_m_client_fd())).c_str()));
		}

		std::string len;
		int content_length = getChunkedSize(rbuf, len);
		if (content_length == -1)
			return ;
		else if (content_length == 0)
		{
			if (rbuf.find("\r\n") == std::string::npos)
				rbuf.insert(0, len + "\r\n");
			else if (rbuf.size() >= 2 && rbuf[0] == '\r' && rbuf[1] == '\n')
			{
				connection.decreaseRbufFromClient(2);
				close(to_child_fd);
				worker->fdClear(to_child_fd, Worker::WRITE_SET);
				worker->fdClear(to_child_fd, Worker::WRITE_COPY_SET);
			}
			return ;
		}
		else if (static_cast<int>(rbuf.size()) < content_length + 2)
		{
			rbuf.insert(0, len + "\r\n");
			return ;
		}
		else
		{
			count = write(to_child_fd, rbuf.c_str(), content_length);
			if (count > 0)
				connection.decreaseRbufFromClient(content_length + 2);
			else if (count == 0 || count == -1)
				throw (Worker::IOError((("IO error detected from write body to child process ") + ft::to_string(to_child_fd)).c_str()));
			else
				rbuf.insert(0, len + "\r\n");
		}
	}


	void
	writeSavedBodyToCGIScript(Worker* worker, Connection& connection)
	{
		int to_child_fd = connection.get_m_write_to_server_fd();
		const std::string& data = connection.get_m_wbuf();

		if (!data.empty())
		{
			int count = (data.size() > BUFFER_SIZE) ? BUFFER_SIZE : data.size();
			count = write(to_child_fd, data.c_str(), count);
			if (count == 0 || count == -1)
				throw (Worker::IOError((("IO error detected from write body to child process ") + ft::to_string(to_child_fd)).c_str()));
			connection.decreaseWbuf(count);
		}
		else
		{
			close(to_child_fd);
			worker->fdClear(to_child_fd, Worker::WRITE_SET);
		}
	}
}

void
Worker::runExecute()
{
	Connection& connection = m_connection;
	int from_child_fd = connection.get_m_read_from_server_fd();
	int to_child_fd = connection.get_m_write_to_server_fd();
	int stat;
	bool read_end = false;

	const Request& request = connection.get_m_request();

	if (from_child_fd != -1 && this->fdIsset(from_child_fd, Worker::READ_COPY_SET))
	{
		char buff[BUFFER_SIZE];
		int count = read(from_child_fd, buff, sizeof(buff));
		if (count == 0)
			read_end = true;
		else if (count > 0)
			connection.addRbufFromServer(buff, count);
		else
			throw (IOError("IO error detected to read from child process."));
	}

	if (to_child_fd != -1 && this->fdIsset(to_child_fd, Worker::WRITE_COPY_SET))
	{
		if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
			writeChunkedBodyToCGIScript(this, connection);
		else
			writeSavedBodyToCGIScript(this, connection);
	}

	waitpid(m_connection.get_m_server_fd(), &stat, WNOHANG);
	if (WIFEXITED(stat) && read_end && !this->fdIsset(to_child_fd, Worker::WRITE_SET))
	{
		if (from_child_fd != -1)
		{
			close(from_child_fd);
			this->fdClear(from_child_fd, Worker::READ_SET);
		}
		std::string body = connection.get_m_rbuf_from_server();
		connection.clearRbufFromServer();
		connection.clearWbuf();
		if (connection.get_m_request().get_m_uri_type() == Request::CGI_PROGRAM)
		{
			if (body.size() > request.get_m_location()->get_m_limit_client_body_size() + body.find("\r\n\r\n") + 4)
				createResponse(connection, 41301);
			else
				createResponse(connection, CGI_SUCCESS_CODE, headers_t(), body);
		}
		else
			createResponse(connection, 200, headers_t(), body);
		connection.set_m_status(Connection::TO_SEND_CLIENT);
	}
	return ;
}

namespace {
	std::string getAcceptLanguagePath(std::string path, std::map<std::string, std::string> headers)
	{
		if (!ft::hasKey(headers, "Accept-Language"))
			return (path);
		std::vector<std::string> langs = ft::split(headers["Accept-Language"], ',');
		if (langs.empty() || langs[0].substr(0, 2) == "ko")
			return (path);
		std::string new_path;
		for (size_t i = 0; i < langs.size(); ++i) {
			if (langs[i].find(";") != std::string::npos)
				langs[i] = langs[i].substr(0, langs[i].find(";"));
			if (langs[i].find("-") != std::string::npos)
				langs[i] = langs[i].substr(0, langs[i].find("-"));
			if (path.find(".") != std::string::npos) {
				new_path = path;
				new_path.insert(path.rfind("."), "_" + langs[i]);
			}
			else
				new_path = path + "_" + langs[i];
			if (ft::isFile(new_path))
				break ;
			new_path.clear();
		}
		if (new_path.empty())
			return (path);
		else
			return (new_path);
	}
	bool makeAutoindexContent(HtmlWriter& html, std::string cwd, std::string directory_uri)
	{
		DIR *dir = NULL;
		struct dirent *de = NULL;
		char buff[1024];
		int idx = 7;

		if ((dir = opendir(cwd.c_str())) == NULL)
			return (false);
		while ((de = readdir(dir)) != NULL) {
			std::string name = de->d_name;
            if (name == "." || (name != ".." && name[0] == '.'))
                continue ;
			if (de->d_type == 4 || de->d_type == 8) // 4 dir, 8 file
			{
				std::string content;
				content.append(html.makeLink(directory_uri + "/" + name, name));
				content.append(std::string(51 - std::string(name).size(), ' '));

				struct stat buf;
            	struct tm t;
				ft::bzero(&buf, sizeof(struct stat));
				stat((std::string(cwd) + "/" + name).c_str(), &buf);
				ft::convertTimespecToTm(buf.st_mtimespec.tv_sec, &t);
				strftime(buff, sizeof(buff), "%d-%h-%G %H:%M", &t);

				content.append(std::string(buff));
				content.append(std::string(20 - ft::to_string(de->d_reclen).size(), ' '));
				content.append(ft::to_string(de->d_reclen));
				html.add_line(idx++, content);
			}
		}
		closedir(dir);
		return (true);
	}
	void makeAutoindexForm(HtmlWriter& html, const Request& request)
	{
		std::string title = "Index of " + request.get_m_uri();
		html.add_title(title);
		html.add_bgcolor("white");
		html.add_tag("\"white\">\n", "h1", title, false);
		html.add_tag("/h1>\n", "hr", "", true);
		html.add_tag("hr>\n", "pre", "", true);
	}
	int getValidIndexFd(Worker* worker, const Request& request)
	{
		std::set<std::string> index = request.get_m_location()->get_m_index();
		std::set<std::string>::iterator it = index.begin();
		struct stat buf;
		int fd = -1;
		std::string path, body;
		for (; it != index.end(); ++it)
		{
			path = request.get_m_script_translated();

			if (path[path.size() - 1] != '/')
				path.push_back('/');
			path.append(*it);
			if (worker->get_m_config()->is_on_plugin_alm())
				path = getAcceptLanguagePath(path, worker->get_m_connection().get_m_request().get_m_headers());

			stat(path.c_str(), &buf);
			if (S_ISREG(buf.st_mode) && (fd = open(path.c_str(), O_RDONLY)) > -1)
				break ;
		}
		return (fd);
	}
}

void
Worker::executeAutoindex()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	char cwd[BUFFER_SIZE];
	getcwd(cwd, sizeof(cwd));

	if (request.get_m_location()->get_m_autoindex())
	{
		HtmlWriter html;
		makeAutoindexForm(html, request);
		std::string directory_uri = request.get_m_uri();
		if (directory_uri[directory_uri.size() - 1] != '/')
			directory_uri.push_back('/');
		if (!makeAutoindexContent(html, request.get_m_script_translated(), directory_uri))
			return (createResponse(connection, 50002));
		return (createResponse(connection, 200, headers_t(), html.get_m_body()));
	}
	else
	{
		int fd = getValidIndexFd(this, request);
		if (fd == -1)
			return (createResponse(connection, 40403));
		return (createResponse(connection, 200, headers_t(), ft::getStringFromFd(fd)));
	}
}

void
Worker::executeEcho()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	std::string path = request.get_m_uri();
	std::string body;

	body = request.get_m_location()->get_m_echo_msg();
	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(connection, 41501));
	headers.push_back(getLastModifiedHeader(path));
	return (createResponse(connection, 200, headers, body));
}

void
Worker::executeGet()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	std::string path = request.get_m_script_translated();
	std::string body;

	if (m_config->is_on_plugin_alm())
		path = getAcceptLanguagePath(path, m_connection.get_m_request().get_m_headers());

	try {
		body = ft::getStringFromFile(path, m_server->get_m_limit_client_body_size());
	} catch (std::overflow_error& e) {
		return (createResponse(connection, 41304));
	}
	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(connection, 41501));
	headers.push_back(getLastModifiedHeader(path));
	return (createResponse(connection, 200, headers, body));
}

void
Worker::executeHead()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	std::string path = request.get_m_path_translated();
	std::string body;

	try {
		body = ft::getStringFromFile(path, m_server->get_m_limit_client_body_size());
	} catch (std::overflow_error& e) {
		return (createResponse(connection, 41305));
	}

	headers_t headers(1, getMimeTypeHeader(path));
	if (headers[0].empty())
		return (createResponse(connection, 41502));
	headers.push_back(getLastModifiedHeader(path));
	headers.push_back("content-length:" + ft::to_string(body.size()));
	return (createResponse(connection, 200, headers));
}

void
Worker::executeTrace()
{
	createResponse(m_connection, 200, headers_t(1, "Content-Type:text/plain"), m_connection.get_m_request().get_m_origin());
}

void
Worker::executePost()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	if (request.get_m_headers().find("Content-Length")->second == "0")
		return (executeGet());
	else
		return (createResponse(connection, 40023));
}

void
Worker::executeOptions() {
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	if (request.get_m_uri() == "*")
		return (createResponse(connection, 200, headers_t(1, std::string("Allow:") + SERVER_ALLOW_METHODS)));
	headers_t headers(1, "Allow:" + ft::containerToString(request.get_m_location()->get_m_allow_method(), ", "));
	return (createResponse(connection, 200, headers));
}

void
Worker::executePut()
{
	int fd;
	struct stat buf;
	int count;

	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	stat(request.get_m_script_translated().c_str(), &buf);
	headers_t headers(1, getMimeTypeHeader(request.get_m_path_translated()));
	// if (headers[0].empty())
	// 	return (createResponse(request.get_m_connection(), 41503));
	if ((fd = open(request.get_m_script_translated().c_str(), O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		return (createResponse(connection, 50003));
	if (!request.get_m_content().empty() && (count = write(fd, request.get_m_content().c_str(), request.get_m_content().size()) <= 0))
	{
		close(fd);
		if (count == 0 || count == -1)
			throw (Worker::IOError((("IO error detected to write body in executePut") + ft::to_string(fd)).c_str()));
		return (createResponse(connection, 50004));
	}
	close(fd);
	if (S_ISREG(buf.st_mode))
		return (createResponse(connection, 204));
	headers.push_back("Location:" + m_server->get_m_host() + "/" + request.get_m_uri());
	return (createResponse(connection, 201, headers, request.get_m_content()));
}

void
Worker::executeDelete() {
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	if (unlink(request.get_m_path_translated().c_str()) == -1)
		createResponse(connection, 204);
	else
		return (createResponse(connection, 204));
}

namespace {
	int	setEnv(char **env, int idx, std::string key, std::string val)
	{
		char	*item;

		if (key.empty())
			return (0);
		item = ft::strsjoin(key, std::string("="), val);
		env[idx] = item;
		return (1);
	}
	char **dupBaseEnvWithExtraSpace(Config *config, const Request& request)
	{
		char **base_env = config->get_m_base_env();
		char **cgi_env = NULL;
		int idx = 0;
		int base_len = ft::lenDoubleStr(base_env);
		int custom_len = request.get_m_special_header_count();

		if ((cgi_env = reinterpret_cast<char **>(malloc(sizeof(char *) * (base_len + custom_len + CGI_META_VARIABLE_COUNT + 1)))) == 0)
			return (NULL);
		while (base_env[idx] != NULL) {
			cgi_env[idx] = ft::strdup(base_env[idx]);
			++idx;
		}
		while (idx < base_len + custom_len + CGI_META_VARIABLE_COUNT + 1)
			cgi_env[idx++] = NULL;
		return (cgi_env);
	}
	std::string getCGIEnvValue(const Request& request, std::string token, Server *server = NULL, Config config = Config())
	{
		if (token == "CONTENT_LENGTH") {
			if (ft::hasKey(request.get_m_headers(), "Content-Length"))
				return (request.get_m_headers().find("Content-Length")->second);
			return (std::string("-1"));
		}
		else if (token == "CONTENT_TYPE") {
			if (ft::hasKey(request.get_m_headers(), "Content-Type"))
				return (request.get_m_headers().find("Content-Type")->second);
			return (std::string());
		}
		else if (token == "AUTH_TYPE")
			return (config.get_m_cgi_version());
		else if (token == "PATH_INFO")
			return (request.get_m_path_info());
		else if (token == "PATH_TRANSLATED")
			return (request.get_m_path_translated());
		else if (token == "QUERY_STRING")
			return (request.get_m_query());
		else if (token == "REMOTE_ADDR")
			return (request.get_m_connection()->get_m_client_ip());
		else if (token == "REQUEST_METHOD")
			return (request.get_m_method_to_string());
		else if (token == "REQUEST_URI")
			return (request.get_m_uri());
		else if (token == "SCRIPT_NAME")
			return (request.get_m_script_translated());
		else if (token == "SERVER_NAME")
			return (server->get_m_server_name());
		else if (token == "SERVER_PORT")
			return (ft::to_string(server->get_m_port()));
		else if (token == "SERVER_PROTOCOL")
			return ("HTTP/" + config.get_m_http_version());
		else if (token == "SERVER_SOFTWARE")
			return (config.get_m_software_name() + "/" + config.get_m_software_version());
		else if (token == "GATEWAY_INTERFACE")
			return (config.get_m_cgi_version());
		return (NULL);
	}
}

char**
Worker::createCGIEnv(const Request& request)
{
	char **env = dupBaseEnvWithExtraSpace(m_config, request);
	int idx = ft::lenDoubleStr(m_config->get_m_base_env());
	setEnv(env, idx++, "AUTH_TYPE", "");
	setEnv(env, idx++, "CONTENT_LENGTH", getCGIEnvValue(request, "CONTENT_LENGTH"));
	setEnv(env, idx++, "CONTENT_TYPE", getCGIEnvValue(request, "CONTENT_TYPE"));
	setEnv(env, idx++, "GATEWAY_INTERFACE", getCGIEnvValue(request, "GATEWAY_INTERFACE", NULL, *m_config));
	setEnv(env, idx++, "PATH_INFO", getCGIEnvValue(request, "PATH_INFO"));
	setEnv(env, idx++, "PATH_TRANSLATED", getCGIEnvValue(request, "PATH_TRANSLATED"));
	setEnv(env, idx++, "QUERY_STRING", getCGIEnvValue(request, "QUERY_STRING"));
	setEnv(env, idx++, "REMOTE_ADDR", getCGIEnvValue(request, "REMOTE_ADDR"));
	setEnv(env, idx++, "REQUEST_METHOD", getCGIEnvValue(request, "REQUEST_METHOD"));
	setEnv(env, idx++, "REQUEST_URI", getCGIEnvValue(request, "REQUEST_URI"));
	setEnv(env, idx++, "SCRIPT_NAME", getCGIEnvValue(request, "SCRIPT_NAME"));
	setEnv(env, idx++, "SERVER_NAME", getCGIEnvValue(request, "SERVER_NAME", m_server));
	setEnv(env, idx++, "SERVER_PORT", getCGIEnvValue(request, "SERVER_PORT", m_server));
	setEnv(env, idx++, "SERVER_PROTOCOL", getCGIEnvValue(request, "SERVER_PROTOCOL", NULL, *m_config));
	setEnv(env, idx++, "SERVER_SOFTWARE", getCGIEnvValue(request, "SERVER_SOFTWARE", NULL, *m_config));

	std::map<std::string, std::string>::const_iterator it = request.get_m_headers().begin();
	for (; it != request.get_m_headers().end(); ++it)
	{
		if (it->first[0] == 'X')
		{
			std::string new_header = "HTTP_";
			for (std::string::const_iterator it2 = it->first.begin(); it2 != it->first.end(); ++it2)
				new_header.push_back(std::toupper(*it2));
			setEnv(env, idx++, new_header, it->second);
		}
	}
	return (env);
}

namespace {
	void closes(int fd1 = -1, int fd2 = -1, int fd3 = -1, int fd4 = -1, int fd5 = -1)
	{
		if (fd1 != -1)
			close(fd1);
		if (fd2 != -1)
			close(fd2);
		if (fd3 != -1)
			close(fd3);
		if (fd4 != -1)
			close(fd4);
		if (fd5 != -1)
			close(fd5);
	}

	int pythonCGI(std::string path, char **env)
	{
		PyObject *pModule = NULL;
		PyObject *pFunc = NULL;
		PyObject *pArg = NULL;
		std::string pwd = "import sys; sys.path.insert(0, '";
		std::string env_str;
		char wd[BUFSIZ];

		getcwd(wd, BUFSIZ);
		pwd += (wd + std::string("/cgi-bin"));
		pwd += "')";
		for (int i = 0; env[i]; ++i)
		{
			env_str += env[i];
			env_str += " ";
		}

		Py_Initialize();
		PyRun_SimpleString (pwd.c_str());
		path.erase(0, path.rfind("/") + 1);
		path.erase(path.rfind(".py"), 3);
		pModule = PyImport_ImportModule(path.c_str());
		pFunc   = PyObject_GetAttrString(pModule, "cgi");
		(void)env;
		pArg = Py_BuildValue("(s)", env_str.c_str());
		if(pFunc != NULL) {
			PyEval_CallObject(pFunc, pArg);
			Py_Finalize();
		}
		else {
			exit(EXIT_FAILURE);
		}
		return (1);
	}

	void execveCGI(const Request& request, char **env, int *parent_write_fd, int *child_write_fd)
	{
		closes(parent_write_fd[1], child_write_fd[0]);
		dup2(parent_write_fd[0], 0);
		dup2(child_write_fd[1], 1);
		/* child process */
		char *arg[2] = { const_cast<char *>(request.get_m_script_translated().c_str()), NULL };
		std::string script_name = getCGIEnvValue(request, "SCRIPT_NAME");
		std::string ext = script_name.substr(script_name.rfind(".") + 1);
		if (ext == "php" && execve("./php-cgi", arg, env) == -1)
			exit(EXIT_FAILURE);
		else if (ext == "py" && pythonCGI(request.get_m_script_translated(), env))
			exit(EXIT_SUCCESS);
		else if (execve(arg[0], arg, env) == -1)
			exit(EXIT_FAILURE);
		exit(EXIT_FAILURE);
	}
}

void
Worker::executeCGI()
{
	pid_t pid;
	int parent_write_fd[2];
	int child_write_fd[2];
	char **env;
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	Request::Method method = request.get_m_method();
	std::string body;

	if ((env = createCGIEnv(request)) == NULL)
		return (createResponse(connection, 50005));
	pipe(parent_write_fd);
	pipe(child_write_fd);
	m_child_pid = pid = fork();
	if (pid == 0)
		return (execveCGI(request, env, parent_write_fd, child_write_fd));
	else if (pid < 0) {
		closes(parent_write_fd[0], parent_write_fd[1], child_write_fd[0], child_write_fd[1]);
		return (createResponse(connection, 50006, headers_t()));
	}

	closes(parent_write_fd[0], child_write_fd[1]);
	if (fcntl(parent_write_fd[1], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("write fnctl error");
	if (fcntl(child_write_fd[0], F_SETFL, O_NONBLOCK) == -1)
		throw std::runtime_error("read fnctl error");
	connection.set_m_status(Connection::ON_EXECUTE);
	if (method == Request::POST)
	{
		connection.set_m_write_to_server_fd(parent_write_fd[1]);
		if (request.get_m_transfer_type() == Request::GENERAL)
			connection.set_m_wbuf_for_execute();
		this->fdSet(connection.get_m_write_to_server_fd(), Worker::WRITE_SET);
	}
	else
		close(parent_write_fd[1]);
	connection.set_m_read_from_server_fd(child_write_fd[0]);
	this->fdSet(connection.get_m_read_from_server_fd(), Worker::READ_SET);
	ft::freeDoublestr(&env);
}

namespace {
	bool isAuthorizationRequired(Location* location) { return (!location->get_m_auth_basic_realm().empty()); }
	bool hasCredential(const Request& request) { return (ft::hasKey(request.get_m_headers(), "Authorization")); }
	bool isValidCredentialForm(std::vector<std::string> credential) {
		return (credential.size() == 2 && credential[0] != "basic");
	}
	bool isValidCredentialContent(Location* location, std::vector<std::string>& credential)
	{
		std::string key, value;
		basic_decode(credential[1], key, value);
		return (!(key.empty() || value.empty() || !ft::hasKey(location->get_m_auth_basic_file(), key)
		|| location->get_m_auth_basic_file().find(key)->second != value));
	}
	void makeResponse401(Worker* worker, const Request& request, Connection& connection) {
		std::string header = "WWW-Authenticate:Basic realm=\"";
		header.append(request.get_m_location()->get_m_auth_basic_realm());
		header.append("\", charset=\"UTF-8\"");
		return (worker->createResponse(connection, 40101, headers_t(1, header)));
	}
}

/*
** function: executeAutoindex
** d_type(4) : DIRECTORY
** d_type(8) : REGULAR_FILE
*/

void
Worker::solveRequest()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	Location* location = request.get_m_location();
	Request::Method method = request.get_m_method();
	std::string methodString = request.get_m_method_to_string();

	if (!request.get_m_location()->get_m_echo_msg().empty())
		return (executeEcho());
	if (!ft::hasKey(location->get_m_allow_method(), methodString)) {
		headers_t headers(1, "Allow:" + ft::containerToString(location->get_m_allow_method(), ", "));
		return (createResponse(connection, 40501, headers));
	}
	if (m_config->is_on_plugin_basic_auth() && isAuthorizationRequired(location)) {
		if (!hasCredential(request)) {
			return (makeResponse401(this, request, connection));
		} else {
			std::vector<std::string> credential = ft::split(request.get_m_headers().find("Authorization")->second, ' ');
			if (!isValidCredentialForm(credential))
				return (createResponse(connection, 40022));
			else if (!isValidCredentialContent(location, credential))
				return (createResponse(connection, 40301));
		}
	}
	if (method == Request::TRACE)
		executeTrace();
	else if (request.get_m_uri_type() == Request::DIRECTORY)
		return (executeAutoindex());
	else if (request.get_m_uri_type() == Request::CGI_PROGRAM)
		return (executeCGI());
	else if (method == Request::GET)
		executeGet();
	else if (method == Request::HEAD)
		executeHead();
	else if (method == Request::POST)
		executePost();
	else if (method == Request::PUT)
		executePut();
	else if (method == Request::DELETE)
		executeDelete();
	else if (method == Request::OPTIONS)
		executeOptions();
	else
		throw (400);
}

/* ************************************************************************** */
/* ----------------------------- READ OPERATION ----------------------------- */
/* ************************************************************************** */

bool
Worker::hasRequest()
{
	Connection::Status status = m_connection.get_m_status();

	int fd = m_connection.get_m_client_fd();

	if (status != Connection::ON_WAIT && status != Connection::ON_RECV_CLIENT)
		return (false);
	if (!this->fdIsset(fd, Worker::READ_COPY_SET))
		return (false);
	return (true);
}

namespace {

	bool
	isMethodHasBody(const Request::Method& method) {
		return (method == Request::POST || method == Request::PUT || method == Request::TRACE);
	}

	bool
	isRequestHasBody(Request &request)
	{
		if (isMethodHasBody(request.get_m_method()))
		{
			if (request.get_m_transfer_type() == Request::CHUNKED)
				return (true);
			if (ft::hasKey(request.get_m_headers(), "Content-Length")
				&& ft::stoi(request.get_m_headers().find("Content-Length")->second) > 0)
					return (true);
		}
		return (false);
	}

	bool
	readGeneralBody(Connection& connection, Request& request)
	{
		std::string& buf = const_cast<std::string&>(connection.get_m_rbuf_from_client());

		if (!ft::hasKey(request.get_m_headers(), "Content-Length"))
			throw (41101);
		connection.set_m_token_size(ft::stoi(request.get_m_headers().find("Content-Length")->second));

		if (connection.get_m_readed_size() + static_cast<int>(buf.size()) <= connection.get_m_token_size())
		{
			request.addContent(buf);
			request.addOrigin(buf);
			connection.set_m_readed_size(connection.get_m_readed_size() + buf.size());
			connection.decreaseRbufFromClient(buf.size());
		}
		else
		{
			std::string part = buf.substr(0, connection.get_m_token_size() - connection.get_m_readed_size());
			request.addContent(part);
			request.addOrigin(part);
			connection.decreaseRbufFromClient(part.size());
			connection.set_m_readed_size(connection.get_m_token_size());
		}
		return (connection.get_m_readed_size() == connection.get_m_token_size());
	}

	bool
	readChunkedBody(Connection& connection, Request& request)
	{
		std::string& buf = const_cast<std::string&>(connection.get_m_rbuf_from_client());

		while (true)
		{
			std::string len;
			int content_length = getChunkedSize(buf, len);
			if (content_length == -1)
				return (false);
			if (content_length == 0)
			{
				if (buf.find("\r\n") == std::string::npos)
				{
					buf.insert(0, len + "\r\n");
					return (false);
				}
				if (buf.size() >= 2 && buf[0] == '\r' && buf[1] == '\n')
				{
					connection.decreaseRbufFromClient(2);
					return (true);
				}
				throw (40018);
			}
			if (static_cast<int>(buf.size()) < content_length + 2)
			{
				buf.insert(0, len + "\r\n");
				return (false);
			}
			if (buf.substr(content_length, 2) != "\r\n")
				throw (40021);
			request.addContent(buf.substr(0, content_length));
			request.addOrigin(len + "\r\n");
			request.addOrigin(buf.substr(0, content_length + 2));
			connection.decreaseRbufFromClient(content_length + 2);
		}
	}

	int
	recvWithoutBody(const Connection& connection, char*buf, int buf_size)
	{
		int count;
		int i = 0;
		if ((count = recv(connection.get_m_client_fd(), buf, buf_size, MSG_PEEK)) > 0)
		{
			while (i < count)
			{
				if (buf[i] == '\r' && i + 3 < count && buf[i + 1] == '\n' && buf[i + 2] == '\r' && buf[i + 3] == '\n')
					break ;
				++i;
			}
			if (i == count)
				return (0);
			else if ((count = recv(connection.get_m_client_fd(), buf, i + 4, 0)) > 0)
				return (i + 4);
		}
		if (count == -1) 
			throw (Worker::IOError((("IO error detected to read reqeust message without body for client ") + ft::to_string(connection.get_m_client_fd())).c_str()));
		else
			throw (Worker::IOError((("Connection close detected by client ") + ft::to_string(connection.get_m_client_fd())).c_str()));			
	}

	int
	recvBody(const Connection& connection, char*buf, int buf_size)
	{
		int count;
		const Request& request = connection.get_m_request();

		if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
			return (0);
		if (!isMethodHasBody(request.get_m_method()))
			return (0);
		if ((count = recv(connection.get_m_client_fd(), buf, buf_size, 0)) > 0)
			return (count);
		else if (count == -1)
			throw (Worker::IOError((("IO error detected to read reqeust message without body for client ") + ft::to_string(connection.get_m_client_fd())).c_str()));
		else
			throw (Worker::IOError((("Connection close detected by client ") + ft::to_string(connection.get_m_client_fd())).c_str()));
	}
}

std::string
Worker::getExtension(std::string path)
{
	std::string ret;

	if (path.find(".") != std::string::npos)
	{
		size_t idx = path.rfind(".");
		if (idx != path.size() - 1)
			ret = path.substr(idx + 1);
	}
	return (ret);
}

std::string
Worker::getMimeTypeHeader(std::string path)
{
	std::string extension = getExtension(path);
	std::string ret;
	if (!extension.empty() && ft::hasKey(mime_types, extension))
		ret = "Content-type:" + mime_types[extension];
	else
		ret = "Content-type:test-for-evaluation";
	return (ret);
}

time_t
Worker::getLastModified(std::string path)
{
	struct stat buf;
	ft::bzero(&buf, sizeof(struct stat));
	stat(path.c_str(), &buf);
	return (buf.st_mtimespec.tv_sec);
}

std::string
Worker::getLastModifiedHeader(std::string path)
{
	time_t modified = getLastModified(path);
	struct tm t;
	char buff[1024];

	ft::convertTimespecToTm(modified, &t);
	strftime(buff, sizeof(buff), "%a, %d %b %Y %X GMT", &t);
	return ("Last-Modified:" + std::string(buff));
}

bool
Worker::parseStartLine()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	size_t new_line;

	if ((new_line = connection.get_m_rbuf_from_client().find("\r\n")) != std::string::npos)
	{
		std::string start_line = connection.get_m_rbuf_from_client().substr(0, new_line);
		connection.decreaseRbufFromClient(start_line.size() + 2);
		request.addOrigin(start_line + "\r\n", true);
		request = Request(&connection, m_server, start_line);
		return (true);
	} else if (connection.get_m_rbuf_from_client().size() > REQUEST_URI_LIMIT_SIZE_MAX)
		throw (40006);
	return (false);
}

bool
Worker::parseHeader()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());
	std::string& rbuf = const_cast<std::string&>(connection.get_m_rbuf_from_client());
	std::string line;

	while (ft::getline(rbuf, line, REQUEST_HEADER_LIMIT_SIZE_MAX) >= 0)
	{
		if (line == "")
		{
			if (!ft::hasKey(request.get_m_headers(), "Host"))
				throw (40011);
			return (true);
		}
		if (!request.isValidHeader(line))
			throw (40010);
		request.addHeader(line);
	}
	return (false);
}

bool
Worker::parseBody()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	if (!isMethodHasBody(request.get_m_method()))
		return (true);
	if (request.get_m_method() == Request::POST && request.get_m_transfer_type() == Request::CHUNKED)
		return (true);
	if (request.get_m_transfer_type() == Request::GENERAL)
		return (readGeneralBody(connection, request));
	if (request.get_m_transfer_type() == Request::CHUNKED)
		return (readChunkedBody(connection, request));
	return (false);
}

bool
Worker::recvRequest()
{
	Connection& connection = m_connection;
	Request& request = const_cast<Request&>(connection.get_m_request());

	char buf[BUFFER_SIZE];
	int count = BUFFER_SIZE - connection.get_m_rbuf_from_client().size();
	Request::Phase phase = request.get_m_phase();
	connection.set_m_status(Connection::ON_RECV_CLIENT);
	if (phase == Request::READY && hasRequest() && (count = recvWithoutBody(connection, buf, sizeof(buf))) > 0)
		connection.addRbufFromClient(buf, count);
	if (count < 0) 
		return (false);
	if (phase == Request::READY && parseStartLine())
		phase = Request::ON_HEADER;
	if (phase == Request::ON_HEADER && parseHeader())
	{
		request.set_m_phase(phase = Request::ON_BODY);
		if (isRequestHasBody(request))
			return (true);
	}
	if (phase == Request::ON_BODY && (count = recvBody(connection, buf, sizeof(buf))) > 0)
		connection.addRbufFromClient(buf, count);
	if (phase == Request::ON_BODY && parseBody())
		phase = Request::COMPLETE;
	if (phase == Request::COMPLETE)
		connection.set_m_last_request_at();
	request.set_m_phase(phase);
	return (true);
}

void
Worker::runRecvAndSolve()
{
	Connection& connection = m_connection;
	try {
		recvRequest();
	} catch (int status_code) {
		return (createResponse(connection, status_code));
	} catch (Worker::IOError& e) {
		throw (e);
	} catch (std::exception& e) {
		ft::log(ServerManager::log_fd, std::string(ft::getTimestamp() + "[Failed][Request] Failed to create request because ") + e.what());
		return (createResponse(connection, 50001));
	}
	const Request& request = connection.get_m_request();
	if (request.get_m_phase() == Request::COMPLETE)
	{
		writeCreateNewRequestLog(request);
		connection.set_m_status(Connection::ON_EXECUTE);
		solveRequest();
	}
	return ;
}

/* ************************************************************************** */
/* -------------------------- CONNECTION MANAGEMENT ------------------------- */
/* ************************************************************************** */

void
Worker::createConnection(Job job) {
	m_connection = Connection(job.client_fd, job.ip, job.port);
	m_connection.set_m_last_request_at();
}

void
Worker::closeConnection()
{
	int fd[3];
	fd[0] =  m_connection.get_m_write_to_server_fd();
	fd[1] =  m_connection.get_m_read_from_server_fd();
	fd[2] = m_connection.get_m_client_fd();

	closes(fd[0], fd[1], fd[2]);
}

void
Worker::clearConnection() {
	m_connection.clear();
}

int
Worker::workerSelect()
{
	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	return (select(get_max_fd() + 1, &m_fdset.read_copy_set, &m_fdset.write_copy_set, NULL, &timeout));
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

bool
Worker::runWork()
{
	m_connection.set_m_last_request_at();
	if (hasSendWork()) {
		if (!runSend())
			return (false);
	}
	else if (hasExecuteWork()) {
		runExecute();
	}
	if (hasRequest()) {
		runRecvAndSolve();
	}
	return (true);
}

namespace {
	void
	writeCloseClientConnection(ServerManager* manager, Server* server, int idx, int fd)
	{
		if (!manager->get_m_config().is_on_plugin_health_check())
			return ;
		std::string text = ft::getTimestamp() + "[Closed][Connection]";
		text += "[Server:" + server->get_m_host() + ":" + ft::to_string(server->get_m_port()) + "]";
		text += "[Worker:" + ft::to_string(idx) + "/" + ft::to_string(server->get_m_worker_count()) + "]";
		text += "[Client:" + ft::to_string(fd) + "]";
		text += " client connection closed.\n";
		ft::log(ServerManager::log_fd, text);
		return ;
	}
}

void
workWithConnection(Worker::threadParam *param)
{
	ServerManager* manager = param->manager;
	Server* server = param->server;
	Worker* worker = param->worker;
	pthread_mutex_t* live_mutex = param->live_mutex;
	int client_fd = param->job.client_fd;
	int cnt;

	worker->fdZero(Worker::ALL_SET);
	worker->fdSet(client_fd, Worker::READ_SET);

	pthread_mutex_lock(live_mutex);
	bool server_live = server->get_m_server_live();
	pthread_mutex_unlock(live_mutex);

	// SELECT AND PROCESS WITH OLD SERVER FUNCTION; WHEN END, CLOSE CONNECTION FD;
	while (server_live)
	{
		worker->writeWorkerHealthLog("in of connection");
		pthread_mutex_lock(live_mutex);
		server_live = server->get_m_server_live();
		pthread_mutex_unlock(live_mutex);
		worker->fdCopy(Worker::ALL_SET);

		if ((cnt = worker->workerSelect()) == -1)
		{
			perror("Worker select error: ");
			throw std::runtime_error("select error");
		}
		else if (cnt == 0) {
			if (worker->get_m_connection().isOverTime())
				break ;
			continue ;
		}
		try {
			if (!worker->runWork()) {
				break ;
			}
		} catch (Worker::IOError& e) {
			ft::log(ServerManager::log_fd, e.location());
			break ;
		}
	}
	worker->closeConnection();
	writeCloseClientConnection(manager, server, worker->get_m_idx(), client_fd);
	return ;
}

void
*worker_routine(void *parameter)
{
	Worker::threadParam *param = reinterpret_cast<Worker::threadParam *>(parameter);
	Worker* worker = param->worker;
	Server* server = param->server;
	pthread_mutex_t* job_mutex = param->job_mutex;
	pthread_mutex_t* live_mutex = param->live_mutex;
	std::queue<Job>* job_queue = server->get_m_job_queue();

	pthread_mutex_lock(live_mutex);
	bool server_live = server->get_m_server_live();
	pthread_mutex_unlock(live_mutex);

	while (server_live)
	{
		worker->writeWorkerHealthLog("");
		pthread_mutex_lock(live_mutex);
		server_live = server->get_m_server_live();
		pthread_mutex_unlock(live_mutex);

		pthread_mutex_lock(job_mutex);
		if (server->get_m_job_queue()->empty()) {
			pthread_mutex_unlock(job_mutex);
			continue ;
		}
		worker->set_m_work_status(true);
		param->job = job_queue->front();
		job_queue->pop();
		pthread_mutex_unlock(job_mutex);
		worker->set_m_client_fd(param->job.client_fd);
		worker->createConnection(param->job);
		worker->writeWorkStartLog();
		workWithConnection(param);
		worker->set_m_work_status(false);
	}
	exit(EXIT_SUCCESS);
}

void
Worker::run() {
	pthread_create(&m_pthread, NULL, worker_routine, reinterpret_cast<void *>(&m_param));
}

void
Worker::exit() {
	void *status;
	pthread_join(m_pthread, &status);
	delete m_config;
	delete m_server;
}

/* ************************************************************************** */
/* ------------------------------ LOG FUNCTION ------------------------------ */
/* ************************************************************************** */

void
Worker::writeWorkerHealthLog(std::string msg)
{
	if (!m_config->is_on_plugin_health_check() || !ft::isRightTime(m_server->get_m_health_check_interval()))
		return ;
	std::string text = ft::getTimestamp() + "[HealthCheck]";
	text += "[Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += " worker is live healthy." + msg + "\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Worker::writeWorkStartLog()
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Started]";
	text += "[Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += "[Client:" + ft::to_string(m_client_fd) + "]";
	text += " new work started.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Worker::writeCreateNewRequestLog(const Request& request)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Request][Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += "[Client:" + ft::to_string(m_client_fd) + "]";
	text += "[Method:" + request.get_m_method_to_string() + "]";
	text += "[URI:" + request.get_m_uri() + "]";
	text += "[Path:" + request.get_m_script_translated() + "]";
	if (request.get_m_method() == Request::GET)
		text.append("[Query:" + request.get_m_query() + "]");
	text += " new request created.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Worker::reportCreateNewRequestLog(int status)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Failed][Request][Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += "[Client:" + ft::to_string(m_client_fd) + "]";
	text += "[Status:" + ft::to_string(status) + "]";
	text += " failed to create new request.\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Worker::writeCreateNewResponseLog(const Response& response)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Created][Response:" + ft::to_string(response.get_m_status_code());
	text += "(" + response.get_m_status_description() + ")]";
	text += "[Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += "[Client:" + ft::to_string(m_client_fd) + "]";
	text += "[Body:" + ft::to_string(response.get_m_content().size()) + "] new response created\n";
	text += response.get_m_content().substr(0, 100) + "\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

void
Worker::writeSendResponseLog(const Response& response)
{
	if (!m_config->is_on_plugin_health_check())
		return ;
	std::string text = ft::getTimestamp() + "[Sended][Response:" + ft::to_string(response.get_m_status_code());
	text += "(" + response.get_m_status_description() + ")]";
	text += "[Server:" + m_server->get_m_host() + ":" + ft::to_string(m_server->get_m_port()) + "]";
	text += "[Worker:" + ft::to_string(m_idx) + "/" + ft::to_string(m_server->get_m_worker_count()) + "]";
	text += "[Client:" + ft::to_string(m_client_fd) + "]";
	text += "[Body:" + ft::to_string(response.get_m_content().size()) + "] response sended\n";
	ft::log(ServerManager::log_fd, text);
	return ;
}

