#ifndef SVM_PROCESSOR_H
#define SVM_PROCESSOR_H

#include <stdint.h>
#include <stdlib.h>
#include "instruction_handler.h"
#include "constants.h"
#include "memory.h"

void exec() {
	uint8_t interrupted = 0;
	do {
		uint16_t instruction = get_word(reg[R_PC]);
		instr_t *instr = process(instruction);
		reg[R_PC] += 2;
		uint16_t term = instr->mode ? instr->term : reg[instr->reg2];
		switch (instr->operation) {
			case OP_ADD:
				reg[instr->reg1] += term;
				reg[R_FLAGS] = reg[instr->reg1] > UINT16_MAX - term ? FL_OVERFLOW : FL_SUCCESS;
				break;
			case OP_SUB:
				reg[instr->reg1] -= term;
				reg[R_FLAGS] = reg[instr->reg1] < term ? FL_OVERFLOW : FL_SUCCESS;
				break;
			case OP_MUL:
				reg[instr->reg1] *= term;
				break;
			case OP_DIV:
				reg[instr->reg1] /= term;
				break;
			case OP_MOD:
				reg[instr->reg1] %= term;
				break;
			case OP_AND:
				reg[instr->reg1] &= term;
				break;
			case OP_OR:
				reg[instr->reg1] |= term;
				break;
			case OP_CMP:
				if (reg[instr->reg1] > term)
					reg[R_FLAGS] = FL_HIGHER;
				else if (reg[instr->reg1] < term)
					reg[R_FLAGS] = FL_LOWER;
				else if (reg[instr->reg1] == term)
					reg[R_FLAGS] = FL_EQUAL;
				break;
			case OP_NOT:
				if (instr->mode) reg[instr->reg1] = term ? 0 : 1;
				else reg[instr->reg1] = ~term;
				break;
			case OP_LDR:
				if (instr->mode) {
					reg[instr->reg1] = get_word(reg[instr->reg2]);
				} else {
					uint16_t pos = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					reg[instr->reg1] = get_word(pos);
				}
				break;
			case OP_STR:
				if (instr->mode) {
					set_word(reg[instr->reg1], reg[instr->reg2]);
				} else {
					uint16_t pos = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					set_word(pos, reg[instr->reg1]);
				}
				break;
			case OP_MOV:
				if (instr->mode) {
					reg[instr->reg1] = reg[instr->reg2];
				} else {
					uint16_t value = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					reg[instr->reg1] = value;
				}
				break;
			case OP_PUSH:
				set_word(reg[R_SP], reg[instr->reg1]);
				reg[R_SP] -= 2;
				if (reg[R_SP] <= reg[R_HP]) reg[R_FLAGS] = FL_MEMERR;
				break;
			case OP_POP:
				reg[R_SP] += 2;
				reg[instr->reg1] = get_word(reg[R_SP]);
				break;
			case OP_JMP:
				if (!reg[R_FLAGS])
					reg[R_PC] = instr->mode ? reg[instr->reg1] : get_word(reg[R_PC]);
				break;
			case OP_TRAP:
				interrupted = 1;
				break;
		}
		free(instr);
	} while (!interrupted);
}

#endif //SVM_PROCESSOR_H
