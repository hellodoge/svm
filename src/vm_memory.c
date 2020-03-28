#include "vm_memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "constants.h"

uint8_t memory[UINT16_MAX];
vm_memory_t segments;

uint16_t reg[R_COUNT];

uint16_t get_word(uint16_t pos) {
	return *(uint16_t*)(memory + pos);
}

void terminate_if_read_only(uint16_t pos) {
	if (pos < segments.data) {
		puts("Segmentation fault");
		exit(-3);
	}
}

void set_word(uint16_t pos, uint16_t value) {
	terminate_if_read_only(pos);
	*((uint16_t*)(memory+pos)) = value;
}

void set_byte(uint16_t pos, uint8_t value) {
	terminate_if_read_only(pos);
	*((uint8_t*)(memory+pos)) = value;
}

void load_image(char *path) {
	FILE *fp;
	fp = fopen(path,"rb");
	fread(&segments.data, sizeof(uint16_t),1,fp);
	fread(&segments.bss, sizeof(uint16_t),1,fp);
	fread(&segments.heap, sizeof(uint16_t),1,fp);
	fread(memory,UINT16_MAX,1,fp);
	fclose(fp);
	reg[R_SP] = UINT16_MAX;
	reg[R_HP] = segments.heap;
}