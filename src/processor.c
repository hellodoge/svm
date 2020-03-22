#include "processor.h"

#include <stdint.h>
#include <stdlib.h>
#include "vm_memory.h"
#include "constants.h"
#include "stdio.h"

void exec() {
	uint8_t interrupted = 0;
	do {
		if (reg[R_PC] >= segments.data) {
			puts("Segmentation fault");
			exit(-4);
		}
		uint16_t instr = get_word(reg[R_PC]);
		reg[R_PC] += 2;
		uint16_t term = GET_MODE(instr) ? GET_TERM(instr) : reg[GET_R2(instr)];
		switch (GET_OP(instr)) {
			case OP_ADD:
				reg[R_FLAGS] = reg[GET_R1(instr)] > UINT16_MAX - term ? FL_OVERFLOW : FL_SUCCESS;
				reg[GET_R1(instr)] += term;
				break;
			case OP_SUB:
				reg[R_FLAGS] = reg[GET_R1(instr)] < term ? FL_OVERFLOW : FL_SUCCESS;
				reg[GET_R1(instr)] -= term;
				break;
			case OP_MUL:
				reg[GET_R1(instr)] *= term;
				break;
			case OP_DIV:
				reg[GET_R1(instr)] /= term;
				break;
			case OP_MOD:
				reg[GET_R1(instr)] %= term;
				break;
			case OP_AND:
				reg[GET_R1(instr)] &= term;
				break;
			case OP_OR:
				reg[GET_R1(instr)] |= term;
				break;
			case OP_CMP:
				if (reg[GET_R1(instr)] > term)
					reg[R_FLAGS] = FL_HIGHER;
				else if (reg[GET_R1(instr)] < term)
					reg[R_FLAGS] = FL_LOWER;
				else if (reg[GET_R1(instr)] == term)
					reg[R_FLAGS] = FL_EQUAL;
				break;
			case OP_NOT:
				if (GET_MODE(instr)) reg[GET_R1(instr)] = ~reg[GET_R2(instr)];
				else reg[GET_R1(instr)] = reg[GET_R1(instr)] ? 0 : 1;
				break;
			case OP_LDR:
				if (GET_MODE(instr)) {
					reg[GET_R1(instr)] = get_word(reg[GET_R2(instr)]);
				} else {
					uint16_t pos = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					reg[GET_R1(instr)] = get_word(pos);
				}
				break;
			case OP_STR:
				if (GET_MODE(instr)) {
					set_word(reg[GET_R2(instr)], reg[GET_R1(instr)]);
				} else {
					uint16_t pos = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					set_word(pos, reg[GET_R1(instr)]);
				}
				break;
			case OP_MOV:
				if (GET_MODE(instr)) {
					reg[GET_R1(instr)] = reg[GET_R2(instr)];
				} else {
					uint16_t value = get_word(reg[R_PC]);
					reg[R_PC] += 2;
					reg[GET_R1(instr)] = value;
				}
				break;
			case OP_PUSH:
				set_word(reg[R_SP], reg[GET_R1(instr)]);
				reg[R_SP] -= 2;
				if (reg[R_SP] <= reg[R_HP]) reg[R_FLAGS] = FL_MEMERR;
				break;
			case OP_POP:
				reg[R_SP] += 2;
				reg[GET_R1(instr)] = get_word(reg[R_SP]);
				break;
			case OP_JMP:
				if (GET_TERM(instr) == UINT8_MAX || GET_TERM(instr) == reg[R_FLAGS])
					reg[R_PC] = GET_MODE(instr) ? reg[GET_R1(instr)] : get_word(reg[R_PC]);
				else if (!GET_MODE(instr)) reg[R_PC] += 2;
				break;
			case OP_TRAP:
				interrupted = 1;
				break;
		}
	} while (!interrupted);
}