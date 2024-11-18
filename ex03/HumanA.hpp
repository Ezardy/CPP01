#ifndef EX03_HUMANA_HPP
# define EX03_HUMANA_HPP

# include <string>

# include "Weapon.hpp"

class HumanA {
public:
	HumanA(void);
	HumanA(const HumanA &other);
	HumanA(std::string name, const Weapon &weapon);
	HumanA	&operator=(const HumanA &other);
	~HumanA(void);

	void	attack(void) const;
private:
	std::string	name;
	Weapon		weapon;

	void	_Copy(const HumanA &other);
};
#endif
