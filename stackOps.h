#ifndef _gd1
#define _gd2

typedef struct{
				int i;
				}element;
				
typedef struct node *link;
struct node {
		int e;
		link next;
	};

typedef struct {
		link head;
		int size;
		}stack;


stack initStack (stack s);
stack push(stack s, int e);
int top (stack s);
stack pop (stack s);
int isEmpty(stack s);
void printStack(stack s);

#endif

