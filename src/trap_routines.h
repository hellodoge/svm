#ifndef SVM_TRAP_ROUTINES_H
#define SVM_TRAP_ROUTINES_H

enum {
	TRAP_EXIT = 0,
	TRAP_PRINT_STR,
	TRAP_PRINT_INT,
	TRAP_PUTCHAR,
	TRAP_GETINT,
};

void handle_trap_routine();

#endif //SVM_TRAP_ROUTINES_H
