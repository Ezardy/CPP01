BUFFER_SIZE?=100

all: replace

iflags=-Wall -Wextra -Werror -std=c++98 -DSTANDARD_BUFFER_SIZE=$(BUFFER_SIZE)
command=c++ $(iflags) -o $@ -c $<

src=main buffer_manipulations
obj=$(addsuffix .o, $(src))

debug:iflags+=-g
debug: replace

replace: $(obj)
	c++ -o $@ $(obj)

main.o: main.cpp constants.hpp ErrorCode.hpp ReplaceData.hpp Makefile
	$(command)

buffer_manipulations.o: buffer_manipulations.cpp Makefile
	$(command)

clean:
	rm -f $(obj)

fclean: clean
	rm -f replace

re: fclean replace