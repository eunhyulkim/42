#include "Character.hpp"

Character::Character(){}
Character::Character(std::string const & name) : name(name), ap(40), weapon(nullptr) {}
Character::~Character() {}

Character& Character::operator=(const Character&) { return (*this); }

Character::Character(const Character&) {}

std::string
Character::getName(void) const { return (this->name); }

AWeapon *
Character::getWeapon(void) const { return (this->weapon ); }

int
Character::getAP(void) const { return (this->ap); }

void
Character::equip(AWeapon* equipment) {
	this->weapon = equipment;
};

void
Character::attack(Enemy* enemy) {
	if (enemy == nullptr || this->weapon == nullptr)
		return ;
	if (this->ap >= weapon->getAPCost())
	{
		enemy->takeDamage(this->weapon->getDamage());
		this->ap -= this->weapon->getAPCost();
		std::cout << this->name << " attacks " << enemy->getType()
		<< " with a " << this->weapon->getName() << std::endl;
		this->weapon->attack();
		if (enemy->getHP() <= 0)
		{
			delete enemy;
			enemy = nullptr;
		}
	}
};

void
Character::recoverAP(void)
{
	if (this->ap + 10 >= 40)
		this->ap = 40;
	else
		this->ap += 10;
}

std::ostream&
operator<<(std::ostream& os, const Character& s) {
if (s.getWeapon() == nullptr)
	os << s.getName() << " has " << s.getAP() << " and is unarmed" << std::endl;
else
	os << s.getName() << " has " << s.getAP() << " and wields a " << s.getWeapon()->getName() << std::endl;
return os;
}
