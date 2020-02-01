#ifndef SVM_INTERRUPT_H
#define SVM_INTERRUPT_H

#include <stdio.h>
#include "virtual_memory.h"
#include "constants.h"

void handle_interrupt() {
	switch (reg[R_AX]) {
		case TRAP_PRINT_STR:
			printf("%s", (char*)&memory[reg[R_BX]]);
			break;
		case TRAP_PRINT_INT:
			printf("%d", reg[R_BX]);
			break;
		case TRAP_PUTCHAR:
			putchar(reg[R_BX]);
			break;
		case TRAP_EXIT:
			exit(reg[R_BX]);
	}
}

#endif //SVM_INTERRUPT_H
