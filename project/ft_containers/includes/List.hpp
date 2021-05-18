#ifndef LIST_HPP
# define LIST_HPP

# include <string>
# include <iostream>
# include <memory>
# include <iterator>
# include "utility/Node.hpp"
# include "utility/Iterator.hpp"
# include "utility/Algorithm.hpp"

namespace ft {

/* ************************************************************************** */
/* --------------------------- ITERATOR PROTOTYPE --------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
class ListIterator {
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
		typedef N					node_type;
		typedef node_type*			node_pointer;
		typedef std::ptrdiff_t 		difference_type;
	protected:
		node_pointer 	p;
	public:
		ListIterator();
		ListIterator(node_pointer p);
		ListIterator(const ListIterator& copy);
		ListIterator&	operator=(const ListIterator& obj);
		virtual ~ListIterator();

		node_pointer&	ptr();
		node_pointer	as_node();

		reference 		operator*();
		const_reference operator*() const;
		pointer			operator->();
		const_pointer	operator->() const;
		ListIterator&	operator++();
		ListIterator	operator++(int);
		ListIterator&	operator--();
		ListIterator	operator--(int);
		ListIterator	operator+(int value) const;
		ListIterator&	operator+=(int value);
		ListIterator	operator-(int value) const;
		ListIterator&	operator-=(int value);
		bool			operator!=(const ListIterator& obj) const;
		bool			operator==(const ListIterator& obj) const;
		bool			operator<(const ListIterator& obj) const;
		bool			operator<=(const ListIterator& obj) const;
		bool			operator>(const ListIterator& obj) const;
		bool			operator>=(const ListIterator& obj) const;
};

/* ************************************************************************** */
/* ------------------------ ITERATOR CANONICAL FORM ------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
ft::ListIterator<T, N>::ListIterator()
: p(nullptr) {}

template <typename T, typename N>
ft::ListIterator<T, N>::ListIterator(node_pointer p)
: p(p) {}

template <typename T, typename N>
ft::ListIterator<T, N>::ListIterator(const ListIterator& copy)
: p(copy.p) {}

template <typename T, typename N>
ft::ListIterator<T, N>::~ListIterator() {}

/* ************************************************************************** */
/* --------------------------- ITERATOR OPERATOR ---------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
ft::ListIterator<T, N>&
ft::ListIterator<T, N>::operator=(const ft::ListIterator<T, N>& obj)
{
	if (this == &obj)
		return (*this);
	this->p = obj.p;
	return (*this);
}

template <typename T, typename N>
typename ft::ListIterator<T, N>::reference
ft::ListIterator<T, N>::operator*(void) {
	return (this->p->value());
}

template <typename T, typename N>
typename ft::ListIterator<T, N>::const_reference
ft::ListIterator<T, N>::operator*(void) const {
	return (this->p->value());
}

template <typename T, typename N>
typename ft::ListIterator<T, N>::pointer
ft::ListIterator<T, N>::operator->() {
	return (&this->p->value());
}

template <typename T, typename N>
typename ft::ListIterator<T, N>::const_pointer
ft::ListIterator<T, N>::operator->() const {
	return (&this->p->value());
}

template <typename T, typename N>
ft::ListIterator<T, N>&
ft::ListIterator<T, N>::operator++(void) {
	this->p = this->p->next();
	return (*this);
}

template <typename T, typename N>
ft::ListIterator<T, N>
ft::ListIterator<T, N>::operator++(int) {
	ListIterator<T, N> tmp(*this);
	this->operator++();
	return (tmp);
}

template <typename T, typename N>
ft::ListIterator<T, N>&
ft::ListIterator<T, N>::operator--(void) {
	this->p = this->p->prev();
	return (*this);
}

template <typename T, typename N>
ft::ListIterator<T, N>
ft::ListIterator<T, N>::operator--(int) {
	ListIterator<T, N> tmp(*this);
	this->operator--();
	return (tmp);
}

template <typename T, typename N>
ft::ListIterator<T, N>&
ft::ListIterator<T, N>::operator+=(int value)
{
	if (value > 0)
	{
		for (int i = 0; i < value; i++)
			this->p = this->p->next();		
	}
	else if (value < 0)
	{
		value *= -1;
		for (int i = 0; i < value; i++)
			this->p = this->p->prev();		
	}
	return (*this);
}

template <typename T, typename N>
ft::ListIterator<T, N>
ft::ListIterator<T, N>::operator+(int value) const {
	ListIterator<T, N> tmp(*this);
	return (tmp += value);
}

template <typename T, typename N>
ft::ListIterator<T, N>&
ft::ListIterator<T, N>::operator-=(int value)
{
	if (value > 0)
	{
		for (int i = 0; i < value; i++)
			this->p = this->p->prev();		
	}
	else if (value < 0)
	{
		value *= -1;
		for (int i = 0; i < value; i++)
			this->p = this->p->next();		
	}
	return (*this);
}

template <typename T, typename N>
ft::ListIterator<T, N>
ft::ListIterator<T, N>::operator-(int value) const {
	ListIterator<T, N> tmp(*this);
	return (tmp -= value);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator!=(const ft::ListIterator<T, N>& obj) const {
	return (this->p != obj.p);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator==(const ft::ListIterator<T, N>& obj) const {
	return (this->p == obj.p);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator<(const ft::ListIterator<T, N>& obj) const {
	return (this->p < obj.p);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator<=(const ft::ListIterator<T, N>& obj) const {
	return (this->p <= obj.p);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator>(const ft::ListIterator<T, N>& obj) const {
	return (this->p > obj.p);
}

template <typename T, typename N>
bool
ft::ListIterator<T, N>::operator>=(const ft::ListIterator<T, N>& obj) const {
	return (this->p >= obj.p);
}

/* ************************************************************************** */
/* --------------------------- ITERATOR FUNCTION ---------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
typename ft::ListIterator<T, N>::node_pointer
ft::ListIterator<T, N>::as_node(void) {
	return (this->p);
}

template <typename T, typename N>
typename ft::ListIterator<T, N>::node_pointer&
ft::ListIterator<T, N>::ptr(void) {
	return (this->p);
}

/* ************************************************************************** */
/* -------------------------- CONTAINER PROTOTYPE --------------------------- */
/* ************************************************************************** */

template<typename T>
class List
{
	public:
		typedef std::allocator<T>									allocator_type;
		typedef typename allocator_type::size_type					size_type;
		typedef T													value_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef value_type*											pointer;
		typedef const pointer										const_pointer;
		typedef Node<value_type>									node_type;
		typedef node_type*											node_pointer; 
		typedef ListIterator<value_type, node_type>					iterator;
		typedef ListIterator<const value_type, const node_type>		const_iterator;
		typedef ReverseIterator<iterator>							reverse_iterator;
		typedef ReverseIterator<const_iterator>						const_reverse_iterator;
		typedef std::ptrdiff_t 										difference_type;
	private:
		node_pointer m_begin;
		node_pointer m_end;
		size_type m_size;

		void init_list(void);
		void reset_list(void);
	public:
		/* canonical form */
		List();
		List(size_type n, const value_type& val = value_type());
		List(iterator first, iterator last);
		List(const List& copy);
		List& operator=(const List& obj);
		virtual ~List();

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
		bool empty() const;
		size_type size() const;
		size_type max_size() const;

		/* element access */
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		/* modifier function */
		void assign(size_type size, const_reference val);
		void assign(iterator first, iterator last);
		void assign(const_iterator first, const_iterator last);
		void push_front(const_reference val);
		void pop_front();
		void push_back(const_reference val);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const_reference val);
		void insert(iterator position, iterator first, iterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(List& obj);
		void resize(size_type n, value_type val = value_type());
		void clear();

		/* operations */
		void splice(iterator position, List& obj);
		void splice(iterator position, List& obj, iterator i);
		void splice(iterator position, List& obj, iterator first, iterator last);
		void remove(const_reference val);
		template <class Predicate>
		void remove_if(Predicate pred);
		void unique();
		template <typename BinaryPredicate>
		void unique(BinaryPredicate binary_pred);
		void merge(List& obj);
		template <typename Compare>
		void merge(List &obj, Compare comp);
		void sort();
		template <typename Compare>
		void sort(Compare comp);
		void reverse();
};

/* ************************************************************************** */
/* ------------------------ CONTAINER CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename T>
ft::List<T>::List()
: m_begin(nullptr), m_end(nullptr), m_size(0) {
	this->init_list();	
}

template <typename T>
ft::List<T>::List(size_type n, const value_type& val)
: m_begin(nullptr), m_end(nullptr), m_size(0) {
	this->init_list();
	this->assign(n, val);
}

template <typename T>
ft::List<T>::List(iterator first, iterator last)
: m_begin(nullptr), m_end(nullptr), m_size(0) {
	this->init_list();
	this->assign(first, last);
}

template <typename T>
ft::List<T>::List(const ft::List<T>& copy)
: m_begin(nullptr), m_end(nullptr), m_size(0) {
	this->init_list();
	this->assign(copy.begin(), copy.end());
}

template <typename T>
ft::List<T>&
ft::List<T>::operator=(const ft::List<T>& obj)
{
	if (this == &obj)
		return (*this);
	this->~List();
	this->init_list();
	this->assign(obj.begin(), obj.end());
	return (*this);
}

template <typename T>
void
ft::List<T>::init_list(void)
{
	this->m_end = new node_type();
	this->reset_list();
}

template <typename T>
void
ft::List<T>::reset_list(void)
{
	this->m_begin = this->m_end;
	this->m_end->prev() = nullptr;
	this->m_end->next() = nullptr;
	this->m_size = 0;
}

template <typename T>
ft::List<T>::~List()
{
	this->clear();
	delete this->m_end;
}

/* ************************************************************************** */
/* -------------------------- CONTAINER ITERATORS --------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::List<T>::iterator
ft::List<T>::begin(void) {
	return (iterator(this->m_begin));
}

template <typename T>
typename ft::List<T>::const_iterator
ft::List<T>::begin(void) const {
	return (const_iterator(this->m_begin));
}

template <typename T>
typename ft::List<T>::iterator
ft::List<T>::end(void) {
	return (iterator(this->m_end));
}

template <typename T>
typename ft::List<T>::const_iterator
ft::List<T>::end(void) const {
	return (const_iterator(this->m_end));
}

template <typename T>
typename ft::List<T>::reverse_iterator
ft::List<T>::rbegin(void) {
	return (reverse_iterator(this->end()));
}

template <typename T>
typename ft::List<T>::const_reverse_iterator
ft::List<T>::rbegin(void) const {
	return (const_reverse_iterator(this->end()));
}

template <typename T>
typename ft::List<T>::reverse_iterator
ft::List<T>::rend(void) {
	return (reverse_iterator(this->begin()));
}

template <typename T>
typename ft::List<T>::const_reverse_iterator
ft::List<T>::rend(void) const {
	return (const_reverse_iterator(this->begin()));
}

/* ************************************************************************** */
/* ------------------------------- CAPACITY --------------------------------- */
/* ************************************************************************** */

template <typename T>
bool
ft::List<T>::empty(void) const {
	return (this->m_size == 0);
}

template <typename T>
typename ft::List<T>::size_type
ft::List<T>::size(void) const {
	return (this->m_size);
}

template <typename T>
typename ft::List<T>::size_type
ft::List<T>::max_size(void) const {
	return (ft::min((size_type)std::numeric_limits<difference_type>::max(), \
	std::numeric_limits<size_type>::max() / (sizeof(node_type) - sizeof(pointer))));
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename T>
typename ft::List<T>::reference
ft::List<T>::front(void) {
	return (this->m_begin->value());
}

template <typename T>
typename ft::List<T>::const_reference
ft::List<T>::front(void) const {
	return (this->m_begin->value());
}

template <typename T>
typename ft::List<T>::reference
ft::List<T>::back(void) {
	return (this->m_end->prev()->value());
}

template <typename T>
typename ft::List<T>::const_reference
ft::List<T>::back(void) const {
	return (this->m_end->prev()->value());
}

/* ************************************************************************** */
/* ------------------------------- MODIFIERS -------------------------------- */
/* ************************************************************************** */

template <typename T>
void
ft::List<T>::assign(size_type size, const_reference val)
{
	this->clear();
	for (size_type i = 0; i < size; i++)
		this->push_back(val);
}

template <typename T>
void
ft::List<T>::assign(iterator first, iterator last)
{
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template <typename T>
void
ft::List<T>::assign(const_iterator first, const_iterator last)
{
	this->clear();
	while (first != last)
		this->push_back(*first++);
}

template <typename T>
void
ft::List<T>::push_front(const_reference val)
{
	node_pointer tmp = new node_type(val);

	if (this->m_size == 0)
		this->m_end->push_front(tmp);
	else
		this->m_begin->push_front(tmp);
	this->m_begin = tmp;
	++this->m_size;
}

template <typename T>
void
ft::List<T>::push_back(const_reference val)
{
	node_pointer tmp = new node_type(val);

	this->m_end->push_front(tmp);
	if (this->m_size == 0)
		this->m_begin = tmp;
	++this->m_size;
}

template <typename T>
void
ft::List<T>::pop_front(void)
{
	if (this->begin() == this->end())
		return ;
	node_pointer tmp = this->m_begin->next();
	this->m_begin->disconnect();
	delete this->m_begin;
	this->m_begin = tmp;
	--this->m_size;
}

template <typename T>
void
ft::List<T>::pop_back(void)
{
	if (this->begin() == this->end())
		return ;
	if (this->m_size == 1)
		this->pop_front();
	node_pointer tmp = this->m_end->prev();
	tmp->disconnect();
	delete tmp;
	--this->m_size;
}

template <typename T>
typename ft::List<T>::iterator
ft::List<T>::insert(iterator position, const_reference val)
{
	if (position == this->begin())
	{
		push_front(val);
		return (this->begin());
	}
	else if (position == this->end())
	{
		push_back(val);
		return (this->end());
	}
	node_pointer new_node = new node_type(val);
	position.as_node()->push_front(new_node);
	++this->m_size;
	return (iterator(new_node));
}

template <typename T>
void
ft::List<T>::insert(iterator position, size_type n, const value_type& val)
{
	for (size_type i = 0; i < n; i++)
		this->insert(position, val);
}

template <typename T>
void
ft::List<T>::insert(iterator position, iterator first, iterator last)
{
	while (first != last)
		this->insert(position, *first++);
}

template <typename T>
typename ft::List<T>::iterator
ft::List<T>::erase(iterator position)
{
	if (position == this->end())
		return (this->end());
	if (position == this->begin())
	{
		this->pop_front();
		return (this->begin());
	}
	node_pointer next = position.as_node()->next();
	position.as_node()->disconnect();
	delete position.as_node();
	--this->m_size;
	return (iterator(next));
}

template <typename T>
typename ft::List<T>::iterator
ft::List<T>::erase(iterator first, iterator last)
{
	while (first != last)
		this->erase(first++);
	return (first);
}

template <typename T>
void
ft::List<T>::swap(List& obj)
{
	ft::swap(this->m_begin, obj.m_begin);
	ft::swap(this->m_end, obj.m_end);
	ft::swap(this->m_size, obj.m_size);
}

template <typename T>
void
ft::List<T>::resize(size_type n, value_type val)
{
	if (this->m_size == 0)
		this->clear();
	else if (this->m_size > n)
	{
		size_t i = 0;
		iterator start = this->begin();
		while (i < n) {
			++i;
			++start;
		}
		this->erase(start, this->end());
	}
	else
		this->insert(this->end(), n - this->m_size, val);
}

template <typename T>
void
ft::List<T>::clear(void)
{
	this->erase(this->begin(), this->end());
	this->reset_list();
}

/* ************************************************************************** */
/* ------------------------------- OPERATIONS ------------------------------- */
/* ************************************************************************** */

template <typename T>
void
ft::List<T>::splice(iterator position, List& obj)
{
	this->splice(position, obj, obj.begin(), obj.end());
}

template <typename T>
void
ft::List<T>::splice(iterator position, List& obj, iterator i)
{
	iterator next(i);
	this->splice(position, obj, i, ++next);
}

template <typename T>
void
ft::List<T>::splice(iterator position, List& obj, iterator first, iterator last)
{
	while (first != last)
	{
		node_pointer tmp = first++.as_node();
		if (tmp == obj.m_begin)
			obj.m_begin = tmp->next();
		tmp->disconnect();
		--obj.m_size;
		position.as_node()->push_front(tmp);
		if (position.as_node() == this->m_begin)
			this->m_begin = tmp;
		++this->m_size;
	}
	if (obj.m_size == 0)
		obj.clear();
}

template <typename T>
void
ft::List<T>::remove(const_reference val)
{
	iterator first = this->begin();
	iterator last = this->end();

	while (first != last)
	{
		if (*first == val)
			first = this->erase(first);
		else
			++first;
	}
}

template <typename T>
template <typename Predicate>
void
ft::List<T>::remove_if(Predicate pred)
{
	iterator first = this->begin();
	iterator last = this->end();

	while (first != last)
	{
		if ((*pred)(*first))
			first = this->erase(first);
		else
			++first;
	}
}

template <typename T>
void
ft::List<T>::unique()
{
	if (this->m_size < 2)
		return ;
	iterator first = ++this->begin();
	iterator last = this->end();

	while (first != last)
	{
		if ((first - 1).as_node()->value() == first.as_node()->value())
			first = this->erase(first);
		else
			++first;
	}
}

template <typename T>
template <typename BinaryPredicate>
void
ft::List<T>::unique(BinaryPredicate binary_pred)
{
	iterator prev = this->begin();
	iterator next = prev + 1;
	iterator last = this->end();

	while (next != last)
	{
		if ((*binary_pred)(*prev, *next))
			prev = this->erase(prev);
		else
			prev = next;
		++next;
	}
}

template <typename T>
void
ft::List<T>::merge(List &obj) {
	if (&obj == this)
		return ;
	this->merge(obj, &less_than<value_type>);
}

template <typename T>
template <typename Compare>
void
ft::List<T>::merge(List &obj, Compare comp)
{
	if (this == &obj)
		return ;
	if (this->m_size == 0) {
		this->assign(obj.begin(), obj.end());
		obj.clear();
		return ;
	}
	iterator f1 = this->begin();
	iterator e1 = this->end();
	iterator f2 = obj.begin();
	iterator e2 = obj.end();

	while (f1 != e1 && f2 != e2) {
		if ((*comp)(*f2, *f1)) {
			obj.m_begin = f2.as_node()->next();
			--obj.m_size;
			f2.as_node()->disconnect();
			f1.as_node()->push_front(f2.as_node());
			if (f1 == this->begin()) {
				this->m_begin = f2.as_node();
			}
			++this->m_size;
			f2 = obj.begin();
		} else
			++f1;
	}
	this->splice(e1, obj);
}

template <typename T>
void
ft::List<T>::sort() {
	if (this->m_size <= 1)
		return ;
	this->sort(&less_than<value_type>);
}

template <typename T>
template <typename Compare>
void
ft::List<T>::sort(Compare comp)
{
	if (this->m_size <= 1)
		return ;
	iterator first = this->begin();
	iterator last = this->end();
	iterator next;
	iterator tmp;

	while (first != last) {
		next = first;
		{
			while (++next != last)
			{
				if ((*comp)(*next, *first)) {
					if (first.as_node() == this->m_begin)
						this->m_begin = next.as_node();
					first.as_node()->swap(next.as_node());
					ft::swap(first, next);
				}
			}
		}
		++first;
	}
}

template <typename T>
void
ft::List<T>::reverse() {
	if (this->m_size <= 1)
		return ;
	iterator first = this->begin();
	iterator last = --this->end();

	size_type limit = this->m_size / 2;
	for (size_t i = 0; i < limit; i++)
		first++.as_node()->swap(last--.as_node());
	while (last.as_node()->prev())
		--last;
	this->m_begin = last.ptr();
}

}
/* ************************************************************************** */
/* --------------------------- NON MEMBER OPERATOR -------------------------- */
/* ************************************************************************** */

template <typename T>
bool
operator==(const ft::List<T>& lhs, const ft::List<T>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::List<T>::const_iterator first = lhs.begin();
	typename ft::List<T>::const_iterator last = lhs.end();
	typename ft::List<T>::const_iterator obj = rhs.begin();
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
operator!=(const ft::List<T>& lhs, const ft::List<T>& rhs) {
	return (!(lhs == rhs));
}

template <typename T>
bool
operator<(const ft::List<T>& lhs, const ft::List<T>& rhs) {
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T>
bool
operator<=(const ft::List<T>& lhs, const ft::List<T>& rhs) {
	return (!(rhs < lhs));
}

template <typename T>
bool
operator>(const ft::List<T>& lhs, const ft::List<T>& rhs) {
	return (rhs < lhs);
}

template <typename T>
bool
operator>=(const ft::List<T>& lhs, const ft::List<T>& rhs) {
	return (!(lhs < rhs));
}

template <typename T>
void
swap(ft::List<T>& lhs, ft::List<T>& rhs) {
	lhs.swap(rhs);
}

#endif
