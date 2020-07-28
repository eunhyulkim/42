#include "eval_expr.hpp"

namespace {
	bool	ft_isset(char c, char const *set)
	{
		int		i;

		i = 0;
		while (set[i] && set[i] != c)
			i++;
		return (set[i] != '\0');
	}
}
namespace parse {
	bool	main(char *arg){
		int		i = -1;
		int		space;
		bool	bracket;
		char 	c;

		bracket = false; 
		while (arg[++i] != '\0')
		{
			c = arg[i];
			if (!ft_isset(c, "0123456789+-*/()"))
				throw("unvalid char is included");
			if ((c == '(' && bracket) || (c == ')' && !bracket))
				throw("bracket is ambigous");
			else if (c == '(' || c == ')')
				bracket = !bracket;
			else if (c == ' ' && )

		}
		if (bracket)
			throw("bracket is not closed");
		return (true);
	}
}