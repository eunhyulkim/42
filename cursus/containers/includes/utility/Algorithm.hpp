#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

# include <utility>
# include <functional>
# include "Pair.hpp"

namespace ft {

template <class iter1, class iter2>
bool
lexicographical_compare(iter1 first1, iter1 last1, iter2 first2, iter2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1;
		++first2;
	}
	return (first2 != last2);
}

template<typename T>
struct less: public std::binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y) const {
		return (x < y);
	}
};

template<typename K, typename V, typename Compare = ft::less<K> >
class MapKeyCompare: public std::binary_function<ft::Pair<K, V>, ft::Pair<K, V>, bool>
{
	public:
		typedef typename ft::Pair<K, V> value_type;
	private:
		Compare comp;
	public:
		MapKeyCompare(Compare const &comp = Compare()): comp(comp) {}
		MapKeyCompare(const MapKeyCompare& copy) { this->comp = copy.comp; }
		MapKeyCompare& operator=(const MapKeyCompare& obj) { this->comp = obj.comp; return (*this); }
		virtual ~MapKeyCompare() {}

		bool operator()(const value_type& a, const value_type& b) const {
			return (comp(a.first, b.first));
		}
		bool operator()(const value_type& a, const V& b) const {
			return (comp(a.first, b));
		}
		bool operator()(const V& a, const value_type& b) const {
			return (comp(a, b.first));
		}
};

template<class value_type>
const value_type&
min(value_type const &a, value_type const &b) {
	return (a < b ? a : b);
}

template<class value_type>
const value_type&
max(value_type const &a, value_type const &b) {
	return (a < b ? b : a);
}

template<class value_type>
bool
equal(value_type const &a, value_type const &b) {
	return (a == b);
}

template<class value_type>
bool
less_than(value_type const &a, value_type const &b) {
	return (a < b);
}

template<class value_type>
bool
more_than(value_type const &a, value_type const &b) {
	return (a > b);
}

template<class value_type>
void
swap(value_type &a, value_type &b)
{
	value_type tmp(a);
	a = b;
	b = tmp;
}

}

#endif
