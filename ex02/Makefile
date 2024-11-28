all: test

test: main.o
	c++ -o $@ $<

main.o: main.cpp Makefile
	c++ -Wall -Wextra -Werror -std=c++98 -o $@ -c $<

clean:
	rm -f main.o

fclean: clean
	rm -f test

re: fclean test