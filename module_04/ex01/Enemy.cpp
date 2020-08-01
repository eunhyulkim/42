#include "Enemy.hpp"

Enemy::Enemy(){}
Enemy::Enemy(int hp, std::string const & type) : hp(hp), type(type) {}
Enemy::~Enemy() {}

Enemy&
Enemy::operator=(const Enemy& obj) {
	if (this != &obj)
	{
		this->type = obj.type;
		this->hp = obj.hp;
	}
	return (*this);
}

Enemy::Enemy(const Enemy& copy) {
	*this = copy;
}

int
Enemy::getHP(void) const { return (this->hp); }
std::string Enemy::getType(void) const { return (this->type); }

void Enemy::takeDamage(int damage) {
	if (damage > hp)
		damage = hp;
	hp -= damage;
}
