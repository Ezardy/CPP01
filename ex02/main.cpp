#include <iostream>
#include <string>

int	main() {
	const std::string	str = "HI THIS IS BRAIN";
	const std::string	*stringPTR = &str;
	const std::string	&stringREF = str;

	std::cout << "The memory address of the string variable: " << &str << '\n';
	std::cout << "The memory address held by stringPTR: " << stringPTR << '\n';
	std::cout << "The memory address held by stringREF: " << &stringREF << '\n';

	std::cout << "The value of the string variable: " << str << '\n';
	std::cout << "The value pointed to by stringPTR: " << *stringPTR << '\n';
	std::cout << "The value pointed to by stringREF: " << stringREF << '\n';
	return 0;
}