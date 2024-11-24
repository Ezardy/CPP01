iflags=-Wall -Wextra -Werror -std=c++98
command=c++ $(iflags) -o $@ -c $<
src=main Harl LogLevel
obj=$(addprefix .o, $(src))

all: harlFilter

harlFilter: $(obj)
	c++ -o $@ $(obj)

main.o: main.cpp Harl.hpp LogLevel.hpp Makefile
	$(command)

Harl.o: Harl.cpp Harl.hpp Makefile
	$(command)

LogLevel.o: LogLevel.cpp LogLevel.hpp Makefile
	$(command)

debug: iflags+=-g
debug: harlFilter

clean:
	rm -f $(obj)

fclean: clean
	rm -f harlFilter

re: fclean harlFilter