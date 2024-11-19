#include <cstdlib>

#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

Weapon::Weapon(void) : _owner(NULL) {

}

Weapon::Weapon(const Weapon &other) {
	_Copy(other);
}

Weapon::Weapon(const std::string &type) : type(type), _owner(NULL) {

}

Weapon::~Weapon(void) {
	if (_owner != NULL) {
		if (_ab)
			reinterpret_cast<HumanB *>(_owner)->DropWeapon();
		else
			reinterpret_cast<HumanA *>(_owner)->DropWeapon();
	}
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

std::string	Weapon::SetOwner(HumanB *owner) {
	return _SetOwner(owner, true);
}


std::string	Weapon::SetOwner(HumanA *owner) {
	return _SetOwner(owner, false);
}

void	Weapon::ClearOwner(const std::string &key) {
	if (key == _key)
		_owner = NULL;
}

bool	Weapon::Owned(void) const {
	return _owner != NULL;
}

void	Weapon::_GenerateSecureKey(void) {
	_key.reserve(10);
	for (int i = 0; i < 10; i += 1)
		_key[i] = rand() % 95 + 32;
}

std::string	Weapon::_SetOwner(void *owner, bool type) {
	std::string	key;
	if (_owner == NULL && owner != NULL) {
		_ab = type;
		_GenerateSecureKey();
		_owner = owner;
		key = _key;
	}
	return _key;
}

void	Weapon::_Copy(const Weapon &other) {
	if (this != &other) {
		type = other.type;
		_owner = NULL;
	}
}
