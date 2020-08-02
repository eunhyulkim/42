#include "Comet.hpp"

Comet::Comet(std::string name) : name(name) {}
Comet::~Comet() {}
Comet::Comet(const Comet& copy) { *this = copy; }
Comet& Comet::operator=(const Comet& obj) { this->name = obj.getName(); return (*this); }

std::string Comet::getName() const { return (this->name); };
std::string Comet::beMined(DeepCoreMiner *) const { return ("Meium"); }
std::string Comet::beMined(StripMiner *) const { return ("Tartarite"); }
