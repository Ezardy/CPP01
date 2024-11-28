all: replace

replace: main.o
	c++ -o $@ $<

iflags=-Wall -Wextra -Werror -std=c++98

debug:iflags+=-g
debug:replace

main.o: main.cpp ErrorCode.hpp Makefile
	c++ $(iflags) -o $@ -c $<

clean:
	rm -f main.o

fclean: clean
	rm -f replace

re: fclean replace