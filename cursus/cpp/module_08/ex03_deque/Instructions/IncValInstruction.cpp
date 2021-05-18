#include "IncValInstruction.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

IncValInstruction::IncValInstruction() {}
IncValInstruction::IncValInstruction(Program& program) : Instruction(program) {}

IncValInstruction::IncValInstruction(const IncValInstruction& copy)
: Instruction(copy.m_program) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

IncValInstruction::~IncValInstruction() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

IncValInstruction& IncValInstruction::operator=(const IncValInstruction&) { return (*this); }

void
IncValInstruction::execute(void) {
	this->m_program->incVal();
}

int
IncValInstruction::getType(void) {
	return (3);
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