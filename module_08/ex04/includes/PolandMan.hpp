#ifndef POLAND_MAN_HPP
# define POLAND_MAN_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <cmath>
# include <vector>
# include <iomanip>

class PolandMan
{
	private:
		std::vector<std::string> m_tokens;
		std::vector<int> m_token_types;
		std::vector<std::string> m_postfix;
		std::vector<std::string> m_stack;
		int m_result;
	public:
		PolandMan();
		PolandMan(const PolandMan& copy);
		PolandMan& operator=(const PolandMan& obj);
		virtual ~PolandMan();

		enum TokenType {
			DEFAULT,
			NUM,
			PAROPEN,
			PARCLOSE,
			OP
		};

		/* setter function */
		bool set_m_tokens(std::string raw_string);
		void set_m_postfix();
		// void set_m_stack(std::vector<std::string> stack);

		/* declare member function */
		void printTokens(std::string prefix);
		void printPostfix(std::string prefix);
		void printStack(void);
		void printResult();

		void runCalc(void);
};

#endif
