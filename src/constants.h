#ifndef SVM_CONSTANTS_H
#define SVM_CONSTANTS_H

enum {
	R_AX = 0,
	R_BX,
	R_CX,
	R_DX,
	R_PC,
	R_SP,
	R_HP,
	R_FLAGS,
	R_COUNT
};



enum {
	OP_ADD = 0,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_AND,
	OP_OR,
	OP_CMP,
	OP_NOT,
	OP_LDR,
	OP_STR,
	OP_STB,
	OP_MOV,
	OP_PUSH,
	OP_POP,
	OP_JMP,
	OP_TRAP
};

enum {
	FL_EQUAL = 0,
	FL_LOWER,
	FL_HIGHER,
	FL_SUCCESS,
	FL_OVERFLOW,
	FL_MEMERR,
	FL_DIVISION_BY_ZERO = UINT16_MAX,
};

#endif //SVM_CONSTANTS_H
