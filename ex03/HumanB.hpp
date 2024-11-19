#ifndef EX03_HUMANB_HPP
# define EX03_HUMANB_HPP

# include <string>

# include "Weapon.hpp"

class HumanB {
public:
	HumanB(void);
	HumanB(const HumanB &other);
	HumanB(std::string name);
	~HumanB(void);
	HumanB	&operator=(const HumanB &other);

	void	attack(void) const;
	void	setWeapon(Weapon &weapon);
	void	DropWeapon(void);
private:
	std::string	name;
	Weapon		*weapon;
	std::string	_key;

	void	_Copy(const HumanB &other);
};
#endif
