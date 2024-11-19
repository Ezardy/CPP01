#include <iostream>

#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(void) : weapon(_defaultWeapon) {

}

HumanA::HumanA(const HumanA &other) : weapon(_defaultWeapon) {
	_Copy(other);
}

HumanA::HumanA(std::string name, Weapon &weapon)
	: name(name), weapon(_defaultWeapon) {
	setWeapon(weapon);
}

HumanA	&HumanA::operator=(const HumanA &other) {
	_Copy(other);
	return *this;
}

HumanA::~HumanA(void) {
	if (!_weaponBroken)
		weapon.ClearOwner(_key);
}

void	HumanA::attack(void) const {
	if (!(name.empty() || _weaponBroken || weapon.getType().empty()))
		std::cout << name << " attacks with their " << weapon.getType() << '\n';
}

void	HumanA::setWeapon(Weapon &weapon) {
	if (!(weapon.Owned() || weapon.getType().empty())) {
		DropWeapon();
		_weaponBroken = false;
		this->weapon = weapon;
		_key = weapon.SetOwner(this);
	}
}

void	HumanA::DropWeapon(void) {
	if (!_weaponBroken) {
		weapon.ClearOwner(_key);
		_weaponBroken = true;
	}
}

void	HumanA::_Copy(const HumanA &other) {
	if (this != &other)
		name = other.name;
}

Weapon	HumanA::_defaultWeapon;
