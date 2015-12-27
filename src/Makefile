gbemu: emu.o
	gcc -g -Wall emu.o -o gbemu

emu.o: emu.c opcodes.h
	gcc -c -Wall -g emu.c

.PHONY: clean all

clean:
	rm -f *.o gbemu

all: clean gbemu