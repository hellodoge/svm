#ifndef SVM_INTERRUPT_H
#define SVM_INTERRUPT_H

#include <stdio.h>
#include "virtual_memory.h"
#include "constants.h"

void handle_interrupt() {
	switch (reg[R_AX]) {
		case TRAP_PUTS:
			puts((char*)&memory[reg[R_BX]]);
			break;
		case TRAP_EXIT:
			exit(reg[R_BX]);
	}
}

#endif //SVM_INTERRUPT_H
