/*
********************
 Batch #47
 Members:-
 			2008A7PS103 - G.Manjunath
 			2008A7PS124 - R.Maheshwar Reddy
 *********************
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"ast.h"
#include"SymbolTable.h"

char astKeys[][20]={
"lite",
"Program"  , //1
"Funct"  , //2
"MainFun"  , //3
"Function_Name"  , //4		
"Return_Type"  , //5				
"Parameters"  , //6
"Declaration"  , //7
"Statement"  , //8
"Var"  , //9
"ID"  , //10						
"ResultType"  , //11
"TK_KEY_NONE"  , //12
"TK_KEY_VAR"  , //13
"FormalParamList"  , //14
"ID_formalParam"  , //15			
"AssignmentStmt"  , //16
"ConditionalStmt"  , //17
"RepetitiveStmt"  , //18
"ReturnStmt"  , //19
"IO_Stmt "  , //20
"FunctionCallStmt"  , //21
"EmptyStmt"  , //22
"NUL"  , //23
"ID_left"  , //24				
"Expr"  , //25
"ID_Name"  , //26				
"Number"  , //27
"PLUS_Expr"  , //28
"MINUS_Expr"  , //29
"MUL_Expr"  , //30
"DIV_Expr"  , //31
"FunctionCall"  , //32
"TK_NUM"  , //33
"ID_FunctName"  , //34			
"ActualParams"  , //35
"ParamsList"  , //36
"ID_ParamName"  , //37			
"BoolExp"  , //38
"EqualityExp"  , //39
"NotEqualityExp"  , //40
"LT_Exp"  , //41
"LE_Exp"  , //42
"GT_Exp"  , //43
"GE_Exp"  , //44
"ID_Exp"  , //45					
"ID_Left"  , //46				
"ID_right"  , //47				
"ID_return"  , //48			
"INStmt"  , //49
"OUTStmt"  , //50	
"ID_input"  , //51				
"ID_output"  , //52				
"MOD_Expr"	//53
};
//---------------------------------------------------------------------------------------------------------
int space=0,tempspace;
astTree ast;
extern int end;
int ret=0;		//to check if the return statement is present or not

extern HashPtr HashTable[200];
astPointer retVar;
FILE *fAst;

//---------------------------------------------------------------------------------------------------------------
astPointer createAstNode (astToken_id id)
{
	astPointer tmp=malloc(sizeof(struct astNode));
	tmp->id=id;
	tmp->parent=NULL;
	tmp->leftChild=NULL;
	tmp->rightSib=NULL;
	
	return tmp;
}
//----------------------------------------------------------------------------------------------------
void createAst ()
{
	extern ParseTree p;
	treePointer tmp1,tmp2,tmp3;
	tmp1=p.root;
	
	astPointer temp1,temp2;
	ast.root=createAstNode(1);
	temp1=ast.root;
	
	
	
	tmp1=tmp1->leftChild->leftChild;
	tmp2=tmp1;						//tmp2 at otherfuns
	
	while(tmp1->leftChild->id==39)
	{
		tmp1=tmp1->leftChild;
		
		temp2=createAstNode(2);
		
		if(temp1==ast.root)
		{
			temp1->leftChild=temp2;
			temp2->parent=temp1;
		}
		else
		{
			temp1->rightSib=temp2;
			temp2->parent=temp1->parent;
		}
		
		temp2->leftChild=createFun(tmp1,temp2);		
		temp1=temp2;
		
		tmp1=tmp1->rightSib;		//moving pointer to adj otherfuns
	}
	
	tmp1=tmp2->rightSib;			//moving tmp1 to mainfun
	
	temp2=createAstNode(3);
	if(temp1==ast.root)
	{
		temp1->leftChild=temp2;
		temp2->parent=temp1;
	}
	else
	{
		temp1->rightSib=temp2;
		temp2->parent=temp1->parent;
	}
	temp1=temp2;
	
	tmp1=tmp1->leftChild->rightSib->rightSib;		//tmp1 at funbody and temp1 at mainfuns
	temp1->leftChild=funBody(tmp1,temp1);			// astPointer funBody(treePointer funBodyptr,astPointer parent)
	
	printAst();

}
//------------------------------------------------------------------------------------------------------------

astPointer createFun(treePointer ptr , astPointer parent)			// ptr is at funct
{
	astPointer temp1,temp2,temp3;
	treePointer tmp1,tmp2,tmp3;
	
	tmp1=tmp2=ptr;
	tmp1=tmp1->leftChild->rightSib;		//tmp1 at id=funtion name
	
	temp1=createAstNode(4);			// starting with funct_name  // shd be the pointer this function shd return 
	temp1->parent=parent;
	temp1->tk=tmp1->tk;
	temp2=temp1;					//temp2 to traverse in ast tree with temp1 as const root
	
	
	tmp3=tmp1->rightSib->rightSib;		//tmp3 at parameters
	tmp3=tmp3->leftChild->rightSib->rightSib->rightSib->rightSib->rightSib->rightSib->leftChild;	// now at child of outid
	
	temp3=createAstNode(5);			// adding return_type
	temp2->rightSib=temp3;
	temp3->parent=parent;
	temp2=temp3;
	temp2->tk=tmp3->tk;
	retVar=temp2;					//chking with return type
	
	
	//temp3=createAstNode(6);			//creating parameters
	//temp2->rightSib=temp3;
	//temp3->parent=temp2->parent;
	//temp2=temp3;
	
	tmp3=tmp1->rightSib->rightSib->leftChild->rightSib->rightSib;	//tmp3 at inlist
	if(tmp3->leftChild->id==9)
	{
		temp3=createAstNode(12);
		//temp3->parent=temp2;
		//temp2->leftChild=temp3;
		temp2->rightSib=temp3;
		temp3->parent=temp2->parent;
		temp2=temp3;
	}
	else
	{
		temp2->rightSib=params(tmp3->leftChild,temp2);			// astPointer params(treePointer IdlistPtr,astPointer parent);
		temp2=temp2->rightSib;
	}
	
	tmp3=tmp1->rightSib->rightSib->rightSib->rightSib->rightSib;	//tmp3 at funbody
	
	temp2->rightSib=funBody(tmp3,temp2->parent);
	
	return temp1;
	
}

//-------------------------------------------------------------------------------------------------------------------

astPointer funBody(treePointer ptr,astPointer parent)		//ptr at funbody 
{
	astPointer temp1,temp2,temp3,temp4,temp5;
	treePointer tmp1,tmp2,tmp3,tmp4;
	
	temp3=temp1=NULL;					//temp3 is to be returned
	tmp1=ptr->leftChild;
	
	while(tmp1->leftChild->id!=29)		//tmp1 at declarations and will be used for traversing declaration
	{
		tmp1=tmp1->leftChild;						
		tmp2=tmp1->leftChild->rightSib;				//tmp2 at idlist
		
		temp2=createAstNode(9);
		//temp4=createAstNode(9);			//adding var to declaration 
		//temp4->parent=temp2;
		//temp2->leftChild=temp4;
		
		temp5=createAstNode(10);
		temp5->parent=temp2;
		temp2->leftChild=temp5;
		
		temp5->tk=tmp2->leftChild->tk;		//adding token
											//temp1 used for sibs of declaration
		if(temp1==NULL)
		{
			temp3=temp2;
			temp1=temp2;
			temp2->parent=parent;
		}
		else
		{	
			temp1->rightSib=temp2;
			temp2->parent=temp1->parent;
			temp1=temp2;
		}
		
		tmp4=tmp2->leftChild->rightSib;			//tmp4 at remid
		
		while(tmp4->leftChild->id!=29)
		{
			tmp4=tmp4->leftChild->rightSib;		//tmp4 at id
			
			temp2=createAstNode(9);
			//temp4=createAstNode(9);			//adding var to declaration 
		//	temp4->parent=temp2;
			//temp2->leftChild=temp4;
			
			temp5=createAstNode(10);
			temp5->parent=temp2;
			temp2->leftChild=temp5;
			
			temp5->tk=tmp4->tk;
			
			temp1->rightSib=temp2;
			temp2->parent=temp1->parent;
			temp1=temp2;
			
			tmp4=tmp4->rightSib;
		}
		
		tmp1=tmp1->rightSib;
	}
	
	//now for statements
	tmp1=ptr->leftChild->rightSib;		//tmp1 at otherstatements
	while(1)
	{
		tmp2=tmp1->leftChild;		//tmp2 at statement
		
		temp2=createSt(tmp2);		// astPointer createSt(treePointer stPtr, astPointer parent)
		if(temp1==NULL)
		{
			temp3=temp2;
			temp1=temp2;
			temp2->parent=parent;
		}
		else
		{
			temp2->parent=parent;
			temp1->rightSib=temp2;
			temp1=temp2;
		}
		
		if(tmp2->rightSib->leftChild->id==29)
		break;
		else
		tmp1=tmp2->rightSib->leftChild;		//setting tmp1 at otherstatements
	}
	
	return temp3;
}
//-----------------------------------------------------------------------------------------------------------
	
astPointer params(treePointer ptr,astPointer parent)			//ptr at Idlist
{	
	treePointer temp1,temp2;
	astPointer tmp1,tmp2,tmp3;
	
	temp1=ptr->leftChild;		//temp1 at id under idlist
	
	tmp1=createAstNode(14);				//making formalparmalist
	tmp1->parent=parent;				//tmp1 to be returned
	tmp2=tmp1;
	
	tmp3=createAstNode(15);
	tmp3->parent=tmp2;
	tmp2->leftChild=tmp3;
	tmp3->tk=temp1->tk;
	tmp2=tmp3;
	
	temp1=temp1->rightSib;
	while(temp1->leftChild->id!=29)
	{
		temp1=temp1->leftChild->rightSib;
		
		tmp3=createAstNode(15);
		tmp3->parent=tmp2->parent;
		tmp2->rightSib=tmp3;
		tmp2=tmp3;
		
		tmp2->tk=temp1->tk;
		
		temp1=temp1->rightSib;
	}
	
	return tmp1;
}
//-----------------------------------------------------------------------------------------------------------

astPointer createSt(treePointer stPtr)
{
	ret=0;
	
	astPointer temp1,temp2,temp3;					//temp1 shd be returned 
	treePointer tmp1,tmp2,tmp3;						//temp2 shd be used to traverse
	
	temp1=createAstNode(8);
	
	tmp1=stPtr;
	
	if(stPtr->leftChild->id==20)													// for empty st
	{
		temp2=createAstNode(22);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(23);
		temp3->parent=temp2;
		
		temp2->leftChild=temp3;
		
		return temp1->leftChild;
	}
	else if(stPtr->leftChild->id==61)												//for io st
	{
		temp2=createAstNode(20);			//iost
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
	
		if(tmp1->leftChild->leftChild->id==0)
		{
			temp3=createAstNode(50);		//out stmt
			temp3->parent=temp2;
			temp2->leftChild=temp3;
			temp2=temp3;
			
			temp3=createAstNode(52);		//id_output
			temp3->parent=temp2;
			temp2->leftChild=temp3;
			temp3->tk=tmp1->leftChild->leftChild->rightSib->tk;
			
			return temp1->leftChild->leftChild;
		}
		else
		{
			temp3=createAstNode(49);		//in stmt
			temp3->parent=temp2;
			temp2->leftChild=temp3;
			temp2=temp3;
			
			temp3=createAstNode(51);		//id_input
			temp3->parent=temp2;
			temp2->leftChild=temp3;
			temp3->tk=tmp1->leftChild->leftChild->rightSib->tk;
			
			return temp1->leftChild->leftChild;
		}
	}
	else if(stPtr->leftChild->id==55)										//for functioncall
	{
		temp2=createAstNode(21);		//functioncallst
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(32);		//functioncall
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=createAstNode(34);		//id_functionname
		temp3->tk=tmp1->leftChild->leftChild->rightSib->tk;
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		//checking if it returns anything
		int hash=hash_s(temp3->tk.att);
		HashPtr hTemp,hPtr=HashTable[hash];
		while(hPtr!=NULL)
		{
			if(hPtr->C.t==1)
			{
				if(strcmp(hPtr->C.name,temp3->tk.att)==0)
				{
					if(hPtr->C.ret)
					{
						fprintf(stderr,"ERROR: the function %s at line %d should not be written as a statement\n",temp3->tk.att,temp3->tk.lineNum);
						end=7;
					}
					
					break;
				}
			}
			hPtr=hPtr->next;
		}
		
		temp2=temp3;
		
		//temp3=createAstNode(35);		//actualparams
	//	temp3->parent=temp2->parent;
		//temp2->rightSib=temp3;
		//temp2=temp3;
		
		temp3=createAstNode(36);		//paramlist
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		temp2=temp3;
		
		tmp1=tmp1->leftChild->leftChild->rightSib->rightSib->rightSib;		//tmp1 at idlist
		
		temp3=createAstNode(37);
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		temp2=temp3;
		temp2->tk=tmp1->leftChild->tk;
		
		tmp1=tmp1->leftChild->rightSib;			//tmp1 at remid
		
		while(tmp1->leftChild->id!=29)
		{
			temp3=createAstNode(37);
			temp3->parent=temp2->parent;
			temp2->rightSib=temp3;
			temp3->tk=tmp1->leftChild->rightSib->tk;
			temp2=temp3;
				
			tmp1=tmp1->leftChild->rightSib->rightSib;
		}
		
		return temp1->leftChild->leftChild;
	}
	
	else if(stPtr->leftChild->id==60)
	{
		ret=1;
		
		temp2=createAstNode(19);		//returnstmt
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(48);		//id_return 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		temp3->tk=stPtr->leftChild->leftChild->rightSib->tk;
		
		if(strcmp(temp3->tk.att,retVar->tk.att)!=0)
		{
			fprintf(stderr,"ERROR: returning other variable %s than specified %s in line %d\n",temp3->tk.att,retVar->tk.att,temp3->tk.lineNum);
			end=6;
		}
		
		return temp1->leftChild->leftChild;
	}
	
	else if(stPtr->leftChild->id==59)										//for repetative st
	{
		temp2=createAstNode(18);		//repetative st
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		tmp1=tmp1->leftChild->leftChild->rightSib->rightSib;			//at boolexp;
		
		temp3=crtBoolexp(tmp1);					// astPointer crtBoolexp(treePointer boolptr)
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		tmp1=tmp1->rightSib->rightSib->rightSib;		//at othersts;
		
		while(1)
		{
			temp3=createSt(tmp1->leftChild);
			temp3->parent=temp2->parent;
			temp2->rightSib=temp3;
			
			temp2=temp3;
			
			tmp1=tmp1->leftChild->rightSib;
			if(tmp1->leftChild->id==29)
			break;
			else
			tmp1=tmp1->leftChild;
		}
		
		return temp1->leftChild;
	}
	
	else if(stPtr->leftChild->id==56)										//conditional st
	{
		temp2=createAstNode(17);				//conditionalst
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		tmp1=tmp1->leftChild->leftChild->rightSib->rightSib;	//at boolexp
		
		temp3=crtBoolexp(tmp1);
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		tmp1=tmp1->rightSib->rightSib->rightSib;		// at otherstmts
		
		while(1)
		{
			temp3=createSt(tmp1->leftChild);
			temp3->parent=temp2->parent;
			temp2->rightSib=temp3;
			
			temp2=temp3;
			
			tmp1=tmp1->leftChild->rightSib;
			if(tmp1->leftChild->id==29)
			break;
			else
			tmp1=tmp1->leftChild;
		}
		
		return temp1->leftChild;
	}
	
	else if(stPtr->leftChild->id==51)									//for assignmentst
	{
		temp2=createAstNode(16);		//assignmentst
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		tmp1=tmp1->leftChild->leftChild->leftChild->rightSib;		//at id
		temp3=createAstNode(46);								//id_left
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		temp3->tk=tmp1->tk;
		
		temp2=temp3;
		
		tmp1=stPtr;					//reset to stptr
		tmp1=tmp1->leftChild->leftChild->rightSib;		//at expr or function

		//temp3=createAstNode(25);		//expr
		//temp2->rightSib=temp3;
		//temp3->parent=temp2->parent;
		//temp2=temp3;
		
		temp3=crtFunRExpr(tmp1);				// astPointer crtFunRExpr(treePointer funorExpr)
		temp2->rightSib=temp3;
		temp3->parent=temp2->parent;
		
		
		return temp1->leftChild;
	}
	
}
//--------------------------------------------------------------------------------------------------------------------

astPointer crtBoolexp(treePointer boolptr)
{
	treePointer tmp1,tmp2;
	astPointer temp1,temp2,temp3;		//temp1 shd be returned 
	
	temp1=createAstNode(38);
	
	tmp1=boolptr;
	
	if(tmp1->leftChild->rightSib->leftChild->id==29)
	{
		temp2=createAstNode(45);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==21)		//for equal
	{
		temp2=createAstNode(39);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==22)		//for nteql
	{
		temp2=createAstNode(40);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==23)		//for lt
	{
		temp2=createAstNode(41);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==24)		//for gt
	{
		temp2=createAstNode(43);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==25)		//for leq
	{
		temp2=createAstNode(42);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==26)		//for geq
	{
		temp2=createAstNode(44);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
	else if(tmp1->leftChild->rightSib->leftChild->id==21)		//for equal
	{
		temp2=createAstNode(39);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=createAstNode(46);
		temp3->tk=tmp1->leftChild->tk;
		temp2->leftChild=temp3;
		temp3->parent=temp2;
		
		temp2=temp3;
		
		temp3=createAstNode(47);
		temp3->tk=tmp1->leftChild->rightSib->leftChild->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		 
		 return temp1->leftChild;
	}
}
//-----------------------------------------------------------------------------------------------------------------------

astPointer crtFunRExpr(treePointer funorExpr)
{
	treePointer tmp1,tmp2,tmp3;
	astPointer temp1,temp2,temp3;
	
	tmp1=funorExpr;
	
	temp1=createAstNode(25);
	
	if(tmp1->leftChild->id==55)				//funtioncall
	{
		tmp1=tmp1->leftChild;		//tmp1 at functioncall
		temp2=createAstNode(32);
		temp1->leftChild=temp2;
		temp2->parent=temp1;
		
		temp3=createAstNode(34);			//id_funtionname
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		temp3->tk=tmp1->leftChild->rightSib->tk;
		
		temp2=temp3;
		tmp1=tmp1->leftChild->rightSib->rightSib->rightSib;		//tmp1 at idlist
		
		//temp3=createAstNode(35);		//actualparams
		//temp3->parent=temp2->parent;
		//temp2->rightSib=temp3;
		//temp2=temp3;
		
		temp3=createAstNode(36);		//paramlist
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		temp2=temp3;
		
		temp3=createAstNode(37);
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		temp2=temp3;
		temp2->tk=tmp1->leftChild->tk;
		
		tmp1=tmp1->leftChild->rightSib;			//tmp1 at remid
		
		while(tmp1->leftChild->id!=29)
		{
			temp3=createAstNode(37);
			temp3->parent=temp2->parent;
			temp2->rightSib=temp3;
			temp3->tk=tmp1->leftChild->rightSib->tk;
			temp2=temp3;
				
			tmp1=tmp1->leftChild->rightSib->rightSib;
		}
		
		return temp1->leftChild;
	}
	
	else
	{	
		//temp2=crtExpr(tmp1->leftChild);			//astPointer crtExpr(treePointer expr)
		//temp2->parent=temp1;
		//temp1->leftChild=temp2;
		
		return crtExpr(tmp1->leftChild);
	}
}

//--------------------------------------------------------------------------------------------------------------

astPointer crtExpr(treePointer expr)
{
	treePointer tmp1,tmp2,tmp3;
	astPointer temp1,temp2,temp3;
	
	tmp1=expr;
	temp1=createAstNode(25);
	
	if(tmp1->leftChild->id==16)		//for id
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(26);
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp2->tk=tmp1->tk;
		
		return temp1->leftChild;
	}
	
	else if(tmp1->leftChild->id==17)		//for num
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(33);			//adding tk_num instead of number
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp2->tk=tmp1->tk;
		
		return temp1->leftChild;
	}
		
	else if(tmp1->leftChild->id==30)		//for plus
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(28);			
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=crtExpr(tmp1->rightSib->rightSib); 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=crtExpr(tmp1->rightSib->rightSib->rightSib->rightSib);
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		return temp1->leftChild;
	}
	
	else if(tmp1->leftChild->id==31)		//for minus
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(29);			
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=crtExpr(tmp1->rightSib->rightSib); 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=crtExpr(tmp1->rightSib->rightSib->rightSib->rightSib);
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		return temp1->leftChild;
	}
	
	else if(tmp1->leftChild->id==32)		//for mul
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(30);			
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=crtExpr(tmp1->rightSib->rightSib); 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=crtExpr(tmp1->rightSib->rightSib->rightSib->rightSib);
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		return temp1->leftChild;
	}
	
	else if(tmp1->leftChild->id==33)		//for div
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(31);			
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=crtExpr(tmp1->rightSib->rightSib); 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=crtExpr(tmp1->rightSib->rightSib->rightSib->rightSib);
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		return temp1->leftChild;
	}
	else if(tmp1->leftChild->id==15)		//for mod
	{
		tmp1=tmp1->leftChild;			
		temp2=createAstNode(53);			
		temp2->parent=temp1;
		temp1->leftChild=temp2;
		
		temp3=crtExpr(tmp1->rightSib->rightSib); 
		temp3->parent=temp2;
		temp2->leftChild=temp3;
		
		temp2=temp3;
		
		temp3=createAstNode(33);
		temp3->tk=tmp1->rightSib->rightSib->rightSib->rightSib->tk;
		temp3->parent=temp2->parent;
		temp2->rightSib=temp3;
		
		return temp1->leftChild;
	}
	else
	{	
		return crtExpr(expr->leftChild->rightSib);		// for exp=(exp) 
	}
}

void printAst()
{
	astPointer rt=ast.root;
	fAst=freopen("astoutput.txt","w",stdout);
	printASTptr(rt);
	fclose(fAst);
}

void printASTptr(astPointer rt)
{
	if(rt!=NULL)
	{
		for(tempspace=space;tempspace>0;tempspace--)
		printf("\t|");
		
		if(rt->id==4 || rt->id==5 || rt->id==10 || rt->id==15 || rt->id==24 || rt->id==26 || rt->id==34 || rt->id==37 || rt->id==45 || rt->id==46 || rt->id==47 ||  rt->id==48 || rt->id==51 || rt->id==52 ||rt->id==33 ||rt->id==13 ) 
		printf("%s(%s)\n",astKeys[rt->id],rt->tk.att);
		else
		printf("%s\n",astKeys[rt->id]);
		
		space++;
		printASTptr(rt->leftChild);
		space--;
		printASTptr(rt->rightSib);
	}
}
/*
void typeChk()
{
	astPointer temp1,temp2,temp3;
	temp1=ast.root;
	
	temp1=temp1->leftChild;
	while(temp1!=NULL)
	{
		temp2=temp1->leftChild;
		
		while(temp2->id < 16 || temp2->id > 19)
		temp2=temp2->rightSib;						//temp2 at statements
		
		while(temp2!=NULL)
		{
			if(temp2->id==16)			//for assignment st
			{
				int status=typeExpr(temp2->leftChild->rightSib);
				//fprintf(stderr,"status=%d\n",status);
				if(!status)
				fprintf(stderr,"ERROR in type checking at line %d\n",temp2->leftChild->tk.lineNum);
			}
			temp2=temp2->rightSib;
		}
		
		temp1=temp1->rightSib;
	}
}

int typeExpr(astPointer expr)
{	
	int hash;
	HashPtr hPtr;
	
	switch(expr->id)
	{	
		case 26:	return 1;
		
		case 33:	return 1;
		
		case 28:	return(typeExpr(expr->leftChild) & typeExpr(expr->leftChild->rightSib));
		
		case 29:	return(typeExpr(expr->leftChild) & typeExpr(expr->leftChild->rightSib));
		
		case 30:	return(typeExpr(expr->leftChild) & typeExpr(expr->leftChild->rightSib));
		
		case 31:	return(typeExpr(expr->leftChild) & typeExpr(expr->leftChild->rightSib));
		
		case 53:	return typeExpr(expr->leftChild);
		
		case 32:	hash=hash_s(expr->leftChild->tk.att);
					hPtr=HashTable[hash];
					while(hPtr!=NULL)
					{
						if(hPtr->C.t==1)
						{
							if(strcmp(hPtr->C.name,expr->leftChild->tk.att)==0)
							return (hPtr->C.ret);
						}
						hPtr=hPtr->next;
					}
		}
}
*/
		
