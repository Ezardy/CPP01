#include <fstream>
#include <iostream>
#include <cstring>
#include <new>

#include "ErrorCode.hpp"
#include "constants.hpp"

void		print_error(ErrorCode code);
ErrorCode	replace(const char *from, const char *to, std::ifstream &in,
				std::ofstream &out);
const char	*ft_strncmp(const char *str1, const char *str2, std::size_t n);
void		shift(char *buff, std::size_t size, std::size_t shift);

int	main(int argc, char **argv) {
	ErrorCode		code = NO_ERR;
	std::ifstream	in;
	std::ofstream	out;
	if (argc != 4)
		code = ARG_COUNT;
	else {
		try {
			in.open(argv[1]);
			try {
				out.open((std::string(argv[1]) + ".replace").c_str());
				code = replace(argv[2], argv[3], in, out);
			} catch (std::ofstream::failure) {
				code = OPEN_WRITE_FILE;
			}
		} catch (std::ifstream::failure) {
			code = OPEN_READ_FILE;
		} catch (std::bad_alloc) {
			code = RESERVE_MEM;
		}
	}
	print_error(code);
	return code;
}

ErrorCode	replace(const char *from, const char *to, std::ifstream &in,
				std::ofstream &out) {
	const std::size_t	fromSize = strlen(from);
	const std::size_t	bufferSize = (fromSize > STANDARD_BUFFER_SIZE
		? fromSize : STANDARD_BUFFER_SIZE);
	ErrorCode			code = NO_ERR;
	char *const			buffer = new char[bufferSize];
	std::size_t			head = 0;
	const char			*matchEnd;
	const char			*matchStart;

	buffer[bufferSize] = '\0';
	while (code == NO_ERR && !in.eof()) {
		try {
			head += in.readsome(buffer + head, bufferSize - head);
			matchEnd = buffer;
			do {
				matchStart = std::strchr(matchEnd, from[0]);
				if (matchStart)
					matchEnd = ft_strncmp(matchStart, from, fromSize);
			} while (matchStart && matchEnd != buffer + bufferSize && matchEnd);
			if (matchStart) {
				out.write(buffer, matchStart - buffer);
				shift(buffer, bufferSize, matchStart - buffer);
				head -= matchStart - buffer;
			}
		} catch (std::ifstream::failure) {
			code = READ_FILE;
		}
	}
	delete [] buffer;
	return code;
}

void	print_error(ErrorCode code) {
	if (code != NO_ERR) {
		switch (code) {
			case ARG_COUNT: std::cerr << "Wrong arguments number\n"
				"Usage: test file substring_to_be_replaced substring_to_replace\n";
				break;
			case RESERVE_MEM: std::cerr << "Can't reserve enough memory\n";
				break;
			case OPEN_READ_FILE: std::cerr << "Can't open the file for reading\n";
				break;
			case OPEN_WRITE_FILE: std::cerr << "Can't open the file for writing\n";
				break;
			case READ_FILE: std::cerr << "Can't read from the file\n";
				break;
			case WRITE_FILE: std::cerr << "Can't write to the file\n";
				break;
			default: std::cerr << "Unknown error";
				break;
		}
	}
}
