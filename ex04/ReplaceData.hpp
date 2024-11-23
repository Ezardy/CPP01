#ifndef EX04_REPLACEDATA_HPP
# define EX04_REPLACEDATA_HPP

# include <fstream>
# include <cstddef>

# include "ErrorCode.hpp"

struct ReplaceData {
	const char			*from;
	const char			*to;
	std::ifstream		&in;
	std::ofstream		&out;
	const std::size_t	&fromSize;
	const std::size_t	&toSize;
	const std::size_t	&bufferSize;
	ErrorCode			code;
	char *const			buffer;
	std::size_t			head;
	std::size_t			offset;
	std::size_t			matchesCount;
	const char			*matchEnd;
	const char			*matchStart;
};
#endif
