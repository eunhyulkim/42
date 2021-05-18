#ifndef SET_HPP
# define SET_HPP

# include "utility/MapBase.hpp"
# include <iostream>

namespace ft
{

template<typename K, typename Compare = ft::less<K> >
class Set: public MapBase<K, K, Compare>
{
    public:
        typedef MapBase<K, K, Compare>                  base;
        using typename                                  base::difference_type;
        using typename                                  base::size_type;
        using typename                                  base::key_type;
        using typename                                  base::value_type;
        using typename                                  base::pointer;
        using typename                                  base::const_pointer;
        using typename                                  base::reference;
        using typename                                  base::const_reference;
        using typename                                  base::key_compare;
        using typename                                  base::value_compare;
        using typename                                  base::tree_type;
        using typename                                  base::node_type;
        using typename                                  base::node_pointer;
        using typename                                  base::iterator;
        using typename                                  base::const_iterator;
        using typename                                  base::reverse_iterator;
        using typename                                  base::const_reverse_iterator;
    public:
        Set();
        Set(iterator first, iterator last);
        Set(Set const &copy);
        virtual ~Set();
        Set& operator=(const Set& obj);

        typename ft::Pair<iterator, bool> insert(const_reference val);
        iterator insert(iterator position, const_reference val);
        template<typename InputIterator>
        void insert(InputIterator first, InputIterator last);

        key_compare key_comp(void) const;
        value_compare value_comp(void) const;
};

/* ************************************************************************** */
/* --------------------------- MAP CANONICAL FORM --------------------------- */
/* ************************************************************************** */

template<typename K, typename Compare>
ft::Set<K, Compare>::Set() : base() {}

template<typename K, typename Compare>
ft::Set<K, Compare>::Set(iterator first, iterator last) : base(first, last) {}

template<typename K, typename Compare>
ft::Set<K, Compare>::Set(const Set& copy) : base(copy) {}

template<typename K, typename Compare>
ft::Set<K, Compare>::~Set() {}

template<typename K, typename Compare>
ft::Set<K, Compare>&
ft::Set<K, Compare>::operator=(const Set& obj) {
    this->base::operator=(obj);
    return (*this);
}

/* ************************************************************************** */
/* ------------------------------ SET FUNCTION ------------------------------ */
/* ************************************************************************** */

template<typename K, typename Compare>
ft::Pair<typename ft::Set<K, Compare>::iterator, bool>
ft::Set<K, Compare>::insert(const_reference val)
{
    node_pointer node = this->m_tree.find(val);
    if (node)
        return (ft::make_pair(iterator(node), false));
    node_pointer inserted = this->m_tree.insert(val);
    ++this->m_size;
    return (ft::make_pair(iterator(inserted), true));
}

template<typename K, typename Compare>
typename ft::Set<K, Compare>::iterator
ft::Set<K, Compare>::insert(iterator position, const_reference val)
{
    node_pointer node = this->m_tree.find(position.as_node(), val);
    if (node)
        return (iterator(node));
    ++this->m_size;
    return (iterator(this->m_tree.insert(position.as_node(), val)));
}

template<typename K, typename Compare>
template<typename InputIterator>
void
ft::Set<K, Compare>::insert(InputIterator first, InputIterator last) {
    while (first != last)
        this->insert(*first++);
}

template<typename K, typename Compare>
typename ft::Set<K, Compare>::key_compare
ft::Set<K, Compare>::key_comp(void) const {
    return (key_compare());
}

template<typename K, typename Compare>
typename ft::Set<K, Compare>::value_compare
ft::Set<K, Compare>::value_comp(void) const {
    return (value_compare());
}

}

template<typename K, typename Compare>
void
swap(ft::Set<K, Compare> &x, ft::Set<K, Compare> &y) {
	x.swap(y);
}

#endif
