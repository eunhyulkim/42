#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "List.hpp"

namespace ft {

/* ************************************************************************** */
/* --------------------------- CONTAINER PROTOTYPE -------------------------- */
/* ************************************************************************** */

template<typename T, typename C = ft::List<T> >
class Queue
{
	public:
		typedef std::allocator<T>									allocator_type;
		typedef typename allocator_type::size_type					size_type;
		typedef T													value_type;
		typedef value_type&											reference;
		typedef const value_type&									const_reference;
		typedef C													container_type;
		typedef std::ptrdiff_t 										difference_type;
	private:
		container_type m_container;
	public:
		/* canonical form */
		Queue(const container_type& ctnr = container_type());
		Queue(const Queue& copy);
		Queue& operator=(const Queue& obj);
		virtual ~Queue();

		/* capacity */
		size_type size() const;
		bool empty() const;

		/* element access */
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		/* modifier function */
		void push(const_reference val);
		void pop();

		friend bool ::operator==(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
		friend bool ::operator!=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
		friend bool ::operator>(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
		friend bool ::operator>=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
		friend bool ::operator<(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
		friend bool ::operator<=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs);
};

/* ************************************************************************** */
/* ------------------------ CONTAINER CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename T, typename C>
ft::Queue<T, C>::Queue(const container_type& ctnr)
: m_container(ctnr) {}

template <typename T, typename C>
ft::Queue<T, C>::Queue(const ft::Queue<T, C>& copy)
: m_container(copy.m_container) {}

template <typename T, typename C>
ft::Queue<T, C>::~Queue() {}

template <typename T, typename C>
ft::Queue<T, C>&
ft::Queue<T, C>::operator=(const ft::Queue<T, C>& obj)
{
	if (this == &obj)
		return (*this);
	this->m_container = obj.m_container;
	return (*this);
}

/* ************************************************************************** */
/* ------------------------------- CAPACITY --------------------------------- */
/* ************************************************************************** */

template <typename T, typename C>
typename ft::Queue<T, C>::size_type
ft::Queue<T, C>::size(void) const {
	return (this->m_container.size());
}

template <typename T, typename C>
bool
ft::Queue<T, C>::empty(void) const {
	return (this->m_container.empty());
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename T, typename C>
typename ft::Queue<T, C>::reference
ft::Queue<T, C>::front(void) {
	return (this->m_container.front());
}

template <typename T, typename C>
typename ft::Queue<T, C>::const_reference
ft::Queue<T, C>::front(void) const {
	return (this->m_container.front());
}

template <typename T, typename C>
typename ft::Queue<T, C>::reference
ft::Queue<T, C>::back(void) {
	return (this->m_container.back());
}

template <typename T, typename C>
typename ft::Queue<T, C>::const_reference
ft::Queue<T, C>::back(void) const {
	return (this->m_container.back());
}

// /* ************************************************************************** */
// /* ------------------------------- MODIFIERS -------------------------------- */
// /* ************************************************************************** */

template <typename T, typename C>
void
ft::Queue<T, C>::push(const_reference val) {
	this->m_container.push_back(val);
}

template <typename T, typename C>
void
ft::Queue<T, C>::pop(void) {
	this->m_container.pop_front();
}

}

// /* ************************************************************************** */
// /* --------------------------- NON MEMBER OPERATOR -------------------------- */
// /* ************************************************************************** */

template <typename T, typename C>
bool
operator==(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs){
	return (lhs.m_container == rhs.m_container);
}

template <typename T, typename C>
bool
operator!=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs) {
	return (lhs.m_container != rhs.m_container);
}

template <typename T, typename C>
bool
operator<(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs) {
	return (lhs.m_container < rhs.m_container);
}

template <typename T, typename C>
bool
operator<=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs) {
	return (lhs.m_container <= rhs.m_container);
}

template <typename T, typename C>
bool
operator>(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs) {
	return (lhs.m_container > rhs.m_container);
}

template <typename T, typename C>
bool
operator>=(const ft::Queue<T, C>& lhs, const ft::Queue<T, C>& rhs) {
	return (lhs.m_container >= rhs.m_container);
}

#endif
