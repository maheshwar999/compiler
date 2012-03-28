#ifndef _asm
#define _asm

#include"ast.h"

void generateCode();
void printStmt(astPointer head);
void printExpr(astPointer head);
void writeFuns();
#endif 
