#ifndef EX03_WEAPON_HPP
# define EX03_WEAPON_HPP

# include <string>

class HumanA;
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
	std::string	SetOwner(HumanB *owner);
	std::string	SetOwner(HumanA *owner);
	void				ClearOwner(const std::string &key);
	bool				Owned(void) const;
private:
	std::string	type;
	void		*_owner;
	bool		_ab;
	std::string	_key;

	void	_Copy(const Weapon &other);
	void	_GenerateSecureKey(void);
	std::string _SetOwner(void *owner, bool type);
};
#endif
