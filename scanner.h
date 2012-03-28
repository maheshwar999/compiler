#ifndef _scanner
#define _scanner


typedef struct
{
	char att[50];
	char token_name[50];
	int id;
	int lineNum;
}Token;	

typedef struct
{
	int keylen;
	char token_name[50];
	int id;
	int empty;
}cell;

typedef cell hashtable[120];	



int hash(char *str);
void filltable();
Token nextToken();
void printTokenStream(FILE f);
void initializeScanner(char *filename);

#endif
