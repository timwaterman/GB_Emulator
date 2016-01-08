/*
Tim Waterman
26 December 2015
Emulator Main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

unsigned char *memoryspace;

//die with an error
void die(const char *message) {

	perror(message);
	exit(1);
}

/*
Getsize will return the size of a file in bytes
File must already be opened prior to call
*/
int getSize(FILE *file) {

	fseek(file, 0L, SEEK_END); //go to the end of the file
	int size = ftell(file);

	rewind(file); //go back to beginning of file

	return size;
}

int main(int argc, char **argv) {

	if (argc != 2) {
		fprintf(stderr, "%s\n", "Usage: ./gbemu <rom file>");
		exit(1);
	}

	memoryspace = malloc(0xFFFF); //create the memory space of 64K

	registers regs;

	FILE *rom = fopen(argv[1], "r");

	if (rom == NULL) {
		die("Fopen failed\n");
	}

	//establish size and buffer
	int size = getSize(rom);
	char buffer[size];
	memset(buffer, 0, sizeof(buffer));

	//read the file into buffer to use as input stream
	fread(buffer, size, 1, rom); 

	initRegisters(&regs); //initialize all the registers
	loadLogo();
	memoryspace[0xFF44] = 0x90; //init the display to work, ONLY HERE FOR TESTING


	while(regs.pc < sizeof buffer) {
		fprintf(stderr, "PC is %u\n", regs.pc);

		opcode op = decodeInstruction(buffer[regs.pc], buffer[regs.pc + 1] );
		executeInstruction(&regs, op, buffer);
		printRegisters(&regs);
		fprintf(stderr, "PC is %u\n", regs.pc);
	}

	fprintf(stderr, "Size of buffer is %u\n", size);


	return 0;
}