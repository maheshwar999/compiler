#ifndef _tree
#define _tree

#include"scanner.h"

typedef struct treeNode *treePointer;
struct treeNode{
				int id;
				Token tk;
				treePointer parent;
				treePointer leftChild;
				treePointer rightSib;	
				};

typedef struct{
			treePointer root;
			}ParseTree;
			
extern treePointer createNode(int id);
extern void addNode (treePointer parent,treePointer current);

#endif
