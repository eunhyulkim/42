#include "Fixed.class.hpp"

Fixed::Fixed() {
	this->_fixedValue = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed&
Fixed::operator=(const Fixed& obj){
	std::cout << "Assignation operator called" << std::endl;
	if (this != &obj)
		this->_fixedValue = obj.getRawBits();
	return (*this);
}

Fixed::Fixed(const Fixed& copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::~Fixed(){
	std::cout << "Default destructor called" << std::endl;
}

int
Fixed::getFractionalBits(void)
{
	std::cout << "getFractionalBits function called" << std::endl;
	return (Fixed::fractional_bits);
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits function called" << std::endl;
	return (this->_fixedValue);
}

void Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits function called" << std::endl;
	this->_fixedValue = raw;
}
