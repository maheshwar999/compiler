#ifndef SymbolTable
#define SymbolTable
#include"tree.h"

typedef enum{var,fun}type;

typedef struct
{
	type t;
	int scope;
	char name[50];
	int ret;
	int count;
	int lineNum;
	char return_var[50];
}Cell;
	
typedef struct  HashNode* HashPtr;

struct HashNode
{
	Cell C;
	HashPtr next;
};

HashPtr HashTable[200];


int hash_s(char str[]);
void insert(char name[],int scope,type t,int lineNum);
void update(treePointer fun_node,int count,int ret_var,char return_var[]);
void getParameters(treePointer root,int scope,treePointer fun_node);
void visit(treePointer root,int scope,treePointer fun_node);
void inorder(treePointer root,int scope,treePointer fun_node);
void getFunbody(treePointer root,int scope,treePointer fun_node);
void fillSymbolTable(ParseTree Pt);
#endif

	
