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
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
}

Program::Program(const Program& copy)
{
	this->m_instruction_pos = 0;
	this->m_pointer = 0;
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
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
	// while (!this->m_instructions.empty())
	// 	this->m_instructions.pop();
	this->m_instructions.clear();
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
	for (int i = 0; i < 30000; i++)
		this->m_stack[i] = 0;
	// this->m_instructions.pop();
	this->m_instructions.clear();
	this->m_instructions = obj.m_instructions;
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
	this->m_instructions.push_back(instruction);
	// this->m_instructions.push(instruction);
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
Program::loopStart(void)
{
	if (this->m_stack[this->m_pointer] != 0)
		return ;
	
	int pair_mask = 0;
	this->m_instruction_pos++;
	while (this->m_instruction_pos < this->m_instructions.size() && pair_mask >= 0)
	{
		if (this->m_instructions[this->m_instruction_pos]->getType() == LOOPSTART)
			pair_mask++;
		else if (this->m_instructions[this->m_instruction_pos]->getType() == LOOPEND)
			pair_mask--;
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
		if (this->m_instructions[this->m_instruction_pos]->getType() == LOOPEND)
			pair_mask++;
		else if (this->m_instructions[this->m_instruction_pos]->getType() == LOOPSTART)
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
Program::runProgram(void) 
{
	size_t last = this->m_instructions.size();

	for (this->m_instruction_pos = 0; this->m_instruction_pos < last; this->m_instruction_pos++)
	{
		this->m_instructions[this->m_instruction_pos]->execute();
	}
}
