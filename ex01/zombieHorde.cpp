#include "Zombie.hpp"

Zombie*	zombieHorde(int N, std::string name) {
	Zombie	*horde;
	try {
		horde = new Zombie[N];
		Zombie	tmp(name);
		if (horde) {
			for (N -= 1; N >= 0; N -= 1)
				horde[N] = tmp;
		}
	} catch (const std::bad_alloc &e) {
		horde = NULL;
	}
	return horde;
}
