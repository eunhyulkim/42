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

	bool	isValidNotEmpty(char const *arg)
	{
		int		i = 0;

		while (arg[i] && !ft_isset(arg[i], "0123456789"))
			i++;
		return (arg[i] ? true : false);
	}

	bool	isValidBracketAndCharacter(char const *arg)
	{
		int		i = -1;
		bool	bracket = false;
		char 	c;

		while (arg[++i] != '\0')
		{
			c = arg[i];
			if (!ft_isset(c, "0123456789. +-*/()"))
				throw("unvalid char is included");
			if ((c == '(' && bracket) || (c == ')' && !bracket))
				throw("bracket is ambigous");
			else if (c == '(' || c == ')')
				bracket = !bracket;
		}
		if (bracket)
			throw("bracket is not closed");
		return (true);
	}

	bool	isValidDotAndOperator(char const *arg)
	{
		int		i = -1;
		int		j;
		char 	c;

		while (arg[++i] != '\0')
		{
			c = arg[i];
			if (ft_isset(c, "+-/*") && (i == 0 || arg[i - 1] != ' ' \
			|| arg[i + 1] != ' '))
				throw("operator's left and right character must be space");
			if (c == '.' && (i == 0 || arg[i - 1] < '0' || arg[i - 1] > '9' \
			|| arg[i + 1] < '0' || arg[i + 1] > '9'))
				throw("dot used twice per number");
			if (c == '.')
			{
				j = i + 1;
				while (arg[j] && arg[j] != ' ' && arg[j] != '.')
					j++;
				if (j == '.')
					throw("dot use just once per number");
			}
		}
		return (true);
	}

	bool	isValidArgumentCountInBracket(char const *arg)
	{
		int		i = -1;
		int		cnt;

		while (arg[++i] != '\0')
		{
			while (arg[i] && arg[i] != '(')
				i++;
			if (arg[i] == '(')
			{
				cnt = 0;
				while (arg[i] && arg[i] != ')')
				{
					if (arg[i] == ' ')
						cnt++;
					i++;
				}
				if (cnt > 4)
					throw("argument in bracket is more than two.");
				if (!arg[i])
					break ;
			}
			if (!arg[i])
				break ;
		}
		return (true);
	}

	bool	isValidSpace(char const *arg)
	{
		int		i = -1;
		char	prev = '\0';

		while (arg[++i] != '\0')
		{
			if (prev == ' ' && arg[i] == ' ')
				throw("space is overlap");
			if (arg[i] == '(' && ((i != 0 && arg[i - 1] != ' ') || (arg[i + 1] != ' ')))
				throw("space is not near bracket");
			if (arg[i] == ')' && ((arg[i + 1] != '\0' && arg[i + 1] != ' ') || (arg[i - 1] != ' ')))
				throw("space is not near bracket");
			prev = arg[i];
		}
		return (true);
	}

}

namespace parse {
	bool	main(char *arg) {
		if (!isValidNotEmpty(arg))
			return (false);
		if (!isValidBracketAndCharacter(arg))
			return (false);
		if (!isValidDotAndOperator(arg))
			return (false);
		if (!isValidSpace(arg))
			return (false);
		if (!isValidArgumentCountInBracket(arg))
			return (false);
		return (true);
	}
}
