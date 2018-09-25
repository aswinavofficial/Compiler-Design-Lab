%{
#include<stdio.h>
#include<stdlib.h>
%}
%token digit letter
%%
stmt:A ;
A: letter B |letter ;
B: letter B | digit B | letter | digit ;
%%
void main(){
printf("enter input \n");
yyparse();
printf("valid");
exit(0);
}
void yyerror(){
printf("invalid");
exit(0);
}