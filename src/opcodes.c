#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

/*
Implementation of register init
and of opcode checking will go in here
Want to always pass around struct * so 
that the access is quicker
*/

void initRegisters(registers *regs) {

	regs->sp = 0;
	regs->pc = 0;
	regs->a = 0;
}