#include "Span.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Span::Span() {}
Span::Span(unsigned int size) : m_size(size) {
	this->m_vector.reserve(size);
}

Span::Span(const Span& copy)
: m_size(copy.m_size)
{
	this->m_vector = copy.m_vector;
	this->m_size = copy.m_size;
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Span::~Span()
{
	this->m_size = 0;
	this->m_vector.clear();
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Span& Span::operator=(const Span& obj)
{
	if (this == &obj)
		return (*this);
	this->m_size = obj.m_size;
	this->m_vector = obj.m_vector;
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

Span::FullSpanException::FullSpanException() throw () : std::exception(){}
Span::FullSpanException::FullSpanException(const FullSpanException&) throw () : std::exception(){}
Span::FullSpanException& Span::FullSpanException::operator=(const Span::FullSpanException&) throw() { return (*this); }
Span::FullSpanException::~FullSpanException() throw (){}
const char* Span::FullSpanException::what() const throw () { return ("FullSpanException error"); }

Span::NotEnoughNumberException::NotEnoughNumberException() throw () : std::exception(){}
Span::NotEnoughNumberException::NotEnoughNumberException(const NotEnoughNumberException&) throw () : std::exception(){}
Span::NotEnoughNumberException& Span::NotEnoughNumberException::operator=(const Span::NotEnoughNumberException&) throw() { return (*this); }
Span::NotEnoughNumberException::~NotEnoughNumberException() throw (){}
const char* Span::NotEnoughNumberException::what() const throw () { return ("NotEnoughNumberException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Span::addNumber(int element)
{
	if (this->m_vector.size() >= this->m_size)
		throw (Span::FullSpanException());
	this->m_vector.push_back(element);
}

long
Span::shortestSpan(void)
{
	long minDiff = std::numeric_limits<long>::max();
	long diff;

	if (this->m_vector.size() < 2)
		throw (Span::NotEnoughNumberException());
	
	std::vector<int> copy = this->m_vector;
	std::sort(copy.begin(), copy.end());

	std::vector<int>::iterator last = copy.begin();
	for (std::vector<int>::iterator it = copy.begin() + 1; it != copy.end(); ++it)
	{
		diff = static_cast<long>(*it) - static_cast<long>(*last);
		if (diff < minDiff)
			minDiff = diff;
		last = it;
	}
	return minDiff;
}

long
Span::longestSpan(void)
{
	if (this->m_vector.size() < 2)
		throw (Span::NotEnoughNumberException());
	return (static_cast<long>(*std::max_element(this->m_vector.begin(), this->m_vector.end())) \
	- static_cast<long>(*std::min_element(this->m_vector.begin(), this->m_vector.end())));
}
