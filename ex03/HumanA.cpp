#include <iostream>

#include "HumanA.hpp"

HumanA::HumanA(void) {

}

HumanA::HumanA(const HumanA &other) {
	_Copy(other);
}

HumanA::HumanA(std::string name, const Weapon &weapon)
	: name(name), weapon(weapon) {

}

HumanA	&HumanA::operator=(const HumanA &other) {
	_Copy(other);
	return *this;
}

HumanA::~HumanA(void) {

}

void	HumanA::attack(void) const {
	if (!(name.empty() || weapon.getType().empty()))
		std::cout << name << " attacks with their " << weapon.getType() << '\n';
}

void	HumanA::_Copy(const HumanA &other) {
	if (this != &other) {
		weapon = other.weapon;
		name = other.name;
	}
}
