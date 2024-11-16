#include "Zombie.hpp"

Zombie*	zombieHorde(int N, std::string name) {
	Zombie	tmp(name);
	Zombie	*horde = new Zombie[N];
	if (horde) {
		for (N -= 1; N >= 0; N -= 1)
			horde[N] = tmp;
	}
	return horde;
}