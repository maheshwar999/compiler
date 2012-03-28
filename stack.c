/*
********************
 Batch #47
 Members:-
 			2008A7PS103 - G.Manjunath
 			2008A7PS124 - R.Maheshwar Reddy
 *********************
*/

#include<stdio.h>
#include"stackOps.h"
#include<stdlib.h>

stack initStack( stack s)
{
	s.head=NULL;
	s.size=0;
	return s;
}

stack push(stack s, int e)
{
	link tmp;
	tmp=malloc(sizeof(struct node));
	tmp->e=e;
	tmp->next=s.head;
	s.head=tmp;
	s.size++;
	
	return s;
}

int top(stack s)
{
	return (s.head->e);
}

int isEmpty(stack s)
{
	return (s.size>0?0:1);
}

stack pop(stack s)
{
	link tmp;
	tmp=s.head;
	if(!isEmpty(s))
	{
		s.head=s.head->next;
		free(tmp);
		s.size--;
	}
	return s;
}

void printStack(stack s)
{
	link tmp;
	tmp=s.head;
	while(tmp!=NULL)
	{
		printf("%d->",tmp->e);
		tmp=tmp->next;
	}
}
