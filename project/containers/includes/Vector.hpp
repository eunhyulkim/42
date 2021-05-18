#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <string>
# include <iostream>
# include <memory>
# include <iterator>
# include <exception>
# include "utility/Iterator.hpp"
# include "utility/Algorithm.hpp"

namespace ft {

/* ************************************************************************** */
/* --------------------------- ITERATOR PROTOTYPE --------------------------- */
/* ************************************************************************** */

template <typename T>
class VectorIterator {
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef std::ptrdiff_t 		difference_type;
	protected:
		pointer 	p;
	public:
		VectorIterator();
		VectorIterator(pointer p);
		VectorIterator(const VectorIterator& copy);
		VectorIterator&	operator=(const VectorIterator& obj);
		virtual ~VectorIterator();

		reference 		operator*();
		const_reference operator*() const;
		pointer			operator->();
		const_pointer	operator->() const;
		reference		operator[](int idx);
		const_reference operator[](int idx) const;
		VectorIterator&	operator++();
		VectorIterator	operator++(int);
		VectorIterator&	operator--();
		VectorIterator	operator--(int);
		VectorIterator	operator+(int value) const;
		VectorIterator&	operator+=(int value);
		VectorIterator	operator-(int value) const;
		VectorIterator&	operator-=(int value);
		difference_type	operator-(VectorIterator const &other) const;
		bool			operator!=(const VectorIterator& obj) const;
		bool			operator==(const VectorIterator& obj) const;
		bool			operator<(const VectorIterator& obj) const;
		bool			operator<=(const VectorIterator& obj) const;
		bool			operator>(const VectorIterator& obj) const;
		bool			operator>=(const VectorIterator& obj) const;
};

/* ************************************************************************** */
/* ------------------------ ITERATOR CANONICAL FORM ------------------------- */
/* ************************************************************************** */

template <typename T>
ft::VectorIterator<T>::VectorIterator()
: p(nullptr) {}

template <typename T>
ft::VectorIterator<T>::VectorIterator(pointer p)
: p(p) {}

template <typename T>
ft::VectorIterator<T>::VectorIterator(const VectorIterator& copy)
: p(copy.p) {}

template <typename T>
ft::VectorIterator<T>::~VectorIterator() {}

/* ************************************************************************** */
/* --------------------------- ITERATOR OPERATOR ---------------------------- */
/* ************************************************************************** */

template <typename T>
ft::VectorIterator<T>&
ft::VectorIterator<T>::operator=(const ft::VectorIterator<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->p = obj.p;
	return (*this);
}

template <typename T>
typename ft::VectorIterator<T>::reference
ft::VectorIterator<T>::operator*(void) {
	return (*this->p);
}

template <typename T>
typename ft::VectorIterator<T>::const_reference
ft::VectorIterator<T>::operator*(void) const {
	return (*this->p);
}

template <typename T>
typename ft::VectorIterator<T>::pointer
ft::VectorIterator<T>::operator->() {
	return (this->p);
}

template <typename T>
typename ft::VectorIterator<T>::const_pointer
ft::VectorIterator<T>::operator->() const {
	return (this->p);
}

template <typename T>
typename ft::VectorIterator<T>::reference
ft::VectorIterator<T>::operator[](int idx) {
	return (*(this->p + idx));
}

template <typename T>
typename ft::VectorIterator<T>::const_reference
ft::VectorIterator<T>::operator[](int idx) const {
	return (*(this->p + idx));
}

template <typename T>
ft::VectorIterator<T>&
ft::VectorIterator<T>::operator++(void) {
	++this->p;
	return (*this);
}

template <typename T>
ft::VectorIterator<T>
ft::VectorIterator<T>::operator++(int) {
	VectorIterator<T> tmp(*this);
	this->operator++();
	return (tmp);
}

template <typename T>
ft::VectorIterator<T>&
ft::VectorIterator<T>::operator--(void) {
	--this->p;
	return (*this);
}

template <typename T>
ft::VectorIterator<T>
ft::VectorIterator<T>::operator--(int) {
	VectorIterator<T> tmp(*this);
	this->operator--();
	return (tmp);
}

template <typename T>
ft::VectorIterator<T>&
ft::VectorIterator<T>::operator+=(int value)
{
	this->p += value;
	return (*this);
}

template <typename T>
ft::VectorIterator<T>
ft::VectorIterator<T>::operator+(int value) const {
	VectorIterator<T> tmp(*this);
	return (tmp += value);
}

template <typename T>
ft::VectorIterator<T>&
ft::VectorIterator<T>::operator-=(int value)
{
	this->p -= value;
	return (*this);
}

template <typename T>
ft::VectorIterator<T>
ft::VectorIterator<T>::operator-(int value) const {
	VectorIterator<T> tmp(*this);
	return (tmp -= value);
}

template <typename T>
typename ft::VectorIterator<T>::difference_type
ft::VectorIterator<T>::operator-(VectorIterator const &other) const {
	return (this->p - other.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator!=(const ft::VectorIterator<T>& obj) const {
	return (this->p != obj.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator==(const ft::VectorIterator<T>& obj) const {
	return (this->p == obj.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator<(const ft::VectorIterator<T>& obj) const {
	return (this->p < obj.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator<=(const ft::VectorIterator<T>& obj) const {
	return (this->p <= obj.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator>(const ft::VectorIterator<T>& obj) const {
	return (this->p > obj.p);
}

template <typename T>
bool
ft::VectorIterator<T>::operator>=(const ft::VectorIterator<T>& obj) const {
	return (this->p >= obj.p);
}

/* ************************************************************************** */
/* -------------------------- CONTAINER PROTOTYPE --------------------------- */
/* ************************************************************************** */

template<typename T>
class Vector
{
	public:
		typedef std::allocator<T>									allocator_type;
		typedef typename allocator_type::size_type					size_type;
		typedef T													value_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef value_type*											pointer;
		typedef const pointer										const_pointer;
		typedef VectorIterator<value_type>							iterator;
		typedef VectorIterator<const value_type>					const_iterator;
		typedef ReverseIterator<iterator>							reverse_iterator;
		typedef ReverseIterator<const_iterator>						const_reverse_iterator;
		typedef std::ptrdiff_t 										difference_type;
	private:
		size_type m_size;
		size_type m_capacity;
		pointer m_container;

		void copy_construct(size_type idx, const_reference val);
		size_type get_next_capacity(size_type n);
	public:
		/* canonical form */
		Vector();
		Vector(size_type n, const value_type& val = value_type());
		Vector(iterator first, iterator last);
		Vector(const Vector& copy);
		Vector& operator=(const Vector& obj);
		virtual ~Vector();

		/* iterators */
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/* capacity */
		size_type size() const;
		size_type max_size() const;
		void resize(size_type n, value_type val = value_type());
		size_type capacity() const;
		void reserve(size_type n);
		bool empty() const;

		/* element access */
		reference operator[](size_type idx);
		const_reference operator[](size_type idx) const;
		reference at(size_type idx);
		const_reference at(size_type idx) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		/* modifier function */
		void assign(size_type size, const_reference val);
		void assign(iterator first, iterator last);
		void assign(const_iterator first, const_iterator last);
		void push_back(const_reference val);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const_reference val);
		void insert(iterator position, iterator first, iterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(Vector& obj);
		void clear();
};

/* ************************************************************************** */
/* ------------------------ CONTAINER CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename T>
ft::Vector<T>::Vector()
: m_size(0), m_capacity(0), m_container(nullptr) {}

template <typename T>
ft::Vector<T>::Vector(size_type n, const_reference val)
: m_size(0), m_capacity(0), m_container(nullptr) {
	this->assign(n, val);
}

template <typename T>
ft::Vector<T>::Vector(iterator first, iterator last)
: m_size(0), m_capacity(0), m_container(nullptr) {
	this->assign(first, last);
}

template <typename T>
ft::Vector<T>::Vector(const ft::Vector<T>& copy)
: m_size(copy.m_size), m_capacity(0), m_container(nullptr) {
	this->reserve(copy.m_capacity);
	std::memcpy(static_cast<void*>(this->m_container), static_cast<void*>(copy.m_container), copy.m_size * sizeof(value_type));
}

template <typename T>
ft::Vector<T>::~Vector()
{
	this->clear();
	if (this->m_container)
		::operator delete(this->m_container);
}

template <typename T>
ft::Vector<T>&
ft::Vector<T>::operator=(const ft::Vector<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->~Vector();
	if (this->m_capacity < obj.m_capacity)
		this->reserve(obj.m_capacity);
	std::memcpy(static_cast<void*>(this->m_container), static_cast<void*>(obj.m_container), obj.m_size * sizeof(value_type));
	this->m_size = obj.m_size;
	return (*this);
}

template <typename T>
void
ft::Vector<T>::copy_construct(size_type idx, const_reference val) {
	new(&this->m_container[idx]) value_type(val);
}

template <typename T>
typename ft::Vector<T>::size_type
ft::Vector<T>::get_next_capacity(size_type n) {
	size_type i = 1;
	while (i <= n)
		i *= 2;
	return (i);
}

/* ************************************************************************** */
/* -------------------------- CONTAINER ITERATORS --------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Vector<T>::iterator
ft::Vector<T>::begin(void) {
	return (iterator(this->m_container));
}

template <typename T>
typename ft::Vector<T>::const_iterator
ft::Vector<T>::begin(void) const {
	return (const_iterator(this->m_container));
}

template <typename T>
typename ft::Vector<T>::iterator
ft::Vector<T>::end(void) {
	return (iterator(&this->m_container[this->m_size]));
}

template <typename T>
typename ft::Vector<T>::const_iterator
ft::Vector<T>::end(void) const {
	return (const_iterator(&this->m_container[this->m_size]));
}

template <typename T>
typename ft::Vector<T>::reverse_iterator
ft::Vector<T>::rbegin(void) {
	return (reverse_iterator(this->end()));
}

template <typename T>
typename ft::Vector<T>::const_reverse_iterator
ft::Vector<T>::rbegin(void) const {
	return (const_reverse_iterator(this->end()));
}

template <typename T>
typename ft::Vector<T>::reverse_iterator
ft::Vector<T>::rend(void) {
	return (reverse_iterator(this->begin()));
}

template <typename T>
typename ft::Vector<T>::const_reverse_iterator
ft::Vector<T>::rend(void) const {
	return (const_reverse_iterator(this->begin()));
}

/* ************************************************************************** */
/* ------------------------------- CAPACITY --------------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Vector<T>::size_type
ft::Vector<T>::size(void) const {
	return (this->m_size);
}

template <typename T>
typename ft::Vector<T>::size_type
ft::Vector<T>::max_size(void) const {
	return (ft::min((size_type)std::numeric_limits<difference_type>::max(), \
	std::numeric_limits<size_type>::max() / sizeof(value_type)));
}

template <typename T>
void
ft::Vector<T>::resize(size_type n, value_type val)
{
	if (n > this->m_capacity)
		this->reserve(n);

	if (n > this->m_size)
	{
		for (size_type i = this->m_size; i < n; ++i)
			this->copy_construct(i, val);
		this->m_size = n;
	}
	else if (n < this->m_size)
	{
		for (size_type i = n; i < this->m_size; ++i)
			this->m_container[i].~value_type();
		this->m_size = n;
	}
}

template <typename T>
typename ft::Vector<T>::size_type
ft::Vector<T>::capacity(void) const {
	return (this->m_capacity);
}

template <typename T>
void
ft::Vector<T>::reserve(size_type n) {
	if (this->m_capacity == 0)
	{
		this->m_container = static_cast<pointer>(::operator new(sizeof(value_type) * n));
		this->m_capacity = n;
	} else if (this->m_capacity < n)
	{
		pointer tmp = static_cast<pointer>(::operator new(sizeof(value_type) * n));
		if (this->m_container)
		{
			for (size_type i = 0; i < this->m_size; ++i)
				new(&tmp[i]) value_type(this->m_container[i]);
			::operator delete(this->m_container);
		}
		this->m_container = tmp;
		this->m_capacity = n;
	}
}

template <typename T>
bool
ft::Vector<T>::empty(void) const {
	return (this->m_size == 0);
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Vector<T>::reference
ft::Vector<T>::operator[](size_type idx) {
	return (this->m_container[idx]);
}

template <typename T>
typename ft::Vector<T>::const_reference
ft::Vector<T>::operator[](size_type idx) const {
	return (this->m_container[idx]);
}

template <typename T>
typename ft::Vector<T>::reference
ft::Vector<T>::at(size_type idx) {
	if (idx > this->m_size)
		throw (std::out_of_range("Vector index out of range"));
	return (this->m_container[idx]);
}

template <typename T>
typename ft::Vector<T>::const_reference
ft::Vector<T>::at(size_type idx) const {
	if (idx > this->m_size)
		throw (std::out_of_range("Vector index out of range"));
	return (this->m_container[idx]);
}

template <typename T>
typename ft::Vector<T>::reference
ft::Vector<T>::front(void) {
	return (this->m_container[0]);
}

template <typename T>
typename ft::Vector<T>::const_reference
ft::Vector<T>::front(void) const {
	return (this->m_container[0]);
}

template <typename T>
typename ft::Vector<T>::reference
ft::Vector<T>::back(void) {
	return (this->m_container[this->m_size - 1]);
}

template <typename T>
typename ft::Vector<T>::const_reference
ft::Vector<T>::back(void) const {
	return (this->m_container[this->m_size - 1]);
}

// /* ************************************************************************** */
// /* ------------------------------- MODIFIERS -------------------------------- */
// /* ************************************************************************** */

template <typename T>
void
ft::Vector<T>::assign(size_type size, const_reference val)
{
	this->clear();
	for (size_type i = 0; i < size; i++)
		this->push_back(val);
}

template <typename T>
void
ft::Vector<T>::assign(iterator first, iterator last)
{
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template <typename T>
void
ft::Vector<T>::assign(const_iterator first, const_iterator last)
{
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template <typename T>
void
ft::Vector<T>::push_back(const_reference val)
{
	if (this->m_size == this->m_capacity)
		this->reserve(this->get_next_capacity(this->m_capacity));
	new(&this->m_container[this->m_size++]) value_type(val);
}

template <typename T>
void
ft::Vector<T>::pop_back(void)
{
	if (this->m_size == 0)
		return ;
	this->m_container[--this->m_size].~value_type();
}

template <typename T>
typename ft::Vector<T>::iterator
ft::Vector<T>::insert(iterator position, const_reference val)
{
	this->insert(position, 1, val);
	return (++position);
}

template <typename T>
void
ft::Vector<T>::insert(iterator position, size_type n, const value_type& val)
{
	iterator it = this->begin();
	if (this->m_size + n >= this->m_capacity)
		this->reserve(get_next_capacity(this->m_size + n));
	size_type i = 0;
	while (it != position) {
		++it;
		++i;
	}
	for (size_type j = this->m_size; j >= 1 && j >= i; j--)
		this->copy_construct(j + n - 1, this->m_container[j - 1]);
	for (size_type j = 0; j < n; j++)
		this->copy_construct(i + j, val);
	this->m_size += n;
}

template <typename T>
void
ft::Vector<T>::insert(iterator position, iterator first, iterator last)
{
		size_type size = last - first;
		iterator it = this->begin();
		if (this->m_size + size >= this->m_capacity)
			this->reserve(get_next_capacity(this->m_size + size));
		size_type i = 0;
		while (it != position) {
			++it;
			++i;
		}
		// std::memmove
		for (size_type j = this->m_size; j > i; j--)
			this->copy_construct(j + size - 1, this->m_container[j - 1]);
		for (size_type j = 0; j < size; j++)
			this->copy_construct(i + j, *first++);
		this->m_size += size;
}

template <typename T>
typename ft::Vector<T>::iterator
ft::Vector<T>::erase(iterator position)
{
	iterator tmp(position);
	++tmp;
	return (this->erase(position, tmp));
}

template <typename T>
typename ft::Vector<T>::iterator
ft::Vector<T>::erase(iterator first, iterator last)
{
	size_type size = last - first;
	iterator it = this->begin();
	size_type i = 0;
	size_type ridx;
	while (it != first) {
		++it;
		++i;
	}
	ridx = i;
	if (it == this->end())
		return (this->end());
	while (first != last) {
		(*first++).value_type::~value_type();
	}
	for (size_type j = i + size; j < this->m_size; j++)
		this->copy_construct(i++, this->m_container[j]);
	this->m_size -= size;
	return (iterator(&this->m_container[ridx]));
}

template <typename T>
void
ft::Vector<T>::swap(Vector& obj)
{
	ft::swap(this->m_size, obj.m_size);
	ft::swap(this->m_capacity, obj.m_capacity);
	ft::swap(this->m_container, obj.m_container);
}

template <typename T>
void
ft::Vector<T>::clear(void)
{
	for (size_type i = 0; i < this->m_size; ++i)
		this->m_container[i].~value_type();
	this->m_size = 0;
}

}

// /* ************************************************************************** */
// /* --------------------------- NON MEMBER OPERATOR -------------------------- */
// /* ************************************************************************** */

template <typename T>
bool
operator==(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::Vector<T>::const_iterator first = lhs.begin();
	typename ft::Vector<T>::const_iterator last = lhs.end();
	typename ft::Vector<T>::const_iterator obj = rhs.begin();
	while (first != last)
	{
		if (*first != *obj++)
			return (false);
		++first;
	}
	return (true);
}

template <typename T>
bool
operator!=(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs) {
	return (!(lhs == rhs));
}

template <typename T>
bool
operator<(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T>
bool
operator<=(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs) {
	return (!(rhs < lhs));
}

template <typename T>
bool
operator>(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs) {
	return (rhs < lhs);
}

template <typename T>
bool
operator>=(const ft::Vector<T>& lhs, const ft::Vector<T>& rhs) {
	return (!(lhs < rhs));
}

template <typename T>
void
swap(ft::Vector<T>& lhs, ft::Vector<T>& rhs) {
	lhs.swap(rhs);
}

#endif
