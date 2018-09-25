 %{

    #include<stdio.h>
    int valid=1;   
%}

%token num id op

%%
start : id '=' s ';'
s :     id x| num x| '-' num x| '(' s ')' x;

x :    op s| '-' s|;

%%

int yyerror(){
    valid=0;
    printf("\nInvalid!!!!!\n");
    return 0;
}

int main(){
    printf("\nEnter expression:\n");
    yyparse();
    if(valid){
        printf("\nValid\n");
    }

}
