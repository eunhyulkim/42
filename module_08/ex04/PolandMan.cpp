#include "includes/PolandMan.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

PolandMan::PolandMan()
{
	this->m_tokens.clear();
	this->m_postfix.clear();
	this->m_stack.clear();
	this->m_token_types.clear();
	this->m_result = 0;
}

PolandMan::PolandMan(const PolandMan& copy)
: m_tokens(copy.m_tokens), 
m_token_types(copy.m_token_types), 
m_postfix(copy.m_postfix), 
m_stack(copy.m_stack), m_result(0) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

PolandMan::~PolandMan()
{
	this->m_tokens.clear();
	this->m_postfix.clear();
	this->m_stack.clear();
	this->m_token_types.clear();
	this->m_result = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

PolandMan& PolandMan::operator=(const PolandMan& obj)
{
	if (this == &obj)
		return (*this);
	this->m_tokens = obj.m_tokens;
	this->m_postfix = obj.m_postfix;
	this->m_stack = obj.m_stack;
	this->m_token_types = obj.m_token_types;
	this->m_result = obj.m_result;
	return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

namespace {
	int getGrade(std::string op)
	{
		if (op == "+")
			return (2);
		else if (op == "-")
			return (2);
		else if (op == "*")
			return (3);
		else if (op == "/")
			return (3);
		else if (op == "^")
			return (4);
		return (0);
	}
}

bool
PolandMan::set_m_tokens(std::string raw_string)
{
	std::string& rs = raw_string;
	int bracket = 0;
	bool prevNum = false;

	for (size_t i = 0; i < rs.length(); i++)
	{
		if (rs[i] == ' ')
			continue ;
		else if (rs[i] == '+' || rs[i] == '-' || rs[i] == '*' || rs[i] == '/' \
		|| rs[i] == '^' || rs[i] == '(' || rs[i] == ')')
		{
			this->m_tokens.push_back(std::string(1, rs[i]));
			int cmd = DEFAULT;
			if (rs[i] == '+' || rs[i] == '-' || rs[i] == '*' || rs[i] == '/' || rs[i] == '^')
			{
				if (prevNum == false)
					return (false);
				prevNum = false;
				cmd = OP;
			}
			else if (rs[i] == '(')
			{
				bracket++;
				cmd = PAROPEN;
			}
			else if (rs[i] == ')')
			{
				bracket--;
				if (bracket < 0)
					return (false);
				cmd = PARCLOSE;
			}
			this->m_token_types.push_back(cmd);
		}
		else if (rs[i] >= '0' && rs[i] <= '9')
		{
			if (prevNum == true)
				return (false);
			prevNum = true;
			int last = i;
			while (rs[last] >= '0' && rs[last] <= '9')
				last++;
			this->m_tokens.push_back(rs.substr(i, last - i));
			this->m_token_types.push_back(NUM);
			i = last - 1;
		}
		else
			return (false);
	}
	if (bracket != 0 || prevNum == false)
		return (false);
	return (true);
}

void
PolandMan::set_m_postfix(void)
{
	this->m_token_types.clear();
	size_t size = this->m_tokens.size();

	for (size_t i = 0; i < size; i++)
	{
		int type = this->m_token_types[i];
		int grade = getGrade(this->m_tokens[i]);
		if (this->m_tokens[i] == "^")
			grade++;

		if (type == NUM)
		{
			this->m_postfix.push_back(this->m_tokens[i]);
			this->m_token_types.push_back(NUM);
		}
		else if (type == PAROPEN)
			this->m_stack.push_back(this->m_tokens[i]);
		else if (type == PARCLOSE)
		{
			while (!this->m_stack.empty() && this->m_stack.back() != "(")
			{
				this->m_postfix.push_back(this->m_stack.back());
				this->m_stack.pop_back();
				std::string& arg = this->m_postfix.back();
				if (arg == "+" || arg == "-" || arg == "*" || arg == "/" || arg == "^")
					this->m_token_types.push_back(OP);
				else
					this->m_token_types.push_back(NUM);
			}
			this->m_stack.pop_back();
		}
		else if (type == OP)
		{
			while (!this->m_stack.empty() && grade <= getGrade(this->m_stack.back()))
			{
				this->m_postfix.push_back(this->m_stack.back());
				this->m_stack.pop_back();
				this->m_token_types.push_back(OP);
			}
			this->m_stack.push_back(this->m_tokens[i]);
		}
	}
	
	while (!this->m_stack.empty())
	{
		this->m_postfix.push_back(this->m_stack.back());
		this->m_stack.pop_back();
		std::string& arg = this->m_postfix.back();
		if (arg == "+" || arg == "-" || arg == "*" || arg == "/" || arg == "^")
			this->m_token_types.push_back(OP);
		else
			this->m_token_types.push_back(NUM);
	}
	this->m_stack.clear();	
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
PolandMan::printTokens(std::string prefix)
{
	size_t size = this->m_tokens.size();

	std::cout << prefix << ": ";
	for (size_t i = 0; i < size; i++)
	{
		if (i != 0)
			std::cout << " ";
		int type = m_token_types[i];
		if (type == OP || type == NUM)
		{
			if (type == OP)
				std::cout << "Op(";
			else if (type == NUM)
				std::cout << "Num(";
			std::cout << m_tokens[i];
			std::cout << ")";
		}
		else if (type == PAROPEN)
			std::cout << "ParOpen";
		else if (type == PARCLOSE)
			std::cout << "ParClose";
	}
	std::cout << std::endl;
	
}

void
PolandMan::printPostfix(std::string prefix)
{
	size_t size = this->m_postfix.size();

	std::cout << prefix << ": ";
	for (size_t i = 0; i < size; i++)
	{
		if (i != 0)
			std::cout << " ";
		int type = m_token_types[i];
		if (type == OP || type == NUM)
		{
			if (type == OP)
				std::cout << "Op(";
			else if (type == NUM)
				std::cout << "Num(";
			std::cout << m_postfix[i];
			std::cout << ")";
		}
	}
	std::cout << std::endl;	
}

void
PolandMan::printStack(void)
{
	size_t size = this->m_stack.size();

	std::cout << std::left << "\033[1;36;40mST\033[0m";
	for (size_t i = size; i > 0; i--)
	{
		std::cout << " ";
		std::cout << this->m_stack[i - 1];
	}
	std::cout << "]" << std::endl;
	
}

namespace {
	std::string addCalc(int first, int second)
	{
		std::cout << std::setw(26) << std::left << "\033[1;36;40mI\033[0m OP(+)";
		std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Add   ";
		int result = first + second;
		return (std::to_string(result));
	}

	std::string subCalc(int first, int second)
	{
		std::cout << std::setw(26) << std::left << "\033[1;36;40mI\033[0m OP(-)";
		std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Substract   ";
		int result = first - second;
		return (std::to_string(result));
	}

	std::string mulCalc(int first, int second)
	{
		std::cout << std::setw(26) << std::left << "\033[1;36;40mI\033[0m OP(*)";
		std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Multiply   ";
		int result = first * second;
		return (std::to_string(result));
	}

	std::string divCalc(int first, int second)
	{
		std::cout << std::setw(26) << std::left << "\033[1;36;40mI\033[0m OP(/)";
		std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Devide   ";
		int result = first / second;
		return (std::to_string(result));
	}

	std::string powCalc(int first, int second)
	{
		std::cout << std::setw(26) << std::left << "\033[1;36;40mI\033[0m OP(^)";
		std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Pow   ";
		int result = std::pow(first, second);
		return (std::to_string(result));
	}
}

void
PolandMan::runCalc(void)
{
	this->m_stack.clear();
	size_t size = this->m_postfix.size();
	for (size_t i = 0; i < size; i++)
	{
		if (this->m_token_types[i] == NUM)
		{
			std::string num = std::string("\033[1;36;40mI\033[0m Num(") + this->m_postfix[i] + ")";
			std::cout << std::setw(26) << std::left << num;
			std::cout << std::setw(32) << "| \033[1;36;40mOP\033[0m Push ";
			this->m_stack.push_back(this->m_postfix[i]);
		}
		else
		{
			std::string op = this->m_postfix[i];

			int second = std::stoi(this->m_stack.back());
			this->m_stack.pop_back();
			int first = std::stoi(this->m_stack.back());
			this->m_stack.pop_back();
	
			if (op == "+")
				this->m_stack.push_back(addCalc(first, second));
			else if (op == "-")
				this->m_stack.push_back(subCalc(first, second));
			else if (op == "*")
				this->m_stack.push_back(mulCalc(first, second));
			else if (op == "/")
				this->m_stack.push_back(divCalc(first, second));
			else if (op == "^")
				this->m_stack.push_back(powCalc(first, second));
		}
		this->printStack();
	}
	this->m_result = std::stoi(this->m_stack.back());
}

void
PolandMan::printResult(void)
{
	std::cout << "Result: " << this->m_result << std::endl;
}
