 %{
    #include<stdio.h>
%}

%token number
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'
%%

ArithmeticExpression: E{

         printf("\nResult:%d\n",$$);

         return 0;

        };

E:E'+'E {$$=$1+$3;}

 |E'-'E {$$=$1-$3;}

 |E'*'E {$$=$1*$3;}

 |E'/'E {$$=$1/$3;}

 |E'%'E {$$=$1%$3;}

 |'('E')' {$$=$2;}

 | number {$$=$1;}

;
%%
void main(){
   
   printf("\nEnter Expression:\n");
   yyparse();
}

void yyerror(){

   printf("\nNot valid Arithmetic Expression!!!\n\n");
}