#include <iostream>

#include "HumanB.hpp"

HumanB::HumanB(void) : weapon(NULL) {

}

HumanB::HumanB(const HumanB &other) {
	_Copy(other);
}

HumanB::HumanB(std::string name) : name(name), weapon(NULL) {

}

HumanB::~HumanB(void) {
	DropWeapon();
}

HumanB	&HumanB::operator=(const HumanB &other) {
	_Copy(other);
	return *this;
}

void	HumanB::attack(void) const {
	if (!(name.empty() || weapon == NULL || weapon->getType().empty()))
		std::cout
			<< name << " attacks with their " << weapon->getType() << '\n';
}

void	HumanB::setWeapon(Weapon &weapon) {
	if (!(name.empty() || weapon.Owned() || weapon.getType().empty())) {
		DropWeapon();
		this->weapon = &weapon;
		_key = weapon.SetOwner(this);
	}
}

void	HumanB::DropWeapon(void) {
	if (weapon != NULL) {
		weapon->ClearOwner(_key);
		weapon = NULL;
	}
}

void HumanB::_Copy(const HumanB &other) {
	if (this != &other)
		name = other.name;
}
