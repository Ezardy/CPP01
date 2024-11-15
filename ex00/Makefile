all: test

iflags=-Wall -Wextra -Werror 

src=main Zombie newZombie randomChump
obj=$(addsuffix .o, $(src))

test: $(obj)
	c++ $(iflags) -o $@ $(obj)

main.o: main.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

Zombie.o: Zombie.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

newZombie.o: newZombie.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

randomChump.o: randomChump.cpp Zombie.hpp Makefile
	c++ $(iflags) -o $@ -c $<

clean:
	rm -f $(obj)

fclean: clean
	rm -f test

re: fclean test

debug: iflags+=-g
debug: test