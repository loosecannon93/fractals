%{
    // parse.y

#include <stdio.h>
#include <stdlib.h>
#include <complex.h> 

void yyerror(char *);
int yylex(void);

complex z = 0; 
%}



%token RAISED_TO PLUS MINUS TIMES DIVIDED_BY  OPEN_PAREN CLOSE_PAREN ERROR EOLN EOFTOK

%union { 
    complex num ;
} 

%token<num> J Z NUMBER 
%type<num>  expression term factor exponential number line
%start input

%%

input
    : lines EOFTOK            { YYACCEPT; }
    ;

lines
    :
    | lines line
    ;
line 
    : expression EOLN           { printf("%f , %f \n", creal($$), cimag($$) ) ; } 
    | ERROR EOLN                { printf("error\n"); } 
    | EOLN                      { printf("err\n");} 
    ;

expression
    : term                              { $$ = $1 } 
    | expression PLUS term              { $$ = $1 + $3 } 
    | expression MINUS term             { $$ = $1 - $3 } 
    ; 
term
    : factor                            { $$ = $1  } 
    | term TIMES factor                 { $$ = $1 * $3 } 
    | term DIVIDED_BY factor            { $$ = $1 / $3 } 
    ; 
factor
    : exponential                       { $$ = $1 } 
    | exponential RAISED_TO exponential { $$ = cpow($1,$3) } 
    ;
exponential
    : number                     { $$ = $1; } 
    | Z                          { $$ = z ; } 
    | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; } 
    ;
number
    : NUMBER                     { $$ = $1; } 
    | OPEN_PAREN MINUS NUMBER CLOSE_PAREN { $$ = -1*$3 ; } 
    | J                          { $$ = I; } 
    ; 









%%

void yyerror(char *msg) {}
int main() { 
    yyparse(); 
} 
