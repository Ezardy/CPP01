all: test

test: main.cpp Makefile
	c++ -Wall -Wextra -Werror -std=c++98 -o $@ $<

clean:

fclean:
	rm -f test

re: fclean test