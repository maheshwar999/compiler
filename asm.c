#include<stdio.h>
#include<string.h>
#include"asm.h"

int label=0;

void generateCode()
{
	extern astTree ast;
	FILE *fasm;
	fasm=freopen("asmout.asm","w",stdout);
	
	astPointer tmp1,tmp2;
	tmp1=ast.root->leftChild;
	
	while(tmp1->id !=3)	//for going to mainfunction
	tmp1=tmp1->rightSib;
	
	tmp1=tmp1->leftChild;	//at declarations
	
	printf(".model tiny\n");
	printf(".data\n");
	while(tmp1->id==9)
	{
		printf("%s  DW  0\n",tmp1->leftChild->tk.att);
		tmp1=tmp1->rightSib;
	}
	
	printf(".code\n");
	printf(".startup\n");
	while(tmp1!=NULL)
	{
		printStmt(tmp1);
		tmp1=tmp1->rightSib;
	}
	
	
	printf(".exit\n\n");
	writeFuns();
	fclose(fasm);
}

void printStmt( astPointer head)
{
	
	astPointer temp1,temp2;
	
	if(head->id==INStmt)
	{
		//printf("PUSH AX\n");
		printf("call readin \n");
		printf("MOV [%s] , AX\n",head->leftChild->tk.att);
		//printf("POP AX\n");
	}
	else if(head->id==OUTStmt)
	{
		//printf("PUSH AX\n");
		printf("MOV AX , [%s]\n",head->leftChild->tk.att);
		printf("call printout \n");
		//printf("POP AX\n");
	}
	else if(head->id==assignmentStmt)
	{
		printExpr(head->leftChild->rightSib);
		printf("MOV [%s], AX\n",head->leftChild->tk.att);
	}
	else if(head->id==conditionalStmt)
	{
		printf("MOV AX , %s\n",head->leftChild->leftChild->tk.att);
		printf("MOV BX , %s\n",head->leftChild->leftChild->rightSib->tk.att);
		printf("CMP AX,BX\n");
		
		
		switch(head->leftChild->id)
		{
			case EqualityExp:		printf("JNZ label%d\n",label);
									break;
								
			case NotEqualityExp:	printf("JZ label%d\n",label);
									break;
								
			case LT_Exp:			printf("JGE label%d\n",label);
									break;
								
			case LE_Exp:			printf("JG label%d\n",label);
									break;
							
			case GT_Exp:			printf("JLE label%d\n",label);
									break;
								
			case GE_Exp:			printf("JL label%d\n",label);
									break;
		}
		int temp=label;
		temp1=head->leftChild->rightSib;
		label++;
		while(temp1!=NULL)
		{
			printStmt(temp1);
			temp1=temp1->rightSib;
		}
		
		printf("label%d:\n",temp);
		
	
	}
		
	else if(head->id==repetitiveStmt)
	{
		printf("label%d:\n",label++);
		
		printf("MOV AX , %s\n",head->leftChild->leftChild->tk.att);
		printf("MOV BX , %s\n",head->leftChild->leftChild->rightSib->tk.att);
		printf("CMP AX,BX\n");
		
		switch(head->leftChild->id)
		{
			case EqualityExp:		printf("JNZ label%d\n",label);
									break;
								
			case NotEqualityExp:	printf("JZ label%d\n",label);
									break;
								
			case LT_Exp:			printf("JGE label%d\n",label);
									break;
								
			case LE_Exp:			printf("JG label%d\n",label);
									break;
							
			case GT_Exp:			printf("JLE label%d\n",label);
									break;
								
			case GE_Exp:			printf("JL label%d\n",label);
									break;
		}
		int whTemp=label;
		temp1=head->leftChild->rightSib;
		label++;
		while(temp1!=NULL)
		{
			printStmt(temp1);
			temp1=temp1->rightSib;
		}
		
		printf("JMP label%d\n",whTemp-1);
		
		printf("label%d:\n",whTemp);
		
	}
}

void printExpr(astPointer head)
{
	astPointer temp1,temp2;
	
	if(head->id==tK_NUM)
	{
		printf("MOV AX ,%s\n",head->tk.att);
	}
	else if(head->id==ID_Name)
	{
		printf("MOV AX ,%s\n",head->tk.att);
	}
	else if(head->id==PLUS_Expr)
	{
		printExpr(head->leftChild);
		printf("PUSH AX\n");
		printExpr(head->leftChild->rightSib);
		printf("POP BX\n");
		printf("ADD AX,BX\n");
	}
	else if(head->id==MINUS_Expr)
	{
		printExpr(head->leftChild);
		printf("PUSH AX\n");
		printExpr(head->leftChild->rightSib);
		printf("PUSH AX\n");
		printf("POP BX\n");
		printf("POP AX\n");
		printf("SUB AX,BX\n");
	}
	else if(head->id==MUL_Expr)
	{
		printExpr(head->leftChild);
		printf("PUSH AX\n");
		printExpr(head->leftChild->rightSib);
		printf("POP BX\n");
		printf("MUL BX\n");
	}
	else if(head->id==DIV_Expr)
	{
		printExpr(head->leftChild);
		printf("PUSH AX\n");
		printExpr(head->leftChild->rightSib);
		printf("PUSH AX\n");
		printf("POP BX\n");
		printf("POP AX\n");
		printf("MOV DX,0\n");
		printf("DIV BX\n");
	}
	else if(head->id==MOD_Expr)
	{
		printExpr(head->leftChild);
		printf("PUSH AX\n");
		printf("MOV BX, %s\n",head->leftChild->rightSib->tk.att);
		printf("MOV DX,0\n");
		printf("DIV BX\n");
		printf("MOV AX,DX\n");
	
	}
}

void writeFuns()
{
	printf("readin proc near\n");
	printf("\tpush bx\n");
	printf("\tpush cx\n");
	printf("\tpush dx\n");
	printf("\tmov cx,10\n");
	printf("\tmov bx,0\n\n");
printf("read:\n");
	printf("\tmov ah,1\n");
	printf("\tint 21h\n");
	printf("\tcmp al,'0'\n");
	printf("\tjl endread\n");
	printf("\tcmp al,'9'\n");
	printf("\tjg endread\n");
	
	printf("\tsub al,'0'\n");
	printf("\tmov ah,0\n");
	printf("\tpush ax\n");
	printf("\tmov ax,bx\n");
	printf("\tmul cx\n");
	printf("\tpop dx\n");
	printf("\tadd ax,dx\n");
	printf("\tmov bx,ax\n");
	printf("\tjmp read\n\n");
	
printf("endread:\n");
	printf("\tpush ax\n");
    printf("\tmov dl,10\n");
    printf("\tmov ah,6\n");
    printf("\tint 21h\n");
    
    printf("\tmov dl,13\n");
    printf("\tmov ah,6\n");
    printf("\tint 21h\n");
    printf("\tpop ax\n");	
	
	printf("\tmov ax,bx\n");
	printf("\tpop dx\n");
	printf("\tpop cx\n");
	printf("\tpop bx\n");
	printf("\tret\n");
	printf("readin endp\n\n");
	
printf("printout proc near\n");
	printf("\tpush bx\n");
	printf("\tpush cx\n");
	printf("\tpush dx\n");
	printf("\tmov bx,10\n");
	printf("\tmov cx,0\n");
	printf("\tcmp ax,0\n");
	printf("\tjl makepos\n\n");
	
printf("print1:	\n");
	printf("\tmov dx,0\n");
	printf("\tdiv bx\n");
	printf("\tpush dx\n");
	printf("\tinc cx\n");
	printf("\tcmp ax,0\n");
	printf("\tjnz print1\n\n");

printf("print2:\n");
	printf("\tpop dx\n");
	printf("\tadd dl,'0'\n");
	printf("\tmov ah,6\n");
	printf("\tint 21h\n");
	printf("\tloop print2\n");
	
	printf("\tpush ax\n");
    printf("\tmov dl,10\n");
    printf("\tmov ah,6\n");
    printf("\tint 21h\n");
    
    printf("\tmov dl,13\n");
    printf("\tmov ah,6\n");
    printf("\tint 21h\n");
    printf("\tpop ax\n");
    
	printf("\tpop dx\n");
	printf("\tpop cx\n");
	printf("\tpop bx\n");
	printf("\tret\n\n");
	
	
	
printf("makepos:\n");
	printf("\tpush ax\n");
	printf("\tmov dl,'-'\n");
	printf("\tmov ah,6\n");
	printf("\tint 21h\n");
	printf("\tpop ax\n");
	printf("\tnot ax\n");
	printf("\tadd ax,1\n");
	printf("\tjmp print1\n");
printf("printout endp	\n\n");		
printf("end\n");
}
	
	
	
	

	
	
