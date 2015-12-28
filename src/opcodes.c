/*
Tim Waterman
28 December 2015
OpCode Source code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"


void printRegisters(registers *regs) {

	fprintf(stderr, "REGISTERS:\n");
	fprintf(stderr, "SP = %x\n", regs->sp);

}
/*
Initialize the registers. Add more here
as needed
*/
void initRegisters(registers *regs) {

	regs->sp = 0;
	regs->pc = 0;
	regs->a = 0;
}

/*
takes in the instruction opcode and the registers,
and then executes the instruction
Will not modify the program, only the registers
*/
void executeInstruction(registers *regs, opcode op, const char *program) {

	switch (op) {

		case LD_SP: {
			regs->sp = program[(regs->pc) + 1]; //store next value in stack pointer
			regs-> pc += 3; //increment pc by 3 bytes
			break;
		}


		default:
			fprintf(stderr, "%s\n", "OPCODE Not yet implemented");
			exit(1);
	}//end main switch

		return;
}


/*
decodes the instruction, returns the enum opcode
*/
opcode decodeInstruction(const char op) {

	unsigned char hex = op;

	switch (hex) {
		case 0x31:
			fprintf(stderr, "LD SP\n");
			return LD_SP;
			break;
		default:
			break;
	}

	return INVALID;
}

