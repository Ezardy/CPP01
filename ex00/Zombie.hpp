#ifndef EX00_ZOMBIE_HPP
# define EX00_ZOMBIE_HPP

# include <string>

class Zombie {
public:
	Zombie(void);
	Zombie(const std::string &name);
	~Zombie(void);
	Zombie(const Zombie &other);
	Zombie						&operator=(const Zombie &other);
	static const std::string	&GetRandomName(void);
	void						announce(void) const;
private:
	static const std::string	_names[100];
	std::string					name;
};
#endif