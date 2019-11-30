#include "virtual_memory.h"
#include "processor.h"
#include "interrupt.h"

int main() {
	//test
	set_word(0, strtol("1011000000000000", NULL, 2));
	set_word(2, strtol("0000000000000000", NULL, 2));
	set_word(4, strtol("1011010000000000", NULL, 2));
	set_word(6, strtol("0000000000000111", NULL, 2));
	set_word(8, strtol("1010010000000000", NULL, 2));
	set_word(10, strtol("0000011000000000", NULL, 2));
	set_word(12, strtol("1001001000000000", NULL, 2));
	set_word(14, strtol("0000011000000000", NULL, 2));
	set_word(16, strtol("1111000000000000", NULL, 2));
	segments.text = 17;

	do {
		exec();
		handle_interrupt();
	} while (reg[R_PC] <= segments.text);
	return 0;
}