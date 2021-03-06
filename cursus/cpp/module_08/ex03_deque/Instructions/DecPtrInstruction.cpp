#include "DecPtrInstruction.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

DecPtrInstruction::DecPtrInstruction() {}
DecPtrInstruction::DecPtrInstruction(Program& program) : Instruction(program) {}

DecPtrInstruction::DecPtrInstruction(const DecPtrInstruction& copy)
: Instruction(copy.m_program) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

DecPtrInstruction::~DecPtrInstruction() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

DecPtrInstruction& DecPtrInstruction::operator=(const DecPtrInstruction&) { return (*this); }

void
DecPtrInstruction::execute(void) {
	this->m_program->decPtr();
}

int
DecPtrInstruction::getType(void) {
	return (2);
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

