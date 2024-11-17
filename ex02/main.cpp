#include <iostream>
#include <string>

int	main() {
	const std::string	str = "HI THIS IS BRAIN";
	const std::string	*stringPTR = &str;
	const std::string	&stringREF = str;
}