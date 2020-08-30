#ifndef STACK_HPP
# define STACK_HPP

# include "List.hpp"

namespace ft {

/* ************************************************************************** */
/* --------------------------- CONTAINER PROTOTYPE -------------------------- */
/* ************************************************************************** */

template<typename T, typename C = ft::List<T> >
class Stack
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
		Stack(const container_type& ctnr = container_type());
		Stack(const Stack& copy);
		Stack& operator=(const Stack& obj);
		virtual ~Stack();

		/* capacity */
		size_type size() const;
		bool empty() const;

		/* element access */
		reference top();
		const_reference top() const;

		/* modifier function */
		void push(const_reference val);
		void pop();

		friend bool ::operator==(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
		friend bool ::operator!=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
		friend bool ::operator>(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
		friend bool ::operator>=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
		friend bool ::operator<(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
		friend bool ::operator<=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs);
};

/* ************************************************************************** */
/* ------------------------ CONTAINER CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename T, typename C>
ft::Stack<T, C>::Stack(const container_type& ctnr)
: m_container(ctnr) {}

template <typename T, typename C>
ft::Stack<T, C>::Stack(const ft::Stack<T, C>& copy)
: m_container(copy.m_container) {}

template <typename T, typename C>
ft::Stack<T, C>::~Stack() {}

template <typename T, typename C>
ft::Stack<T, C>&
ft::Stack<T, C>::operator=(const ft::Stack<T, C>& obj)
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
typename ft::Stack<T, C>::size_type
ft::Stack<T, C>::size(void) const {
	return (this->m_container.size());
}

template <typename T, typename C>
bool
ft::Stack<T, C>::empty(void) const {
	return (this->m_container.empty());
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename T, typename C>
typename ft::Stack<T, C>::reference
ft::Stack<T, C>::top(void) {
	return (this->m_container.back());
}

template <typename T, typename C>
typename ft::Stack<T, C>::const_reference
ft::Stack<T, C>::top(void) const {
	return (this->m_container.back());
}

// /* ************************************************************************** */
// /* ------------------------------- MODIFIERS -------------------------------- */
// /* ************************************************************************** */

template <typename T, typename C>
void
ft::Stack<T, C>::push(const_reference val) {
	this->m_container.push_back(val);
}

template <typename T, typename C>
void
ft::Stack<T, C>::pop(void) {
	this->m_container.pop_back();
}

}

// /* ************************************************************************** */
// /* --------------------------- NON MEMBER OPERATOR -------------------------- */
// /* ************************************************************************** */

template <typename T, typename C>
bool
operator==(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs){
	return (lhs.m_container == rhs.m_container);
}

template <typename T, typename C>
bool
operator!=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs) {
	return (lhs.m_container != rhs.m_container);
}

template <typename T, typename C>
bool
operator<(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs) {
	return (lhs.m_container < rhs.m_container);
}

template <typename T, typename C>
bool
operator<=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs) {
	return (lhs.m_container <= rhs.m_container);
}

template <typename T, typename C>
bool
operator>(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs) {
	return (lhs.m_container > rhs.m_container);
}

template <typename T, typename C>
bool
operator>=(const ft::Stack<T, C>& lhs, const ft::Stack<T, C>& rhs) {
	return (lhs.m_container >= rhs.m_container);
}

#endif
