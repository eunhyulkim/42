#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

# include <iostream>
# include <cmath>

class Fixed;
std::ostream& operator<<(std::ostream& os, const Fixed& obj);
Fixed& min(Fixed& n, Fixed& m);
const Fixed& min(const Fixed& n, const Fixed& m);
Fixed& max(Fixed& n, Fixed& m);
const Fixed& max(const Fixed& n, const Fixed& m);

class Fixed
{
	private:
		const static int fractional_bits = 8;
		const static int crease = (1 << 7);
		int		_fixedValue;

	public:
		Fixed(const Fixed& copy);
		Fixed(const int number);
		Fixed(const float number);
		Fixed();
		~Fixed();

		Fixed& operator=(const Fixed& obj);
		bool operator>(const Fixed& obj) const;
		bool operator>=(const Fixed& obj) const;
		bool operator<(const Fixed& obj) const;
		bool operator<=(const Fixed& obj) const;
		bool operator==(const Fixed& obj) const;
		bool operator!=(const Fixed& obj) const;

		float operator+(const Fixed& obj) const;
		float operator-(const Fixed& obj) const;
		float operator*(const Fixed& obj) const;
		float operator/(const Fixed& obj) const;

		Fixed& operator++();
		const Fixed operator++(int);
		Fixed& operator--();
		const Fixed operator--(int);

		static int getFractionalBits(void);
		int getRawBits(void) const;
		void setRawBits(int const raw);
		int toInt(void) const;
		float toFloat(void) const;
};

#endif
