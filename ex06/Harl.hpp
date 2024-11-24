#ifndef EX06_HARL_HPP
# define EX06_HARL_HPP

# include <string>
# include <map>

class Harl {
public:
	typedef std::pair<std::string, void (Harl::*)(void) const> LevelPair;
	typedef std::map<std::string, void (Harl::*)(void) const> LevelMap;

	Harl(void);
	Harl(const Harl &other);
	~Harl(void);
	Harl	&operator=(const Harl &other);

	void	complain(std::string level) const;
private:
	void	debug(void) const;
	void	info(void) const;
	void	warning(void) const;
	void	error(void) const;

	static const LevelPair	_levelPairs[4];
	static const LevelMap	_levelMap;
};
#endif