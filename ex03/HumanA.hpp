#ifndef EX03_HUMANA_HPP
# define EX03_HUMANA_HPP

# include <string>

# include "Weapon.hpp"

class HumanA {
public:
	HumanA(void);
	HumanA(const HumanA &other);
	HumanA(std::string name, Weapon &weapon);
	HumanA	&operator=(const HumanA &other);
	~HumanA(void);

	void	attack(void) const;
	void	setWeapon(Weapon &weapon);
	void	DropWeapon(void);
private:
	static Weapon	_defaultWeapon;

	std::string		name;
	Weapon			&weapon;
	bool			_weaponBroken;
	std::string		_key;

	void	_Copy(const HumanA &other);
};
#endif
