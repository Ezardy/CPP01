#include <iostream>

#include "LogLevel.hpp"
#include "Harl.hpp"

void	harl_program(const std::string levelStrings[4]);
void	harl_filter(LogLevel level, std::string levelStrings[4]);
void	print_error(int error);

int	main(int argc, char **argv) {
	std::string	levelStrings[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	int			error;
	int			i;

	try {
		if (argc == 2) {
			for (i = 0; levelStrings[i] != argv[1] && i < 4; i += 1);
			harl_filter(static_cast<LogLevel>(i), levelStrings);
			harl_program(levelStrings);
		} else
			error = 1;
	} catch (const std::bad_alloc &e) {
		error = 3;
	}
	print_error(error);
	return error;
}

void	harl_filter(LogLevel level, std::string levelStrings[4]) {
	switch (level) {
		case DEBUG:
			break;
		case INFO:
			levelStrings[DEBUG] = "";
			break;
		case WARNING:
			levelStrings[DEBUG] = "";
			levelStrings[INFO] = "";
			break;
		case ERROR:
			levelStrings[DEBUG] = "";
			levelStrings[INFO] = "";
			levelStrings[WARNING] = "";
			break;
		default:
			levelStrings[DEBUG] = "";
			levelStrings[INFO] = "";
			levelStrings[WARNING] = "";
			levelStrings[ERROR] = "";
			std::cout <<
				"[ Probably complaining about insignificant problems ]\n";
			break;
	}
}

void	harl_program(const std::string levelStrings[4]) {
	const Harl	harl;

	harl.complain(levelStrings[DEBUG]);
	harl.complain(levelStrings[INFO]);
	harl.complain(levelStrings[WARNING]);
	harl.complain(levelStrings[ERROR]);
}

void	print_error(int error) {
	switch (error) {
		case 1:
			std::cerr << "Wrong arguments count\n";
			break;
		case 3:
			std::cerr << "The program memory allocation failed\n";
			break;
		default:
			break;
	}
}
