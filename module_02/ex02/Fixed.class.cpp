#include "Fixed.class.hpp"

/*
** canonical form
*/
Fixed::Fixed() {
	this->_fixedValue = 0;
}

Fixed::Fixed(const int number) {
	this->_fixedValue = number << fractional_bits;
}

Fixed::Fixed(const float number) {
	this->_fixedValue = roundf(number * (1 << fractional_bits));
}

Fixed::Fixed(const Fixed& copy) {
	*this = copy;
}

Fixed::~Fixed() {}

/*
** overload comparison operator (>, <, >=, <=, == and !=)
*/
Fixed&
Fixed::operator=(const Fixed& obj) {
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

float
Fixed::operator+(const Fixed& obj) const{
	Fixed ret(this->toFloat() + obj.toFloat());
	return (ret.toFloat());
}

float
Fixed::operator-(const Fixed& obj) const{
	Fixed ret(this->toFloat() - obj.toFloat());
	return (ret.toFloat());
}

float
Fixed::operator*(const Fixed& obj) const{
	Fixed ret(this->toFloat() * obj.toFloat());
	return (ret.toFloat());
}

float
Fixed::operator/(const Fixed& obj) const{
	Fixed ret(this->toFloat() / obj.toFloat());
	return (ret.toFloat());
}

Fixed&
Fixed::operator++() {
	this->_fixedValue += this->crease;
	return (*this);
}

const Fixed
Fixed::operator++(int) {
	const Fixed temp(*this);
	operator++();
	return (temp);
}

Fixed&
Fixed::operator--() {
	this->_fixedValue -= this->crease;
	return (*this);
}

const Fixed
Fixed::operator--(int) {
	const Fixed temp(*this);
	this->_fixedValue -= this->crease;
	return (temp);
}

/*
** function
*/
int
Fixed::getFractionalBits(void) {
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

Fixed& min(Fixed& n, Fixed& m) {return ((n <= m) ? n : m);}
const Fixed& min(const Fixed& n, const Fixed& m) {return ((n <= m) ? n : m);}
Fixed& max(Fixed& n, Fixed& m) {return ((n >= m) ? n : n);}
const Fixed& max(const Fixed& n, const Fixed& m) {return ((n >= m) ? n : n);}
