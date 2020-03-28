#ifndef SVM_VM_MEMORY_H
#define SVM_VM_MEMORY_H

#include <stdint.h>
#include "constants.h"

typedef struct vm_memory {
	uint16_t stack, heap;
	uint16_t stack_size, heap_size;
	uint16_t text, data, bss;
} vm_memory_t;

extern vm_memory_t segments;

extern uint16_t reg[R_COUNT];

uint16_t get_word(uint16_t pos);
void set_word(uint16_t pos, uint16_t value);
void set_byte(uint16_t pos, uint8_t value);
void load_image(char *path);

#endif //SVM_VM_MEMORY_H
