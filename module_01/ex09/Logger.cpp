#include "Logger.hpp"

typedef void (Logger::* func_member)(std::string);

namespace {
	std::string	get_timestamp(bool has_bracket = false)
	{
		std::time_t	t = std::time(0);
		std::tm* now = std::localtime(&t);
		std::stringstream	ss;

		if (has_bracket)
			ss << "[";
		ss << (now->tm_year + 1900);
		ss << std::setw(2) << std::setfill('0') << (now->tm_mon + 1);
		ss << std::setw(2) << std::setfill('0') << now->tm_mday << "_";
		ss << std::setw(2) << std::setfill('0') << now->tm_hour;
		ss << std::setw(2) << std::setfill('0') << now->tm_min;
		ss << std::setw(2) << std::setfill('0') << now->tm_sec;
		if (has_bracket)
			ss << "]";
		return (ss.str());
	}
}

Logger::Logger(){
	this->os = new std::ofstream(get_timestamp());
}

Logger::~Logger() {
	(this->os)->close();
	delete os;
}

std::string	Logger::MakeLogEntry(std::string const &msg){
	return (get_timestamp(true).append(msg));
}

void		Logger::logToConsole(std::string entry){
	std::cout << entry << std::endl;
}

void		Logger::logToFile(std::string entry){
	*this->os << entry << std::endl;
}

void		Logger::log(std::string const &dest, std::string const &msg){
	std::string dest_name[2] = {"file", "console"};
	func_member	member[2] = {&Logger::logToFile, &Logger::logToConsole};
	if (dest == dest_name[0])
		(this->*member[0])(MakeLogEntry(msg));
	else if (dest == dest_name[1])
		(this->*member[1])(MakeLogEntry(msg));
	else
		std::cout << "dest is unvalid" << std::endl;
}
