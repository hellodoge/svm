#include "trap_routines.h"

#include <stdlib.h>
#include <stdio.h>
#include "virtual_memory.h"
#include "constants.h"

extern uint8_t memory[UINT16_MAX];

void handle_trap_routine() {
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
		case TRAP_GETINT: {
			int tmp;
			reg[R_AX] = scanf("%d",&tmp); // NOLINT(cert-err34-c)
			if (!reg[R_AX]) while (getchar() != '\n');
			reg[R_BX] = tmp;
			break;
		}
		case TRAP_EXIT:
			exit(reg[R_BX]);
	}
}