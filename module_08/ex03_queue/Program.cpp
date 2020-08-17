#include "Program.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Program::Program()
{
	this->m_instruction_pos = 0;
	this->m_pointer = 0;
	this->m_instruction_size = 0;
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
}

Program::Program(const Program& copy)
{
	this->m_instruction_pos = 0;
	this->m_pointer = 0;
	this->m_instruction_size = 0;
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = copy.m_stack[i];
	this->m_instructions = copy.m_instructions;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Program::~Program()
{
	this->m_instruction_pos = 0;
	this->m_pointer = 0;
	this->m_instruction_size = 0;
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
	while (!this->m_instructions.empty())
		this->m_instructions.pop();
	// this->m_instructions.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Program& Program::operator=(const Program& obj)
{
	if (this == &obj)
		return (*this);
	this->m_instruction_pos = obj.m_instruction_pos;
	this->m_pointer = obj.m_pointer;
	this->m_instruction_size = obj.m_instruction_size;
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
	while (!this->m_instructions.empty())
		this->m_instructions.pop();
	// this->m_instructions.clear();
	this->m_instructions = obj.m_instructions;
	this->m_log_instructions = obj.m_log_instructions;
	return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Program::addInstruction(Instruction *instruction) {
	// this->m_instructions.push_back(instruction);
	this->m_instructions.push(instruction);
	this->m_instruction_size++;
}

void
Program::incPtr(void) {
	this->m_pointer++;
}

void
Program::decPtr(void) {
	this->m_pointer--;
}

void
Program::incVal(void) {
	this->m_stack[this->m_pointer]++;
}

void
Program::decVal(void) {
	this->m_stack[this->m_pointer]--;
}

void
Program::loopStart(bool startByQueue)
{
	if (this->m_stack[this->m_pointer] != 0)
		return ;
	
	if (startByQueue)
	{
		this->m_log_instructions.push_back(this->m_instructions.front()->getType());
		this->m_instructions.pop();
	}
	this->m_instruction_pos++;

	int pair_mask = 0;

	while (this->m_instruction_pos < this->m_instruction_size && pair_mask >= 0)
	{
		bool inQueue = (this->m_instruction_pos >= this->m_log_instructions.size());
		int cmd = DEFAULT;
		if (!inQueue)
			cmd = this->m_log_instructions[this->m_instruction_pos];
		else
			cmd = this->m_instructions.front()->getType();
		if (cmd == LOOPSTART)
			pair_mask++;
		else if (cmd == LOOPEND)
			pair_mask--;
		if (inQueue)
		{
			this->m_log_instructions.push_back(cmd);
			this->m_instructions.pop();
		}
		this->m_instruction_pos++;
	}
	this->m_instruction_pos--;
}

void
Program::loopEnd(void)
{
	if (this->m_stack[this->m_pointer] == 0)
		return ;

	int pair_mask = 0;
	this->m_instruction_pos--;
	while (this->m_instruction_pos >= 0 && pair_mask >= 0)
	{
		if (this->m_log_instructions[this->m_instruction_pos] == LOOPEND)
			pair_mask++;
		else if (this->m_log_instructions[this->m_instruction_pos] == LOOPSTART)
			pair_mask--;
		this->m_instruction_pos--;
	}
	this->m_instruction_pos++;
}

void
Program::input(void)
{
	char c;
	std::cin >> c;
	this->m_stack[this->m_pointer] = c;
}

void
Program::output(void) {
	std::cout << static_cast<char>(this->m_stack[this->m_pointer]);
}

void
Program::runCommand(int cmd)
{
	switch (cmd)
	{
		case INCPTR:
			this->incPtr();
			break ;
		case DECPTR:
			this->decPtr();
			break ;
		case INCVAL:
			this->incVal();
			break ;
		case DECVAL:
			this->decVal();
			break ;
		case INPUT:
			this->input();
			break ;
		case OUTPUT:
			this->output();
			break ;
		case LOOPSTART:
			this->loopStart(false);
			break ;
		case LOOPEND:
			this->loopEnd();
			break ;
	}
}

void
Program::runProgram(void) 
{
	this->m_instruction_pos = 0;
	for (this->m_instruction_pos = 0; this->m_instruction_pos < this->m_instruction_size; this->m_instruction_pos++)
	{
		if (this->m_instruction_pos < this->m_log_instructions.size())
			this->runCommand(this->m_log_instructions[this->m_instruction_pos]);
		else if (!this->m_instructions.empty())
		{
			this->m_instructions.front()->execute();
			this->m_log_instructions.push_back(this->m_instructions.front()->getType());
			this->m_instructions.pop();
		}
	}

	// size_t last = this->m_instructions.size();

	// for (this->m_instruction_pos = 0; this->m_instruction_pos < last; this->m_instruction_pos++)
	// {
	// 	this->m_instructions[this->m_instruction_pos]->execute();
	// }
}
