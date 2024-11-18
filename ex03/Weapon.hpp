#ifndef EX03_WEAPON_HPP
# define EX03_WEAPON_HPP

# include <string>

class HumanB;

class Weapon {
public:
	Weapon(void);
	Weapon(const Weapon &other);
	Weapon(const std::string &type);
	~Weapon(void);
	Weapon	&operator=(const Weapon &other);

	const std::string	&getType(void) const;
	void				setType(std::string type);
	void				SetOwner(HumanB *owner);
	bool				Owned(void) const;
private:
	std::string	type;
	HumanB		*_owner;

	void	_Copy(const Weapon &other);
};
#endif
