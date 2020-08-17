#ifndef CONVERTER_HPP
# define CONVERTER_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <limits>
# include <cmath>

# define DEFAULT			0
# define NON_DISPLAYABLE	1
# define NANV				2
# define INF				3
# define NINF				4
# define IMPOSSIBLE			5
# define SCIENCE			6
# define INTEGER			7

# define CHAR_STAT			0
# define INT_STAT			1
# define FLOAT_STAT			2
# define DOUBLE_STAT		3

class Converter
{
	private:
		std::string m_type;
		std::string m_data;
		int m_status[4];
		int m_int;
		char m_char;
		float m_float;
		double m_double;
	protected:
		Converter(const Converter&);
		Converter& operator=(const Converter&);
	public:
		Converter();
		virtual ~Converter();

		/* getter function */
		std::string get_m_type() const;
		int get_m_status(int nth) const;
		char get_m_char() const;
		int get_m_int() const;
		float get_m_float() const;
		double get_m_double() const;

		/* setter function */
		void set_m_status(int nth, int v);
		void set_m_char(char c);
		void set_m_int(int n);
		void set_m_float(float f);
		void set_m_double(double d);

		/* declare member function */
		void parse(const std::string& data);
		void charToOthers(void);
		void intToOthers(void);
		void floatToOthers(void);
		void doubleToOthers(void);
		void convert(void);
		void print(void);
};

#endif
