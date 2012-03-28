#include<stdio.h>
#include<string.h>
FILE temp; //
int end=0; // 1=to specify the end of input; 2=to specify error
int flag=1;
typedef struct
{
	 char att[50];
	char token_name[50];
}Token;	
char ch;   // variable to store the character


char keywords[20][30]={"print","get","return","begin","end","while","if","fun","var","none","in","out","main","let","be","plus","minus","mul","div","mod"};
char tokenwords[20][30]={"TK_KEY_PRINT","TK_KEY_GET","TK_KEY_RETURN","TK_KEY_BEGIN","TK_KEY_END","TK_KEY_WHILE","TK_KEY_IF","TK_KEY_FUN","TK_KEY_VAR","TK_KEY_NONE","TK_KEY_IN","TK_KEY_OUT","TK_KEY_MAIN","TK_KEY_LET","TK_KEY_BE","TK_KEY_PLUS","TK_KEY_MINUS","TK_KEY_MUL","TK_KEY_DIV","TK_KEY_MOD"};


Token nextToken()
{
	Token Tk;
	char str[30];
	switch(ch)
	{
		case '(':	printf("<TK_OPEN,NULL>");
					ch=getchar();
				 	return;
				  
		case ')':	printf("<TK_CLOSE,NULL>");
				 	ch=getchar();
				 	return;
				 
		case ';':	printf("<TK_SEMI,NULL>");
				 	ch=getchar();
				 	return;
				  
		case '=':	printf("<TK_EQUAL,NULL>");
				 	ch=getchar();
				 	return;
				  
		case '!':	ch=getchar();
					if(ch=='=')
					{
						ch=getchar();
						printf("<TK_NOTEQUAL,NULL>");
					}
					else
						end=2;
					
					return;
					
		case '+':	printf("<TK_PLUS,NULL">);
					ch=getchar();
					return;
					
		case '-':	printf("<TK_MINUS,NULL>");
					ch=getchar();
					return;
					
		case '*':	printf("<TK_TIMES,NULL>");
					ch=getchar();
					return;
					
		case '/':	printf("<TK_DIV,NULL>");
					ch=getchar();
					return;
					
		case '<':	ch=getchar();
					if(ch=='=')
					{
						printf("<TK_LEQ,NULL>");
						ch=getchar();
					}
					else
						printf("<TK_LT,NULL>");
						
					return;
					
		case '>':	ch=getchar();
					if(ch=='=')
					{
						printf("<TK_GEQ,NULL>");
						ch=getchar();
					}
					else
						printf("<TK_GT,NULL>");
						
					return;
					
		case '.':	printf("<TK_DOT,NULL>");
					ch=getchar();
					return;
					
		case ',':	printf("<TK_COMMA,NULL>");
					ch=getchar();
					return;
	}
	
//	--------------------------------------------------------------------------------------------
	if(ch==EOF)
	{
		end=1;
		return ;
	}	
//	else if(ch!='(' && ch!=')' && ch!=';' && ch!='+' && ch!='-' && ch!='*' && ch!='/' && ch!='<' && ch!='>' && ch!='!' && ch!='=' && ch!='.' && ch!=',' && (ch<65 && ch>90) && (ch<97 && ch>122))//raising error if char is not in the specified alphabet
	else if((ch<65 && ch>90) && (ch<97 && ch>122))
	{
		end=2;
		return;
	}
	else
	{
		str[0]=ch;
		int i=1;
		if(ch>47 && ch<58)  // if first char is a digit then it should be a number
		{
			while(1)
			{
				ch=getchar();
				if(ch>47 && ch<58)
				{
					str[i++]=ch;
					continue;
				}	
				else
				{
					strcpy(Tk.att,str);
					strcpy(Tk.token_name,"TK_NUM");
					return Tk;
				}				
			}	
		}
		else
		{
		
			while(1)
			{
				ch=getchar();
				if(ch>='a' && ch<='z') 
				str[i++]=ch;
				else if(ch>='A' && ch<='Z')
				{
					flag=2;
					str[i++]=ch;
				}
				else if(ch>='0' && ch>='9')
				{
					flag=2;
					str[i++]=ch;
				}
				else break;		
			}
			str[i]='\0';
			if(flag==2) // flag=2 means alphabet followed by digit implies it is an ID
			{
				
				strcpy(Tk.token_name,"TK_ID");
				strcpy(Tk.att,str);
				return Tk;
			}
			else
			{
				for(i=0;i<20;i++)
				{
					if(!strcmp(keywords[i],str))
					{
						strcpy(Tk.att,"NULL");
						strcpy(Tk.token_name,tokenwords[i]);
						return Tk;
					}
				}
				strcpy(Tk.token_name,"TK_ID");
				strcpy(Tk.att,str);
				return Tk;
						
			}				
		
		}
	}

}	



void printTokenStream(FILE f)
{
	FILE *fout;
	fout=freopen("token.txt","w",stdout);
	temp=f;
	Token token;

	while(1)
	{
		token=nextToken();
		if(end==1)
		break;
		else if(end==2)
		printf("error");
		else if(token!=NULL)
		{
			printf("<%s,%s>",token.token_name,token.att);
		}
	
	}
	
}




void initializeScanner(char *filename)
{
	FILE *fin,*fout;
	fin=freopen(filename,"r",stdin);
	 ch=getchar();
	
	
	printTokenStream(*fin);
	
}


