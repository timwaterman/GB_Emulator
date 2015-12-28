/*
Tim Waterman
26 December 2015
OpCode Header
*/

#ifndef __OPCODES_H__
#define __OPCODES_H__

typedef struct memory {
	unsigned char a;
	unsigned char h;
	unsigned char l;
	unsigned short pc;
	unsigned short sp;
} registers;

typedef enum {
	INVALID, //invalid base case


	LD_SP, //load stack pointer with a value
	LD_HL_DEC_A,
	LD_HL,

	XOR_A

} opcode;

void printRegisters(registers *regs);

void initRegisters(registers *regs);

void executeInstruction(registers *regs, opcode op, const char *program);

opcode decodeInstruction(const char op);

#endif