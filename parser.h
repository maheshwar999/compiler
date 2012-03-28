#ifndef _parser
#define _parser

#include"scanner.h"
#include"tree.h"


typedef enum{
TK_KEY_PRINT, 	//0
TK_KEY_GET,		//1
TK_KEY_RETURN, 	//2
TK_KEY_BEGIN,	//3
TK_KEY_END,   	//4
TK_KEY_WHILE, 	//5
TK_KEY_IF,    	//6
TK_KEY_FUN, 	//7
TK_KEY_VAR,   	//8
TK_KEY_NONE, 	//9
TK_KEY_IN,   	//10
TK_KEY_OUT, 	//11
TK_KEY_MAIN, 	//12
TK_KEY_LET,		//13
TK_KEY_BE,		//14
TK_KEY_MODULO,	//15
TK_ID,			//16
TK_NUM, 		//17
TK_OPEN,		//18
TK_CLOSE, 		//19
TK_SEMI,		//20
TK_EQUAL,		//21
TK_NOTEQUAL,	//22
TK_LT,			//23
TK_GT,			//24
TK_LEQ, 		//25
TK_GEQ,			//26
TK_COMMA, 		//27
TK_COLON,		//28
e,				//29
TK_KEY_PLUS,	//30
TK_KEY_MINUS, 	//31
TK_KEY_MUL,		//32
TK_KEY_DIV,		//33

Programs=35,	//35
Functions,		//36
MainFun,		//37
OtherFuns,		//38
Funct,			//39
Parameters,		//40
InList,			//41
IDList,			//42
RemID,			//43
OutID,			//44
FunBody,		//45
Declarations,	//46
Declaration,	//47
OtherStatements,//48
Theta,			//49
Statement,		//50
AssignmentStmt,	//51
Alpha,			//52
ExprOrFunc,		//53
Expression,		//54
FunctionCall,	//55
ConditionalStmt,//56
BoolExp,		//57
Type,			//58
RepetitiveStmt,	//59
ReturnStmt,		//60
IO_Stmt			//61
} token_id;




void initializeParser(char *filename);
ParseTree parse();
void printParseTree(FILE f);
int isTerminal(token_id id);
void print(treePointer tp);

#endif
