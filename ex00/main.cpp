#include <iostream>
#include <sstream>

#include "Zombie.hpp"

#define TEST_LOGIC_START(func_name) static bool func_name() {bool success = true; std::string _func_name = #func_name; std::cout << "[START " << _func_name << "]\n";
#define TEST_LOGIC_END if (!success) std::cout << _func_name << " failed\n"; return success;}

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

static bool	standard_stack_zombie_announce_test(void);
static bool	standard_stack_zombie_destructor_test(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		standard_stack_zombie_announce_test,
		standard_stack_zombie_destructor_test
	};
	size_t	tests_count = sizeof(tests)/sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1)
		success = tests[i]();
	if (success)
		std::cout << "OK\n";
	return success;
}

TEST_LOGIC_START(standard_stack_zombie_destructor_test)
	Zombie				zombies[5];
	std::streambuf		*old = std::cout.rdbuf();
	std::ostringstream	oss;
	std::string			message;
	std::string			name;
	size_t				pos_of_space;

	for (int i = 0; success && i < 5; i += 1) {
		std::cout.rdbuf(oss.rdbuf());
		zombies[i].~Zombie();
		std::cout.rdbuf(old);
		message = oss.str();
		oss.str("");
		name = message;
		pos_of_space = name.find_last_of(' ');
		name.erase(pos_of_space, name.length() - pos_of_space);
		std::cout << message;
		success = name + " destructed\n" == message;
	}
TEST_LOGIC_END

TEST_LOGIC_START(standard_stack_zombie_announce_test)
	Zombie				zombies[5];
	std::streambuf		*old = std::cout.rdbuf();
	std::string			announcement;
	std::string			name;
	size_t				pos_of_colon;
	std::ostringstream	oss;

	for (int i = 0; success && i < 5; i += 1) {
		std::cout.rdbuf(oss.rdbuf());
		zombies[i].announce();
		std::cout.rdbuf(old);
		announcement = oss.str();
		oss.str("");
		name = announcement;
		pos_of_colon = name.find(':');
		name.erase(pos_of_colon, name.length() - pos_of_colon);
		std::cout << announcement;
		success = name + ": BraiiiiiiinnnzzzZ...\n" == announcement;
	}
TEST_LOGIC_END
