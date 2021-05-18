#ifndef DEQUE_HPP
# define DEQUE_HPP

# include <limits>
# include <iostream>
# include "utility/Pair.hpp"
# include "utility/Iterator.hpp"
# include "utility/Algorithm.hpp"

# define CONTAINER_SIZE		8

namespace ft {

/* ************************************************************************** */
/* --------------------------- ITERATOR PROTOTYPE --------------------------- */
/* ************************************************************************** */

template<typename T>
class Deque;

template <typename T, typename C>
class DequeIterator
{
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef std::ptrdiff_t 		difference_type;
	protected:
		ft::Deque<C>*	m_deq;
		int				m_idx;
		pointer			p;
	public:
		DequeIterator();
		DequeIterator(const Deque<C>* deq, int idx);
		DequeIterator(const DequeIterator& copy);
		DequeIterator&	operator=(const DequeIterator& obj);
		virtual ~DequeIterator();

		int				as_idx();

		reference 		operator*();
		const_reference operator*() const;
		pointer			operator->();
		const_pointer	operator->() const;
		reference		operator[](int idx);
		const_reference operator[](int idx) const;
		DequeIterator&	operator++();
		DequeIterator	operator++(int);
		DequeIterator&	operator--();
		DequeIterator	operator--(int);
		DequeIterator	operator+(int value) const;
		DequeIterator&	operator+=(int value);
		DequeIterator	operator-(int value) const;
		DequeIterator&	operator-=(int value);
		bool			operator!=(const DequeIterator& obj) const;
		bool			operator==(const DequeIterator& obj) const;
		bool			operator<(const DequeIterator& obj) const;
		bool			operator<=(const DequeIterator& obj) const;
		bool			operator>(const DequeIterator& obj) const;
		bool			operator>=(const DequeIterator& obj) const;
};

template <typename T>
class DequeReverseIterator : public T
{
	public:
		using typename T::value_type;
		using typename T::pointer;
		using typename T::const_pointer;
		using typename T::reference;
		using typename T::const_reference;
		using typename T::difference_type;
	public:
		DequeReverseIterator();
		DequeReverseIterator(const T& it);
		DequeReverseIterator(const DequeReverseIterator& copy);
		DequeReverseIterator&	operator=(const DequeReverseIterator& obj);
		virtual ~DequeReverseIterator();

		T						base() const;

		reference 				operator*();
		const_reference 		operator*() const;
		pointer					operator->();
		const_pointer			operator->() const;
		reference				operator[](int idx);
		const_reference 		operator[](int idx) const;
		DequeReverseIterator&	operator++();
		DequeReverseIterator	operator++(int);
		DequeReverseIterator&	operator--();
		DequeReverseIterator	operator--(int);
		DequeReverseIterator	operator+(int value) const;
		DequeReverseIterator&	operator+=(int value);
		DequeReverseIterator	operator-(int value) const;
		DequeReverseIterator&	operator-=(int value);
		bool					operator!=(const DequeReverseIterator& obj) const;
		bool					operator==(const DequeReverseIterator& obj) const;
		bool					operator<(const DequeReverseIterator& obj) const;
		bool					operator<=(const DequeReverseIterator& obj) const;
		bool					operator>(const DequeReverseIterator& obj) const;
		bool					operator>=(const DequeReverseIterator& obj) const;
};

/* ************************************************************************** */
/* ------------------------ ITERATOR CANONICAL FORM ------------------------- */
/* ************************************************************************** */

template <typename T, typename C>
ft::DequeIterator<T, C>::DequeIterator()
: m_deq(nullptr), m_idx(0), p(nullptr) {}

template <typename T, typename C>
ft::DequeIterator<T, C>::DequeIterator(const Deque<C>* deq, int idx)
: m_deq(const_cast<Deque<C>* >(deq)), m_idx(idx) {
	this->p = &(*this->m_deq)[this->m_idx];
}

template <typename T, typename C>
ft::DequeIterator<T, C>::DequeIterator(const DequeIterator& copy)
: m_deq(copy.m_deq), m_idx(copy.m_idx), p(copy.p) {}

template <typename T, typename C>
ft::DequeIterator<T, C>::~DequeIterator() {}

template <typename T, typename C>
ft::DequeIterator<T, C>&
ft::DequeIterator<T, C>::operator=(const ft::DequeIterator<T, C>& obj)
{
	if (this == &obj)
		return (*this);
	this->m_deq = obj.m_deq;
	this->m_idx = obj.m_idx;
	this->p = obj.p;
	return (*this);
}

template <typename T, typename C>
int
ft::DequeIterator<T, C>::as_idx()
{
	return (this->m_idx);
}

template <typename T>
ft::DequeReverseIterator<T>::DequeReverseIterator()
: T() {}

template <typename T>
ft::DequeReverseIterator<T>::DequeReverseIterator(const T& it)
: T(it) {}

template <typename T>
ft::DequeReverseIterator<T>::DequeReverseIterator(const DequeReverseIterator& copy)
: T(copy.m_deq, copy.m_idx) {}

template <typename T>
ft::DequeReverseIterator<T>::~DequeReverseIterator() {}

template <typename T>
ft::DequeReverseIterator<T>&
ft::DequeReverseIterator<T>::operator=(const ft::DequeReverseIterator<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->T::operator=(obj);
	return (*this);
}

template <typename T>
T
ft::DequeReverseIterator<T>::base() const
{
	T tmp(*this);
	return (tmp);
}

/* ************************************************************************** */
/* --------------------------- ITERATOR OPERATOR ---------------------------- */
/* ************************************************************************** */

template <typename T, typename C>
typename ft::DequeIterator<T, C>::reference
ft::DequeIterator<T, C>::operator*(void) {
	return (*this->p);
}

template <typename T, typename C>
typename ft::DequeIterator<T, C>::const_reference
ft::DequeIterator<T, C>::operator*(void) const {
	return (*this->p);
}

template <typename T, typename C>
typename ft::DequeIterator<T, C>::pointer
ft::DequeIterator<T, C>::operator->() {
	return (this->p);
}

template <typename T, typename C>
typename ft::DequeIterator<T, C>::const_pointer
ft::DequeIterator<T, C>::operator->() const {
	return (this->p);
}

template <typename T, typename C>
typename ft::DequeIterator<T, C>::reference
ft::DequeIterator<T, C>::operator[](int idx) {
	return ((*this->m_deq)[this->m_idx + idx]);
}

template <typename T, typename C>
typename ft::DequeIterator<T, C>::const_reference
ft::DequeIterator<T, C>::operator[](int idx) const {
	return ((*this->m_deq)[this->m_idx + idx]);
}

template <typename T, typename C>
ft::DequeIterator<T, C>&
ft::DequeIterator<T, C>::operator++(void) {
	++this->m_idx;
	this->p = &(*this->m_deq)[this->m_idx];
	return (*this);
}

template <typename T, typename C>
ft::DequeIterator<T, C>
ft::DequeIterator<T, C>::operator++(int) {
	DequeIterator<T, C> tmp(*this);
	this->operator++();
	return (tmp);
}

template <typename T, typename C>
ft::DequeIterator<T, C>&
ft::DequeIterator<T, C>::operator--(void) {
	--this->m_idx;
	this->p = &(*this->m_deq)[this->m_idx];
	return (*this);
}

template <typename T, typename C>
ft::DequeIterator<T, C>
ft::DequeIterator<T, C>::operator--(int) {
	DequeIterator<T, C> tmp(*this);
	this->operator--();
	return (tmp);
}

template <typename T, typename C>
ft::DequeIterator<T, C>&
ft::DequeIterator<T, C>::operator+=(int value)
{
	this->m_idx += value;
	this->p = &(*this->m_deq)[this->m_idx];
	return (*this);
}

template <typename T, typename C>
ft::DequeIterator<T, C>
ft::DequeIterator<T, C>::operator+(int value) const {
	DequeIterator<T, C> tmp(*this);
	return (tmp += value);
}

template <typename T, typename C>
ft::DequeIterator<T, C>&
ft::DequeIterator<T, C>::operator-=(int value)
{
	this->m_idx -= value;
	this->p = &(*this->m_deq)[this->m_idx];
	return (*this);
}

template <typename T, typename C>
ft::DequeIterator<T, C>
ft::DequeIterator<T, C>::operator-(int value) const {
	DequeIterator<T, C> tmp(*this);
	return (tmp -= value);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator!=(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx != obj.m_idx);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator==(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx == obj.m_idx);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator<(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx < obj.m_idx);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator<=(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx <= obj.m_idx);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator>(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx > obj.m_idx);
}

template <typename T, typename C>
bool
ft::DequeIterator<T, C>::operator>=(const ft::DequeIterator<T, C>& obj) const {
	return (this->m_idx >= obj.m_idx);
}


template <typename T>
typename ft::DequeReverseIterator<T>::reference
ft::DequeReverseIterator<T>::operator*(void) {
	T tmp(*this);
	return (*(--tmp));
}

template <typename T>
typename ft::DequeReverseIterator<T>::const_reference
ft::DequeReverseIterator<T>::operator*(void) const {
	T tmp(*this);
	return (*(--tmp));
}

template <typename T>
typename ft::DequeReverseIterator<T>::pointer
ft::DequeReverseIterator<T>::operator->() {
	T tmp(*this);
	return (&(*(--tmp)));
}

template <typename T>
typename ft::DequeReverseIterator<T>::const_pointer
ft::DequeReverseIterator<T>::operator->() const {
	T tmp(*this);
	return (&(*(--tmp)));
}

template <typename T>
typename ft::DequeReverseIterator<T>::reference
ft::DequeReverseIterator<T>::operator[](int idx) {
	DequeReverseIterator<T> tmp(*this);
	tmp += idx;
	return ((*tmp.m_deq)[tmp.m_idx - 1]);
}

template <typename T>
typename ft::DequeReverseIterator<T>::const_reference
ft::DequeReverseIterator<T>::operator[](int idx) const {
	DequeReverseIterator<T> tmp(*this);
	tmp += idx;
	return ((*tmp.m_deq)[tmp.m_idx - 1]);
}

template <typename T>
ft::DequeReverseIterator<T>&
ft::DequeReverseIterator<T>::operator++(void) {
	this->T::operator--();
	return (*this);
}

template <typename T>
ft::DequeReverseIterator<T>
ft::DequeReverseIterator<T>::operator++(int) {
	DequeReverseIterator<T> tmp(*this);
	this->operator++();
	return (tmp);
}

template <typename T>
ft::DequeReverseIterator<T>&
ft::DequeReverseIterator<T>::operator--(void) {
	this->T::operator++();
	return (*this);
}

template <typename T>
ft::DequeReverseIterator<T>
ft::DequeReverseIterator<T>::operator--(int) {
	DequeReverseIterator<T> tmp(*this);
	this->operator--();
	return (tmp);
}

template <typename T>
ft::DequeReverseIterator<T>&
ft::DequeReverseIterator<T>::operator+=(int value)
{
	this->T::operator-=(value);
	return (*this);
}

template <typename T>
ft::DequeReverseIterator<T>
ft::DequeReverseIterator<T>::operator+(int value) const {
	DequeReverseIterator<T> tmp(*this);
	return (tmp += value);
}

template <typename T>
ft::DequeReverseIterator<T>&
ft::DequeReverseIterator<T>::operator-=(int value)
{
	this->T::operator+=(value);
	return (*this);
}

template <typename T>
ft::DequeReverseIterator<T>
ft::DequeReverseIterator<T>::operator-(int value) const {
	DequeReverseIterator<T> tmp(*this);
	return (tmp -= value);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator!=(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx != obj.m_idx);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator==(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx == obj.m_idx);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator<(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx > obj.m_idx);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator<=(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx >= obj.m_idx);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator>(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx < obj.m_idx);
}

template <typename T>
bool
ft::DequeReverseIterator<T>::operator>=(const ft::DequeReverseIterator<T>& obj) const {
	return (this->m_idx <= obj.m_idx);
}

/* ************************************************************************** */
/* -------------------------- CONTAINER PROTOTYPE --------------------------- */
/* ************************************************************************** */

template<typename T>
class Deque
{
	public:
		typedef std::allocator<T>							allocator_type;
		typedef typename allocator_type::size_type			size_type;
		typedef T											value_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef T*											pointer;
		typedef const T*									const_pointer;
		typedef DequeIterator<value_type, T>				iterator;
		typedef DequeIterator<const value_type, T>			const_iterator;
		typedef DequeReverseIterator<iterator>				reverse_iterator;
		typedef DequeReverseIterator<const_iterator>		const_reverse_iterator;
		typedef std::ptrdiff_t 								difference_type;
	private:
		pointer*	m_containers;
		size_type	m_capacity;
		size_type	m_start_container;
		size_type	m_start_idx;
		size_type	m_end_container;
		size_type	m_end_idx;
		size_type	m_size;
	private:
		void reserve(size_type size, bool front = false);
		ft::Pair<size_type, size_type> convert_idx(size_type absolute_idx) const;
		size_type revert_idx(size_type container_idx, size_type order_idx) const;
		void move_container_to_front(iterator position, size_type start_container, size_type start_idx, size_type n);
		void move_container_to_back(iterator position, size_type last_container, size_type last_idx, size_type n);
	public:
		/* canonical form */
		Deque();
		Deque(size_type n, const_reference val = value_type());
		Deque(iterator first, iterator last);
		Deque(const Deque& copy);
		Deque& operator=(const Deque& obj);
		virtual ~Deque();

		/* capacity */
		size_type size() const;
		size_type max_size() const;
		void resize(size_type n, value_type val = value_type());
		bool empty() const;

		/* iterators */
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		/* element access */
		reference operator[](size_type idx);
		const_reference operator[](size_type idx) const;
		reference at(size_type idx);
		const_reference at(size_type idx) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const_reference val);
		void push_front(const_reference val);
		void push_back(const_reference val);
		void pop_front();
		void pop_back();
		iterator insert(iterator position, const value_type& val);
    	void insert(iterator position, size_type n, const value_type& val);
    	void insert(iterator position, iterator first, iterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(Deque& obj);
		void clear();
};

/* ************************************************************************** */
/* ---------------------------- INTERNAL FUNCTION --------------------------- */
/* ************************************************************************** */

template <typename T>
void
ft::Deque<T>::reserve(size_type size, bool front)
{
	size_type new_capacity = 0;

	while ((this->m_capacity + new_capacity) * CONTAINER_SIZE <= size * 2)
		new_capacity = (new_capacity == 0) ? 1 : new_capacity * 2;
	if (new_capacity == 0)
		return ;
	if (this->m_capacity == 0)
	{
		this->m_capacity = (new_capacity < 8) ? 8 : new_capacity;
		this->m_containers = new pointer[this->m_capacity];
		for (size_type i = 0; i < this->m_capacity; ++i)
			this->m_containers[i] = static_cast<pointer>(::operator new(sizeof(value_type) * CONTAINER_SIZE));
		this->m_start_container = (this->m_capacity - 1) / 2;
		this->m_end_container = (this->m_capacity / 2);
		if (this->m_capacity % 2 == 0) {
			this->m_start_idx = CONTAINER_SIZE - 1;
			this->m_end_idx = 0;
		} else {
			this->m_start_idx = (CONTAINER_SIZE / 2) - 1;
			this->m_end_idx = CONTAINER_SIZE / 2;
		}
	}
	else
	{
		pointer* new_containers = new pointer[this->m_capacity + new_capacity];
		if (front == true) {
			for (size_type i = 0; i < this->m_capacity; ++i)
				new_containers[new_capacity + i] = this->m_containers[i];
			for (size_type i = 0; i < new_capacity; ++i)
				new_containers[i] = static_cast<pointer>(::operator new(sizeof(value_type) * CONTAINER_SIZE));
			this->m_start_container += new_capacity;
			this->m_end_container += new_capacity;
		} else {
			for (size_type i = 0; i < this->m_capacity; ++i)
				new_containers[i] = this->m_containers[i];
			for (size_type i = this->m_capacity; i < this->m_capacity + new_capacity; ++i)
				new_containers[i] = static_cast<pointer>(::operator new(sizeof(value_type) * CONTAINER_SIZE));
		}
		delete[] this->m_containers;
		this->m_containers = new_containers;
		this->m_capacity += new_capacity;
	}
}

template <typename T>
ft::Pair<typename ft::Deque<T>::size_type, typename ft::Deque<T>::size_type>
ft::Deque<T>::convert_idx(size_type absolute_idx) const
{
	size_type container = this->m_start_container + ((this->m_start_idx + 1 + absolute_idx) / CONTAINER_SIZE);
	size_type idx = (this->m_start_idx + 1 + absolute_idx) % CONTAINER_SIZE;

	return (ft::make_pair(container, idx));
}

template <typename T>
typename ft::Deque<T>::size_type
ft::Deque<T>::revert_idx(size_type container_idx, size_type order_idx) const
{
	return ((container_idx * CONTAINER_SIZE + order_idx) - (this->m_start_container * CONTAINER_SIZE + this->m_start_idx + 1));
}

template <typename T>
void
ft::Deque<T>::move_container_to_front(iterator position, size_type start_container, size_type start_idx, size_type n) {
	size_type tmp_container = this->convert_idx(position.as_idx()).first;
	size_type tmp_idx = this->convert_idx(position.as_idx()).second;
	size_type it_container = start_container;
	size_type it_idx = start_idx;
	size_type dst_container = this->convert_idx(this->revert_idx(it_container, it_idx) - n).first;
	size_type dst_idx = this->convert_idx(this->revert_idx(it_container, it_idx) - n).second;
	while (it_container < tmp_container || (it_container == tmp_container && it_idx <= tmp_idx)) {
		std::memcpy(static_cast<void*>(&this->m_containers[dst_container][dst_idx]), static_cast<void*>(&this->m_containers[it_container][it_idx]), sizeof(value_type));
		this->m_containers[it_container][it_idx].~value_type();
		it_container += (it_idx == CONTAINER_SIZE - 1) ? 1 : 0;
		it_idx = (it_idx == CONTAINER_SIZE - 1) ? 0 : it_idx + 1;
		dst_container += (dst_idx == CONTAINER_SIZE - 1) ? 1 : 0;
		dst_idx = (dst_idx == CONTAINER_SIZE - 1) ? 0 : dst_idx + 1;
	}
}

template <typename T>
void
ft::Deque<T>::move_container_to_back(iterator position, size_type last_container, size_type last_idx, size_type n) {
	size_type tmp_container = this->convert_idx(position.as_idx()).first;
	size_type tmp_idx = this->convert_idx(position.as_idx()).second;
	size_type it_container = last_container;
	size_type it_idx = last_idx;
	size_type dst_container = it_container + ((it_idx + n) / CONTAINER_SIZE);
	size_type dst_idx = (it_idx + n) % CONTAINER_SIZE;
	while (tmp_container < it_container || (tmp_container == it_container && tmp_idx <= it_idx)) {
		std::memcpy(static_cast<void*>(&this->m_containers[dst_container][dst_idx]), static_cast<void*>(&this->m_containers[it_container][it_idx]), sizeof(value_type));
		this->m_containers[it_container][it_idx].~value_type();
		it_container -= (it_idx == 0) ? 1 : 0;
		it_idx = (it_idx == 0) ? CONTAINER_SIZE - 1 : it_idx - 1;
		dst_container -= (dst_idx == 0) ? 1 : 0;
		dst_idx = (dst_idx == 0) ? CONTAINER_SIZE - 1 : dst_idx - 1;
	}
}

/* ************************************************************************** */
/* ------------------------ CONTAINER CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename T>
ft::Deque<T>::Deque()
: m_containers(nullptr), m_capacity(0), m_start_container(0), m_start_idx(0), m_end_container(0), m_end_idx(0), m_size(0) {}

template <typename T>
ft::Deque<T>::Deque(size_type n, const_reference val)
: m_containers(nullptr), m_capacity(0), m_start_container(0), m_start_idx(0), m_end_container(0), m_end_idx(0), m_size(0) {
	this->assign(n, val);
}

template <typename T>
ft::Deque<T>::Deque(const ft::Deque<T>& copy)
: m_containers(nullptr),
m_capacity(copy.m_capacity),
m_start_container(copy.m_start_container),
m_start_idx(copy.m_start_idx),
m_end_container(copy.m_end_container),
m_end_idx(copy.m_end_idx),
m_size(copy.m_size)
{
	this->m_containers = new pointer[this->m_capacity];
	for (size_type i = 0; i < this->m_capacity; ++i) {
		this->m_containers[i] = static_cast<pointer>(::operator new(sizeof(value_type) * CONTAINER_SIZE));
		std::memcpy(static_cast<void*>(this->m_containers[i]), static_cast<void*>(copy.m_containers[i]), CONTAINER_SIZE * sizeof(value_type));
	}
}

template <typename T>
ft::Deque<T>::Deque(iterator first, iterator last)
: m_containers(nullptr), m_capacity(0), m_start_container(0), m_start_idx(0), m_end_container(0), m_end_idx(0), m_size(0) {
	this->assign(first, last);
}

template <typename T>
ft::Deque<T>::~Deque() {
	if (this->m_capacity == 0)
		return ;
	this->clear();
	for (size_type i = 0; i < this->m_capacity; ++i)
		::operator delete(this->m_containers[i]);
	delete[] this->m_containers;
	this->m_containers = nullptr;
	this->m_capacity = 0;
	this->m_start_container = 0;
	this->m_start_idx = 0;
	this->m_end_container = 0;
	this->m_end_idx = 0;
	this->m_size = 0;
}

template <typename T>
ft::Deque<T>&
ft::Deque<T>::operator=(const ft::Deque<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->~Deque();
	this->m_capacity = obj.m_capacity;
	this->m_start_container = obj.m_start_container;
	this->m_end_container = obj.m_end_container;
	this->m_start_idx = obj.m_start_idx;
	this->m_end_idx = obj.m_end_idx;
	this->m_size = obj.m_size;
	this->m_containers = new pointer[this->m_capacity];
	for (size_type i = 0; i < this->m_capacity; ++i) {
		this->m_containers[i] = static_cast<pointer>(::operator new(sizeof(value_type) * CONTAINER_SIZE));
		std::memcpy(static_cast<void*>(this->m_containers[i]), static_cast<void*>(obj.m_containers[i]), CONTAINER_SIZE * sizeof(value_type));
	}
	return (*this);
}

/* ************************************************************************** */
/* ------------------------------- CAPACITY --------------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Deque<T>::size_type
ft::Deque<T>::size(void) const {
	return (this->m_size);
}

template <typename T>
typename ft::Deque<T>::size_type
ft::Deque<T>::max_size(void) const {
	return (ft::min((size_type)std::numeric_limits<difference_type>::max(), \
	std::numeric_limits<size_type>::max() / sizeof(value_type)));
}

template <typename T>
void
ft::Deque<T>::resize(size_type n, value_type val)
{
	if (n == this->m_size)
		return ;
	while (n > this->m_size)
		this->push_back(val);
	while (n < this->m_size)
		this->pop_back();
}

template <typename T>
bool
ft::Deque<T>::empty(void) const {
	return (this->m_size == 0);
}

/* ************************************************************************** */
/* -------------------------- CONTAINER ITERATORS --------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Deque<T>::iterator
ft::Deque<T>::begin(void) {
	return (iterator(this, revert_idx(this->m_start_container, this->m_start_idx + 1)));
}

template <typename T>
typename ft::Deque<T>::const_iterator
ft::Deque<T>::begin(void) const {
	return (const_iterator(this, revert_idx(this->m_start_container, this->m_start_idx + 1)));
}

template <typename T>
typename ft::Deque<T>::iterator
ft::Deque<T>::end(void) {
	return (iterator(this, revert_idx(this->m_end_container, this->m_end_idx)));
}

template <typename T>
typename ft::Deque<T>::const_iterator
ft::Deque<T>::end(void) const {
	return (const_iterator(this, revert_idx(this->m_end_container, this->m_end_idx)));
}

template <typename T>
typename ft::Deque<T>::reverse_iterator
ft::Deque<T>::rbegin(void) {
	return (reverse_iterator(this->end()));
}

template <typename T>
typename ft::Deque<T>::const_reverse_iterator
ft::Deque<T>::rbegin(void) const {
	return (const_reverse_iterator(this->end()));
}

template <typename T>
typename ft::Deque<T>::reverse_iterator
ft::Deque<T>::rend(void) {
	return (reverse_iterator(this->begin()));
}

template <typename T>
typename ft::Deque<T>::const_reverse_iterator
ft::Deque<T>::rend(void) const {
	return (const_reverse_iterator(this->begin()));
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::Deque<T>::reference
ft::Deque<T>::operator[](size_type absolute_idx) {
	ft::Pair<size_type, size_type> idx = this->convert_idx(absolute_idx);
	return (this->m_containers[idx.first][idx.second]);
}

template <typename T>
typename ft::Deque<T>::const_reference
ft::Deque<T>::operator[](size_type absolute_idx) const {
	ft::Pair<size_type, size_type> idx = this->convert_idx(absolute_idx);
	return (this->m_containers[idx.first][idx.second]);
}

template <typename T>
typename ft::Deque<T>::reference
ft::Deque<T>::at(size_type absolute_idx)
{
	ft::Pair<size_type, size_type> idx = this->convert_idx(absolute_idx);
	if (idx.first <= this->m_start_container && idx.second <= this->m_start_idx)
		throw (std::out_of_range("Deque index out of range"));
	else if (idx.first >= this->m_end_container && idx.second >= this->m_end_idx)
		throw (std::out_of_range("Deque index out of range"));
	return (this->m_containers[idx.first][idx.second]);
}

template <typename T>
typename ft::Deque<T>::const_reference
ft::Deque<T>::at(size_type absolute_idx) const
{
	ft::Pair<size_type, size_type> idx = this->convert_idx(absolute_idx);
	if (idx.first <= this->m_start_container && idx.second <= this->m_start_idx)
		throw (std::out_of_range("Deque index out of range"));
	else if (idx.first >= this->m_end_container && idx.second >= this->m_end_idx)
		throw (std::out_of_range("Deque index out of range"));
	return (this->m_containers[idx.first][idx.second]);
}

template <typename T>
typename ft::Deque<T>::reference
ft::Deque<T>::front(void)
{
	if (this->m_start_idx == CONTAINER_SIZE - 1)
		return (this->m_containers[this->m_start_container + 1][0]);
	return (this->m_containers[this->m_start_container][this->m_start_idx + 1]);
}

template <typename T>
typename ft::Deque<T>::const_reference
ft::Deque<T>::front(void) const
{
	if (this->m_start_idx == CONTAINER_SIZE - 1)
		return (this->m_containers[this->m_start_container + 1][0]);
	return (this->m_containers[this->m_start_container][this->m_start_idx + 1]);
}

template <typename T>
typename ft::Deque<T>::reference
ft::Deque<T>::back(void)
{
	if (this->m_end_idx == 0)
		return (this->m_containers[this->m_end_container - 1][CONTAINER_SIZE - 1]);
	return (this->m_containers[this->m_end_container][this->m_end_idx - 1]);
}

template <typename T>
typename ft::Deque<T>::const_reference
ft::Deque<T>::back(void) const
{
	if (this->m_end_idx == 0)
		return (this->m_containers[this->m_end_container - 1][CONTAINER_SIZE - 1]);
	return (this->m_containers[this->m_end_container][this->m_end_idx - 1]);
}

/* ************************************************************************** */
/* ------------------------------- MODIFIERS -------------------------------- */
/* ************************************************************************** */

template <typename T>
void
ft::Deque<T>::assign(size_type size, const_reference val)
{
	this->clear();
	this->reserve(size);
	for (size_t i = 0; i < size / 2; i++)
		this->push_front(val);
	for (size_t i = size / 2; i < size; i++)
		this->push_back(val);
}

template <typename T>
template <typename InputIterator>
void
ft::Deque<T>::assign(InputIterator first, InputIterator last)
{
	this->clear();
	while (first != last)
		this->push_back(*first++);

}

template <typename T>
void
ft::Deque<T>::push_front(const_reference val)
{
	if (this->m_capacity == 0 || this->m_start_container == 0)
		this->reserve(this->m_capacity * CONTAINER_SIZE, true);
	new(&this->m_containers[this->m_start_container][this->m_start_idx]) value_type(val);
	if (this->m_start_idx == 0) {
		--this->m_start_container;
		this->m_start_idx = CONTAINER_SIZE - 1;
	} else
		--this->m_start_idx;
	++this->m_size;
}

template <typename T>
void
ft::Deque<T>::push_back(const_reference val)
{
	if (this->m_capacity == 0 || this->m_end_container == this->m_capacity - 1)
		this->reserve(this->m_capacity * CONTAINER_SIZE, false);
	new(&this->m_containers[this->m_end_container][this->m_end_idx]) value_type(val);
	if (this->m_end_idx == CONTAINER_SIZE - 1) {
		++this->m_end_container;
		this->m_end_idx = 0;
	} else
		++this->m_end_idx;
	++this->m_size;
}

template <typename T>
void
ft::Deque<T>::pop_front(void)
{
	if (this->m_size == 0)
		return ;
	if (this->m_start_idx == CONTAINER_SIZE - 1) {
		this->m_start_idx = 0;
		++this->m_start_container;
	} else {
		++this->m_start_idx;
	}
	this->m_containers[this->m_start_container][this->m_start_idx].~value_type();
	--this->m_size;
}

template <typename T>
void
ft::Deque<T>::pop_back(void)
{
	if (this->m_size == 0)
		return ;
	if (this->m_end_idx == 0) {
		this->m_end_idx = CONTAINER_SIZE - 1;
		--this->m_end_container;
	} else {
		--this->m_end_idx;
	}
	this->m_containers[this->m_end_container][this->m_end_idx].~value_type();
	--this->m_size;
}


template <typename T>
typename ft::Deque<T>::iterator
ft::Deque<T>::insert(iterator position, const_reference val)
{
	this->insert(position, 1, val);
	return (++position);
}

template <typename T>
void
ft::Deque<T>::insert(iterator position, size_type n, const value_type& val)
{
	if (((this->m_capacity * CONTAINER_SIZE) - (this->m_end_container * CONTAINER_SIZE)) < n)
		this->reserve(this->m_capacity * CONTAINER_SIZE + n, false);
	size_type tmp_container = this->m_end_container + ((this->m_end_idx + n) / CONTAINER_SIZE);
	size_type tmp_idx = (this->m_end_idx + n) % CONTAINER_SIZE;
	if (tmp_idx >= CONTAINER_SIZE) {
		tmp_idx -= CONTAINER_SIZE;
		++tmp_container;
	}
	size_type param_container = this->convert_idx(this->revert_idx(this->m_end_container, this->m_end_idx) - 1).first;
	size_type param_idx = this->convert_idx(this->revert_idx(this->m_end_container, this->m_end_idx) - 1).second;
	move_container_to_back(position, param_container, param_idx, n);
	this->m_end_container = convert_idx(position.as_idx()).first;
	this->m_end_idx = convert_idx(position.as_idx()).second;
	for (size_t i = 0; i < n; i++)
		this->push_back(val);	
	this->m_end_container = tmp_container;
	this->m_end_idx = tmp_idx;
}

template <typename T>
void
ft::Deque<T>::insert(iterator position, iterator first, iterator last)
{
	while (first != last)
	{
		--last;
		this->insert(position, 1, static_cast<T>(*last));
	}
}

template <typename T>
typename ft::Deque<T>::iterator
ft::Deque<T>::erase(iterator position)
{
	iterator tmp(position);
	++tmp;
	return (this->erase(position, tmp));
}

template <typename T>
typename ft::Deque<T>::iterator
ft::Deque<T>::erase(iterator first, iterator last)
{
	size_type container;
	size_type idx;
	iterator start(first);
	size_type count = 0;

	while (first != last)
	{
		container = this->convert_idx(first.as_idx()).first;
		idx = this->convert_idx(first.as_idx()).second;
		this->m_containers[container][idx].~value_type();
		++first;
		++count;
	}
	this->m_size -= count;
	if (start == this->begin() && last == this->end()) {
		this->clear();
		return (this->begin());
	} else if (last == this->end()) {
		this->m_end_container = this->convert_idx(start.as_idx()).first;
		this->m_end_idx = this->convert_idx(start.as_idx()).second;
		return (this->end());
	} else if (start == this->begin()) {
		this->m_start_container = this->convert_idx(last.as_idx() - 1).first;
		this->m_start_idx = this->convert_idx(last.as_idx() - 1).second;
		return (this->begin());
	}

	size_type left = (this->m_start_container * CONTAINER_SIZE) + this->m_start_idx;
	size_type right = (this->m_capacity - 1 - this->m_end_container) * CONTAINER_SIZE + (CONTAINER_SIZE - this->m_end_idx);

	if (left > right) {
		this->move_container_to_front(--this->end(), this->convert_idx(last.as_idx()).first, this->convert_idx(last.as_idx()).second, count);
		container = this->convert_idx(this->revert_idx(this->m_end_container, this->m_end_idx) - count).first;
		idx = this->convert_idx(this->revert_idx(this->m_end_container, this->m_end_idx) - count).second;
		this->m_end_container = container;
		this->m_end_idx = idx;
		return (start);
	} else {
		this->move_container_to_back(this->begin(), this->convert_idx(start.as_idx() - 1).first, this->convert_idx(last.as_idx() - 1).second, count);
		container = this->convert_idx(this->revert_idx(this->m_start_container, this->m_start_idx) + count).first;
		idx = this->convert_idx(this->revert_idx(this->m_start_container, this->m_start_idx) + count).second;
		this->m_start_container = container;
		this->m_start_idx = idx;
	}
	return (++start);
}

template <typename T>
void
ft::Deque<T>::swap(Deque& obj)
{
	ft::swap(this->m_containers, obj.m_containers);
	ft::swap(this->m_capacity, obj.m_capacity);
	ft::swap(this->m_start_container, obj.m_start_container);
	ft::swap(this->m_start_idx, obj.m_start_idx);
	ft::swap(this->m_end_container, obj.m_end_container);
	ft::swap(this->m_end_idx, obj.m_end_idx);
	ft::swap(this->m_size, obj.m_size);
}

template <typename T>
void
ft::Deque<T>::clear()
{
	if (this->m_capacity == 0)
		return ;
	for (size_type i = this->m_start_container; i <= this->m_end_container; ++i)
	{
		for (size_type j = 0; j < CONTAINER_SIZE; ++j) {
			if (i == this->m_start_container && j <= this->m_start_idx)
				;
			else if (i == this->m_end_container && j >= this->m_end_idx)
				;
			else
				this->m_containers[i][j].~value_type();
		}
	}
	this->m_start_container = (this->m_capacity - 1) / 2;
	this->m_end_container = (this->m_capacity / 2);
	if (this->m_capacity % 2 == 0) {
		this->m_start_idx = CONTAINER_SIZE - 1;
		this->m_end_idx = 0;
	} else {
		this->m_start_idx = (CONTAINER_SIZE / 2) - 1;
		this->m_end_idx = CONTAINER_SIZE / 2;
	}
	this->m_size = 0;
}



}
// /* ************************************************************************** */
// /* --------------------------- NON MEMBER OPERATOR -------------------------- */
// /* ************************************************************************** */

template<typename T>
bool
operator==(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	if (lhs.size() != rhs.size())
		return (false);
	for (size_t i = 0; i < lhs.size(); i++)
		if (lhs[i] != rhs[i])
			return (false);
	return (true);
}

template<typename T>
bool
operator!=(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	return (!(lhs == rhs));
}

template<typename T>
bool
operator<(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<typename T>
bool
operator<=(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	return (!(rhs < lhs));
}

template<typename T>
bool
operator>(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	return (rhs < lhs);
}

template<typename T>
bool
operator>=(ft::Deque<T> const &lhs, ft::Deque<T> const &rhs) {
	return (!(lhs < rhs));
}

template <typename T>
void
swap(ft::Deque<T>& lhs, ft::Deque<T>& rhs) {
	lhs.swap(rhs);
}


#endif
