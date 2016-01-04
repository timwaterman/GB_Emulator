/*
Tim Waterman
26 December 2015
OpCode Header
*/

#ifndef __OPCODES_H__
#define __OPCODES_H__

#define ZERO_FLAG 0x80
#define SUBTRACT_FLAG 0x40
#define HALF_CARRY_FLAG 0x20
#define CARRY_FLAG 0x10

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
	JR_NZ, LD_HL, LD_HL_INC_A, INC_HL, INC_H, DEC_H, LD_H, DAA, //0x20 - 0x27
	JR_Z, ADD_HL_HL, LD_A_HL_INC, DEC_HL, INC_L, DEC_L, LD_L, CPL, //0x28 - 0x2F
	JR_NC, LD_SP, LD_HL_DEC_A, INC_SP, INC_HL_REF, DEC_HL_REF, LD_HL_8, SCF, //0x30 - 0x37
	JR_C, ADD_HL_SP, LD_A_HL_DEC, DEC_SP, INC_A, DEC_A, LD_A, CCF, //0x38 - 0x3F

	LD_B_B, LD_B_C, LD_B_D, LD_B_E, LD_B_H, LD_B_L, LD_B_HL, LD_B_A, //0x40 - 0x47
	LD_C_B, LD_C_C, LD_C_D, LD_C_E, LD_C_H, LD_C_L, LD_C_HL, LD_C_A, //0x48 - 0x4F
	LD_D_B, LD_D_C, LD_D_D, LD_D_E, LD_D_H, LD_D_L, LD_D_HL, LD_D_A, //0x50 - 0x57
	LD_E_B, LD_E_C, LD_E_D, LD_E_E, LD_E_H, LD_E_L, LD_E_HL, LD_E_A, //0x58 - 0x5F
	LD_H_B, LD_H_C, LD_H_D, LD_H_E, LD_H_H, LD_H_L, LD_H_HL, LD_H_A, //0x60 - 0x67
	LD_L_B, LD_L_C, LD_L_D, LD_L_E, LD_L_H, LD_L_L, LD_L_HL, LD_L_A, //0x68 - 0x6F
	LD_HL_B, LD_HL_C, LD_HL_D, LD_HL_E, LD_HL_H, LD_HL_L, HALT, LD_HL_A, //0x70 - 0x77
	LD_A_B, LD_A_C, LD_A_D, LD_A_E, LD_A_H, LD_A_L, LD_A_HL, LD_A_A, //0x78 - 0x7F

	ADD_A_B, ADD_A_C, ADD_A_D, ADD_A_E, ADD_A_H, ADD_A_L, ADD_A_HL, ADD_A_A, //0x80 - 0x87
	ADC_A_B, ADC_A_C, ADC_A_D, ADC_A_E, ADC_A_H, ADC_A_L, ADC_A_HL, ADC_A_A, //0x88 - 0x8F
	SUB_B, SUB_C, SUB_D, SUB_E, SUB_H, SUB_L, SUB_HL, SUB_A, //0x90 - 0x97
	SBC_A_B, SBC_A_C, SBC_A_D, SBC_A_E, SBC_A_H, SBC_A_L, SBC_A_HL, SBC_A_A, //0x98 - 0x9F
	AND_B, AND_C, AND_D, AND_E, AND_H, AND_L, AND_HL, AND_A, //0xA0 - 0xA7
	XOR_B, XOR_C, XOR_D, XOR_E, XOR_H, XOR_L, XOR_HL, XOR_A, //0xA8 - 0xAF
	OR_B, OR_C, OR_D, OR_E, OR_H, OR_L, OR_HL, OR_A, //0xB0 - 0xB7
	CP_B, CP_C, CP_D, CP_E, CP_H, CP_L, CP_HL, CP_A, //0xB8 - 0xBF

	RET_NZ, POP_BC, JP_NZ, JP, CALL_NZ, PUSH_BC, ADD_A, RST_0, //0xC0 - 0xC7
	RET_Z, RET, JP_Z, EXT, CALL_Z, CALL, ADC_A, RST_8, //0xC8 - 0xCF
	RET_NC, POP_DE, JP_NC, /*No D3,*/ CALL_NC, PUSH_DE, SUB, RST_10, //0xD0 - 0xD7
	RET_C, RETI, JP_C, /*No DB,*/ CALL_C, /*No DD,*/ SBC_A, RST_18, //0xD8 - 0xDF
	LDH_ADDR_A, POP_HL, LD_C_ADDR_A, /*No E3 - E4,*/ PUSH_HL, AND, RST_20, //0xE0 - 0xE7
	ADD_SP, JP_HL, LD_ADDR_A, /*No EB - ED,*/ XOR, RST_28, //0xE8 - 0xEF
	LDH_A, POP_AF, LD_A_ADDR_C, DI, /*No F4,*/ PUSH_AF, OR, RST_30, //0xF0 - 0xF7
	LD_HL_SP, LD_SP_HL, LD_A_16, EI, /*No FC-FD,*/ CP, RST_38, //0xF8 - 0xFF   

	//extended ops
	RL_C, BIT_7H

} opcode;

void clearFlags(registers *regs, unsigned char flags);
void setFlags(registers *regs, unsigned char flags);

void loadLogo();

//write 1 byte to memory (8 bits). Most memory writes are this
void writeToMemory_8(unsigned short address, unsigned char data);

void printRegisters(registers *regs);

void initRegisters(registers *regs);

void executeInstruction(registers *regs, opcode op, const char *program);


//FETCHING AND DECODING FUNCTIONS
opcode fetchInstruction_03(const char op);
opcode fetchInstruction_47(const char op);
opcode fetchInstruction_8B(const char op);
opcode fetchInstruction_CF(const char op);
opcode fetchInstruction_ext(const char nextop);

opcode decodeInstruction(const char op, const char nextop);

#endif