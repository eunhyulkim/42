#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <ctime>
#include <iomanip>

class Logger;

class Logger {
	private:
		std::ofstream	*os;
		void		logToConsole(std::string entry);
		void		logToFile(std::string entry);
		std::string	MakeLogEntry(std::string const & msg);
	public:
		Logger();
		~Logger();
		void 		log(std::string const & dest, std::string const & msg);
};
#endif
