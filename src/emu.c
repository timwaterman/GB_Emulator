/*
Tim Waterman
26 December 2015
Emulator Main
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	FILE *rom = fopen(argv[1], "r");

	if (rom == NULL) {
		die("Fopen failed\n");
	}

	int size = getSize(rom);

	char buffer[size];
	memset(buffer, 0, sizeof(buffer));


	return 0;
}