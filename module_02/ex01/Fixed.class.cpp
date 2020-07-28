#include "Fixed.class.hpp"

std::ostream&
operator<<(std::ostream& os, const Fixed& obj) {
	int data = obj.getRawBits();
	if (data & (1 << 31))
	{
		os << (~(data - (1 << 8)) >> 8);
		std::cout << std::endl << "NEGATIVE NUMBER: " << data << std::endl;
	}
	else
	{
		os << (data >> 8);
		std::cout << std::endl << "POSITIVE NUMBER: " << data << std::endl;
	}
	return os;
}

Fixed::Fixed() {
	this->_fixedValue = 0;
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int number) {
	this->_fixedValue = number << fractional_bits;
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float number) {
	this->_fixedValue = roundf(number * (1 << fractional_bits));
	std::cout << "Float constructor called" << std::endl;
}

Fixed&
Fixed::operator=(const Fixed& obj){
	std::cout << "Assignation operator called" << std::endl;
	if (this != &obj)
		this->_fixedValue = obj.getRawBits();
	return (*this);
}

Fixed&
Fixed::operator<<(const Fixed& obj){
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
