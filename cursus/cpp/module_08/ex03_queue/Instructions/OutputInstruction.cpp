#include "OutputInstruction.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* static variable code */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

OutputInstruction::OutputInstruction() {}
OutputInstruction::OutputInstruction(Program& program) : Instruction(program) {}

OutputInstruction::OutputInstruction(const OutputInstruction& copy)
: Instruction(copy.m_program) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

OutputInstruction::~OutputInstruction() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

OutputInstruction& OutputInstruction::operator=(const OutputInstruction&) { return (*this); }

void
OutputInstruction::execute(void) {
	this->m_program->output();
}

int
OutputInstruction::getType(void) {
	return (6);
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
