all: test

src=main HumanA HumanB Weapon
obj=$(addsuffix .o, $(src))
iflags=-Wall -Wextra -Werror -std=c++98

test: $(obj)
	c++ $(iflags) -o $@ $(obj)

debug: iflags+=-g
debug: test

compile=c++ $(iflags) -o $@ -c $<

main.o: main.cpp HumanA.hpp HumanB.hpp Weapon.hpp Makefile
	$(compile)

HumanA.o: HumanA.cpp Weapon.hpp HumanB.hpp Makefile
	$(compile)

HumanB.o: HumanB.cpp Weapon.hpp Makefile
	$(compile)

Weapon.o: Weapon.cpp HumanB.hpp Makefile
	$(compile)

clean:
	rm -f $(obj)

fclean: clean
	rm -f test

re: fclean test