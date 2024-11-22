#include <cstddef>

const char	*ft_strncmp(const char *str1, std::size_t size1, const char *str2,
				std::size_t size2) {
	for (; size1 && size2 && *str1 && *str2 && *str1 == *str2;
		size1 -= 1, size2 -= 1, str1 += 1, str2 += 1);
	if (!size2)
		str1 = NULL;
	return str1;
}

const char	*ft_strnchr(const char *str, char c, std::size_t s) {
	for (; s && *str && *str != c; s -= 1, str += 1);
	if (!s || (c && !*str))
		str = NULL;
	return str;
}

void	shift(char *buff, const std::size_t size, const std::size_t shift) {
	for (std::size_t i = 0; i < size - shift; i += 1)
		buff[i] = buff[i + shift];
}
