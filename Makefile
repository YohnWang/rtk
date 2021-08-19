
CC=gcc

srcs=$(wildcard *.c)
objs=$(srcs:%.c=%.o)
cflags=-Wall
ldflags=-lwinmm -lmsimg32 -lkernel32 -luser32 -lgdi32 -lole32 -loleaut32 -luuid

main.exe: $(objs)
	$(CC) $^ -o $@ $(ldflags)

%.o:%.c 
	$(CC) -c $(cflags) $< -o $@


.PHONY: clean run

run: main.exe 
	./main.exe

clean:
	-rm *.o
	-rm *.exe
	-rm *.d