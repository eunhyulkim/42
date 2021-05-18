#ifndef NODE_HPP
# define NODE_HPP

namespace ft {

template <typename value_type>
class Node {
	private:
		Node<value_type>* m_prev;
		value_type m_value;
		Node<value_type>* m_next;
	public:
        /* canonical form */
		Node();
        Node(const value_type &value);
        Node(Node* prev, const value_type& value, Node *next = nullptr);
        Node(const Node& copy);
        virtual ~Node();

        /* overload operator */
        Node& operator=(Node const &obj);

        /* getter function */
        value_type& value(void);
        const value_type& value(void) const;
        Node*& prev(void);
        Node const *prev(void) const;
        Node*& next(void);
        Node const *next(void) const;

        /* member function */
		void push_front(Node *element);
		void push_back(Node *element);
        void reverse(void);
        void swap(Node *node);
        void swap_values(Node *node);
        void disconnect(void);
};

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename value_type>
ft::Node<value_type>::Node()
: m_prev(nullptr), m_value(), m_next(nullptr) {}

template <typename value_type>
ft::Node<value_type>::Node(const value_type& value)
: m_prev(nullptr), m_value(value), m_next(nullptr) {}

template <typename value_type>
ft::Node<value_type>::Node(Node<value_type>* prev, const value_type& value, Node<value_type> *next)
: m_prev(prev), m_value(value), m_next(next) {}

template <typename value_type>
ft::Node<value_type>::Node(const Node<value_type>& copy)
: m_prev(copy.m_prev), m_value(copy.m_value), m_next(copy.m_next) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename value_type>
ft::Node<value_type>::~Node() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

template <typename value_type>
Node<value_type>&
ft::Node<value_type>::operator=(Node<value_type> const &obj) {

	if (this == &obj)
		return (*this);
    this->m_previous = obj.m_prev;
    this->m_value = obj.m_value;
    this->m_next = obj.m_next;
    return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

template <typename value_type>
value_type&
ft::Node<value_type>::value(void) {
    return (this->m_value);
}

template <typename value_type>
const value_type& ft::Node<value_type>::value(void) const {
    return (this->m_value);
}

template <typename value_type>
Node<value_type>*& ft::Node<value_type>::prev(void) {
    return (this->m_prev);
}

template <typename value_type>
Node<value_type> const * ft::Node<value_type>::prev(void) const {
    return (this->m_prev);
}

template <typename value_type>
Node<value_type> *& ft::Node<value_type>::next(void) {
    return (this->m_next);
}

template <typename value_type>
Node<value_type> const *
ft::Node<value_type>::next(void) const {
    return (this->m_next);
}

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */
#include <iostream>

template <typename value_type>
void
ft::Node<value_type>::push_front(Node<value_type> *element)
{
	if (this->m_prev) {
		element->m_prev = this->m_prev;
		this->m_prev->m_next = element;
	}
	element->m_next = this;
	this->m_prev = element;

	// if (this->m_prev) {
	// 	element->m_prev = this->m_prev;
	// 	element->m_prev->m_next = element;
	// }
	// element->m_next = this;
	// this->m_prev = element;
}

template <typename value_type>
void
ft::Node<value_type>::push_back(Node<value_type> *element)
{
	if (this->m_next) {
		element->m_next = this->m_next;
		element->m_next->m_prev = element;
	}
	element->m_prev = this;
	this->m_next = element;
}

template <typename value_type>
void
ft::Node<value_type>::reverse()
{
    Node<value_type>* tmp = this->m_next;
    this->m_next = this->m_prev;
    this->m_prev = tmp;
}

template <typename value_type>
void
ft::Node<value_type>::swap(Node<value_type> *node)
{
    if (node == this)
        return ;
    if (this->m_next == node)
    {
        if (this->m_prev)
            this->m_prev->m_next = node;
        node->m_prev = this->m_prev;
        this->m_prev = node;
        if (node->m_next)
            node->m_next->m_prev = this;
        this->m_next = node->m_next;
        node->m_next = this;
    }
    else if (this->m_prev == node)
    {
        if (node->m_prev)
            node->m_prev->m_next = this;
        this->m_prev = node->m_prev;
        node->m_prev = this;
        if (this->m_next)
            this->m_next->m_prev = node;
        node->m_next = this->m_next;
        this->m_next = node;
    }
    else
    {
        Node<value_type>* t_prev = this->m_prev;
        Node<value_type>* t_next = this->m_next;

        if (this->m_prev)
            this->m_prev->m_next = node;
        if (this->m_next)
            this->m_next->m_prev = node;
        this->m_prev = node->m_prev;
        this->m_next = node->m_next;
        if (node->m_prev)
            node->m_prev->m_next = this;
        if (node->m_next)
            node->m_next->m_prev = this;
        node->m_prev = t_prev;
        node->m_next = t_next;
    }
}

template <typename value_type>
void
ft::Node<value_type>::swap_values(Node<value_type> *node)
{
    value_type tmp;
    std::memmove(static_cast<void*>(&tmp), static_cast<void*>(&node->m_value), 1);
    std::memmove(static_cast<void*>(&node->m_value), static_cast<void*>(&this->m_value), 1);
    std::memmove(static_cast<void*>(&this->m_value), static_cast<void*>(&tmp), 1);
}

template <typename value_type>
void
ft::Node<value_type>::disconnect(void)
{
    if (this->m_prev) {
        this->m_prev->m_next = this->m_next;
    }
    if (this->m_next) {
        this->m_next->m_prev = this->m_prev;
    }
    this->m_prev = nullptr;
    this->m_next = nullptr;
}

}

#endif
