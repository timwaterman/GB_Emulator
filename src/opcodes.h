/*
Tim Waterman
26 December 2015
OpCode Header
*/

#ifndef __OPCODES_H__
#define __OPCODES_H__

typedef struct memory {
	char a;
	short pc;
	short sp;
} registers;

void initRegisters(registers *regs);

#endif