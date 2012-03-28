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
#include"scanner.h"

char ch;   // variable to store the character
hashtable h;
int hash_key;
FILE *tempFile; // just to have a global variable for the input file
int end=0; // 1=to specify the end of input; 2=to specify error
int flag=1;
int line=1;		// vaiable to store the line number

char keywords[34][30]={"print","get","return","begin","end","while","if","fun","var","none","in","out","main","let","be","mod","","","","","","","","","","","","","","","plus","minus","mul","div"};
char tokenwords[34][30]={"TK_KEY_PRINT","TK_KEY_GET","TK_KEY_RETURN","TK_KEY_BEGIN","TK_KEY_END","TK_KEY_WHILE","TK_KEY_IF","TK_KEY_FUN","TK_KEY_VAR","TK_KEY_NONE","TK_KEY_IN","TK_KEY_OUT","TK_KEY_MAIN","TK_KEY_LET","TK_KEY_BE","TK_KEY_MODULO","","","","","","","","","","","","","","","TK_KEY_PLUS","TK_KEY_MINUS","TK_KEY_MUL","TK_KEY_DIV"};


int hash(char *str)
{
	int ret=7,i=0;
	while(str[i]!=0)
	{
		ret=ret*31+(i+1)*str[i++];
	}
	ret=ret%113;
	return ret;
}		


void filltable()
{
	int i;
	for(i=0;i<100;i++)
	h[hash_key].empty=1;
	for(i=0;i<34;i++)
	{	
		if(keywords[i]!="")
		{
			hash_key=hash(keywords[i]);
			strcpy(h[hash_key].token_name,tokenwords[i]);

			h[hash_key].id=i;
			h[hash_key].keylen=strlen(keywords[i]);
			h[hash_key].empty=0;
		}
	}
}		



Token nextToken()
{
	Token Tk;
	Tk.token_name[0]='\0';
	Tk.att[0]='\0';
	if(ch==EOF)
	{
		end=1;
		return Tk;
	}	
	
	char str[30];
	str[0]=0;
	switch(ch)
	{
		case ' ':	ch=getchar();		// things to escape or neglect
					return Tk;
		case '\t':	ch=getchar();
					return Tk;
		case '\n':	ch=getchar();
					line++;
					return Tk;
		case '\r':	ch=getchar();
					return Tk;
		case '\0':	ch=getchar();
					return Tk;
						
		case '(':	strcpy(Tk.token_name,"TK_OPEN");
					ch=getchar();
				 	strcpy(Tk.att,"NULL");
				 	
				 	Tk.lineNum=line;
				 	Tk.id=18;
				 	return Tk;
				  
		case ')':	strcpy(Tk.token_name,"TK_CLOSE");
				 	ch=getchar();
				 	strcpy(Tk.att,"NULL");
				 	Tk.lineNum=line;
				 	Tk.id=19;
				 	return Tk;
				 
		case ';':	strcpy(Tk.token_name,"TK_SEMI");
				 	ch=getchar();
				 	strcpy(Tk.att,"NULL");
				 	Tk.lineNum=line;
				 	Tk.id=20;
				 	return Tk;
				  
		case '=':	strcpy(Tk.token_name,"TK_EQUAL");
				 	ch=getchar();
				 	strcpy(Tk.att,"NULL");
				 	Tk.lineNum=line;
				 	Tk.id=21;
				 	return Tk;
				  
		case '!':	ch=getchar();
					if(ch=='=')
					{
						ch=getchar();
						strcpy(Tk.token_name,"TK_NOTEQUAL");
					}
					else
						end=2;
					
					strcpy(Tk.att,"NULL");
					Tk.lineNum=line;
					Tk.id=22;
					return Tk;
					
			
		case '<':	ch=getchar();
				//	str[i++]=ch;
					if(ch=='=')
					{
						strcpy(Tk.token_name,"TK_LEQ");
						Tk.lineNum=line;
						Tk.id=25;
						ch=getchar();
					}
					else
					{
						strcpy(Tk.token_name,"TK_LT");
						Tk.lineNum=line;
						Tk.id=23;
					}							
					strcpy(Tk.att,"NULL");
					return Tk;
					
		case '>':	ch=getchar();
					if(ch=='=')
					{
						strcpy(Tk.token_name,"TK_GEQ");
						Tk.lineNum=line;
						Tk.id=26;
						ch=getchar();
					}
					else
					{
						strcpy(Tk.token_name,"TK_GT");
						Tk.lineNum=line;
						Tk.id=24;
					}	
					strcpy(Tk.att,"NULL");
					return Tk;
					//str[i++]=ch;
					
					
		case ',':	strcpy(Tk.token_name,"TK_COMMA");
					strcpy(Tk.att,"NULL");
					Tk.lineNum=line;
					Tk.id=27;
					ch=getchar();
					return Tk;
					
					
		case ':':   strcpy(Tk.token_name,"TK_COLON");
					strcpy(Tk.att,"NULL");
					Tk.lineNum=line;
					Tk.id=28;
					ch=getchar();
					return Tk;			
	}
	

	
	if(ch<48 || (ch>57 && ch<65) || (ch>90 && ch<97) ||ch>122 )
	{
		end=2;
		return Tk;
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
				{	str[i]='\0';
					strcpy(Tk.att,str);
					strcpy(Tk.token_name,"TK_NUM");
					Tk.lineNum=line;
					Tk.id=17;
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
				else if(ch>='0' && ch<='9')
				{
					flag=2;
					str[i++]=ch;
				}
				else break;		
			}
			str[i]='\0';

				
					if(h[hash(str)].empty==0)
					{
						if(strcmp(str,keywords[h[hash(str)].id])==0)
						{
							strcpy(Tk.att,"NULL");
							strcpy(Tk.token_name,h[hash(str)].token_name);
							Tk.lineNum=line;
							Tk.id=h[hash(str)].id;
							return Tk;
						}
						else
						{
							strcpy(Tk.token_name,"TK_ID");		
							strcpy(Tk.att,str);
							Tk.lineNum=line;
							Tk.id=16;
							return Tk;
						}	
						
					}
				
				
				strcpy(Tk.token_name,"TK_ID");		
				strcpy(Tk.att,str);
				Tk.lineNum=line;
				Tk.id=16;
				return Tk;
										
		
		}
	}

}	

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void printTokenStream(FILE f)
{
	FILE *fp;
	fp=freopen("tokenStream.txt","w",stdout);
	
	fseek(tempFile,0,SEEK_SET);
	ch=getchar();
	Token token;
	while(1)
	{
		token=nextToken();
		if(end==1)
		break;
		else if(end==2)
		{
			fprintf(stderr,"error in line number %d with char=%c\n",line,ch);
			break;
		}
		else 
		{	if(token.token_name[0]!='\0')
			printf("<%s,%s>\n",token.token_name,token.att);
		}
	
	}
	//fseek(tempFile,0,SEEK_SET);
	fclose(fp);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void initializeScanner(char *filename)
{
	tempFile=freopen(filename,"r",stdin);
	
	filltable();
	ch=getchar();
	
}



