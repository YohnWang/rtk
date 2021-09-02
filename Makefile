
CC=gcc

srcs=$(wildcard *.c)
objs=$(srcs:%.c=%.o)
cflags=-Wall -Wextra -Wno-unused -include rtkdebug.h -DRTK_DEBUG
ldflags=-lwinmm -lmsimg32 -lkernel32 -luser32 -lgdi32 -lole32 -loleaut32 -luuid

main.exe: $(objs)
	$(CC) $^ -o $@ $(ldflags)

%.o:%.c 
	$(CC) -c $(cflags) $< -o $@

sinclude $(srcs:.c=.d)

%.d: %.c
	$(CC) -MM $(cflags) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

.PHONY: clean run

run: main.exe 
	./main.exe

clean:
	-rm *.o
	-rm *.exe
	-rm *.d