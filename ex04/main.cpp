#include <iostream>
#include <fstream>
#include <string>

#include "ErrorCode.hpp"

static ErrorCode		replace(std::ifstream &in, std::ofstream &out,
							const std::string from, const std::string to);
static std::ifstream	&getline(std::ifstream &in, std::string &buffer);
static void				print_error(ErrorCode code);
static void				replace_in_buffer(std::ofstream &out,
							std::string &buffer, std::string &tmp,
							const std::string &from, const std::string &to);

int	main(int argc, char **argv) {
	ErrorCode	code;
	
	if (argc == 4) {
		try {
			std::ifstream	in(argv[1]);
			std::ofstream	out((std::string(argv[1]) + ".replace").c_str());

			if (!in)
				code = OPEN_READ_FILE;
			else if (!out)
				code = OPEN_WRITE_FILE;
			else
				code = replace(in, out, argv[2], argv[3]);
		} catch (const std::bad_alloc &e) {
			code = RESERVE_MEM;
		}
	} else
		code = ARG_COUNT;
	print_error(code);
	return code;
}

static ErrorCode	replace(std::ifstream &in, std::ofstream &out,
						const std::string from, const std::string to) {
	ErrorCode	code = NO_ERR;
	std::string	buffer;
	std::string	tmp;

	try {
		if (from.empty())
			throw std::invalid_argument("from is empty");
		tmp.reserve(to.size());
		while (!in.bad() && !out.bad() && (!buffer.empty()
					|| !getline(in, buffer).eof() || !buffer.empty())) {
			if (tmp.empty())
				replace_in_buffer(out, buffer, tmp, from, to);
			else if (tmp.size() < from.size()) {
				std::size_t	count = from.size() - tmp.size();
				tmp.append(buffer.substr(0, count));
				buffer.erase(0, count);
			}
			else if (tmp.compare(from)) {
				std::size_t	match_pos;
				if ((match_pos = tmp.find(from[0])) == std::string::npos
					|| (match_pos == 0 && (match_pos = tmp.find(from[0], 1))
						== std::string::npos)) {
					out << tmp;
					tmp.erase();
				} else {
					out << tmp.substr(0, match_pos);
					tmp.erase(0, match_pos);
				}
			} else {
				out << to;
				tmp.erase();
			}
		}
		out << tmp;
		if (in.bad())
			code = READ_FILE;
		else if (out.bad())
			code = WRITE_FILE;
	} catch (const std::bad_alloc &e) {
		code = RESERVE_MEM;
	} catch (const std::invalid_argument &e) {
		code = SUBSTR_EMPTY;
	}
	return code;
}

static void	replace_in_buffer(std::ofstream &out, std::string &buffer,
				std::string &tmp, const std::string &from,
				const std::string &to) {
	std::size_t	match_pos;
	if ((match_pos = buffer.find(from)) == std::string::npos) {
		std::size_t	pos = buffer.size() >= from.size() ? buffer.size() - from.size() + 1 : 0;
		if ((match_pos = buffer.find(from[0], pos)) == std::string::npos)
			out << buffer;
		else {
			tmp = buffer.substr(match_pos);
			out << buffer.substr(0, match_pos);
		}
		buffer.erase();
	} else {
		out << buffer.substr(0, match_pos) << to;
		buffer.erase(0, match_pos + from.size());
	}
}

static std::ifstream	&getline(std::ifstream &in, std::string &buffer) {
	if (!std::getline(in, buffer).eof())
		buffer.append(1, '\n');
	return in;
}

static void	print_error(ErrorCode code) {
	switch (code) {
		case NO_ERR:
			break;
		case ARG_COUNT:
			std::cerr << "Wrong command line arguments count\n""Usage: "
				"test file substring_to_be_replaced substring_to_replace\n";
			break;
		case RESERVE_MEM:
			std::cerr << "Memory allocation failed\n";
			break;
		case OPEN_READ_FILE:
			std::cerr << "Can't open the file for reading\n";
			break;
		case OPEN_WRITE_FILE:
			std::cerr << "Can't open the file for writing\n";
			break;
		case READ_FILE:
			std::cerr << "The file for reading is corrupted\n";
			break;
		case WRITE_FILE:
			std::cerr << "The file for writing is corrupted\n";
			break;
		case SUBSTR_EMPTY:
			std::cerr << "The replacing substring can't be empty\n";
			break;
		default:
			std::cerr << "Unknown error\n";
			break;
	}
}
