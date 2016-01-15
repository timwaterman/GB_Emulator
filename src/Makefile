CFLAGS= -c -Wall -g `sdl2-config --cflags`
LFLAGS= -g -Wall `sdl2-config --libs`

gbemu: emu.o opcodes.o
	gcc $(LFLAGS) emu.o opcodes.o -o gbemu

emu.o: emu.c opcodes.h
	gcc $(CFLAGS) emu.c

opcodes.o: opcodes.c opcodes.h
	gcc $(CFLAGS) opcodes.c

.PHONY: clean all

clean:
	rm -f *.o gbemu

all: clean gbemu
