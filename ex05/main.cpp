#include <iostream>
#include <sstream>
#include <string>

#include "Harl.hpp"

#define TEST_LOGIC_START(func_name) static bool func_name(void) {\
		bool				success = true;\
		try {\
			const std::string	_func_name = #func_name;\
			std::streambuf		*oldOut = std::cout.rdbuf();\
			std::streambuf		*oldErr = std::cerr.rdbuf();\
			std::ostringstream	ossOut;\
			std::ostringstream	ossErr;\
			std::string			expectedOut;\
			std::string			expectedErr;\
			std::cout << "[START " << _func_name << "]\n";\
			std::cout.rdbuf(ossOut.rdbuf());\
			std::cerr.rdbuf(ossErr.rdbuf());
#define TEST_LOGIC_END\
			std::cout.rdbuf(oldOut);\
			std::cerr.rdbuf(oldErr);\
			success = success && expectedOut == ossOut.str() && expectedErr == ossErr.str();\
			std::cout << "stdout:\n" << ossOut.str() << "stderr:\n" << ossErr.str();\
			if (!success) {\
				std::cout << "EXPECTED STDOUT:\n" << expectedOut << "EXPECTED STDERR:\n" << expectedErr;\
				std::cout << _func_name << " failed\n";\
			}\
		} catch(const std::bad_alloc &e) {\
			std::cerr << "Memory allocation failed\n";\
			success = false;\
		}\
		return success;\
	}

static bool	debug(void);
static bool	info(void);
static bool	warning(void);
static bool	error(void);
static bool	debug_error(void);
static bool	non_existant(void);
static bool	demo(void);

int	main() {
	bool	success = true;
	bool	(*tests[])(void) = {
		debug, info, warning, error, debug_error, non_existant, demo
	};
	const std::size_t	testsCount = sizeof(tests) / sizeof(tests[0]);
	for (std::size_t i = 0; success && i < testsCount; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

static bool	demo(void) {
	Harl	harl;

	std::cout << "[DEMONSTRATION]\n";
	harl.complain("DEBUG");
	harl.complain("ERROR");
	harl.complain("aw");
	harl.complain("INFO");
	harl.complain("WARNING");
	return true;
}

TEST_LOGIC_START(non_existant)
	Harl	harl;

	harl.complain("");
TEST_LOGIC_END

TEST_LOGIC_START(debug_error)
	Harl	harl;

	harl.complain("DEBUG");
	harl.complain("ERROR");
	expectedOut = "I love having extra bacon for my 7XL-double-cheese-triple-pi"
		"ckle-specialketchup burger. I really do!\n";
	expectedErr = "This is unacceptable! I want to speak to the manager now.\n";
TEST_LOGIC_END

TEST_LOGIC_START(error)
	Harl	harl;

	harl.complain("ERROR");
	expectedErr = "This is unacceptable! I want to speak to the manager now.\n";
TEST_LOGIC_END

TEST_LOGIC_START(warning)
	Harl	harl;

	harl.complain("WARNING");
	expectedErr = "I think I deserve to have some extra bacon for free.\nI've b"
		"een coming for years whereas you started working here since last month"
		".\n";
TEST_LOGIC_END

TEST_LOGIC_START(info)
	Harl	harl;

	harl.complain("INFO");
	expectedOut = "I cannot believe adding extra bacon costs more money. You di"
		"dn't put enough bacon in my burger! If you did, I wouldn't be asking f"
		"or more!\n";
TEST_LOGIC_END

TEST_LOGIC_START(debug)
	Harl	harl;

	harl.complain("DEBUG");
	expectedOut = "I love having extra bacon for my 7XL-double-cheese-triple-pi"
		"ckle-specialketchup burger. I really do!\n";
TEST_LOGIC_END
