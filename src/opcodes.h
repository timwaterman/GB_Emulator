/*
Tim Waterman
26 December 2015
OpCode Header
*/

#ifndef __OPCODES_H__
#define __OPCODES_H__

typedef struct memory {

	unsigned char a;
	unsigned char b;
	unsigned char d;
	unsigned char h;

	unsigned char f;
	unsigned char c;
	unsigned char e;
	unsigned char l;

	unsigned short sp;
	unsigned short pc;
} registers;


typedef enum {
	INVALID, //invalid base case
	NO_OP, LD_BC, LD_BC_A, INC_BC, INC_B, DEC_B, LD_B, RLCA, //0x00 - 0x07
	LD_SP_TO, ADD_HL_BC, LD_A_BC, DEC_BC, INC_C, DEC_C, LD_C, RRCA, //0x08 - 0x0F
	STOP, LD_DE, LD_DE_A, INC_DE, INC_D, DEC_D, LD_D, RLA, //0x10 - 0x17
	JR, ADD_HL_DE, LD_A_DE, DEC_DE, INC_E, DEC_E, LD,E, RRA, //0x18 - 0x1F
	JR_NZ, LD_HL, LD_HL_INC_A, INC_HL, INC_H, DEC_H, LD_H, DAA, //0x21 - 0x27
	JR_Z, ADD_HL_HL, LD_A_HL_INC, DEC_HL, INC_L, DEC_L, LD_L, CPL, //0x28 - 0x2F

	LD_SP, //load stack pointer with a value
	LD_HL_DEC_A,

	XOR_A,

	//extended ops
	BIT_7H

} opcode;

//write 1 byte to memory (8 bits). Most memory writes are this
void writeToMemory_8(unsigned char address, unsigned char data);

void printRegisters(registers *regs);

void initRegisters(registers *regs);

void executeInstruction(registers *regs, opcode op, const char *program);

opcode decodeInstruction(const char op, const char nextop);

#endif