BUFFER_SIZE=100

all: test

iflags=-Wall -Wextra -Werror -std=c++98 -DSTANDARD_BUFFER_SIZE=$(BUFFER_SIZE)

debug:iflags+=-g
debug: test

test: main.cpp ErrorCode.hpp constants.hpp Makefile
	c++ $(iflags) -o $@ $<

clean:
	rm -f test

fclean: clean

re: fclean test