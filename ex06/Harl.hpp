#ifndef EX05_HARL_HPP
# define EX05_HARL_HPP

# include <string>

class Harl {
public:
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
};
#endif
