#include "virtual_memory.h"
#include "processor.h"
#include "interrupt.h"

int main(int argc, char** argv) {

	if (!argc) {
		puts("usage: svm [image]");
		return -1;
	}

	load_image(argv[argc - 1]);

	do {
		exec();
		handle_interrupt();
	} while (reg[R_PC] <= segments.text);
	return -2;
}