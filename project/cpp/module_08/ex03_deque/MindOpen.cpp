#include "MindOpen.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

MindOpen::MindOpen() {}

MindOpen::MindOpen(const MindOpen& copy)
: m_raw_string(copy.m_raw_string), m_program(copy.m_program) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

MindOpen::~MindOpen()
{
	this->m_raw_string.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

MindOpen&
MindOpen::operator=(const MindOpen& obj)
{
	if (this == &obj)
		return (*this);
	this->m_raw_string = obj.m_raw_string;
	this->m_program = obj.m_program;
	return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

bool
MindOpen::set_m_raw_string(const std::string& filename)
{ 
	std::string path = std::string(std::string(std::getenv("PWD")).append(std::string("/") + filename));
	std::ifstream in(path);
	if (!in.is_open())
		return (false);

	std::string raw_string, line;
	while (std::getline(in, line))
		raw_string.append(line);

	if (in.bad())
	{
		in.close();
		return (false);
	}
	in.close();
	this->m_raw_string = raw_string;
	return (true);
}

bool
MindOpen::set_m_program(void)
{
	std::string str = this->m_raw_string;
	size_t length = str.length();
	int bracketCount = 0;

	for (size_t i = 0; i < length; i++)
	{
		switch (str[i])
		{
			case '>':
				this->m_program.addInstruction(new IncPtrInstruction(this->m_program));
				break ;
			case '<':
				this->m_program.addInstruction(new DecPtrInstruction(this->m_program));
				break ;
			case '+':
				this->m_program.addInstruction(new IncValInstruction(this->m_program));
				break ;
			case '-':
				this->m_program.addInstruction(new DecValInstruction(this->m_program));
				break ;
			case ',':
				this->m_program.addInstruction(new InputInstruction(this->m_program));
				break ;
			case '.':
				this->m_program.addInstruction(new OutputInstruction(this->m_program));
				break ;
			case '[':
				bracketCount++;
				this->m_program.addInstruction(new LoopStartInstruction(this->m_program));
				break ;
			case ']':
			{
				if (bracketCount == 0)
					return (false);
				bracketCount--;
				this->m_program.addInstruction(new LoopEndInstruction(this->m_program));
				break ;
			}
		}
	}
	if (bracketCount != 0)
		return (false);
	return (true);
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
MindOpen::runProgram(void) {
	this->m_program.runProgram();
}
