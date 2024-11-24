#include <iostream>
#include <map>

#include "LogLevel.hpp"
#include "Harl.hpp"

void				harl_program(const Harl &harl, const std::map<LogLevel,
						std::string> levelStrings);
void				print_message(int error);

int	main(int argc, char **argv) {
	int											error;
	try {
		const Harl								harl;
		const std::pair<std::string, LogLevel>	stringToLevelPairs[4] = {
			std::make_pair("DEBUG", DEBUG),
			std::make_pair("INFO", INFO),
			std::make_pair("WARNING", WARNING),
			std::make_pair("ERROR", ERROR)
		};
		const std::map<std::string, LogLevel>	stringToLevel(stringToLevelPairs,
			stringToLevelPairs +  sizeof(stringToLevelPairs) / sizeof(stringToLevelPairs[0]));
		const std::pair<LogLevel, std::string>	levelToStringPairs[4] = {
			std::make_pair(stringToLevelPairs[0].second, stringToLevelPairs[0].first),
			std::make_pair(stringToLevelPairs[1].second, stringToLevelPairs[1].first),
			std::make_pair(stringToLevelPairs[2].second, stringToLevelPairs[2].first),
			std::make_pair(stringToLevelPairs[3].second, stringToLevelPairs[3].first)
		};
		std::map<LogLevel, std::string>			levelToString(
			levelToStringPairs, levelToStringPairs + sizeof(levelToStringPairs)
			/ sizeof(levelToStringPairs[0])
		);

		if (argc == 2) {
			switch (stringToLevel.at(argv[1])) {
				case DEBUG:
					break;
				case INFO:
					levelToString[DEBUG] = "";
					break;
				case WARNING:
					levelToString[DEBUG] = "";
					levelToString[INFO] = "";
					break;
				case ERROR:
					levelToString[DEBUG] = "";
					levelToString[INFO] = "";
					levelToString[WARNING] = "";
					break;
				default:
					error = 2;
					break;
			}
		} else
			error = 1;
		if (!error)
			harl_program(harl, )
	} catch (const std::bad_alloc &e) {
		error = 3;
	} catch (const std::out_of_range &e) {
				error = 2;
	}
	print_message(error);
	return error;
}

void	harl_program(const Harl &harl, const std::map<LogLevel,
			std::string> levelStrings) {
	harl.complain()
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
