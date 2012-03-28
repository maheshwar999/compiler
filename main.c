/*
********************
 Batch #47
 Members:-
 			2008A7PS103 - G.Manjunath
 			2008A7PS124 - R.Maheshwar Reddy
 *********************
*/

#include<stdio.h>
#include"scanner.h"
#include"parser.h"
#include"ast.h"
#include"SymbolTable.h"
#include"asm.h"

int main(int argc,char *argv[])
{
		FILE *fscannerIn,fscannerOut,*fparserOut;
		extern FILE *temp;
		extern int end;
		initializeScanner(argv[1]);
		
		printTokenStream(fscannerOut);
		
		if(end==1)
		initializeParser("outputParser.txt");
		
		extern ParseTree p;
		if(end==1)
		{
			fillSymbolTable(p);
			createAst();
			generateCode();
		}
		
		return 0;
		
}
