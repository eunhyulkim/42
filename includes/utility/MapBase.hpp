#ifndef MAPBASE_HPP
# define MAPBASE_HPP

# include <utility>
# include "Algorithm.hpp"
# include "Iterator.hpp"
# include "Tree.hpp"
# include "Pair.hpp"

namespace ft
{
template<typename K, typename V, class Compare = ft::less<K> >
class MapBase
{
public:
	typedef std::allocator<V>								allocator_type;
	typedef typename allocator_type::size_type				size_type;
	typedef K 												key_type;
	typedef V 												value_type;
	typedef value_type*										pointer;
	typedef const value_type* 								const_pointer;
	typedef value_type& 									reference;
	typedef const value_type&								const_reference;
	typedef Tree<value_type, Compare> 						tree_type;
	typedef typename tree_type::Node 						node_type;
	typedef node_type*										node_pointer;
	typedef Compare											key_compare;
	typedef Compare											value_compare;
	typedef TreeIterator<value_type, node_type> 			iterator;
	typedef TreeIterator<const value_type, const node_type> const_iterator;
	typedef ReverseIterator<iterator> 						reverse_iterator;
	typedef ReverseIterator<const_iterator> 				const_reverse_iterator;
	typedef std::ptrdiff_t 									difference_type;
protected:
	tree_type 	m_tree;
	size_type 	m_size;
public:
	MapBase();
	MapBase(iterator first, iterator last);
	MapBase(const MapBase& copy);
	virtual ~MapBase();
	MapBase& operator=(const MapBase& obj);

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
	bool empty() const;

	/* element access */
	iterator find(const key_type& key);
	const_iterator find(key_type const &key) const;
	Compare compare() const;
	size_type count(const key_type& key) const;
	iterator lower_bound(const key_type& key);
	const_iterator lower_bound(const key_type& key) const;
	iterator upper_bound(const key_type& key);
	const_iterator upper_bound(const key_type& key) const;
	ft::Pair<iterator, iterator> equal_range(key_type const &key);
	ft::Pair<const_iterator, const_iterator> equal_range(key_type const &key) const;

	/* modifier function */
	void erase(iterator position);
	size_type erase(key_type const &key);
	void erase(iterator first, iterator last);
	void clear();
	void swap(MapBase &obj);
};

/* ************************************************************************** */
/* -------------------------- MAPBASE CANONICAL FORM ------------------------ */
/* ************************************************************************** */

template <typename K, typename V, typename Compare>
ft::MapBase<K, V, Compare>::MapBase()
: m_tree(), m_size() {}

template <typename K, typename V, typename Compare>
ft::MapBase<K, V, Compare>::MapBase(iterator first, iterator last)
: m_tree(), m_size(0) {
	while (first != last)
	{
		this->m_tree.insert(*first);
		++first;
	}
}

template <typename K, typename V, typename Compare>
ft::MapBase<K, V, Compare>::MapBase(const MapBase& copy)
: m_tree(copy.m_tree), m_size(copy.m_size) {}

template <typename K, typename V, typename Compare>
ft::MapBase<K, V, Compare>&
ft::MapBase<K, V, Compare>::operator=(const ft::MapBase<K, V, Compare>& obj)
{
	if (this == &obj)
		return (*this);
	this->clear();
	this->m_tree = obj.m_tree;
	this->m_size = obj.m_size;
	return (*this);
}

template <typename K, typename V, typename Compare>
ft::MapBase<K, V, Compare>::~MapBase() {}

/* ************************************************************************** */
/* ---------------------------- MAPBASE ITERATORS --------------------------- */
/* ************************************************************************** */

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::iterator
ft::MapBase<K, V, Compare>::begin(void) {
	return (iterator(this->m_tree.begin()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_iterator
ft::MapBase<K, V, Compare>::begin(void) const {
	return (const_iterator(this->m_tree.begin()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::reverse_iterator
ft::MapBase<K, V, Compare>::rbegin(void) {
	return (reverse_iterator(this->end()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_reverse_iterator 
ft::MapBase<K, V, Compare>::rbegin(void) const {
	return (const_reverse_iterator(this->end()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::iterator
ft::MapBase<K, V, Compare>::end(void) {
	return (iterator(this->m_tree.end()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_iterator
ft::MapBase<K, V, Compare>::end(void) const {
	return (const_iterator(this->m_tree.end()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::reverse_iterator
ft::MapBase<K, V, Compare>::rend(void) {
	return (reverse_iterator(this->begin()));
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_reverse_iterator
ft::MapBase<K, V, Compare>::rend(void) const {
	return (const_reverse_iterator(this->begin()));
}

/* ************************************************************************** */
/* ------------------------------- CAPACITY --------------------------------- */
/* ************************************************************************** */

template <typename K, typename V, typename Compare>
bool
ft::MapBase<K, V, Compare>::empty(void) const {
	return (this->m_size == 0);
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::size_type
ft::MapBase<K, V, Compare>::size(void) const {
	return (this->m_size);
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::size_type
ft::MapBase<K, V, Compare>::max_size(void) const {
	return (ft::min((size_type) std::numeric_limits<difference_type>::max(),
					std::numeric_limits<size_type>::max() / (sizeof(node_type))));
}

/* ************************************************************************** */
/* ----------------------------- ELEMENT ACCESS ----------------------------- */
/* ************************************************************************** */

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::iterator
ft::MapBase<K, V, Compare>::find(const key_type& key)
{
	node_pointer node = this->m_tree.find(key);
	if (node)
		return (iterator(node));
	return (this->end());
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_iterator
ft::MapBase<K, V, Compare>::find(const key_type& key) const 
{
	node_pointer node = this->m_tree.find(key);
	if (node)
		return (const_iterator(node));
	return (this->end());
}

template <typename K, typename V, typename Compare>
Compare
ft::MapBase<K, V, Compare>::compare(void) const {
	return (this->m_tree.compare());
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::size_type
ft::MapBase<K, V, Compare>::count(const key_type& key) const 
{
	const_iterator it = this->begin();
	const_iterator ite = this->end();
	size_type total = 0;

	while (it != ite)
	{
		if (!this->compare()(*it, key) && !this->compare()(key, *it))
			++total;
		++it;
	}
	return (total);
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::iterator
ft::MapBase<K, V, Compare>::lower_bound(const key_type& key) 
{
	iterator it = this->begin();
	iterator ite = this->end();

	node_pointer node = this->m_tree.find(key);
	if (!node)
		return (ite);

	while (it != ite)
	{
		if (!this->compare()(*it, key))
			return (iterator(it));
		++it;
	}
	return (this->end());
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_iterator
ft::MapBase<K, V, Compare>::lower_bound(const key_type& key) const 
{
	const_iterator it = this->begin();
	const_iterator ite = this->end();

	node_pointer node = this->m_tree.find(key);
	if (!node)
		return (ite);

	while (it != ite)
	{
		if (!this->compare()(*it, key))
			return (const_iterator(it));
		++it;
	}
	return (this->end());
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::iterator
ft::MapBase<K, V, Compare>::upper_bound(const key_type& key) 
{
	iterator it = this->begin();
	iterator ite = this->end();

	node_pointer node = this->m_tree.find(key);
	if (!node)
		return (ite);

	while (it != ite)
	{
		if (this->compare()(key, *it))
			return (iterator(it));
		++it;
	}
	return (this->end());
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::const_iterator
ft::MapBase<K, V, Compare>::upper_bound(const key_type& key) const 
{
	const_iterator it = this->begin();
	const_iterator ite = this->end();

	node_pointer node = this->m_tree.find(key);
	if (!node)
		return (ite);

	while (it != ite)
	{
		if (this->compare()(key, *it))
			return (const_iterator(it));
		++it;
	}
	return (this->end());
}

template <typename K, typename V, typename Compare>
typename ft::Pair<typename ft::MapBase<K, V, Compare>::iterator, typename ft::MapBase<K, V, Compare>::iterator>
ft::MapBase<K, V, Compare>::equal_range(key_type const &key) {
	return (ft::Pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
}

template <typename K, typename V, typename Compare>
typename ft::Pair<typename ft::MapBase<K, V, Compare>::const_iterator, typename ft::MapBase<K, V, Compare>::const_iterator>
ft::MapBase<K, V, Compare>::equal_range(key_type const &key) const {
	return (ft::Pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key)));
}

// /* ************************************************************************** */
// /* ------------------------------- MODIFIERS -------------------------------- */
// /* ************************************************************************** */

template <typename K, typename V, typename Compare>
void
ft::MapBase<K, V, Compare>::erase(iterator position) {
	this->m_tree.erase(position.as_node());
	--this->m_size;
}

template <typename K, typename V, typename Compare>
typename ft::MapBase<K, V, Compare>::size_type
ft::MapBase<K, V, Compare>::erase(key_type const &key) {
	size_type count = this->m_tree.erase(key);
	this->m_size -= count;
	return (count);
}

template <typename K, typename V, typename Compare>
void
ft::MapBase<K, V, Compare>::erase(iterator first, iterator last) {
	if (first == this->begin() && last == this->end())
		this->clear();
	else {
		while (first != last) {
			first = this->m_tree.erase(first.as_node());
			--this->m_size;
		}
	}
}

template <typename K, typename V, typename Compare>
void
ft::MapBase<K, V, Compare>::clear(void) {
	if (this->m_size > 0)
		this->m_tree.make_empty();
	this->m_size = 0;
}

template <typename K, typename V, typename Compare>
void
ft::MapBase<K, V, Compare>::swap(MapBase &other) {
	this->m_tree.swap(other.m_tree);
	ft::swap(this->m_size, other.m_size);
}
}
#endif
