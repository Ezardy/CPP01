#include <iostream>
#include <sstream>

#include "Zombie.hpp"

#define TEST_LOGIC_START(func_name) static bool func_name() {bool success = true; std::string _func_name = #func_name; std::cout << "[START " << _func_name << "]\n";
#define TEST_LOGIC_END if (!success) std::cout << _func_name << " failed\n"; return success;}

Zombie	*newZombie(std::string name);
void	randomChump(std::string name);

static bool	standard_stack_zombie_announce_test(void);
static bool	standard_stack_zombie_destructor_test(void);
static bool	standard_heap_zombie_announce_test(void);
static bool	standard_heap_zombie_destruction_test(void);
static bool	random_chump_test(void);
static bool	new_zombie_test(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		standard_stack_zombie_announce_test,
		standard_stack_zombie_destructor_test,
		standard_heap_zombie_announce_test,
		standard_heap_zombie_destruction_test,
		random_chump_test,
		new_zombie_test
	};
	size_t	tests_count = sizeof(tests)/sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

TEST_LOGIC_START(new_zombie_test)
	std::string			names[5] = {
		Zombie::GetRandomName(), Zombie::GetRandomName(),
		Zombie::GetRandomName(), Zombie::GetRandomName(),
		Zombie::GetRandomName()
	};
	Zombie				*zombies[5] = {
		newZombie(names[0]), newZombie(names[1]), newZombie(names[2]),
		newZombie(names[3]), newZombie(names[4])
	};
	std::streambuf		*old = std::cout.rdbuf();
	std::ostringstream	oss;
	std::string			message;

	for (int i = 4; success && i >= 0; i -= 1) {
		std::cout.rdbuf(oss.rdbuf());
		zombies[i]->announce();
		delete zombies[i];
		std::cout.rdbuf(old);
		message = oss.str();
		oss.str("");
		std::cout << message;
		success = names[i] + ": BraiiiiiiinnnzzzZ...\n"
			+ names[i] + " destructed\n" == message;
	}
TEST_LOGIC_END

TEST_LOGIC_START(random_chump_test)
	std::streambuf		*old = std::cout.rdbuf();
	std::ostringstream	oss;
	std::string			message;

	for (int i = 0; success && i < 5; i += 1) {
		const std::string	&name = Zombie::GetRandomName();
		std::cout.rdbuf(oss.rdbuf());
		randomChump(name);
		message = oss.str();
		oss.str("");
		std::cout.rdbuf(old);
		std::cout << message;
		success = name + ": BraiiiiiiinnnzzzZ...\n" + name
			+ " destructed\n" == message;
	}
TEST_LOGIC_END

TEST_LOGIC_START(standard_heap_zombie_destruction_test)
	Zombie				*zombies[5] = {
		new Zombie, new Zombie, new Zombie, new Zombie, new Zombie
	};
	std::streambuf		*old = std::cout.rdbuf();
	std::ostringstream	oss;
	std::string			message;
	std::string			name;
	size_t				pos_of_space;

	for (int i = 4; success && i >= 0; i -= 1) {
		std::cout.rdbuf(oss.rdbuf());
		delete zombies[i];
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

TEST_LOGIC_START(standard_heap_zombie_announce_test)
	Zombie				*zombies = new Zombie[5];
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
	delete [] zombies;
TEST_LOGIC_END

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
