#include "Character.hpp"

/* ************************************************************************** */
/* ---------------------------- STATIC VARIABLE ----------------------------- */
/* ************************************************************************** */

/* ************************************************************************** */
/* ------------------------------ CONSTRUCTOR ------------------------------- */
/* ************************************************************************** */

Character::Character() {}
Character::Character(const std::string& name)
: m_name(name), m_ap(40)
{
	this->m_weapon = nullptr;
}

Character::Character(const Character&) {}

/* ************************************************************************** */
/* ------------------------------- DESTRUCTOR ------------------------------- */
/* ************************************************************************** */

Character::~Character()
{
	this->m_name.clear();
	this->m_ap = 0;
	this->m_weapon = nullptr;
}

/* ************************************************************************** */
/* -------------------------------- OVERLOAD -------------------------------- */
/* ************************************************************************** */

Character& Character::operator=(const Character&) {
	return (*this);
}

std::ostream&
operator<<(std::ostream& out, const Character& character)
{
	if (character.get_m_weapon() == nullptr)
	{
		out << character.get_m_name();
		out << " has " << character.get_m_ap();
		out << " and is unarmed" << std::endl;
	}
	else
	{
		out << character.get_m_name();
		out << " has " << character.get_m_ap();
		out << " and wields a " << character.get_m_weapon()->get_m_name();
		out << std::endl;
	}
	return (out);
}

/* ************************************************************************** */
/* --------------------------------- GETTER --------------------------------- */
/* ************************************************************************** */

std::string Character::get_m_name() const { return (this->m_name); }
int Character::get_m_ap() const { return (this->m_ap); }
AWeapon *Character::get_m_weapon() const { return (this->m_weapon); }

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
Character::recoverAP(void) {
	if (this->m_ap + 10 >= 40)
		this->m_ap = 40;
	else
		this->m_ap += 10;
}

void
Character::equip(AWeapon* equipment) {
	this->m_weapon = equipment;
}

void
Character::attack(Enemy* enemy) {
	if (enemy == nullptr || this->m_weapon == nullptr)
		return ;
	if (this->m_ap < this->m_weapon->get_m_apcost())
		return ;
	enemy->takeDamage(this->m_weapon->get_m_damage());
	this->m_ap -= this->m_weapon->get_m_apcost();
	std::cout << this->m_name << " attacks " << enemy->get_m_type()
	<< " with a " << this->m_weapon->get_m_name() << std::endl;
	this->m_weapon->attack();
	if (enemy->get_m_hp() <= 0)
	{
		delete enemy;
		enemy = nullptr;
	}
}
