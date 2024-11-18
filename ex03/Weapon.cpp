#include "Weapon.hpp"
#include "HumanB.hpp"

Weapon::Weapon(void) : _owner(NULL) {

}

Weapon::Weapon(const Weapon &other) {
	_Copy(other);
}

Weapon::Weapon(const std::string &type) : type(type), _owner(NULL) {

}

Weapon::~Weapon(void) {
	if (_owner != NULL)
		_owner->DropWeapon();
}

Weapon	&Weapon::operator=(const Weapon &other) {
	_Copy(other);
	return *this;
}

const std::string	&Weapon::getType(void) const {
	return type;
}

void	Weapon::setType(std::string type) {
	this->type = type;
}

void	Weapon::SetOwner(HumanB *owner) {
	_owner = owner;
}

bool	Weapon::Owned(void) const {
	return _owner != NULL;
}

void	Weapon::_Copy(const Weapon &other) {
	if (this != &other)
		type = other.type;
}
