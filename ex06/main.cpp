#include <iostream>
#include <map>

#include "LogLevel.hpp"
#include "Harl.hpp"

void	harl_program(const Harl &harl, const std::map<LogLevel,
			std::string> levelStrings);
//void	complain(const Harl &harl, std::string)
void	print_message(int error);

int	main(int argc, char **argv) {
	int	error;
	try {
		switch ()
	} catch (const std::bad_alloc &e) {
		error = 3;
	}
	print_message(error);
	return error;
}

void	print_message(int error) {
	switch (error) {
		case 1:
			std::cerr << "Wrong arguments count\n";
			break;
		case 3:
			std::cerr << "The program memory allocation failed\n";
			break;
		default:
			std::cout <<
				"[ Probably complaining about insignificant problems ]\n";
			break;
	}
}
