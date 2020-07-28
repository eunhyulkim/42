#include "Fixed.class.hpp"

/*
** canonical form
*/
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

Fixed::Fixed(const Fixed& copy) {
	std::cout << "Copy constructor called" << std::endl;
	*this = copy;
}

Fixed::~Fixed() {
	std::cout << "Default destructor called" << std::endl;
}

/*
** overload comparison operator (>, <, >=, <=, == and !=)
*/
Fixed&
Fixed::operator=(const Fixed& obj) {
	std::cout << "Assignation operator called" << std::endl;
	if (this != &obj)
		this->_fixedValue = obj.getRawBits();
	return (*this);
}

bool
Fixed::operator>(const Fixed& obj) const{
	return (this->_fixedValue > obj._fixedValue);
}

bool
Fixed::operator>=(const Fixed& obj) const{
	return (this->_fixedValue >= obj._fixedValue);
}

bool
Fixed::operator<(const Fixed& obj) const{
	return (this->_fixedValue < obj._fixedValue);
}

bool
Fixed::operator<=(const Fixed& obj) const{
	return (this->_fixedValue <= obj._fixedValue);
}

bool
Fixed::operator==(const Fixed& obj) const{
	return (this->_fixedValue == obj._fixedValue);
}

bool
Fixed::operator!=(const Fixed& obj) const{
	return (this->_fixedValue != obj._fixedValue);
}

int
Fixed::getFractionalBits(void) {
	std::cout << "getFractionalBits function called" << std::endl;
	return (Fixed::fractional_bits);
}

int
Fixed::getRawBits(void) const {
	return (this->_fixedValue);
}

void
Fixed::setRawBits(int const raw) {
	this->_fixedValue = raw;
}

int
Fixed::toInt(void) const{
	return (this->_fixedValue >> fractional_bits);
}

float
Fixed::toFloat(void) const {
	return ((float)this->_fixedValue / (float)(1 << fractional_bits));
}


std::ostream&
operator<<(std::ostream& os, const Fixed& obj) {
	std::cout << obj.toFloat();
	return os;
}
