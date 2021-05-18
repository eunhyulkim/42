#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <string>
# include <iostream>
# include <exception>
# include <cctype>

template<typename T>
class Array
{
	private:
		size_t length;
		T *elements;
	public:
		Array();
		Array(size_t length);
		Array(const Array& copy);
		Array& operator=(const Array& obj);
		virtual ~Array();

		/* declare member function */
		T& operator[](size_t index);
		size_t size(void) const;

		/* getter function */
		size_t get_length() const;

		/* exception declare */
		class OutOfBoundsException : public std::exception {
			public:
				OutOfBoundsException() throw ();
				OutOfBoundsException(const OutOfBoundsException&) throw ();
				OutOfBoundsException& operator= (const OutOfBoundsException&) throw ();
				virtual ~OutOfBoundsException() throw ();
				virtual const char* what() const throw ();
		};
};

# include "Array.ipp"

#endif
