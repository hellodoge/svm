#include "vm_malloc.h"

#include <stdint.h>
#include "vm_memory.h"

block_t blocks[BLOCKS_LEN];
uint8_t counter = 0;


block_t* new_block(uint16_t size) {
	block_t *best = blocks;
	for (uint8_t i = 0; i < counter; i++) {
		if (blocks[i].size >= size) {
			if (blocks[i].size < best->size || best->size < size)
				best = &blocks[i];
		}
	}
	if (!counter || best->size < size) {
		if (reg[R_SP] - reg[R_HP] < size) return 0;
		best = &blocks[counter];
		blocks[counter].ptr = reg[R_HP];
		blocks[counter++].size = size;
		reg[R_HP] += size;
	}

	return best;
}

uint16_t vm_malloc(uint16_t size) {
	size += HEADER;
	block_t *block = new_block(size);
	if (!block) return 0;

	uint16_t ptr = block->ptr + HEADER;

	set_word(block->ptr, size);
	block->ptr += size;
	block->size -= size;

	if (!block->size) {
		*block = blocks[--counter];
	}

	return ptr;
}

void vm_free(uint16_t ptr) {
	ptr = ptr - HEADER;
	uint16_t size = get_word(ptr);

	block_t *prev = 0, *next = 0;
	for (uint8_t i = 0; i < counter; i++) {
		if (blocks[i].ptr + blocks[i].size == ptr)
			prev = &blocks[i];
		else if (ptr + size == blocks[i].ptr)
			next = &blocks[i];
		if (next && prev) break;
	}

	if (next)
		size += next->size;

	if (prev) {
		prev->size += size;
	} else {
		blocks[counter].ptr = ptr;
		blocks[counter++].size = size;
	}

	if (next)
		*next = blocks[--counter];
}