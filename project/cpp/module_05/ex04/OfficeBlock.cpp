#include "OfficeBlock.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ---------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

OfficeBlock::OfficeBlock() : m_signer(nullptr), m_executor(nullptr), m_intern(nullptr) {}
OfficeBlock::OfficeBlock(Bureaucrat& signer, Bureaucrat& executor, Intern& intern)
: m_signer(&signer), m_executor(&executor), m_intern(&intern) {
	if (&signer == &executor)
		throw (OfficeBlock::ForbiddenMultiException());
}

OfficeBlock::OfficeBlock(const OfficeBlock&) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

OfficeBlock::~OfficeBlock() {
	
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

OfficeBlock& OfficeBlock::operator=(const OfficeBlock&) { return (*this); }

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

Bureaucrat *OfficeBlock::get_m_signer() const
{
	if (this->m_signer)
		return (this->m_signer);
	else
		return (nullptr);
}

Bureaucrat *OfficeBlock::get_m_executor() const
{
	if (this->m_executor)
		return (this->m_executor);
	else
		return (nullptr);
}

Intern *OfficeBlock::get_m_intern() const
{
	if (this->m_intern)
		return (this->m_intern);
	else
		return (nullptr);
}

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

void OfficeBlock::set_m_intern(Intern& intern)
{
	if (this->m_intern != nullptr)
		throw (OfficeBlock::FulledInBlockException());
	this->m_intern = &intern; 
}

void OfficeBlock::set_m_signer(Bureaucrat& signer)
{
	if (this->m_signer != nullptr)
		throw (OfficeBlock::FulledInBlockException());
	else if (&signer == this->m_executor)
		throw (OfficeBlock::ForbiddenMultiException());
	this->m_signer = &signer; 
}
void OfficeBlock::set_m_executor(Bureaucrat& executor)
{
	if (this->m_executor != nullptr)
		throw (OfficeBlock::FulledInBlockException());
	else if (&executor == this->m_signer)
		throw (OfficeBlock::ForbiddenMultiException());
	this->m_executor = &executor;
}

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

OfficeBlock::GradeTooLowException::GradeTooLowException() throw () : std::exception(){}
OfficeBlock::GradeTooLowException::GradeTooLowException(const GradeTooLowException&) throw () : std::exception(){}
OfficeBlock::GradeTooLowException& OfficeBlock::GradeTooLowException::operator=(const OfficeBlock::GradeTooLowException&) throw() { return (*this); }
OfficeBlock::GradeTooLowException::~GradeTooLowException() throw (){}
const char* OfficeBlock::GradeTooLowException::what() const throw () { return ("GradeTooLowException error"); }

OfficeBlock::NotFilledBlockException::NotFilledBlockException() throw () : std::exception(){}
OfficeBlock::NotFilledBlockException::NotFilledBlockException(const NotFilledBlockException&) throw () : std::exception(){}
OfficeBlock::NotFilledBlockException& OfficeBlock::NotFilledBlockException::operator=(const OfficeBlock::NotFilledBlockException&) throw() { return (*this); }
OfficeBlock::NotFilledBlockException::~NotFilledBlockException() throw (){}
const char* OfficeBlock::NotFilledBlockException::what() const throw () { return ("NotFilledBlockException error"); }

OfficeBlock::FailedMakeFormException::FailedMakeFormException() throw () : std::exception(){}
OfficeBlock::FailedMakeFormException::FailedMakeFormException(const FailedMakeFormException&) throw () : std::exception(){}
OfficeBlock::FailedMakeFormException& OfficeBlock::FailedMakeFormException::operator=(const OfficeBlock::FailedMakeFormException&) throw() { return (*this); }
OfficeBlock::FailedMakeFormException::~FailedMakeFormException() throw (){}
const char* OfficeBlock::FailedMakeFormException::what() const throw () { return ("FailedMakeFormException error"); }

OfficeBlock::ForbiddenMultiException::ForbiddenMultiException() throw () : std::exception(){}
OfficeBlock::ForbiddenMultiException::ForbiddenMultiException(const ForbiddenMultiException&) throw () : std::exception(){}
OfficeBlock::ForbiddenMultiException& OfficeBlock::ForbiddenMultiException::operator=(const OfficeBlock::ForbiddenMultiException&) throw() { return (*this); }
OfficeBlock::ForbiddenMultiException::~ForbiddenMultiException() throw (){}
const char* OfficeBlock::ForbiddenMultiException::what() const throw () { return ("ForbiddenMultiException error"); }

OfficeBlock::FulledInBlockException::FulledInBlockException() throw () : std::exception(){}
OfficeBlock::FulledInBlockException::FulledInBlockException(const FulledInBlockException&) throw () : std::exception(){}
OfficeBlock::FulledInBlockException& OfficeBlock::FulledInBlockException::operator=(const OfficeBlock::FulledInBlockException&) throw() { return (*this); }
OfficeBlock::FulledInBlockException::~FulledInBlockException() throw (){}
const char* OfficeBlock::FulledInBlockException::what() const throw () { return ("FulledInBlockException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
OfficeBlock::doBureaucracy(const std::string& form_name, const std::string& target) {
	if (!this->m_intern || !this->m_executor || !this->m_signer)
		throw (OfficeBlock::NotFilledBlockException());
	Form *form;
	try {
		form = this->m_intern->makeForm(form_name, target);
		this->m_signer->signForm(*form);
		this->m_executor->executeForm(*form);
		delete form;
	} catch (Intern::FailedMakeFormException& e) {
		throw (OfficeBlock::FailedMakeFormException());
	} catch (Form::GradeTooLowException& e) {
		delete form;
		throw (OfficeBlock::GradeTooLowException());
	} catch (std::exception& e) {
		delete form;
		throw (e);
	}
}
