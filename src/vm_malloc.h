#ifndef SVM_VM_MALLOC_H
#define SVM_VM_MALLOC_H

#include <stdint.h>

#define HEADER 2
#define BLOCKS_LEN 128

typedef struct block {
	uint16_t ptr;
	uint16_t size;
} block_t;


uint16_t vm_malloc(uint16_t size);
void vm_free(uint16_t ptr);

#endif //SVM_VM_MALLOC_H
