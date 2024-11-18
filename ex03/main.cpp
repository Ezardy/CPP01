#include <iostream>
#include <sstream>

#include "HumanA.hpp"
#include "HumanB.hpp"

#define TEST_LOGIC_START(func_name) static bool func_name() {\
		bool success = true;\
		std::string _func_name = #func_name;\
		std::cout << "[START " << _func_name << "]\n";\
		std::streambuf		*old = std::cout.rdbuf();\
		std::ostringstream	oss;
		std::string			expected;
#define TEST_LOGIC_END\
		success = success && expected == oss.str();\
		std::cout.rdbuf(old);\
		std::cout << oss.str();\
		if (!success)\
			std::cout << _func_name << " failed\n";\
		return success;\
	}

static bool	hmnA_single_weapon(void);
static bool	hmnA_multiple_weapon(void);
static bool	hmnB_single_weapon(void);
static bool	hmnB_multiple_weapon(void);
static bool	hmnB_dead_other_pick_weapon(void);
static bool	hmnB_drop_weapon_other_pick_weapon(void);
static bool	hmnB_weapon_brake(void);
static bool	hmnA_invalid_weapon(void);
static bool	hmnB_invalid_weapon(void);
static bool	hmnA_invalid_name(void);
static bool	hmnB_invalid_name(void);
static bool	hmnA_invalid_weapon_and_name(void);
static bool	hmnB_invalid_weapon_and_name(void);
static bool	standard_test(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		hmnA_single_weapon, hmnA_multiple_weapon, hmnB_single_weapon,
		hmnB_multiple_weapon, hmnB_dead_other_pick_weapon,
		hmnB_drop_weapon_other_pick_weapon, hmnB_weapon_brake,
		hmnA_invalid_weapon, hmnB_invalid_weapon, hmnA_invalid_name,
		hmnB_invalid_name, hmnA_invalid_weapon_and_name,
		hmnB_invalid_weapon_and_name, standard_test
	};
	size_t	tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

TEST_LOGIC_START(standard_test)
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	expected = "Bob attacks with their crude spiked club\nJim attacks with thei\
		r some other type of club\n";
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_invalid_weapon_and_name)
	Weapon	weapon;
	HumanB	human;

	human.setWeapon(weapon);
	human.attack();
	success = !weapon.Owned();

TEST_LOGIC_END

TEST_LOGIC_START(hmnA_invalid_weapon_and_name)
	Weapon	weapon;
	HumanA	human("", weapon);

	human.attack();
	success = !weapon.Owned();

TEST_LOGIC_END

TEST_LOGIC_START(hmnB_invalid_name)
	Weapon	weapon("gun");
	HumanB	human;

	human.setWeapon(weapon);
	human.attack();
	success = !weapon.Owned();

TEST_LOGIC_END

TEST_LOGIC_START(hmnA_invalid_name)
	Weapon	weapon("gun");
	HumanA	human("", weapon);

	human.attack();
	success = !weapon.Owned();

TEST_LOGIC_END

TEST_LOGIC_START(hmnB_invalid_weapon)
	Weapon	weapon;
	HumanB	human("Jake");

	human.setWeapon(weapon);
	human.attack();
	success = !weapon.Owned();

TEST_LOGIC_END

TEST_LOGIC_START(hmnA_invalid_weapon)
	Weapon	weapon;
	HumanA	human("Jake", weapon);
	human.attack();
	success = !weapon.Owned();
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_weapon_brake)
	const std::string	n = "Jake";
	const std::string	wn = "gun";
	Weapon				weapon(wn);
	HumanB				human(n);

	human.setWeapon(weapon);
	human.attack();
	expected = n + " attacks with their " + wn + '\n';
	weapon.~Weapon();
	human.attack();
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_drop_weapon_other_pick_weapon)
	const std::string	n1 = "Jake";
	const std::string	n2 = "Roger";
	const std::string	wn = "gun";
	HumanB	jake(n1);
	HumanB	roger(n2);
	Weapon	weapon(wn);

	jake.setWeapon(weapon);
	roger.setWeapon(weapon);
	jake.attack();
	roger.attack();
	expected = n1 + " attacks with their " + wn + '\n';
	jake.DropWeapon();
	roger.setWeapon(weapon);
	jake.attack();
	roger.attack();
	expected += n2 + " attacks with their " + wn + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_dead_other_pick_weapon)
	const std::string	n1 = "Jake";
	const std::string	n2 = "Roger";
	const std::string	wn = "gun";
	HumanB	jake(n1);
	HumanB	roger(n2);
	Weapon	weapon(wn);

	jake.setWeapon(weapon);
	roger.setWeapon(weapon);
	jake.attack();
	roger.attack();
	expected = n1 + " attacks with their " + wn + '\n';
	jake.~HumanB();
	roger.setWeapon(weapon);
	roger.attack();
	expected += n2 + " attacks with their " + wn + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_multiple_weapon)
	const std::string	weaponTypes[5] = {
		"gun", "rifle", "carabine", "shotgun", "knife"
	};
	Weapon		weapons[5] = {
		Weapon(weaponTypes[0]), Weapon(weaponTypes[1]), Weapon(weaponTypes[2]),
		Weapon(weaponTypes[3]), Weapon(weaponTypes[4])
	};
	const std::string	names[5] = {
		"Jake", "Allan", "Alice", "Esra", "Gillian"
	};
	HumanB	humans[5] = {
		HumanB(names[0]), HumanB(names[1]), HumanB(names[2]), HumanB(names[3]),
		HumanB(names[4])
	};
	for (int i = 0; i < 5; i += 1)
		humans[i].setWeapon(weapons[i]);
	for (int i = 0; i < 5; i += 1) {
		humans[i].attack();
		expected += names[i] + " attacks with their " + weaponTypes[i] + '\n';
	}
	success = weapons[0].Owned() && weapons[1].Owned() && weapons[2].Owned()
		&& weapons[3].Owned() && weapons[4].Owned();
	
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_single_weapon)
	int					i;
	const std::string	initWeaponType = "gun";
	const std::string	weaponType = "knife";
	Weapon		weapon(initWeaponType);
	const std::string	names[5] = {
		"Jake", "Allan", "Alice", "Esra", "Gillian"
	};
	weapon.setType(weaponType);
	HumanB	humans[5] = {
		HumanB(names[0]), HumanB(names[1]), HumanB(names[2]), HumanB(names[3]),
		HumanB(names[4])
	};
	for (i = 0; i < 5; i += 1)
		humans[i].setWeapon(weapon);
	for (i = 0; i < 5; i += 1)
		humans[i].attack();
	success = weapon.Owned();
	expected = names[0] + " attacks with their " + weaponType + '\n';
	
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_multiple_weapon)
	const std::string	weaponTypes[5] = {
		"gun", "rifle", "carabine", "shotgun", "knife"
	};
	Weapon		weapons[5] = {
		Weapon(weaponTypes[0]), Weapon(weaponTypes[1]), Weapon(weaponTypes[2]),
		Weapon(weaponTypes[3]), Weapon(weaponTypes[4])
	};
	const std::string	names[5] = {
		"Jake", "Allan", "Alice", "Esra", "Gillian"
	};
	HumanA	humans[5] = {
		HumanA(names[0], weapons[0]), HumanA(names[1], weapons[1]),
		HumanA(names[2], weapons[2]), HumanA(names[3], weapons[3]),
		HumanA(names[4], weapons[4])
	};
	for (int i = 0; i < 5; i += 1) {
		humans[i].attack();
		expected += names[i] + " attacks with their " + weaponTypes[i] + '\n';
	}
	success = !(weapons[0].Owned() || weapons[1].Owned() || weapons[2].Owned()
		|| weapons[3].Owned() || weapons[4].Owned());
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_single_weapon)
	const std::string	weaponType = "gun";
	Weapon		weapon(weaponType);
	const std::string	names[5] = {
		"Jake", "Allan", "Alice", "Esra", "Gillian"
	};
	HumanA	humans[5] = {
		HumanA(names[0], weapon), HumanA(names[1], weapon),
		HumanA(names[2], weapon), HumanA(names[3], weapon),
		HumanA(names[4], weapon)
	};
	weapon.setType("knife");
	for (int i = 0; i < 5; i += 1) {
		humans[i].attack();
		expected += names[i] + " attacks with their " + weaponType + '\n';
	}
	success = !weapon.Owned();
TEST_LOGIC_END
