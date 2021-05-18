#ifndef MULTIMAP_HPP
# define MULTIMAP_HPP

# include "utility/MapBase.hpp"
# include <iostream>

namespace ft
{

template<typename K, typename V, typename Compare = ft::MapKeyCompare<K, V> >
class Multimap: public MapBase<K, ft::Pair<K, V>, Compare>
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
        Multimap();
        Multimap(iterator first, iterator last);
        Multimap(Multimap const &copy);
        virtual ~Multimap();
        Multimap& operator=(const Multimap& obj);

        mapped_type &operator[](key_type const &k);
        iterator insert(const_reference val);
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
ft::Multimap<K, V, Compare>::Multimap() : base() {}

template<typename K, typename V, typename Compare>
ft::Multimap<K, V, Compare>::Multimap(iterator first, iterator last) : base(first, last) {}

template<typename K, typename V, typename Compare>
ft::Multimap<K, V, Compare>::Multimap(const Multimap& copy) : base(copy) {}

template<typename K, typename V, typename Compare>
ft::Multimap<K, V, Compare>::~Multimap() {}

template<typename K, typename V, typename Compare>
ft::Multimap<K, V, Compare>&
ft::Multimap<K, V, Compare>::operator=(const Multimap& obj) {
    this->base::operator=(obj);
    return (*this);
}

/* ************************************************************************** */
/* ------------------------------ MAP FUNCTION ------------------------------ */
/* ************************************************************************** */

template<typename K, typename V, typename Compare>
typename ft::Multimap<K, V, Compare>::iterator
ft::Multimap<K, V, Compare>::insert(const_reference val)
{
    node_pointer inserted = this->m_tree.insert(val);
    ++this->m_size;
    return (iterator(inserted));
}

template<typename K, typename V, typename Compare>
typename ft::Multimap<K, V, Compare>::iterator
ft::Multimap<K, V, Compare>::insert(iterator position, const_reference val)
{
    ++this->m_size;
    return (iterator(this->m_tree.insert(position.as_node(), val)));
}

template<typename K, typename V, typename Compare>
template<typename InputIterator>
void
ft::Multimap<K, V, Compare>::insert(InputIterator first, InputIterator last) {
    while (first != last)
        this->insert(*first++);
}

template<typename K, typename V, typename Compare>
typename ft::Multimap<K, V, Compare>::key_compare
ft::Multimap<K, V, Compare>::key_comp(void) const {
    return (key_compare());
}

template<typename K, typename V, typename Compare>
typename ft::Multimap<K, V, Compare>::value_compare
ft::Multimap<K, V, Compare>::value_comp(void) const {
    return (value_compare());
}

}

template<typename K, typename T, typename Compare>
void
swap(ft::Multimap<K, T, Compare> &x, ft::Multimap<K, T, Compare> &y) {
	x.swap(y);
}

#endif
