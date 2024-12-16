all: test

iflags=-Wall -Wextra -Werror -std=c++98

src=main Zombie zombieHorde
obj=$(addsuffix .o, $(src))

test: $(obj)
	c++ $(iflags) -o $@ $(obj)

main.o: main.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

Zombie.o: Zombie.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

zombieHorde.o: zombieHorde.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

clean:
	rm -f $(obj)

fclean: clean
	rm -f test

re: fclean test

debug: iflags+=-g
debug: test
