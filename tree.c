/*
********************
 Batch #47
 Members:-
 			2008A7PS103 - G.Manjunath
 			2008A7PS124 - R.Maheshwar Reddy
 *********************
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"tree.h"

extern char tokens[62][30];
treePointer createNode(int id)
{
	treePointer tmp;
	tmp=malloc(sizeof(struct treeNode));
	tmp->id=id;
	strcpy(tmp->tk.token_name,tokens[id]);
	tmp->parent=NULL;
	tmp->leftChild=NULL;
	tmp->rightSib=NULL;
	
	return tmp;
}

void addNode(treePointer parent,treePointer current)
{	
	current->parent=parent;
	current->rightSib=parent->leftChild;
	parent->leftChild=current;
}
	
