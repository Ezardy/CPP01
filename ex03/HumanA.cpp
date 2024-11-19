#include <iostream>

#include "HumanA.hpp"
#include "Weapon.hpp"

HumanA::HumanA(void) : weapon(_defaultWeapon), _weaponBroken(true) {

}

HumanA::HumanA(const HumanA &other) : weapon(_defaultWeapon), _weaponBroken(true) {
	_Copy(other);
}

HumanA::HumanA(std::string name, Weapon &weapon)
	: name(name), weapon(weapon), _weaponBroken(false) {
	if (weapon.Owned())
		_weaponBroken = true;
	else
		_key = weapon.SetOwner(this);
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
