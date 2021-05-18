#ifndef ARRAY_IPP
# define ARRAY_IPP

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

template<typename T>
Array<T>::Array() : length(0), elements(nullptr) {}

template<typename T>
Array<T>::Array(size_t length)
: length(length), elements(nullptr)
{
	this->elements = new T[length];
}

template<typename T>
Array<T>::Array(const Array& copy)
: length(copy.length), elements(nullptr)
{
	if (copy.length > 0)
	{
		this->elements = new T[copy.length];
		for (size_t i = 0; i < copy.length; i++)
			this->elements[i] = copy.elements[i];
	}
}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

template<typename T>
Array<T>::~Array()
{
	if (this->length > 0)
		delete[] this->elements;
	this->length = 0;
	this->elements = nullptr;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& obj)
{
	if (this == &obj)
		return (*this);
	if (this->length > 0)
		delete[] this->elements;
	if (obj.length > 0)
	{
		this->elements = new T[obj.length];
		for (size_t i = 0; i < obj.length; i++)
			this->elements[i] = obj.elements[i];
	}
	this->length = obj.length;
	return (*this);
}

template <typename T>
T&
Array<T>::operator[](size_t index) {
	if (index >= this->length || index < 0)
		throw (Array<T>::OutOfBoundsException());
	return (this->elements[index]);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

template <typename T>
size_t Array<T>::get_length() const { return (this->length); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

template <typename T>
Array<T>::OutOfBoundsException::OutOfBoundsException() throw () : std::exception(){}

template <typename T>
Array<T>::OutOfBoundsException::OutOfBoundsException(const OutOfBoundsException&) throw () : std::exception(){}

template <typename T>
typename Array<T>::OutOfBoundsException& Array<T>::OutOfBoundsException::operator=(const Array<T>::OutOfBoundsException&) throw() { return (*this); }

template <typename T>
Array<T>::OutOfBoundsException::~OutOfBoundsException() throw (){}

template <typename T>
const char* Array<T>::OutOfBoundsException::what() const throw () { return ("OutOfBoundsException error"); }

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

template <typename T>
size_t
Array<T>::size(void) const {
	return (this->length);
}

#endif
