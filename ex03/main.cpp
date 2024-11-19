#include <iostream>
#include <sstream>
#include <string>

#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

#define TEST_LOGIC_START(func_name) static bool func_name() {\
		bool				success = true;\
		const std::string	_func_name = #func_name;\
		std::streambuf		*old = std::cout.rdbuf();\
		std::ostringstream	oss;\
		std::string			expected;\
		std::cout << "[START " << _func_name << "]\n";\
		std::cout.rdbuf(oss.rdbuf());
#define TEST_LOGIC_END\
		std::cout.rdbuf(old);\
		success = success && expected == oss.str();\
		std::cout << oss.str();\
		if (!success) {\
			std::cout << "EXPECTED:\n" << expected;\
			std::cout << _func_name << " failed\n";\
		}\
		return success;\
	}

static bool	hmnA_change_weapon_type(void);
static bool	hmnB_change_weapon_type(void);
static bool	hmnA_dies_hmnB_take_his_weapon(void);
static bool	hmnB_dies_hmnA_take_his_weapon(void);
static bool	hmnB_and_hmnA_swap_theirs_weapons(void);
static bool	hmnA_weapon_brakes(void);
static bool	hmnB_weapon_brakes(void);
static bool	hmnA_tries_take_invalid_and_owned_weapons(void);
static bool	hmnB_tries_take_invalid_and_owned_weapons(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		hmnA_change_weapon_type, hmnB_change_weapon_type,
		hmnA_dies_hmnB_take_his_weapon, hmnB_dies_hmnA_take_his_weapon,
		hmnB_and_hmnA_swap_theirs_weapons, hmnA_weapon_brakes,
		hmnB_weapon_brakes, hmnA_tries_take_invalid_and_owned_weapons,
		hmnB_tries_take_invalid_and_owned_weapons
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

TEST_LOGIC_START(hmnB_tries_take_invalid_and_owned_weapons)
	const char	*gunName = "gun";
	const char	*jakeName = "Jake";
	const char	*paulName = "Paul";
	Weapon		gun(gunName);
	Weapon		invWpn;
	HumanA		jake(jakeName, gun);
	HumanB		paul(paulName);

	paul.attack();
	paul.setWeapon(gun);
	paul.attack();
	paul.setWeapon(invWpn);
	paul.attack();
	jake.~HumanA();
	paul.setWeapon(gun);
	paul.attack();
	expected = std::string(paulName) + " attacks with their " + gunName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_tries_take_invalid_and_owned_weapons)
	const char	*gunName = "gun";
	const char	*jakeName = "Jake";
	const char	*paulName = "Paul";
	Weapon		gun(gunName);
	Weapon		invWpn;
	HumanA		jake(jakeName, gun);
	HumanA		paul(paulName, gun);

	paul.attack();
	paul.setWeapon(invWpn);
	paul.attack();
	jake.~HumanA();
	paul.setWeapon(gun);
	paul.attack();
	expected = std::string(paulName) + " attacks with their " + gunName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_weapon_brakes)
	const char	*gunName = "gun";
	const char	*rifleName = "rifle";
	const char	*jakeName = "Jake";
	Weapon		gun(gunName);
	Weapon		rifle(rifleName);
	HumanB		jake(jakeName);

	jake.setWeapon(gun);
	jake.attack();
	jake.setWeapon(rifle);
	jake.attack();
	rifle.~Weapon();
	jake.attack();
	jake.setWeapon(gun);
	jake.attack();
	expected = std::string(jakeName) + " attacks with their " + gunName + '\n'
		+ jakeName + " attacks with their " + rifleName + '\n'
		+ jakeName + " attacks with their " + gunName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_weapon_brakes)
	const char	*gunName = "gun";
	const char	*rifleName = "rifle";
	const char	*jakeName = "Jake";
	Weapon		gun(gunName);
	Weapon		rifle(rifleName);
	HumanA		jake(jakeName, gun);

	jake.attack();
	jake.setWeapon(rifle);
	jake.attack();
	rifle.~Weapon();
	jake.attack();
	jake.setWeapon(gun);
	jake.attack();
	expected = std::string(jakeName) + " attacks with their " + gunName + '\n'
		+ jakeName + " attacks with their " + rifleName + '\n'
		+ jakeName + " attacks with their " + gunName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_and_hmnA_swap_theirs_weapons)
	const char	*gunName = "gun";
	const char	*rifleName = "rifle";
	const char	*knifeName = "knife";
	const char	*jakeName = "Jake";
	const char	*donaldName = "Donald";
	Weapon		gun(gunName);
	Weapon		rifle(rifleName);
	Weapon		knife(knifeName);
	HumanA		jake(jakeName, gun);
	HumanB		donald(donaldName);

	donald.setWeapon(gun);
	jake.attack();
	donald.attack();
	donald.setWeapon(rifle);
	jake.attack();
	donald.attack();
	jake.setWeapon(rifle);
	jake.attack();
	donald.attack();
	jake.setWeapon(knife);
	donald.setWeapon(gun);
	jake.setWeapon(rifle);
	jake.attack();
	donald.attack();
	success = gun.Owned() && rifle.Owned() && !knife.Owned();
	expected = std::string(jakeName) + " attacks with their " + gunName + '\n'
		+ jakeName + " attacks with their " + gunName + '\n'
		+ donaldName + " attacks with their " + rifleName + '\n'
		+ jakeName + " attacks with their " + gunName + '\n'
		+ donaldName + " attacks with their " + rifleName + '\n'
		+ jakeName + " attacks with their " + rifleName + '\n'
		+ donaldName + " attacks with their " + gunName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_dies_hmnA_take_his_weapon)
	const char	*nameA = "Jake";
	const char	*nameB = "Rachel";
	const char	*gunName = "gun";
	const char	*rifleName = "rifle";
	Weapon		gun(gunName);
	Weapon		rifle(rifleName);
	HumanA		ha(nameA, gun);
	HumanB		hb(nameB);

	hb.setWeapon(rifle);
	ha.setWeapon(rifle);
	ha.attack();
	hb.attack();
	hb.~HumanB();
	ha.setWeapon(rifle);
	ha.attack();
	success = !gun.Owned() && rifle.Owned();
	expected = std::string(nameA) + " attacks with their " + gunName + '\n'
		+ nameB + " attacks with their " + rifleName + '\n' + nameA
		+ " attacks with their " + rifleName + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_dies_hmnB_take_his_weapon)
	const char	*nameA = "Jake";
	const char	*nameB = "Rachel";
	const char	*type = "gun";
	Weapon		weapon(type);
	HumanA		ha(nameA, weapon);
	HumanB		hb(nameB);

	hb.setWeapon(weapon);
	ha.attack();
	hb.attack();
	ha.~HumanA();
	hb.setWeapon(weapon);
	hb.attack();
	expected = std::string(nameA) + " attacks with their " + type + '\n'
		+ nameB + " attacks with their " + type + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnB_change_weapon_type)
	const char	*name = "Jake";
	const char	*type = "gun";
	const char	*newType = "knife";
	Weapon		weapon(type);
	HumanB		h(name);

	h.setWeapon(weapon);
	h.attack();
	weapon.setType(newType);
	h.attack();
	expected = std::string(name) + " attacks with their " + type + '\n'
		+ name + " attacks with their " + newType + '\n';
TEST_LOGIC_END

TEST_LOGIC_START(hmnA_change_weapon_type)
	const char	*name = "Jake";
	const char	*type = "gun";
	const char	*newType = "knife";
	Weapon		weapon = Weapon(type);
	HumanA		h(name, weapon);

	h.attack();
	weapon.setType(newType);
	h.attack();
	expected = std::string(name) + " attacks with their " + type + '\n'
		+ name + " attacks with their " + newType + '\n';
TEST_LOGIC_END
