#ifndef MAP_HPP
# define MAP_HPP

# include "utility/MapBase.hpp"
# include <iostream>

namespace ft
{

template<typename K, typename V, typename Compare = ft::MapKeyCompare<K, V> >
class Map: public MapBase<K, ft::Pair<K, V>, Compare>
{
    public:
        typedef MapBase<K, ft::Pair<K, V>, Compare>     base;
        using typename                                  base::difference_type;
        using typename                                  base::size_type;
        using typename                                  base::key_type;
        using typename                                  base::value_type;
        typedef V                                       mapped_type;
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
        Map();
        Map(iterator first, iterator last);
        Map(Map const &copy);
        virtual ~Map();
        Map& operator=(const Map& obj);

        mapped_type &operator[](key_type const &k);
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

template<typename K, typename V, typename Compare>
ft::Map<K, V, Compare>::Map() : base() {}

template<typename K, typename V, typename Compare>
ft::Map<K, V, Compare>::Map(iterator first, iterator last) : base(first, last) {}

template<typename K, typename V, typename Compare>
ft::Map<K, V, Compare>::Map(const Map& copy) : base(copy) {}

template<typename K, typename V, typename Compare>
ft::Map<K, V, Compare>::~Map() {}

template<typename K, typename V, typename Compare>
ft::Map<K, V, Compare>&
ft::Map<K, V, Compare>::operator=(const Map& obj) {
    this->base::operator=(obj);
    return (*this);
}

/* ************************************************************************** */
/* ------------------------------ MAP FUNCTION ------------------------------ */
/* ************************************************************************** */

template<typename K, typename V, typename Compare>
typename ft::Map<K, V, Compare>::mapped_type&
ft::Map<K, V, Compare>::operator[](const key_type& key)
{
    node_pointer found = this->m_tree.find(key);
    if (found)
        return (found->value.second);
    ++this->m_size;
    return (this->m_tree.insert(ft::make_pair(key, mapped_type()))->value.second);
}

template<typename K, typename V, typename Compare>
ft::Pair<typename ft::Map<K, V, Compare>::iterator, bool>
ft::Map<K, V, Compare>::insert(const_reference val)
{
    node_pointer node = this->m_tree.find(val);
    if (node)
        return (ft::make_pair(iterator(node), false));
    node_pointer inserted = this->m_tree.insert(val);
    ++this->m_size;
    return (ft::make_pair(iterator(inserted), true));
}

template<typename K, typename V, typename Compare>
typename ft::Map<K, V, Compare>::iterator
ft::Map<K, V, Compare>::insert(iterator position, const_reference val)
{
    node_pointer node = this->m_tree.find(position.as_node(), val);
    if (node)
        return (iterator(node));
    ++this->m_size;
    return (iterator(this->m_tree.insert(position.as_node(), val)));
}

template<typename K, typename V, typename Compare>
template<typename InputIterator>
void
ft::Map<K, V, Compare>::insert(InputIterator first, InputIterator last) {
    while (first != last)
        this->insert(*first++);
}

template<typename K, typename V, typename Compare>
typename ft::Map<K, V, Compare>::key_compare
ft::Map<K, V, Compare>::key_comp(void) const {
    return (key_compare());
}

template<typename K, typename V, typename Compare>
typename ft::Map<K, V, Compare>::value_compare
ft::Map<K, V, Compare>::value_comp(void) const {
    return (value_compare());
}

}

template<typename K, typename T, typename Compare>
void
swap(ft::Map<K, T, Compare> &x, ft::Map<K, T, Compare> &y) {
	x.swap(y);
}

#endif
