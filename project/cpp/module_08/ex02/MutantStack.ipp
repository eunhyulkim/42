#include "MutantStack.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename T>
MutantStack<T>::MutantStack() : std::stack<T>() {}

template <typename T>
MutantStack<T>::MutantStack(const MutantStack&)
: std::stack<T>() {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename T>
MutantStack<T>::~MutantStack() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

template <typename T>
MutantStack<T>&
MutantStack<T>::operator=(const MutantStack<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->c = obj;
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

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

template <typename T>
typename MutantStack<T>::iterator
MutantStack<T>::begin(void) {
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::iterator
MutantStack<T>::end(void) {
	return (this->c.end());
}

template <typename T>
typename MutantStack<T>::const_iterator
MutantStack<T>::begin(void) const {
	return (this->c.begin());
}

template <typename T>
typename MutantStack<T>::const_iterator
MutantStack<T>::end(void) const {
	return (this->c.end());
}

template <typename T>
typename MutantStack<T>::reverse_iterator
MutantStack<T>::rbegin(void) {
	return (this->c.rbegin());
}

template <typename T>
typename MutantStack<T>::reverse_iterator
MutantStack<T>::rend(void) {
	return (this->c.rend());
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator
MutantStack<T>::rbegin(void) const {
	return (this->c.rbegin());
}

template <typename T>
typename MutantStack<T>::const_reverse_iterator
MutantStack<T>::rend(void) const {
	return (this->c.rend());
}
