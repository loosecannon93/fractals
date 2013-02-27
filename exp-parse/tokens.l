%{
// tokens.l
// tokenization for complex valued fucntions 

#include <stdio.h>
#include <complex.h> 
#include "func.tab.h"

int yyparse();
%}

%option noyywrap

element [[:upper:]][[:lower:]]{0,2}

%%

z|Z                                   {   return Z;            } 

i|I                                   {  return J; } 

[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)? {   
                                            yylval.num = atof(yytext); 
                                            return NUMBER;
                                      } 

"^"                                   {   return RAISED_TO;   }
"+"                                   {   return PLUS;  } 
"-"                                   {   return MINUS; } 
"*"                                   {   return TIMES;  }
"/"                                   {   return DIVIDED_BY;  } 


"("                                   {   return OPEN_PAREN; }
")"                                   {   return CLOSE_PAREN; }

[ \t]           {}

.               {   return ERROR; }

\n              {   return EOLN; }

<<EOF>>         {   return EOFTOK; }

%%
