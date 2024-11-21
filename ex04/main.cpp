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
const char	*ft_strnchr(const char *str, char c, std::size_t s);
void		shift(char *buff, const std::size_t size, const std::size_t shift);

int	main(int argc, char **argv) {
	ErrorCode		code = NO_ERR;
	std::ifstream	in;
	std::ofstream	out;
	if (argc != 4)
		code = ARG_COUNT;
	else {
		out.exceptions(std::ofstream::badbit | std::ofstream::failbit);
		in.open(argv[1]);
		if (in.fail())
			code = OPEN_READ_FILE;
		else {
			try {
				out.open((std::string(argv[1]) + ".replace").c_str());
				code = replace(argv[2], argv[3], in, out);
			} catch (std::ofstream::failure &e) {
				code = OPEN_WRITE_FILE;
			} catch (const std::bad_alloc &e) {
				code = RESERVE_MEM;
			}
		}
	}
	print_error(code);
	return code;
}

ErrorCode	replace(const char *from, const char *to, std::ifstream &in,
				std::ofstream &out) {
	const std::size_t	fromSize = strlen(from);
	const std::size_t	toSize = strlen(to);
	const std::size_t	bufferSize = (fromSize > STANDARD_BUFFER_SIZE
		? fromSize : STANDARD_BUFFER_SIZE);
	ErrorCode			code = NO_ERR;
	char *const			buffer = new char[bufferSize];
	std::size_t			head = 0;
	std::size_t			offset = 0;
	std::size_t			shiftSize;
	const char			*matchEnd;
	const char			*matchStart;

	while (code == NO_ERR && (head || !in.eof())) {
		try {
			in.read(buffer + head, bufferSize - head);
			head += in.gcount();
			if (offset) {
				matchEnd = ft_strncmp(buffer + offset, from + offset, fromSize - offset);
				matchStart = buffer;
				offset = 0;
			} else {
				matchEnd = buffer;
				do {
					matchStart = ft_strnchr(matchEnd, from[0], head);
					if (matchStart)
						matchEnd = ft_strncmp(matchStart, from, fromSize);
				} while (matchStart && matchEnd != buffer + head && matchEnd);
			}
			try {
				if (matchStart) {
					shiftSize = matchStart - buffer;
					out.write(buffer, shiftSize);
					if (matchEnd)
						offset = matchEnd - matchStart;
					else {
						out.write(to, toSize);
						shiftSize += fromSize;
					}
					shift(buffer, head, shiftSize);
					head -= shiftSize;
				} else {
					out.write(buffer, head);
					head = 0;
				}
			} catch (const std::ofstream::failure &e) {
				code = WRITE_FILE;
			}
		} catch (const std::ifstream::failure &e) {
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

const char	*ft_strncmp(const char *str1, const char *str2, std::size_t n) {
	for (; n && *str1 && *str2 && *str1 == *str2; n -= 1, str1 += 1, str2 += 1);
	if (!n)
		str1 = NULL;
	return str1;
}

const char	*ft_strnchr(const char *str, char c, std::size_t s) {
	for (; s && *str && *str != c; s -= 1, str += 1);
	if (!s || (c && !*str))
		str = NULL;
	return str;
}

void		shift(char *buff, const std::size_t size, const std::size_t shift) {
	for (std::size_t i = 0; i < size - shift; i += 1)
		buff[i] = buff[i + shift];
}
