/*
Tim Waterman
28 December 2015
OpCode Source code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

extern unsigned char memoryspace[54000];

 void writeToMemory_8(unsigned short address, unsigned char data) {

 	//fprintf(stderr, "Writing %x to address %x\n", data, address);
 	memoryspace[address] = data;

 	return;
 }


void printRegisters(registers *regs) {

	fprintf(stderr, "REGISTERS:\n");
	fprintf(stderr, "SP = %x\n", regs->sp);
	fprintf(stderr, "A = %u\n", regs->a);
	fprintf(stderr, "C = %u\n", regs->c);
	fprintf(stderr, "H = %x\n", regs->h);
	fprintf(stderr, "L = %x\n", regs->l);
	fprintf(stderr, "F = %x\n", regs->f);


}
/*
Initialize the registers. Add more here
as needed
*/
void initRegisters(registers *regs) {

	regs->sp = 0;
	regs->pc = 0;
	regs->a = 0x1;
	regs->h = 0x0;
	regs->l = 0x0;
	regs->f = 0x8; //testing the zero bit
}

/*
takes in the instruction opcode and the registers,
and then executes the instruction
Will not modify the program, only the registers
*/
void executeInstruction(registers *regs, opcode op, const char *program) {

	switch (op) {
		case LD_C:
			regs->c = program[regs->pc + 1];
			regs->pc += 2;
			break;
		case JR_NZ: {//jump if zero flag is cleared
			char offset = program[regs->pc + 1]; //the offset is in the next byte
			if((regs->f >> 7) & 1) {
				regs->pc += 2;
			}
			else
				regs->pc += 2 + offset;
			break;
		}
		case LD_HL:
			regs->h = program[regs->pc + 2];
			regs->l = program[regs->pc + 1];
			regs->pc += 3;
			break;
		case LD_SP: //0x31, LOAD SP
			regs->sp = program[(regs->pc) + 1]; //store next value in stack pointer
			regs->pc += 3; //increment pc by 3 bytes
			break;
		case LD_HL_DEC_A: {
			unsigned short high = regs->h;
			unsigned short low = regs->l;
			unsigned short addr = (high << 8) | low;

			writeToMemory_8(addr, regs->a);
			if (regs->l > 0) 
				--regs->l;
			else {
				--regs->h;
				regs->l = 0xFF;
			}
			regs->pc++;
		}
			break;
		case XOR_A: //0xAF, XOR Register A
			regs->a ^= regs->a;
			(regs->pc)++;
			break;
		case BIT_7H: //0xCB7C, check high bit of H
			if( (regs->h >> 7) & 1) { //if it's one, clear the zero flag
				regs->f = ((regs->f >> 7) & 0) << 7; 
			}
			else {
				regs->f = ((regs->f >> 7) | 1) << 7; //zero flag is on
			}

			regs->pc += 2;
			break;
		default:
			fprintf(stderr, "OPCODE %x Not yet implemented\n", program[regs->pc]);
			exit(1);
	}//end main switch

		return;
}


/*
decodes the instruction, returns the enum opcode
Nextop is only used in the case of an extended operation,
which starts with opcode 0xCB
*/
opcode decodeInstruction(const char op, const char nextop) {

	unsigned char hex = op;
	unsigned char next = nextop;

	switch (hex) {
		case 0x0E:
			fprintf(stderr, "LD C\n");
			return LD_C;
			break;
		case 0x20:
			fprintf(stderr, "JR NZ\n");
			return JR_NZ;
			break;
		case 0x21:
			fprintf(stderr, "LD HL\n");
			return LD_HL;
			break;
		case 0x31:
			fprintf(stderr, "LD SP\n");
			return LD_SP;
			break;
		case 0x32:
			fprintf(stderr, "LD_HL_DEC_A\n");
			return LD_HL_DEC_A;
			break;
		case 0xAF:
			fprintf(stderr, "XOR A\n");
			return XOR_A;
			break;
		case 0xCB://second set of opcodes
			//fprintf(stderr, "SECOND SET\n");
			switch (next) {
				case 0x7C:
			//		fprintf(stderr, "CHECKING BIT 7\n");
					return BIT_7H;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}

	return INVALID;
}

