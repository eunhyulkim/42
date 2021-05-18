#ifndef SPAN_HPP
# define SPAN_HPP

# include <string>
# include <iostream>
# include <vector>
# include <limits>

class Span
{
	private:
		unsigned int m_size;
		std::vector<int> m_vector;
		Span();
	public:
		Span(unsigned int size);
		Span(const Span& copy);
		Span& operator=(const Span& obj);
		virtual ~Span();

		/* declare member function */
		void addNumber(int element);
		long shortestSpan(void);
		long longestSpan(void);

		template<typename T>
		void addNumber(T begin, T end);

		/* exception declare */
		class FullSpanException : public std::exception {
			public:
				FullSpanException() throw ();
				FullSpanException(const FullSpanException&) throw ();
				FullSpanException& operator= (const FullSpanException&) throw ();
				virtual ~FullSpanException() throw ();
				virtual const char* what() const throw ();
		};

		class NotEnoughNumberException : public std::exception {
			public:
				NotEnoughNumberException() throw ();
				NotEnoughNumberException(const NotEnoughNumberException&) throw ();
				NotEnoughNumberException& operator= (const NotEnoughNumberException&) throw ();
				virtual ~NotEnoughNumberException() throw ();
				virtual const char* what() const throw ();
		};
};

# include "Span.ipp"

#endif
