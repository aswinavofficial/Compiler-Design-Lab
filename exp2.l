digit [0-9]*
letter [a-zA-Z]
%%
"int"|"return"|"goto"|"char"|"if"|"else"|"for"|"while"|"do"|"void"|"printf"|"switch"|"float"|"double" {printf("\n%s\tkeyword",yytext);}
{digit}*                                                    {printf("\n%s\tNumber",yytext);}
("_")*{letter}("_"|{letter}|{digit})*		                {printf("\n%s\tIdentifier",yytext);}
{letter}*\(({letter}|{digit})*\)                            {printf("\n%s\tFunction",yytext);}
#.*                                                         {printf("\n%s\tHeader File",yytext);}
\/\/.*                                                      {printf("\n%s\tComment",yytext);}
\".*\"                                                      {printf("\n%s\tString",yytext);}
"+"|"-"|"*"|"/"|"%"                                         {printf("\n%s\tArithmetic Operator",yytext);}
"<"|">"|"<="|">="|"=="|"!="                                 {printf("\n%s\tRelational Operator",yytext);}
"="                                                         {printf("\n%s\tAssignment Operator",yytext);}
\{                                                          {printf("\n%s\tOpening Brace\nBLOCK BEGINS",yytext);}                                                       
\}                                                          {printf("\nBLOCK ENDS\n%s\tClosing Brace",yytext);}                                                 
\;                                                          {printf("\n%s\tDelimiter",yytext);}
\(                                                          {printf("\n%s\tOpening Bracket",yytext);}
\)                                                          {printf("\n%s\tClosing Bracket",yytext);}
%%
int main(){
	FILE *file;
	file = fopen("input.c","r");
	if(!file)
	{	
		printf("File not found!!!");
		exit(0);
	}		
	yyin = file;
	yylex();
	printf("\nCompleted Scanning!");
	return 0;
}
