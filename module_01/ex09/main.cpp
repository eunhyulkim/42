#include "Logger.hpp"

namespace {
	void	leaks_test(void)
	{
		Logger loggy;

		loggy.log("file", "this if filelog0");
		loggy.log("console", "this if consolelog0");
		loggy.log("invalid", "this if invalidlog0");
		loggy.log("file", "this if filelog1");
		loggy.log("console", "this if consolelog1");
		loggy.log("invalid", "this if invalidlog1");
		loggy.log("file", "this if filelog2");
		loggy.log("file", "this if filelog3");
		loggy.log("file", "this if filelog4");
		loggy.log("console", "this if consolelog2");
		loggy.log("console", "this if consolelog3");
		loggy.log("console", "this if consolelog4");
		loggy.log("invalid", "this if invalidlog2");
		loggy.log("invalid", "this if invalidlog3");
		loggy.log("invalid", "this if invalidlog4");
	}
}

int		main(void)
{
	leaks_test();
	return (0);
}
