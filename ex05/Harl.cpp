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
	try {
		(this->*_levelMap.at(level))();
	} catch (const std::out_of_range &e) {
		std::cerr << "There is no such comment level\n";
	}
}

void	Harl::debug(void) const {
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pic"
		"kle-specialketchup burger. I really do!\n";
}

void	Harl::info(void) const {
	std::cout << "I cannot believe adding extra bacon costs more money. You did"
		"n't put enough bacon in my burger! If you did, I wouldn't be asking fo"
		"r more!\n";
}

void	Harl::warning(void) const {
	std::cerr << "I think I deserve to have some extra bacon for free. I've bee"
		"n coming for years whereas you started working here since last month."
		"\n";
}

void	Harl::error(void) const {
	std::cerr << "This is unacceptable! I want to speak to the manager now.\n";
}

const Harl::LevelPair	Harl::_levelPairs[4] = {
	std::make_pair("DEBUG", &Harl::debug),
	std::make_pair("INFO", &Harl::info),
	std::make_pair("WARNING", &Harl::warning),
	std::make_pair("ERROR", &Harl::error)
};

const Harl::LevelMap	Harl::_levelMap(_levelPairs,
	_levelPairs + sizeof(_levelPairs) / sizeof(_levelPairs[0]));