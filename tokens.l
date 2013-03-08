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

element [[:upper:]][[:lower:]]{0,2}

%%

z|Z                                   {   return Z_TOK;            } 

i|I                                   {  return J_TOK; } 

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
