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
	void						announce(void) const;
	static const std::string	&GetRandomName(void);
private:
	static const std::string	_names[100];
	std::string					name;
};
#endif