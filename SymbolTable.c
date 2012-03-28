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
#include"SymbolTable.h"


int error=0;
int expected_ret=0;

int hash_s(char str[])
{
	int i,l=strlen(str),ret=0;
	for(i=0;i<l;i++)
	{
		ret=ret+str[i]*(i+1)*(i+2);
		ret%=200;
	}
	return ret;
}		
void insert(char name[],int scope,type t,int lineNum)
{
	if(error)
	return;
	//fprintf(stderr,"INSIDE INSERT\n");
	int ret=hash_s(name);
	HashPtr curr=HashTable[ret];
	//printf("%d %s %d %d\n",ret,name,scope,t);
	
	
	HashPtr temp=(HashPtr)malloc(sizeof(struct HashNode));
	strcpy((temp->C).name,name);
	(temp->C).scope=scope;
	(temp->C).t=t;
	(temp->C).ret=-1;
	(temp->C).count=-1;
	(temp->C).return_var[0]=0;
	(temp->C).lineNum=lineNum;
	temp->next=NULL;
	
	if(curr==NULL)
	{
		HashTable[ret]=temp;
		printf("%10s %7d %8d\n",temp->C.name,temp->C.scope,temp->C.t);
	}	
	else
	{
		while(curr->next!=NULL)
		{
			if(strcmp((curr->C).name,name)==0)
			{
				if((curr->C).scope==scope)
				{
					fprintf(stderr,"ERROR:Double Declaration of variable %s at line %d\n",name,lineNum);
					error=1;
					return ;
				}
			}
		 curr=curr->next;
		}
		
		if(strcmp((curr->C).name,name)==0)
		{
			if((curr->C).scope==scope)
			{
				fprintf(stderr,"ERROR:Double Declaration of variable %s at line %d\n",name,lineNum);
				error=1;
				return ;
			}
		}
		curr->next=temp;
		 printf("%10s %7d %8d\n",temp->C.name,temp->C.scope,temp->C.t);
		return;
	}	
}				
void update(treePointer fun_node,int count,int ret_var,char return_var[])
{
	HashPtr curr;
	int loc;
	loc=hash_s((fun_node->tk).att);
	curr=HashTable[loc];
	if(curr->next==NULL)
	{
		curr->C.count=count;
		curr->C.ret=ret_var;
		strcpy(curr->C.return_var,return_var);
		//return;
	}	
	while(curr->next!=NULL)
	{
		if(strcmp((fun_node->tk).att,curr->C.name)==0 && curr->C.t==1)
		{
			curr->C.count=count;
			curr->C.ret=ret_var;
			strcpy(curr->C.return_var,return_var);
		}
		curr=curr->next;
	}	
	printf("fun %s has %d input parameters",fun_node->tk.att,count);
	if(ret_var==1)
	printf(" and a return variable\n");
	else printf(" and no return variable\n");
		
	return;
}	
	
void getParameters(treePointer root,int scope,treePointer fun_node)
{
	int count=0,ret_var=0;
	if(error)
	return;
	treePointer outid,remid,idlist,inlist=root->leftChild->rightSib->rightSib; //going till you get inlist
	if(inlist->leftChild->id!=9)         //if inlist is not empty
	{
		if(inlist->leftChild->id==42)  //if inlist is idlist
		{	
			idlist=inlist->leftChild;                   
			insert((idlist->leftChild)->tk.att,scope,var,(idlist->leftChild)->tk.lineNum);        //taking out the first id
			count++;
			 if(!error)
			 {
				 remid=idlist->leftChild->rightSib;       
				 while(1)                      //to get the remaining ids till you get remid as empty
				 {
				 	if(remid->leftChild->id==29)
				 	break;
				 	else if(!error)
				 	{	
			 			insert((remid->leftChild->rightSib)->tk.att,scope,var,(remid->leftChild->rightSib)->tk.lineNum);
			 			count++;
			 			remid=remid->leftChild->rightSib->rightSib;
				 	}
				 }
			}	 
		}
	}
	outid=inlist->rightSib->rightSib->rightSib->rightSib;
	if(outid->leftChild->id==16 && error==0)
	{
		insert((outid->leftChild)->tk.att,scope,var,(outid->leftChild)->tk.lineNum);
		ret_var=1;
	}	
	
	update(fun_node,count,ret_var,(outid->leftChild)->tk.att);//updating no of parameters and return for fun 
	return ;
}		



int chk_no_of_parameters(treePointer root)
{
	int loc=hash_s(root->tk.att),count=-1;
	HashPtr curr=HashTable[loc];
	if(curr->next==NULL)
	{
		if(strcmp(root->tk.att,curr->C.name)==0)
		{
			if(curr->C.t==0)
			{
				error=1;
				fprintf(stderr,"ERROR:fun %s is not declared \n",root->tk.att);
				return;
			}
			else  count=curr->C.count;
		}
	}
	while(curr->next!=NULL)
	{
		if(strcmp(root->tk.att,curr->C.name)==0)
		{
			if(curr->C.t==0)
			{
				error=1;
				fprintf(stderr,"ERROR:fun %s is not declared \n",root->tk.att);
				return;
			}
			else
			{
				 count=curr->C.count;
				 break;
			}
		}
		curr=curr->next;		 
	}	
	if(!error)
	{				
		int temp=1;
		treePointer Idlist=root->rightSib->rightSib;
		treePointer RemID=Idlist->leftChild->rightSib;
			while(1)
			{
				if(RemID->leftChild->id!=29)
					{
						temp++;
						RemID=RemID->leftChild->rightSib->rightSib;
					}
					else break;				
			}
			if(temp==count)
			return 1;
			else return 0;
	}		
}				
	 		
void visit(treePointer root,int scope,treePointer fun_node)
{
	//fprintf(stderr,"INSIDE VISIT WITH %20s %19s %10d %10d\n",(root->tk).token_name,(root->tk).att,root->id,fun_node->id);
	if(error)
	return;
	int flag=0;
	if(root->id==2)   //if there is a return statement
 	{
 		expected_ret=1;
 		if(fun_node->id==37)    //if we are in main funBody
		{
			fprintf(stderr,"ERROR:return statement is not expected in the main fun\n");
			error=1;
			return ;
		}
		else              //if it is a function funBody
		{
			int loc=hash_s((fun_node->tk).att);               //checking if there should be any return statement
			HashPtr curr=HashTable[loc];					  		
			if(curr->C.ret==0)
			{
				fprintf(stderr,"ERROR:there should be no return statement in fun %s according to its prototype\n",curr->C.name);
				error=1;
				return ;
			}	
		}	 	
	}	
	
	if(root->id==51)   //if it is an assignment statement
	{
		treePointer ExprOrFunc=root->leftChild->rightSib;
		if(ExprOrFunc->leftChild->id==55)   //checking if func call is thr
		{
			treePointer FunctionCall = ExprOrFunc->leftChild;
			treePointer func=FunctionCall->leftChild->rightSib;      //should chk if fun is of type void or not
			int loc=hash_s(func->tk.att);
			HashPtr curr=HashTable[loc];
			if(curr->next==NULL)
			{
				if(curr->C.ret==0)           //if fun is of void type
 				{
					fprintf(stderr,"ERROR:In assignment statement at line %d -- calling fun %s  of void type\n",FunctionCall->leftChild->tk.lineNum,curr->C.name);
					error=1;
					return;
				}	
			}
			else
			{
				while(curr->next!=NULL)
				{
					if(curr->C.t==1)
					{			
						if(curr->C.ret==0)
						{
							fprintf(stderr,"ERROR:In assignment statement at line %d -- calling fun %s void type\n",FunctionCall->leftChild->tk.lineNum,curr->C.name);
							error=1;
							return;
						}
					}
					curr=curr->next;
				}
			}
		}
	}
	
	if(root->id==7)
	{
		treePointer func=root->rightSib;
		if(!chk_no_of_parameters(func))
		{
			fprintf(stderr,"ERROR:no of parameters in fun call of fun %s at line %d and fun prototype are different\n",func->tk.att,root->tk.lineNum);
			error=1;
			return ;
		}
	}						
							
	if(root->id==16)    // if the node is of identifier
	{
	//	fprintf(stderr,"INSIDE VISIT WITH %20s %19s\n",(root->tk).token_name,(root->tk).att);
	
		int ret=hash_s((root->tk).att);
		HashPtr curr=HashTable[ret];
		if(curr==NULL)
		{
			//fprintf(stderr,"variable %s not declared at all\n",(root->tk).att);
			flag=0;
		}	
		else
		{
			while(curr->next!=NULL)
			{
				if(error==1)break;
				
				if(curr->C.scope==scope && strcmp((root->tk).att,curr->C.name)==0)
				{
					if(curr->C.t==0)
					flag=1;
					else if(curr->C.t==1)
					{
						//fprintf(stderr,"YES IM HERE\n");
						flag=2;
						error=1;
						break;
					}
				}	
				
				if(curr->C.scope!=scope && strcmp((root->tk).att,curr->C.name)==0 && curr->C.t==1)
				flag=1;
		
				curr=curr->next;	
			}
			if(curr->next==NULL && error==0)
			{
				if(curr->C.scope==scope && strcmp((root->tk).att,curr->C.name)==0)
				{
					if(curr->C.t==0)
					flag=1;
					else if(curr->C.t==1)
					{
						//fprintf(stderr,"YES IM HERE\n");
						flag=2;
						error=1;
					}
				}
				else if(curr->C.scope!=scope && strcmp((root->tk).att,curr->C.name)==0 && curr->C.t==1)
				{	
					flag=1;		
					
				}	
			}	
		}
		if(flag==0)
		{
			fprintf(stderr,"ERROR:variable %s not declared in this scope at line %d\n",(root->tk).att,root->tk.lineNum);
			error=1;
			return;
		}
		if(flag==2)
		{
			fprintf(stderr,"ERROR:Reference to the same function is not allowed\nfun %s referred to the same in line %d\n",(root->tk).att,root->tk.lineNum);
			return ;
		}
	}
}		

				
void inorder(treePointer root,int scope,treePointer fun_node)
{
	if(root!=NULL && error==0)
	{
		inorder(root->leftChild,scope,fun_node);
		visit(root,scope,fun_node);
		inorder(root->rightSib,scope,fun_node);
	}
	return ;
}	


void chk_for_return(treePointer fun_node)
{
	if(error)
	return;
	
	int loc=hash_s(fun_node->tk.att);
	HashPtr curr=HashTable[loc];
	if(curr->next==NULL)
	{
		if(curr->C.ret!=expected_ret)
		{
			expected_ret=0;
			fprintf(stderr,"ERROR:Expected return statement in fun %s\n",curr->C.name);
			error=1;
			return;
		}
	}
	else 
	{
		while(curr->next!=NULL)
		{
			if(strcmp(curr->C.name,fun_node->tk.att)==0 && curr->C.t==1)
			{
				if(curr->C.ret!=expected_ret)
				{
					expected_ret=0;
					fprintf(stderr,"ERROR:Expected return statement in fun %s\n",curr->C.name);
					error=1;
					return;
				}	
			}
			curr=curr->next;
		}
	}
	return ;
}					
	
	
	
		
void getFunbody(treePointer root,int scope,treePointer fun_node)
{
	if(error)
	return;
	treePointer remid,idlist,declaration,declarations=root->leftChild;
	treePointer otherStmts=declarations->rightSib;
	while(1)
	{
		if(declarations->leftChild->id==29)
		break;
		else if(!error)
		{
			declaration=declarations->leftChild;
			idlist=declaration->leftChild->rightSib;
			insert((idlist->leftChild)->tk.att,scope,var,(idlist->leftChild)->tk.lineNum);        //taking out the first id
			if(!error)
			{	
				remid=idlist->leftChild->rightSib; 
			 	while(1)                      //to get the remaining ids till you get remid as empty
				{
					if(remid->leftChild->id==29)
				 	break;
				 	else if(!error)
				 	{	
					 		insert(remid->leftChild->rightSib->tk.att,scope,var,remid->leftChild->rightSib->tk.lineNum);
				 			remid=remid->leftChild->rightSib->rightSib;	
				 	}
				}
				
			}	
		}
		declarations=declaration->rightSib;
	}
	if(!error)
	inorder(otherStmts,scope,fun_node);
	if(!error && fun_node->id!=37)
	chk_for_return(fun_node);
	
return ;
}				


void fillSymbolTable(ParseTree Pt)
{
		freopen("symbolTable.txt","w",stdout);	
		
	printf("IDENTIFIER   SCOPE   TYPE(VAR:0,FUN:1)\n");
	int i;
	for(i=0;i<200;i++)
	HashTable[i]=NULL;
	
	treePointer temp,curr=Pt.root->leftChild->leftChild,fun_node=NULL; //going to other functions node
	treePointer curr2,curr_main=curr->rightSib;  //going to main fun node
	int scope=0;
	while(1)
	{
		if(error)
		return ;
		if(curr->leftChild->id==29)     //checking if other funs give empty
		{
			break;
		}
		else
		{
			printf("-------------------------------------------------------------------------\n");
			scope++;
			curr=curr->leftChild;
			temp=curr->leftChild->rightSib;    //going to fun node
			fun_node=temp;
			insert(temp->tk.att,scope,fun,temp->tk.lineNum);     //if not insert fun id         
			if(!error)
			{
				temp=temp->rightSib->rightSib;		//going to parameters node					
				getParameters(temp,scope,fun_node);    //getting the parameters 
				temp=temp->rightSib->rightSib->rightSib;      //going to funbody node
				getFunbody(temp,scope,fun_node);     //entering into funBody 
				curr=curr->rightSib;
			}			
		}
		fun_node=NULL;  	
	}
	
	if(!error)
	{	
			printf("-------------------------------------------------------------------------\n");
		scope++;
		fun_node=curr_main;
		//fprintf(stderr,"curr _ main %d\n",fun_node->id);
		curr2=curr_main->leftChild->rightSib->rightSib;
		getFunbody(curr2,scope,fun_node);
	}
	if(!error)
	{
		printf("FILLED SYMBOL TABLE SUCCESSFULLY\n");
		//printSymbolTable(scope);
	}	
}		
