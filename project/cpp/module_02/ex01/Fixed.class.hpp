#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

# include <iostream>
# include <cmath>

class Fixed;
std::ostream& operator<<(std::ostream& os, const Fixed& obj);

class Fixed
{
	private:
		const static int fractional_bits = 8;
		int		_fixedValue;

	public:
		Fixed& operator=(const Fixed& obj);
		Fixed(const Fixed& copy);
		Fixed(const int number);
		Fixed(const float number);
		Fixed();
		~Fixed();

		static int getFractionalBits(void);
		int getRawBits(void) const;
		void setRawBits(int const raw);
		int toInt(void) const;
		float toFloat(void) const;
};

#endif
