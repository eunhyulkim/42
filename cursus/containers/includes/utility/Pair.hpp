#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {

template <typename F, typename S>
class Pair {
    public:
        typedef F                   first_type;
        typedef const first_type&   const_first_reference;
        typedef S                   second_type;
        typedef const second_type&  const_second_reference;

		first_type      first;
        second_type     second;

        /* canonical form */
		Pair();
        Pair(const_first_reference first);
        Pair(const_first_reference first, const_second_reference second);
        Pair(const Pair& copy);
        virtual ~Pair();

        /* overload operator */
        Pair& operator=(const Pair& obj);

};

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename F, typename S>
ft::Pair<F, S>::Pair()
: first(), second() {}

template <typename F, typename S>
ft::Pair<F, S>::Pair(const_first_reference first)
: first(first), second() {}

template <typename F, typename S>
ft::Pair<F, S>::Pair(const_first_reference first, const_second_reference second)
: first(first), second(second) {}

template <typename F, typename S>
ft::Pair<F, S>::Pair(const Pair<F, S>& copy)
: first(copy.first), second(copy.second) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

template <typename F, typename S>
ft::Pair<F, S>::~Pair() {}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

template <typename F, typename S>
Pair<F, S>&
ft::Pair<F, S>::operator=(Pair<F, S> const &obj) {

	if (this == &obj)
		return (*this);
    this->first = obj.first;
    this->second = obj.second;
    return (*this);
}

template <typename T1, typename T2>
ft::Pair<T1, T2> make_pair(T1 x, T2 y) {
    return ( ft::Pair<T1, T2>(x, y) );
};

}

#endif
