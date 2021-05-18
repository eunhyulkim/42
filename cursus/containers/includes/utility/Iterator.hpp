#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "Node.hpp"

namespace ft {

/* ************************************************************************** */
/* --------------------------- ITERATOR PROTOTYPE --------------------------- */
/* ************************************************************************** */

template <typename It>
class ReverseIterator : public It{
	public:
		using typename It::value_type;
		using typename It::pointer;
		using typename It::const_pointer;
		using typename It::reference;
		using typename It::const_reference;
		using typename It::difference_type;
	public:
		ReverseIterator();
		ReverseIterator(const It& it);
		ReverseIterator(const ReverseIterator& copy);
		virtual ~ReverseIterator();

		It						base() const;
		ReverseIterator 		&operator=(ReverseIterator const &copy);

		reference 				operator*();
		const_reference 		operator*() const;
		pointer					operator->();
		const_pointer			operator->() const;
		ReverseIterator&		operator++();
		ReverseIterator			operator++(int);
		ReverseIterator&		operator--();
		ReverseIterator			operator--(int);
		ReverseIterator			operator+(int value) const;
		ReverseIterator&		operator+=(int value);
		ReverseIterator			operator-(int value) const;
		ReverseIterator&		operator-=(int value);
		
		bool					operator!=(const ReverseIterator& obj) const;
		bool					operator==(const ReverseIterator& obj) const;
		bool					operator<(const ReverseIterator& obj) const;
		bool					operator<=(const ReverseIterator& obj) const;
		bool					operator>(const ReverseIterator& obj) const;
		bool					operator>=(const ReverseIterator& obj) const;
};

/* ************************************************************************** */
/* ------------------------ ITERATOR CANONICAL FORM ------------------------- */
/* ************************************************************************** */

template <typename It>
ft::ReverseIterator<It>::ReverseIterator()
: It() {}

template <typename It>
ft::ReverseIterator<It>::ReverseIterator(const It& it)
: It(it) {}

template <typename It>
ft::ReverseIterator<It>::ReverseIterator(const ft::ReverseIterator<It>& copy)
: It(copy.p) {}

/* destructor */
template <typename It>
ft::ReverseIterator<It>::~ReverseIterator() {}

template <typename It>
It
ft::ReverseIterator<It>::base() const
{
	It tmp(*this);
	return (tmp);
}

/* ************************************************************************** */
/* --------------------------- ITERATOR OPERATOR ---------------------------- */
/* ************************************************************************** */

template <typename It>
ft::ReverseIterator<It>&
ft::ReverseIterator<It>::operator=(const ft::ReverseIterator<It>& obj)
{
	if (this == &obj)
		return (*this);
	this->p = obj.p;
	return (*this);
}

template <typename It>
typename ft::ReverseIterator<It>::reference
ft::ReverseIterator<It>::operator*(void) {
	It tmp(*this);
	return (*(--tmp));
}

template <typename It>
typename ft::ReverseIterator<It>::const_reference
ft::ReverseIterator<It>::operator*(void) const {
	It tmp(*this);
	return (*(--tmp));
}

template <typename It>
typename ft::ReverseIterator<It>::pointer
ft::ReverseIterator<It>::operator->() {
	It tmp(*this);
	return (&(*(--tmp)));
}

template <typename It>
typename ft::ReverseIterator<It>::const_pointer
ft::ReverseIterator<It>::operator->() const {
	It tmp(*this);
	return (&(*(--tmp)));
}

template <typename It>
ft::ReverseIterator<It>&
ft::ReverseIterator<It>::operator++(void) {
	this->It::operator--();
	return (*this);
}

template <typename It>
ft::ReverseIterator<It>
ft::ReverseIterator<It>::operator++(int) {
	ReverseIterator<It> tmp(*this);
	this->operator++();
	return (tmp);
}

template <typename It>
ft::ReverseIterator<It>&
ft::ReverseIterator<It>::operator--(void) {
	this->It::operator++();
	return (*this);
}

template <typename It>
ft::ReverseIterator<It>
ft::ReverseIterator<It>::operator--(int) {
	ReverseIterator<It> tmp(*this);
	this->operator--();
	return (tmp);
}

template <typename It>
ft::ReverseIterator<It>&
ft::ReverseIterator<It>::operator+=(int value)
{
	this->It::operator-=(value);
	return (*this);
}

template <typename It>
ft::ReverseIterator<It>
ft::ReverseIterator<It>::operator+(int value) const {
	ft::ReverseIterator<It> tmp(*this);
	return (tmp += value);
}

template <typename It>
ft::ReverseIterator<It>&
ft::ReverseIterator<It>::operator-=(int value)
{
	this->It::operator+=(value);
	return (*this);
}

template <typename It>
ft::ReverseIterator<It>
ft::ReverseIterator<It>::operator-(int value) const {
	ft::ReverseIterator<It> tmp(*this);
	return (tmp -= value);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator!=(const ft::ReverseIterator<It>& obj) const {
	return (this->p != obj.p);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator==(const ft::ReverseIterator<It>& obj) const {
	return (this->p == obj.p);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator<(const ft::ReverseIterator<It>& obj) const {
	return (this->p > obj.p);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator<=(const ft::ReverseIterator<It>& obj) const {
	return (this->p >= obj.p);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator>(const ft::ReverseIterator<It>& obj) const {
	return (this->p < obj.p);
}

template <typename It>
bool
ft::ReverseIterator<It>::operator>=(const ft::ReverseIterator<It>& obj) const {
	return (this->p <= obj.p);
}

}
#endif
