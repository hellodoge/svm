#ifndef SVM_PROCESSOR_H
#define SVM_PROCESSOR_H

#define GET(word,pos,len) ((word) >> (16 - (pos) - (len)) & 0xFFFF >> (16 - (len)))
#define GET_OP(instr) (GET(instr, 0, 4))
#define GET_R1(instr) (GET(instr, 4, 3))
#define GET_R2(instr) (GET(instr, 8, 3))
#define GET_MODE(instr) (GET(instr, 7, 1))
#define GET_TERM(instr) (GET(instr, 8, 8))

void exec();

#endif //SVM_PROCESSOR_H
