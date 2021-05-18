#include "eval_expr.hpp"

namespace {
	std::string calc(std::string _data, std::string op, std::string _obj)
	{
		Fixed data(_data);
		Fixed obj(_obj);
		std::string ret;
		if (op == "+")
			ret = std::to_string(data + obj);
		if (op == "-")
			ret = std::to_string(data - obj);
		if (op == "*")
			ret = std::to_string(data * obj);
		if (op == "/")
			ret = std::to_string(data / obj);
		return (ret);
	}

	std::string	eval_bracket(std::string arg)
	{
		std::istringstream is(arg);
		std::ostringstream os;
		std::string data;
		std::string op;
		std::string obj;

		while (is >> data)
		{
			if (data == "(")
			{
				is >> data;
				is >> op;
				is >> obj;
				os << calc(data, op, obj);
				is >> data;
			}
			else
				os << data;
			os << " ";
		}
		return (os.str());
	}

	std::string	eval_primary(std::string arg)
	{
		std::istringstream is(arg);
		std::ostringstream os;
		std::string data;
		std::string op;
		std::string obj;

		while (is >> data)
		{
			if (!(is >> op))
			{
				os << data;
				break ;
			}
			if (op == "+" || op == "-")
			{
				os << data;
				os << " ";
				os << op;
				os << " ";
				continue;
			}
			while (op == "*" || op == "/")
			{
				is >> obj;
				data = calc(data, op, obj);
				if (!(is >> op))
				{
					os << data;
					break ;
				}
				if (op == "+" || op == "-")
				{
					os << data;
					os << " ";
					os << op;
					os << " ";
					continue;
				}
			}
		}
		return (os.str());
	}

	std::string	eval_secondary(std::string arg)
	{
		std::istringstream is(arg);
		std::ostringstream os;
		std::string data;
		std::string op;
		std::string obj;

		while (is >> data)
		{
			if (!(is >> op))
			{
				os << data;
				break ;
			}
			while (true)
			{
				is >> obj;
				data = calc(data, op, obj);
				if (!(is >> op))
				{
					os << data;
					break ;
				}
			}
		}
		return (os.str());
	}
}

namespace eval {
	void	main(char const *arg)
	{
		std::string str(arg);
		std::string data;
		std::string obj;

		str = eval_bracket(str);
		str = eval_primary(str);
		str = eval_secondary(str);
		std::cout << str << std::endl;
	}
}
