#include <iostream>
#include <cstdlib>

#include "Zombie.hpp"

Zombie::Zombie(void) : name(GetRandomName()) {

}

Zombie::Zombie(const std::string &name) : name(name) {

}

Zombie::Zombie(const Zombie &other) {
	if (this != &other)
		name = other.name;
}

Zombie	&Zombie::operator=(const Zombie &other) {
	if (this != &other)
		name = other.name;
	return *this;
}

Zombie::~Zombie(void) {
	std::cout << name << " destructed\n";
}

void	Zombie::announce(void) const {
	std::cout << name << ": BraiiiiiiinnnzzzZ...\n";
}

const std::string	&Zombie::GetRandomName(void) {
	return _names[rand() % 100];
}

const std::string Zombie::_names[100] = {
	"Jane Mcguire",
	"Cash Ortega",
	"Armani Mcknight",
	"Kaylen Pineda",
	"Rigoberto King",
	"Bria Alvarado",
	"Mollie Stein",
	"Darian Orozco",
	"Jairo Cisneros",
	"Nataly Vance",
	"Madden Tyler",
	"Quinten Randall",
	"Dominique Bridges",
	"Edwin Palmer",
	"Sherlyn Spencer",
	"Camron Carney",
	"Vincent Lucero",
	"Kaylynn Mccall",
	"Ethan Mejia",
	"Denzel Mckee",
	"Selah Warner",
	"Jordon Downs",
	"Gunner Romero",
	"Ashly Dixon",
	"Kaitlynn Rice",
	"Angelina Franco",
	"Destiny Rojas",
	"Israel Carroll",
	"Tia Marquez",
	"Alvaro Mayer",
	"Luka Spears",
	"Eden Greer",
	"Augustus Santos",
	"Perla Trujillo",
	"Bria Solis",
	"Janessa Rios",
	"Marley Cross",
	"Reina Freeman",
	"Eleanor Turner",
	"Jazlene Mcmahon",
	"Alia Ellison",
	"Annie Hayes",
	"Mario Martinez",
	"Mina Williamson",
	"Mikaela Solis",
	"Sadie Lewis",
	"Clay Peterson",
	"Dayami Galloway",
	"Janiah Gutierrez",
	"Brennan Foster",
	"Tania Sullivan",
	"Eleanor Ortiz",
	"Byron Small",
	"Myla Good",
	"Carmen Gonzalez",
	"Emilie Grimes",
	"Nathan Snow",
	"Nehemiah Stafford",
	"Cristopher Woods",
	"Colton Huynh",
	"Javon Cowan",
	"Mateo Rivers",
	"Rachael Bauer",
	"Pranav Walsh",
	"Cheyanne Benson",
	"Daisy Norton",
	"Talia Juarez",
	"Maya Copeland",
	"Emmanuel Huffman",
	"Sabrina Webster",
	"Cannon York",
	"Deandre Drake",
	"Karson Mercer",
	"Rafael Burke",
	"Jensen Stevens",
	"Nina Dillon",
	"Griffin Jarvis",
	"Fiona Gibson",
	"Amya Burton",
	"Arjun Murray",
	"Eileen Charles",
	"Ezra Miles",
	"Jadyn Rangel",
	"Alivia Reilly",
	"Amaya Khan",
	"Donovan Ruiz",
	"Sydney Curry",
	"Frankie Cowan",
	"Jordan Hood",
	"Devin Ball",
	"Samuel Stafford",
	"Isabella Mercado",
	"Brandon Dunlap",
	"Caitlyn Perry",
	"Dulce Peters",
	"Alisa Barber",
	"Lila Decker",
	"Nick Baird",
	"Hector Camacho",
	"Dylan Cisneros"
};