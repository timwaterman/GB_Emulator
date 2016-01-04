gbemu: emu.o opcodes.o
	gcc -g -Wall emu.o opcodes.o -o gbemu

emu.o: emu.c opcodes.h
	gcc -c -Wall -g emu.c

opcodes.o: opcodes.c opcodes.h
	gcc -c -Wall -g opcodes.c

.PHONY: clean all

clean:
	rm -f *.o gbemu

all: clean gbemu
