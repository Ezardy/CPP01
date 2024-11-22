#include <fstream>
#include <iostream>
#include <cstring>
#include <new>

#include "ReplaceData.hpp"
#include "constants.hpp"

const char			*ft_strncmp(const char *str1, std::size_t size1, const char *str2,
						std::size_t size2);
const char			*ft_strnchr(const char *str, char c, std::size_t s);
void				shift(char *buff, const std::size_t size, const std::size_t shift);

static void			print_error(ErrorCode code);
static ErrorCode	replace(const char *from, const char *to, std::ifstream &in,
						std::ofstream &out);
static void			count_matches(ReplaceData &d);
static void			output_buffer(ReplaceData &d);

int	main(int argc, char **argv) {
	ErrorCode		code = NO_ERR;
	std::ifstream	in;
	std::ofstream	out;
	if (argc != 4)
		code = ARG_COUNT;
	else if (!argv[2][0])
		code = SUBSTR_EMPTY;
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

static ErrorCode	replace(const char *from, const char *to, std::ifstream &in,
				std::ofstream &out) {
	const std::size_t	fromSize = strlen(from);
	const std::size_t	toSize = strlen(to);
	const std::size_t	bufferSize = (fromSize > STANDARD_BUFFER_SIZE
		? fromSize : STANDARD_BUFFER_SIZE);
	ReplaceData			d = {
		from,
		to,
		in,
		out,
		fromSize,
		toSize,
		bufferSize,
		NO_ERR,
		new char[bufferSize],
		0,
		0,
		0,
		0,
		NULL,
		NULL
	};

	while (d.code == NO_ERR && (d.head || !in.eof())) {
		try {
			in.read(d.buffer + d.head, bufferSize - d.head);
			d.head += in.gcount();
			if (d.offset) {
				d.matchEnd = ft_strncmp(d.buffer + d.offset, d.head - d.offset,
					from + d.offset, fromSize - d.offset);
				d.matchesCount += !d.matchEnd;
				d.matchStart = d.buffer;
				d.offset = 0;
			} else
				count_matches(d);
			try {
				output_buffer(d);
			} catch (const std::ofstream::failure &e) {
				d.code = WRITE_FILE;
			}
			shift(d.buffer, d.head, d.shiftSize);
			d.head -= d.shiftSize;
		} catch (const std::ifstream::failure &e) {
			d.code = READ_FILE;
		}
	}
	delete [] d.buffer;
	return d.code;
}

static void	count_matches(ReplaceData &d) {
	d.matchEnd = d.buffer;
	do {
		if ((d.matchStart = ft_strnchr(d.matchEnd, d.from[0], d.head))) {
			if (!(d.matchEnd = ft_strncmp(d.matchStart,
						d.buffer + d.head - d.matchStart,
						d.from, d.fromSize)))
				for (d.matchesCount = 1;
					d.buffer + d.head - d.matchStart - d.fromSize * d.matchesCount >= d.fromSize
					&& !(d.matchEnd = ft_strncmp(d.matchStart + d.fromSize * d.matchesCount,
						d.buffer + d.head - d.matchStart - d.fromSize * d.matchesCount,
						d.from, d.fromSize)); d.matchesCount += 1);
		}
	} while (d.matchStart && d.matchEnd != d.buffer + d.head
			&& !d.matchesCount);
}

static void	output_buffer(ReplaceData &d) {
	if (d.matchEnd == d.buffer + d.head || d.matchesCount) {
		d.shiftSize = d.matchStart - d.buffer;
		d.out.write(d.buffer, d.shiftSize);
		if (d.matchesCount) {
			d.shiftSize += d.fromSize * d.matchesCount;
			for (; d.matchesCount > 0; d.matchesCount -= 1)
				d.out.write(d.to, d.toSize);
		} else
			d.offset = d.matchEnd - d.matchStart;
	} else {
		d.out.write(d.buffer, d.head);
		d.shiftSize = 0;
		d.head = 0;
	}
}

static void	print_error(ErrorCode code) {
	if (code != NO_ERR) {
		switch (code) {
			case ARG_COUNT: std::cerr << "Wrong arguments number\n"
				"Usage: test file substring_to_be_replaced substring_to_replac"
				"e\n";
				break;
			case RESERVE_MEM: std::cerr << "Can't reserve enough memory\n";
				break;
			case OPEN_READ_FILE: std::cerr << "Can't open the file for reading"
				"\n";
				break;
			case OPEN_WRITE_FILE: std::cerr << "Can't open the file for writing"
				"\n";
				break;
			case READ_FILE: std::cerr << "Can't read from the file\n";
				break;
			case WRITE_FILE: std::cerr << "Can't write to the file\n";
				break;
			case SUBSTR_EMPTY: std::cerr << "The substring to be replaced canno"
				"t be empty\n";
				break;
			default: std::cerr << "Unknown error";
				break;
		}
	}
}
