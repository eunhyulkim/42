#ifndef TREE_HPP
# define TREE_HPP

# include <utility>
# include "Iterator.hpp"
# include "Algorithm.hpp"

namespace ft
{

/* ************************************************************************** */
/* --------------------------- ITERATOR PROTOTYPE --------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
class TreeIterator {
	public:
		typedef T					value_type;
		typedef value_type*			pointer;
		typedef value_type const *	const_pointer;
		typedef value_type&			reference;
		typedef const value_type&	const_reference;
        typedef N                   node_type;
        typedef node_type*          node_pointer;
		typedef std::ptrdiff_t 		difference_type;
	protected:
		node_pointer 	p;

        void prev();
        void next();
	public:
		TreeIterator();
		TreeIterator(node_pointer p);
		TreeIterator(const TreeIterator& copy);
		TreeIterator&	operator=(const TreeIterator& obj);
		virtual ~TreeIterator();

        node_pointer    as_node() const;

		reference 		operator*();
		const_reference operator*() const;
		pointer			operator->();
		const_pointer	operator->() const;
		TreeIterator&	operator++();
		TreeIterator	operator++(int);
		TreeIterator&	operator--();
		TreeIterator	operator--(int);
		TreeIterator	operator+(int value) const;
		TreeIterator&	operator+=(int value);
		TreeIterator	operator-(int value) const;
		TreeIterator&	operator-=(int value);
		bool			operator!=(const TreeIterator& obj) const;
		bool			operator==(const TreeIterator& obj) const;
		bool			operator<(const TreeIterator& obj) const;
		bool			operator<=(const TreeIterator& obj) const;
		bool			operator>(const TreeIterator& obj) const;
		bool			operator>=(const TreeIterator& obj) const;
};

/* ************************************************************************** */
/* ---------------------- ITERATOR PROTECT FUNCTION ------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
void
ft::TreeIterator<T, N>::prev(void)
{
    if (this->p->left) {
        this->p = this->p->left;
        while (this->p->right)
            this->p = this->p->right;
    } else {
        node_pointer tmp = this->p;
        this->p = this->p->parent;
        while (this->p->right != tmp) {
            tmp = this->p;
            this->p = this->p->parent;
        }
    }
}

template <typename T, typename N>
void
ft::TreeIterator<T, N>::next(void)
{
    if (this->p->right) {
        this->p = this->p->right;
        while (this->p->left)
            this->p = this->p->left;
    } else {
        node_pointer tmp = this->p;
        this->p = this->p->parent;
        while (this->p->left != tmp) {
            tmp = this->p;
            this->p = this->p->parent;
        }
    }
}

/* ************************************************************************** */
/* ------------------------ ITERATOR CANONICAL FORM ------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
ft::TreeIterator<T, N>::TreeIterator()
: p(nullptr) {}

template <typename T, typename N>
ft::TreeIterator<T, N>::TreeIterator(node_pointer p)
: p(p) {}

template <typename T, typename N>
ft::TreeIterator<T, N>::TreeIterator(const TreeIterator& copy)
: p(copy.p) {}

template <typename T, typename N>
ft::TreeIterator<T, N>::~TreeIterator() {}

template <typename T, typename N>
ft::TreeIterator<T, N>&
ft::TreeIterator<T, N>::operator=(const ft::TreeIterator<T, N>& obj)
{
	if (this == &obj)
		return (*this);
	this->p = obj.p;
	return (*this);
}

/* ************************************************************************** */
/* ----------------------- ITERATOR PUBLIC FUNCTION ------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
typename ft::TreeIterator<T, N>::node_pointer
ft::TreeIterator<T, N>::as_node(void) const {
	return (this->p);
}

/* ************************************************************************** */
/* --------------------------- ITERATOR OPERATOR ---------------------------- */
/* ************************************************************************** */

template <typename T, typename N>
typename ft::TreeIterator<T, N>::reference
ft::TreeIterator<T, N>::operator*(void) {
	return (this->p->value);
}

template <typename T, typename N>
typename ft::TreeIterator<T, N>::const_reference
ft::TreeIterator<T, N>::operator*(void) const {
	return (this->p->value);
}

template <typename T, typename N>
typename ft::TreeIterator<T, N>::pointer
ft::TreeIterator<T, N>::operator->() {
	return (&this->p->value);
}

template <typename T, typename N>
typename ft::TreeIterator<T, N>::const_pointer
ft::TreeIterator<T, N>::operator->() const {
	return (&this->p->value);
}

template <typename T, typename N>
ft::TreeIterator<T, N>&
ft::TreeIterator<T, N>::operator++(void) {
	this->next();
	return (*this);
}

template <typename T, typename N>
ft::TreeIterator<T, N>
ft::TreeIterator<T, N>::operator++(int) {
	TreeIterator<T, N> tmp(*this);
	this->next();
	return (tmp);
}

template <typename T, typename N>
ft::TreeIterator<T, N>&
ft::TreeIterator<T, N>::operator--(void) {
	this->prev();
	return (*this);
}

template <typename T, typename N>
ft::TreeIterator<T, N>
ft::TreeIterator<T, N>::operator--(int) {
	TreeIterator<T, N> tmp(*this);
	this->prev();
	return (tmp);
}

template <typename T, typename N>
ft::TreeIterator<T, N>&
ft::TreeIterator<T, N>::operator+=(int value)
{
    if (value > 0) {
        for (int i = 0; i < value; i++)
            this->next();
    } else {
        for (int i = -value; i > 0; i--)
            this->prev();
    }
	return (*this);
}

template <typename T, typename N>
ft::TreeIterator<T, N>
ft::TreeIterator<T, N>::operator+(int value) const {
	TreeIterator<T, N> tmp(*this);
	return (tmp += value);
}

template <typename T, typename N>
ft::TreeIterator<T, N>&
ft::TreeIterator<T, N>::operator-=(int value)
{
	this->operator+=(-value);
	return (*this);
}

template <typename T, typename N>
ft::TreeIterator<T, N>
ft::TreeIterator<T, N>::operator-(int value) const {
	TreeIterator<T, N> tmp(*this);
	return (tmp -= value);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator!=(const ft::TreeIterator<T, N>& obj) const {
	return (this->p != obj.p);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator==(const ft::TreeIterator<T, N>& obj) const {
	return (this->p == obj.p);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator<(const ft::TreeIterator<T, N>& obj) const {
	return (this->p < obj.p);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator<=(const ft::TreeIterator<T, N>& obj) const {
	return (this->p <= obj.p);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator>(const ft::TreeIterator<T, N>& obj) const {
	return (this->p > obj.p);
}

template <typename T, typename N>
bool
ft::TreeIterator<T, N>::operator>=(const ft::TreeIterator<T, N>& obj) const {
	return (this->p >= obj.p);
}

/* ************************************************************************** */
/* ----------------------------- TREE PROTOTYPE ----------------------------- */
/* ************************************************************************** */

template <typename T, typename Compare>
class Tree
{
    public:
        typedef size_t                  size_type;
        typedef T                       value_type;
        typedef value_type*             pointer;
        typedef value_type const *      const_pointer;
        typedef value_type&             reference;
        typedef const value_type&       const_reference;


        struct Node
        {
            value_type  value;
            Node*       parent;
            Node*       left;
            Node*       right;

            Node(const_reference val = value_type()):
                value(val), parent(nullptr), left(nullptr), right(nullptr) {}
            Node(Node const &other):
                value(other.value), parent(nullptr), left(nullptr), right(nullptr) {}
        };
	    typedef Node* node_pointer;

    protected:
        node_pointer    m_root;
        node_pointer    m_begin;
        node_pointer    m_end;
        Compare         m_comp;

        void init_tree();
        void delete_tree(node_pointer node);
        void repair_tree();
        void insert_node_at(node_pointer node, node_pointer new_node);
        node_pointer find_node(const_reference val, node_pointer node);
        void disconnect_node(node_pointer node);
        node_pointer next_node(node_pointer node);
    public:
        Tree();
        Tree(const Compare& comp);
        Tree(const Tree& copy);
        virtual ~Tree();
        Tree& operator=(const Tree& obj);

        void make_empty();
        void copy_subtree(node_pointer *dest, node_pointer source, node_pointer end);
        void copy_tree(const Tree& copy);
        node_pointer insert(const_reference val);
        node_pointer insert(node_pointer hint, const_reference val);
        node_pointer find(const_reference val);
        node_pointer find(node_pointer hint, const_reference val);
        node_pointer erase(node_pointer node);
        size_type erase(const_reference key);
        node_pointer erase_node(node_pointer node);

        Compare compare(void) const;
        node_pointer begin(void) const;
        node_pointer root(void) const;
        node_pointer end(void) const;

        void swap(Tree &obj);
};

/* ************************************************************************** */
/* ------------------------- TREE INTERNAL FUNCTION ------------------------- */
/* ************************************************************************** */

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::init_tree()
{
	this->m_begin = new Node();
    this->m_end = this->m_begin;
    this->m_root = this->m_end;
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::delete_tree(node_pointer node)
{
    if (!node || node == this->m_end)
        return ;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::repair_tree(void)
{
    node_pointer tmp = this->m_root;
    while (tmp->left)
        tmp = tmp->left;
    this->m_begin = tmp;
    tmp = this->m_root;
    while (tmp->right)
        tmp = tmp->right;
    tmp->right = this->m_end;
    this->m_end->parent = tmp;
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::insert_node_at(node_pointer node, node_pointer new_node)
{
    if (this->m_comp(new_node->value, node->value)) {
        if (node->left) {
            this->insert_node_at(node->left, new_node);
            return ;
        } else
            node->left = new_node;
    } else {
        if (node->right) {
            this->insert_node_at(node->right, new_node);
            return ;
        } else
            node->right = new_node;
    }
    new_node->parent = node;
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::find_node(const_reference val, node_pointer node)
{
    if (node == this->m_end || !node)
        return (nullptr);
    bool comp_left = this->m_comp(val, node->value);
    if (!comp_left && !this->m_comp(node->value, val))
        return (node);
    if (comp_left)
        return (this->find_node(val, node->left));
    return (this->find_node(val, node->right));
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::disconnect_node(node_pointer node) {
    if (!node)
        return ;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::next_node(node_pointer node)
{
    node_pointer alter = node;

    if (alter->right) {
        alter = alter->right;
        while (alter->left)
            alter = alter->left;
    } else if (alter == this->m_root) {
        return (this->m_end);
    } else {
        node_pointer tmp = alter;
        alter = alter->parent;
        while (alter->left != tmp) {
            tmp = alter;
            alter = alter->parent;
            if (alter == this->m_root && alter->left != tmp)
                return (this->m_end);
        }
    }
    return (alter);
}

/* ************************************************************************** */
/* --------------------------- TREE CANONICAL FORM -------------------------- */
/* ************************************************************************** */

template <typename T, typename Compare>
ft::Tree<T, Compare>::Tree()
: m_root(nullptr), m_comp() {
	this->init_tree();
}

template <typename T, typename Compare>
ft::Tree<T, Compare>::Tree(const Compare& comp)
: m_root(nullptr), m_comp(comp) {
	this->init_tree();
}

template <typename T, typename Compare>
ft::Tree<T, Compare>::Tree(const Tree& copy)
: m_root(copy.m_root), m_comp(copy.m_comp) {
	this->init_tree();
    this->copy_tree(copy);
}

template <typename T, typename Compare>
ft::Tree<T, Compare>&
ft::Tree<T, Compare>::operator=(const ft::Tree<T, Compare>& obj)
{
	if (this == &obj)
		return (*this);
	if (this->m_root != this->m_end)
        this->make_empty();
    this->m_comp = obj.m_comp;
    this->copy_tree(obj);
	return (*this);
}

template <typename T, typename Compare>
ft::Tree<T, Compare>::~Tree()
{
	this->make_empty();
	delete this->m_end;
}

/* ************************************************************************** */
/* ------------------------- TREE EXTERNAL FUNCTION ------------------------- */
/* ************************************************************************** */

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::make_empty()
{
    this->delete_tree(this->m_root);
    this->m_end->parent = nullptr;
    this->m_end->left = nullptr;
    this->m_end->right = nullptr;
    this->m_begin = this->m_root = this->m_end;
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::copy_subtree(node_pointer *dest, node_pointer source, node_pointer end)
{
    if (!source)
        return ;
    *dest = new Node(*source);
    if (source->left) {
        copy_subtree(&(*dest)->left, source->left, end);
        (*dest)->left->parent = *dest;
    }
    if (source->right && source->right != end) {
        copy_subtree(&(*dest)->right, source->right, end);
        (*dest)->right->parent = *dest;
    }
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::copy_tree(Tree const &copy)
{
    if (copy.m_root == copy.m_end)
        return ;
    this->m_root = new Node(*copy.m_root);
    if (copy.m_root->left) {
        this->copy_subtree(&this->m_root->left, copy.m_root->left, copy.m_end);
        this->m_root->left->parent = this->m_root;
    }
    if (copy.m_root->right && copy.m_root->right != copy.m_end) {
        this->copy_subtree(&this->m_root->right, copy.m_root->right, copy.m_end);
        this->m_root->right->parent = this->m_root;
    }
    this->repair_tree();
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::insert(const_reference val)
{
    node_pointer new_node = new Node(val);
    if (this->m_root == this->m_end)
        this->m_root = new_node;
    else {
        if (this->m_end->parent)
            this->m_end->parent->right = nullptr;
        this->insert_node_at(this->m_root, new_node);
    }
    this->repair_tree();
    return (new_node);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::insert(node_pointer hint, const_reference val)
{
    if (!hint || this->m_root == this->m_end
        || (hint->parent && (m_comp(val, hint->parent->value) || m_comp(hint->parent->value, val))))
        return (this->insert(val));
    node_pointer new_node = new Node(val);
    if (this->m_end->parent)
        this->m_end->parent->right = nullptr;
    this->insert_node_at(hint, new_node);
    this->repair_tree();
    return (new_node);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::find(const_reference val) {
    return (this->find_node(val, this->m_root));
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::find(node_pointer hint, const_reference val)
{
    if (!hint)
        return (this->find_node(val, this->m_root));
    if (!m_comp(hint->value, val) && !m_comp(val, hint->value))
        return (hint);
    return (this->find_node(val, hint));
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::erase_node(node_pointer node)
{
    if (!node)
        return (node);
    node_pointer ret = node;
    // no children
    if (!node->left && !node->right) {
        if (node == this->m_root) {
            this->m_root = this->m_begin = this->m_end;
            this->disconnect_node(this->m_end);
        }
        ret = next_node(node);
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = nullptr;
            else
                node->parent->right = nullptr;
        }
        delete node;
    // one child (right)
    } else if (!node->left) {
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = node->right;
            else
                node->parent->right = node->right;
        }
        node->right->parent = node->parent;
        if (node == this->m_root)
            this->m_root = node->right;
        ret = node->right;
        delete node;
    // one child (left)
    } else if (!node->right) {
        if (node->parent) {
            if (node->parent->left == node)
                node->parent->left = node->left;
            else
                node->parent->right = node->left;
        }
        node->left->parent = node->parent;
        if (node == this->m_root)
            this->m_root = node->left;
        ret = next_node(node);
        delete node;
    // two children
    } else {
        node_pointer tmp = node->right; // find minimal value of right sub tree
        while (tmp && tmp->left != nullptr)
            tmp = tmp->left;
        if (node->right != tmp)
            tmp->parent->left = nullptr;
        tmp->left = node->left;
        if (node->right != tmp)
            tmp->right = node->right;
        tmp->parent = node->parent;
        if (node->parent && node->parent->left == node)
            node->parent->left = tmp;
        else if (node->parent && node->parent->right == node)
            node->parent->right = tmp;
        node->left->parent = tmp;
        if (node->right != tmp)
            node->right->parent = tmp;
        if (node == this->m_root)
            this->m_root = tmp;
        ret = tmp;
        delete node; // delete the duplicate node
    }
    return (ret);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::erase(node_pointer node)
{
    if (this->m_end->parent)
        this->m_end->parent->right = nullptr;
    node_pointer next = this->erase_node(node);
    this->repair_tree();
    return (next);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::size_type
ft::Tree<T, Compare>::erase(const_reference key)
{
    node_pointer node = nullptr;
    size_type total = 0;

    if (this->m_end->parent)
        this->m_end->parent->right = nullptr;
    while ((node = this->find(key))) {
        this->erase_node(node);
        total++;
    }
    this->repair_tree();
    return (total);
}

template <typename T, typename Compare>
Compare
ft::Tree<T, Compare>::compare(void) const {
    return (this->m_comp);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::begin(void) const {
    return (this->m_begin);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::root(void) const {
    return (this->m_root);
}

template <typename T, typename Compare>
typename ft::Tree<T, Compare>::node_pointer
ft::Tree<T, Compare>::end(void) const {
    return (this->m_end);
}

template <typename T, typename Compare>
void
ft::Tree<T, Compare>::swap(Tree &obj)
{
    ft::swap(this->m_root, obj.m_root);
    ft::swap(this->m_begin, obj.m_begin);
    ft::swap(this->m_end, obj.m_end);
    ft::swap(this->m_comp, obj.m_comp);
}



};

#endif
