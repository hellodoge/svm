#ifndef SVM_VIRTUAL_MEMORY_H
#define SVM_VIRTUAL_MEMORY_H

#include <stdint.h>
#include "constants.h"

#define GET(word,pos,len) ((word) >> (16 - (pos) - (len)) & 0xFFFF >> (16 - (len)))

typedef struct virtual_memory {
	uint16_t stack, heap;
	uint16_t stack_size, heap_size;
	uint16_t text, data, bss;
} virtual_memory_t;

uint8_t memory[UINT16_MAX];
virtual_memory_t segments;

uint16_t reg[R_COUNT];

uint16_t get_word(uint16_t pos) {
	return *(uint16_t*)(memory + pos);
}

void set_word(uint16_t pos, uint16_t value) {
	*((uint16_t*)(memory+pos)) = value;
}

#endif //SVM_VIRTUAL_MEMORY_H
