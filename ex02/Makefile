all: test

test: main.cpp Makefile
	c++ -Wall -Wextra -Werror -std=c++98 -o $@ $<

clean:
	rm -f test

fclean: clean

re: fclean test