#ifndef SVM_INSTRUCTION_HANDLER_H
#define SVM_INSTRUCTION_HANDLER_H

#include <stdlib.h>
#include <stdint.h>
#include "virtual_memory.h"
#include "constants.h"

typedef struct instruction {
	uint8_t operation;
	uint8_t mode;
	uint8_t reg1;
	uint8_t reg2;
	uint8_t term;
} instr_t;

instr_t* process(uint16_t instr) {
	instr_t *processed = malloc(sizeof(instr_t));
	processed->operation = GET(instr, 0, 4);
	processed->reg1 = GET(instr, 4, 3);
	processed->mode = GET(instr, 7, 1);
	processed->reg2 = GET(instr, 8, 3);
	processed->term = GET(instr, 8, 8);
	return processed;
}

#endif //SVM_INSTRUCTION_HANDLER_H
