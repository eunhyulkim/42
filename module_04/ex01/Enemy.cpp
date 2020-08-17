#include "Enemy.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */


/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Enemy::Enemy() {}
Enemy::Enemy(int hp, const std::string& type)
: m_type(type), m_hp(hp) {}

Enemy::Enemy(const Enemy& copy)
: m_type(copy.get_m_type()), m_hp(copy.get_m_hp()) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Enemy::~Enemy()
{
	this->m_type.clear();
	this->m_hp = 0;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Enemy& Enemy::operator=(const Enemy& obj)
{
	if (this == &obj)
		return (*this);
	this->m_type = obj.get_m_type();
	this->m_hp = obj.get_m_hp();
	/* overload= code */
	return (*this);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Enemy::get_m_type() const { return (this->m_type); }
int Enemy::get_m_hp() const { return (this->m_hp); }

/* ************************************************************************** */
/* --------------------------------- SETTER --------------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------- EXCEPTION -------------------------------- */
/* ************************************************************************** */

/* exception code */

/* ************************************************************************** */
/* ---------------------------- MEMBER FUNCTION ----------------------------- */
/* ************************************************************************** */

void
Enemy::takeDamage(int damage)
{
	if (damage < 0)
		return ;
	if (damage > this->m_hp)
		damage = this->m_hp;
	this->m_hp -= damage;
}
