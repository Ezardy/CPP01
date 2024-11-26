#include <iostream>

#include "Harl.hpp"

Harl::Harl(void) {

}

Harl::Harl(const Harl &other) {
	(void)other;
}

Harl::~Harl(void) {

}

Harl	&Harl::operator=(const Harl &other) {
	(void)other;
	return *this;
}

void	Harl::complain(std::string level) const {
	static const std::string	levels[4] = {
		"DEBUG",
		"INFO",
		"WARNING",
		"ERROR"
	};
	static void	(Harl::*const funcs[4])(void) const = {
		&Harl::debug,
		&Harl::info,
		&Harl::warning,
		&Harl::error
	};

	int							i;

	for (i = 0; i < 4 && levels[i] != level; i += 1);
	if (i < 4)
		(this->*funcs[i])();
}

void	Harl::debug(void) const {
	std::cout << "[ DEBUG ]\n";
	std::cout << "I love having extra bacon for my 7XL-double-cheese"
		"-triple-pickle-specialketchup burger. I really do!\n";
	std::cout << '\n';
}

void	Harl::info(void) const {
	std::cout << "[ INFO ]\n";
	std::cout << "I cannot believe adding extra bacon costs more mone"
		"y. You didn't put enough bacon in my burger! If you did, I wouldn't be"
		" asking for more!\n";
	std::cout << '\n';
}

void	Harl::warning(void) const {
	std::cout << "[ WARNING ]\n";
	std::cerr << "I think I deserve to have some extra bacon for f"
		"ree.\nI've been coming for years whereas you started working here since"
		" last month.\n";
	std::cout << '\n';
}

void	Harl::error(void) const {
	std::cout << "[ ERROR ]\n";
	std::cerr << "This is unacceptable! I want to speak to the manag"
		"er now.\n";
	std::cout << '\n';
}
