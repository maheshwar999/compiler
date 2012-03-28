#ifndef _ast
#define _ast

#include"parser.h"

typedef enum{
Program=1,//1
funct,//2
mainFun,//3
Function_Name,//4			//id stores function name
Return_Type,//5				// id stores return type
parameters,//6
declaration,//7
statement,//8
Var,//9
ID,//10						//id
ResultType,//11
tK_KEY_NONE,//12
tK_KEY_VAR,//13				//id
FormalParamList,//14
ID_formalParam,//15			//id
assignmentStmt,//16
conditionalStmt,//17
repetitiveStmt,//18
returnStmt,//19
iO_Stmt ,//20
functionCallStmt,//21
EmptyStmt,//22
NUL,//23
ID_left,//24				//id
Expr,//25
ID_Name,//26				//id
Number,//27
PLUS_Expr,//28
MINUS_Expr,//29
MUL_Expr,//30
DIV_Expr,//31
functionCall,//32
tK_NUM,//33					//id
ID_FunctName,//34			//id
ActualParams,//35
ParamsList,//36
ID_ParamName,//37			//id
boolExp,//38
EqualityExp,//39
NotEqualityExp,//40
LT_Exp,//41
LE_Exp,//42
GT_Exp,//43
GE_Exp,//44
ID_Exp,//45					//id
ID_Left,//46				//id
ID_right,//47				//id
ID_return,//48				//id
INStmt,//49
OUTStmt,//50	
ID_input,//51				//id
ID_output,//52				//id
MOD_Expr	//53
}astToken_id;

typedef struct astNode *astPointer;
struct astNode{
				int type;
				astToken_id id;
				Token tk;
				astPointer leftChild,rightSib,parent;
				};
				
typedef struct {
				astPointer root;
				}astTree;
				
extern astPointer createAstNode (astToken_id id);
extern void createAst ();
extern astPointer createFun(treePointer ptr , astPointer parent);
extern astPointer funBody(treePointer ptr,astPointer parent);
extern astPointer params(treePointer ptr,astPointer parent);
extern astPointer createSt(treePointer stPtr);
extern astPointer crtBoolexp(treePointer boolptr);
extern astPointer crtFunRExpr(treePointer funorExpr);
extern astPointer crtExpr(treePointer expr);
void printAst();
void printASTptr(astPointer rt);


#endif
