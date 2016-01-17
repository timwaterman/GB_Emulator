/*
Tim Waterman
28 December 2015
OpCode Source code
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opcodes.h"

extern unsigned char *memoryspace;

void clearFlags(registers *regs, unsigned char flags) {

	if (flags & ZERO_FLAG)
		regs->f = regs->f & ~ZERO_FLAG;

	if (flags & SUBTRACT_FLAG)
		regs->f = regs->f & ~SUBTRACT_FLAG;

	if (flags & HALF_CARRY_FLAG)
		regs->f = regs->f & ~HALF_CARRY_FLAG;

	if (flags & CARRY_FLAG)
		regs->f = regs->f & ~CARRY_FLAG;

}

void setFlags(registers *regs, unsigned char flags) {

	if (flags & ZERO_FLAG)
		regs->f = regs->f | ZERO_FLAG;

	if (flags & SUBTRACT_FLAG)
		regs->f = regs->f | SUBTRACT_FLAG;

	if (flags & HALF_CARRY_FLAG)
		regs->f = regs->f | HALF_CARRY_FLAG;

	if (flags & CARRY_FLAG)
		regs->f = regs->f | CARRY_FLAG;

}

/*
Function to hardcode the Nintendo logo in memory
Only useful for testing. Will be removed.
*/
void loadLogo() {

	unsigned int i = 0x104; //starting address

	memoryspace[i++] = 0xCE;
	memoryspace[i++] = 0xED;
	memoryspace[i++] = 0x66;
	memoryspace[i++] = 0x66;
	memoryspace[i++] = 0xCC;
	memoryspace[i++] = 0x0D;
	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x0B;
	memoryspace[i++] = 0x03;
	memoryspace[i++] = 0x73;
	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x83;
	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x0C; //end of first row

	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x0D;
	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x08;
	memoryspace[i++] = 0x11;
	memoryspace[i++] = 0x1F;
	memoryspace[i++] = 0x88;
	memoryspace[i++] = 0x89;
	memoryspace[i++] = 0x00;
	memoryspace[i++] = 0x0E;
	memoryspace[i++] = 0xDC;
	memoryspace[i++] = 0xCC;
	memoryspace[i++] = 0x6E;
	memoryspace[i++] = 0xE6; //end of second row

	memoryspace[i++] = 0xDD;
	memoryspace[i++] = 0xDD;
	memoryspace[i++] = 0xD9;
	memoryspace[i++] = 0x99;
	memoryspace[i++] = 0xBB;
	memoryspace[i++] = 0xBB;
	memoryspace[i++] = 0x67;
	memoryspace[i++] = 0x63;
	memoryspace[i++] = 0x6E;
	memoryspace[i++] = 0x0E;
	memoryspace[i++] = 0xEC;
	memoryspace[i++] = 0xCC;
	memoryspace[i++] = 0xDD; //end of third row

	memoryspace[i++] = 0xDC;
	memoryspace[i++] = 0x99;
	memoryspace[i++] = 0x9F;
	memoryspace[i++] = 0xBB;
	memoryspace[i++] = 0xB9;
	memoryspace[i++] = 0x33;
	
	memoryspace[i] = 0x3E; //last one!

	//fprintf(stderr, "LOGO ENDS AT %03x\n", i);


}

 void writeToMemory_8(unsigned short address, unsigned char data) {

 	fprintf(stderr, "Writing %x to address %x\n", data, address);
 	memoryspace[(unsigned short)address] = data;

 	return;
 }

 void readFromMemory_8(unsigned char *reg, unsigned short address) {

 	*reg = memoryspace[address];

 	return;
 }


void printRegisters(registers *regs) {

	fprintf(stderr, "REGISTERS:\n");
	fprintf(stderr, "SP = %x\n", regs->sp);
	fprintf(stderr, "A = %02x\n", regs->a);
	fprintf(stderr, "B = %02x\n", regs->b);
	fprintf(stderr, "C = %02x\n", regs->c);
	fprintf(stderr, "D = %02x\n", regs->d);
	fprintf(stderr, "E = %02x\n", regs->e);
	fprintf(stderr, "H = %02x\n", regs->h);
	fprintf(stderr, "L = %02x\n", regs->l);
	fprintf(stderr, "F = %02x\n", regs->f);


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
		case INC_B: //0x04, increment B
			clearFlags(regs, SUBTRACT_FLAG);

			if(regs->b == 0xFF)
				setFlags(regs, ZERO_FLAG | HALF_CARRY_FLAG);
			else
				clearFlags(regs, ZERO_FLAG | HALF_CARRY_FLAG);
			regs->b++;
			regs->pc++;
			break;
		case DEC_B: //0x05, decrement B
			regs->b--;
			if (regs->b == 0) {
				setFlags(regs, ZERO_FLAG);
			}
			else
				clearFlags(regs, ZERO_FLAG);

			setFlags(regs, SUBTRACT_FLAG);
			regs->pc++;
			break;
		case LD_B: //0x06 load next byte into register b
			regs->b = (unsigned char)program[regs->pc + 1];
			regs->pc += 2;
			break;
		case INC_C:
			clearFlags(regs, SUBTRACT_FLAG | ZERO_FLAG);
			if (regs->c == 0x0F) //if it would wrap
				setFlags(regs, HALF_CARRY_FLAG);
			regs->c++;

			if (regs->c == 0)
				setFlags(regs, ZERO_FLAG);
			regs->pc++;
			break;
		case DEC_C:
			clearFlags(regs, ZERO_FLAG | HALF_CARRY_FLAG);
			regs->c--;

			if(regs->c == 0)
				setFlags(regs, ZERO_FLAG);

			regs->pc++;
			break;
		case LD_C:
			regs->c = program[regs->pc + 1];
			regs->pc += 2;
			break;
		case LD_DE:
			regs->d = program[regs->pc + 2];
			regs->e = program[regs->pc + 1];
			regs->pc += 3;
			break;
		case INC_DE:
			if (regs->e != 0xFF)
				regs->e++;
			else {
				regs->d++;
				regs->e = 0x00;
			}
			regs->pc++;
			break;
		case RLA: //0x17 Rotate A left
			clearFlags(regs, ZERO_FLAG | HALF_CARRY_FLAG | SUBTRACT_FLAG);

			if ((regs-> a >> 7) & 1) { //if the msb is one
				setFlags(regs, CARRY_FLAG);
				regs->a = (regs->a << 1) | 1;
			}
			else { //else msb is 0, just shift it left
				regs->a = regs->a << 1;
			}
			regs->pc++;
			break;

		case JR: {
			signed char offset = program[regs->pc + 1];
			regs->pc += 2 + offset;
		}
			break;
		case LD_A_DE: {//0x1A. Load into A addr stored in DE + 0xFF00
			unsigned short high = regs->d;
			unsigned short low = regs->e;
			unsigned short addr = (high << 8) | low;

			readFromMemory_8(&(regs->a), addr);
			regs->pc++;
		}
			break;
		case DEC_E:
			clearFlags(regs, ZERO_FLAG | HALF_CARRY_FLAG);
			setFlags(regs, SUBTRACT_FLAG);
			if (regs->e == 0)
				setFlags(regs, HALF_CARRY_FLAG);
			regs->e--;
			if (regs->e == 0)
				setFlags(regs, ZERO_FLAG);
			regs->pc++;
			break;
		case LD_E: //0x1E, Load next byte into E
			regs->e = (unsigned char)program[regs->pc + 1];
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
		case LD_HL_INC_A: {//0x22, load A into address stored in, then increment the address
			unsigned short high = regs->h;
			unsigned short low = regs->l;
			unsigned short addr = (high << 8) | low;

			writeToMemory_8(addr, regs->a);
			if (regs->l == 0xFF) {//if we're at the upper limit of l, wrap around
				regs->h++;
				regs->l = 0x00;
			}
			else
				regs->l++;

			regs->pc++;
		}
		break;
		case INC_HL:
			if(regs->l != 0xFF)
				regs->l++;
			else {
				regs->h++;
				regs->l = 0x00;
			}
			regs->pc++;
			break;
		case INC_H:
			clearFlags(regs, SUBTRACT_FLAG | HALF_CARRY_FLAG | ZERO_FLAG);
			if (regs->h == 0xFF) {
				setFlags(regs, HALF_CARRY_FLAG | ZERO_FLAG);
			}
			regs->h++;
			regs->pc++;
			break;
		case JR_Z: {//0x28, jump if ZEROFLAG is set
			signed char offset = program[regs->pc + 1];

			if ((regs->f >> 7) & 1)
				regs->pc += 2 + offset;
			else
				regs->pc += 2;
		}
			break;
		case LD_L: //0x2E, LOAD INTO L
			regs->l = program[regs->pc + 1];
			regs->pc += 2;
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
		case DEC_A:
			setFlags(regs, SUBTRACT_FLAG);
			regs->a--;

			if (regs->a == 0)
				setFlags(regs, ZERO_FLAG);
			else
				clearFlags(regs, ZERO_FLAG);

			regs->pc++;
			break;
		case LD_A: //0x3E
			regs->a = program[regs->pc + 1];
			regs->pc += 2;
			break;
		case LD_C_A://0x4F, load contents of A into C
			regs->c = regs->a;
			regs->pc++;
			break;
		case LD_D_A: //0x57, load A into D
			regs->d = regs->a;
			regs->pc++;
			break;
		case LD_H_A: //0x67, load A into H
			regs->h = regs->a;
			regs->pc++;
			break;
		case LD_HL_A: {
			unsigned short high = regs->h;
			unsigned short low = regs->l;
			unsigned short addr = (high << 8) | low;

			writeToMemory_8(addr, regs->a);
			regs->pc++;
		}
			break;
		case LD_A_E:
			regs->a = regs->e;
			regs->pc++;
			break;
		case LD_A_H:
			regs->a = regs->h;
			regs->pc++;
			break;
		case SUB_B:
			setFlags(regs, SUBTRACT_FLAG);
			clearFlags(regs, HALF_CARRY_FLAG | ZERO_FLAG | CARRY_FLAG);

			if ( ((regs->a&0xF) - (regs->b&0xF)) == 0x10) //if we have a half carry
				setFlags(regs, HALF_CARRY_FLAG);

			//TODO: Implement carry flag

			regs->a = regs->a - regs->b;

			if(regs->a == 0)
				setFlags(regs, ZERO_FLAG);

			regs->pc++;
			break;
		case XOR_A: //0xAF, XOR Register A
			clearFlags(regs, SUBTRACT_FLAG | HALF_CARRY_FLAG | CARRY_FLAG);
			regs->a ^= regs->a;

			if (!regs->a)
				setFlags(regs, ZERO_FLAG);
			(regs->pc)++;
			break;
		case BIT_7H: //0xCB7C, check high bit of H
			clearFlags(regs, SUBTRACT_FLAG);
			setFlags(regs, HALF_CARRY_FLAG);
			if( (regs->h >> 7) & 1) { //if it's one, clear the zero flag
				//regs->f = ((regs->f >> 7) & 0) << 7; 
				clearFlags(regs, ZERO_FLAG);
			}
			else {
				//regs->f = ((regs->f >> 7) | 1) << 7; //zero flag is on
				setFlags(regs, ZERO_FLAG);
			}

			regs->pc += 2;
			break;
		case POP_BC: //0xC1, pop BC from the stack
			regs->c = memoryspace[regs->sp];
			regs->b = memoryspace[regs->sp + 1];
			regs->sp += 2;
			regs->pc++;
			break;
		case PUSH_BC: //0xC5, push BC onto the stack, B first, then C
			memoryspace[regs->sp - 1] = regs->b;
			memoryspace[regs->sp - 2] = regs->c;
			regs->sp -= 2;
			regs->pc++;
			break;
		case RET: {//return from function, get the old pc from the top of the stack
			unsigned char lo = memoryspace[regs->sp] & 0x00FF;
			unsigned char hi = (memoryspace[regs->sp + 1] & 0xFF00) >> 4;
			unsigned short slow = lo;
			unsigned short shigh = hi;
			unsigned short oldpc = (shigh << 8) | slow;
			regs->sp += 2;
			regs->pc = oldpc;
		}
		break;
		case CALL: { //we need to store the next pc in sp - 1 and sp - 2, then move the sp down 2
			//we then will move the current pc to the address given in the next 16 bit value
			regs->pc += 3; //go to next instruction
			unsigned short loc = regs->pc;
			unsigned char hi = (loc & 0xFF00) >> 4; //take the upper half
			unsigned char lo = loc & 0x00FF; //take the lower half
			writeToMemory_8(regs->sp - 1, hi);
			writeToMemory_8(regs->sp - 2, lo);
			regs->sp -= 2;
			regs->pc -= 3;
			unsigned char low = program[regs->pc + 1];
			unsigned char high = program[regs->pc + 2];
			hi = high;
			lo = low;
			unsigned short addr = (hi << 8) | lo;
			regs->pc = addr; //use the address starting from the original pc + 1
			//fprintf(stderr, "Setting PC to %u\n", regs->pc);
		}
			break;
		case LDH_ADDR_A: {//load A into the 8-bit address given (+ 0xFF00)
			unsigned short addr = 0xFF00 + (unsigned char)program[regs->pc + 1];
			writeToMemory_8(addr, regs->a);
			regs->pc += 2;
		}
			break;
		case LD_C_ADDR_A: {//load contents of A into addr inside C + 0xFF00
			unsigned short addr = 0xFF00 + regs->c;
			writeToMemory_8(addr, regs->a);
			regs->pc++;
		}
			break;
		case RL_C: {//rotate C left through carry flag, which will hold old bit 7
			unsigned char msb = (regs->c >> 7) & 1;
			clearFlags(regs, HALF_CARRY_FLAG | SUBTRACT_FLAG);

			//if msb is 1, set the carry flag
			if (msb)
				setFlags(regs, CARRY_FLAG);

			regs->c = (regs->c << 1) | msb; //shift it to the left, wrap around msb

			//if C is now zero, set the zero flag
			if(regs->c == 0)
				setFlags(regs, ZERO_FLAG);

			regs->pc += 2;

		}
			break;

		case LD_ADDR_A: {
			//grab high and low bits of the address
			unsigned char low = program[regs->pc + 1];
			unsigned char high = program[regs->pc + 2];

			unsigned short lo = low;
			unsigned short hi = high;
			unsigned short addr = (hi << 8) | lo;
			writeToMemory_8(addr, regs->a);
			regs->pc += 3;
		}
			break;
		case LDH_A: {//0xF0, load value located at pc + 1 + $FF00 into A
			unsigned short addr = program[regs->pc + 1] + 0xFF00;
			readFromMemory_8(&regs->a, addr);
			regs->pc += 2;
		}
		break;
		 case CP: //compare value given next to register A, set ZFLAG if equal
		 	clearFlags(regs, SUBTRACT_FLAG | ZERO_FLAG);
		 	if( (unsigned char)program[regs->pc + 1] == regs->a)
		 		setFlags(regs, ZERO_FLAG);

		 	regs->pc += 2;
		 	break;
		default:
			fprintf(stderr, "OPCODE %02x Not yet implemented\n", (unsigned char)program[regs->pc]);
			exit(1);
	}//end main switch

		return;
}

/*--------------------------------------------------*
* Start of OpCode decoding functions.  				*
* There are 5 functions, each that will decode 		*
* a specific section of the opcode table. Each 		*
* function deals with 64 specific opcodes, as 		*
* designated by the range in its suffix				*
*---------------------------------------------------*/

// Matches instructions with opcodes 0x00 - 0x3F
opcode fetchInstruction_03(const char op) {

	unsigned char hex = op;

	switch (hex) {
		case 0x04:
			fprintf(stderr, "INC B\n");
			return INC_B;
			break;
		case 0x05:
			fprintf(stderr, "DEC B\n");
			return DEC_B;
			break;
		case 0x06:
			fprintf(stderr, "LD B\n");
			return LD_B;
			break;
		case 0x0C:
			fprintf(stderr, "INC C\n");
			return INC_C;
			break;
		case 0x0D:
			fprintf(stderr, "DEC C\n");
			return DEC_C;
			break;
		case 0x0E:
			fprintf(stderr, "LD C\n");
			return LD_C;
			break;
		case 0x11:
			fprintf(stderr, "LD DE\n");
			return LD_DE;
			break;
		case 0x13:
			fprintf(stderr, "INC DE\n");
			return INC_DE;
			break;
		case 0x17:
			fprintf(stderr, "RLA\n");
			return RLA;
			break;
		case 0x18:
			fprintf(stderr, "JR\n");
			return JR;
			break;
		case 0x1A:
			fprintf(stderr, "LD A DE\n");
			return LD_A_DE;
			break;
		case 0x1D:
			fprintf(stderr, "DEC E\n");
			return DEC_E;
			break;
		case 0x1E:
			fprintf(stderr, "LD E\n");
			return LD_E;
			break;
		case 0x20:
			fprintf(stderr, "JR NZ\n");
			return JR_NZ;
			break;
		case 0x21:
			fprintf(stderr, "LD HL\n");
			return LD_HL;
			break;
		case 0x22:
			fprintf(stderr, "LD HL INC A\n");
			return LD_HL_INC_A;
			break;
		case 0x23:
			fprintf(stderr, "INC HL\n");
			return INC_HL;
			break;
		case 0x24:
			fprintf(stderr, "INC H\n");
			return INC_H;
			break;
		case 0x28:
			fprintf(stderr, "JR Z\n");
			return JR_Z;
			break;
		case 0x2E:
			fprintf(stderr, "LD L\n");
			return LD_L;
			break;
		case 0x31:
			fprintf(stderr, "LD SP\n");
			return LD_SP;
			break;
		case 0x32:
			fprintf(stderr, "LD_HL_DEC_A\n");
			return LD_HL_DEC_A;
			break;
		case 0x3D:
			fprintf(stderr, "DEC A\n");
			return DEC_A;
			break;
		case 0x3E:
			fprintf(stderr, "LD A\n");
			return LD_A;
			break;
		default:
			break;
		}

	return INVALID;
}

// Matches instructions with opcodes 0x40 - 0x7F
opcode fetchInstruction_47(const char op) {

	unsigned char hex = op;

	switch (hex) {
		case 0x4F:
			fprintf(stderr, "LD C <- A\n");
			return LD_C_A;
			break;
		case 0x57:
			fprintf(stderr, "LD D A\n");
			return LD_D_A;
			break;
		case 0x67:
			fprintf(stderr, "LD H A\n");
			return LD_H_A;
			break;
		case 0x77:
			fprintf(stderr, "LD HL A\n");
			return LD_HL_A;
			break;
		case 0x7B:
			fprintf(stderr, "LD A E\n");
			return LD_A_E;
			break;
		case 0x7C:
			fprintf(stderr, "LD A H\n");
			return LD_A_H;
			break;
		default:
			break;
	}

	return INVALID;
}

// Matches instructions with opcodes 0x80 - 0xBF
opcode fetchInstruction_8B(const char op) {

	unsigned char hex = op;

	switch (hex) {
		case 0x90:
			fprintf(stderr, "SUB B\n");
			return SUB_B;
			break;
		case 0xAF:
			fprintf(stderr, "XOR A\n");
			return XOR_A;
			break;
	}

	return INVALID;
}

// Matches instructions with opcodes 0xC0 - 0xFF
// except for 0xCB, which maps to the extended set
opcode fetchInstruction_CF(const char op) {

	unsigned char hex = op;

	switch (hex) {
		case 0xC1:
			fprintf(stderr, "POP BC\n");
			return POP_BC;
			break;
		case 0xC5:
			fprintf(stderr, "PUSH BC\n");
			return PUSH_BC;
			break;
		case 0xC9:
			fprintf(stderr, "RET\n");
			return RET;
			break;
		case 0xCD:
			fprintf(stderr, "CALL\n");
			return CALL;
			break;
		case 0xE0:
			fprintf(stderr, "LDH ADDR A\n");
			return LDH_ADDR_A;
			break;
		case 0xE2:
			fprintf(stderr, "LD C ADDR A\n");
			return LD_C_ADDR_A;
			break;
		case 0xEA:
			fprintf(stderr, "LD ADDR <- A\n");
			return LD_ADDR_A;
			break;
		case 0xF0:
			fprintf(stderr, "LDH A\n");
			return LDH_A;
			break;
		case 0xFE:
			fprintf(stderr, "CP\n");
			return CP;
			break;
		default:
			break;

	}

	return INVALID;
}

// Handles all extended opcodes (may need to break this up)
opcode fetchInstruction_ext(const char nextop) {

	unsigned char next = nextop;

	switch (next) {
		case 0x11:
			fprintf(stderr, "RL C\n");
			return RL_C;
			break;
		case 0x7C:
			fprintf(stderr, "CHECKING BIT 7\n");
			return BIT_7H;
			break;
		default:
			break;
	}

	return INVALID;
}

/*
decodes the instruction, returns the enum opcode
Nextop is only used in the case of an extended operation,
which starts with opcode 0xCB
*/
opcode decodeInstruction(const char op, const char nextop) {

	unsigned char hex = op;

	if (hex >= 0x00 && hex < 0x40) {
		return fetchInstruction_03(op);
	}

	if (hex >= 0x40 && hex < 0x80) {
		return fetchInstruction_47(op);
	}

	if (hex >= 0x80 && hex < 0xC0) {
		return fetchInstruction_8B(op);
	}

	if (hex >= 0xC0 && hex != 0xCB) {
		return fetchInstruction_CF(op);
	}

	return fetchInstruction_ext(nextop);

}

