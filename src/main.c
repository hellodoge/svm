#include <stdio.h>
#include "vm_memory.h"
#include "processor.h"
#include "trap_routines.h"

int main(int argc, char** argv) {

	if (argc < 2) {
		puts("usage: svm [image]");
		return -1;
	}

	load_image(argv[argc - 1]);

	do {
		exec();
		handle_trap_routine();
	} while (reg[R_PC] <= segments.data);
	return -2;
}