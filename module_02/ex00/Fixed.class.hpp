#ifndef FIXED_CLASS_HPP
# define FIXED_CLASS_HPP

# include <iostream>

class Fixed
{
	private:
		const static int fractional_bits = 8;
		int		_fixedValue;

	public:
		Fixed& operator=(const Fixed& obj);
		Fixed(const Fixed& copy);
		Fixed();
		~Fixed();

		static int getFractionalBits(void);
		int getRawBits(void) const;
		void setRawBits(int const raw);
};

#endif