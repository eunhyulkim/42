#include "Asteroid.hpp"
#include <iostream>

Asteroid::Asteroid(std::string name) : name(name) {}
Asteroid::~Asteroid() {}
Asteroid::Asteroid(const Asteroid& copy) { *this = copy; }
Asteroid& Asteroid::operator=(const Asteroid& obj) { this->name = obj.getName(); return (*this); }

std::string Asteroid::getName() const { return (this->name); };
std::string Asteroid::beMined(DeepCoreMiner *) const { return ("Dragonite"); }
std::string Asteroid::beMined(StripMiner *) const { return ("Flavium"); }
