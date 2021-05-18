#include "Logger.hpp"

namespace {
	void	print(std::string msg) {
		std::cout << std::endl
		<< "\033[1;32;44m" << msg << "\033[0m"
		<< std::endl << std::endl;
	}
	void	leaks_test(void)
	{
		Logger loggy;

		loggy.log("file", "this if filelog0");
		print("LOG TO CONSOLE");
		loggy.log("console", "this if consolelog0");
		print("INVALID ARG");
		loggy.log("invalid", "this if invalidlog0");
		loggy.log("file", "this if filelog1");
		print("LOG TO CONSOLE");
		loggy.log("console", "this if consolelog1");
		print("INVALID ARG");
		loggy.log("invalid", "this if invalidlog1");
		loggy.log("file", "this if filelog2");
		loggy.log("file", "this if filelog3");
		loggy.log("file", "this if filelog4");
		print("LOG TO CONSOLE");
		loggy.log("console", "this if consolelog2");
		loggy.log("console", "this if consolelog3");
		loggy.log("console", "this if consolelog4");
		print("INVALID ARG");
		loggy.log("invalid", "this if invalidlog2");
		loggy.log("invalid", "this if invalidlog3");
		loggy.log("invalid", "this if invalidlog4");
		print("OTHER LOGS ARE IN THE FILE");
	}
}

int		main(void)
{
	leaks_test();
	return (0);
}
