%{
// tokens.l
// tokenization for complex valued fucntions 

#include <stdio.h>
#include <complex.h> 
#include "expression.h" 
#include "expression_parse.tab.h"

int yyparse();
%}

%option noyywrap


%%

sin                                   { return SIN_TOK; } 
cos                                   { return COS_TOK; } 
sinh                                  { return SINH_TOK; }
cosh                                  { return COSH_TOK ; } 
log                                   { return LOG_TOK; } 
exp                                   { return EXP_TOK; } 

z|Z                                   {   return Z_TOK;            } 

i|I                                   {  return J_TOK; } 

#.*\n                                 { return COMMENT_TOK; } 

[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)? {   
                                            yylval.num = atof(yytext); 
                                            return NUMBER_TOK;
                                      } 

"^"                                   {   return RAISED_TO_TOK;   }
"+"                                   {   return PLUS_TOK;  } 
"-"                                   {   return MINUS_TOK; } 
"*"                                   {   return TIMES_TOK;  }
"/"                                   {   return DIVIDED_BY_TOK;  } 


"("                                   {   return OPEN_PAREN_TOK; }
")"                                   {   return CLOSE_PAREN_TOK; }

[ \t]           {}

.               {   return ERROR_TOK; }

\n              {   return EOLN_TOK; }

<<EOF>>         {   return EOF_TOK; }

%%
