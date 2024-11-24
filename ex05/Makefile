iflags=-Wall -Wextra -Werror -std=c++98
src=main Harl
obj=$(addsuffix .o, $(src))
command=c++ $(iflags) -o $@ -c $<

all: test

test: $(obj)
	c++ -o $@ $(obj)

debug: iflags+=-g
debug: test

main.o: main.cpp Harl.hpp Makefile
	$(command)

Harl.o: Harl.cpp Harl.hpp Makefile
	$(command)

clean:
	rm -f $(obj)

fclean: clean
	rm -f test

re: fclean test