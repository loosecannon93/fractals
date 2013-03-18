%{
    // parse.y

#include <stdio.h>
#include <stdlib.h>
#include <complex.h> 
#include "expression.h" 

void yyerror(const char *);
int yylex(void);

extern expression_list *expressions; 

%}



%union { 
    expression_t *expr; 
    term_t *term ;
    factor_t * factor;
    exponential_t *expn;
    trig_t *trig;
    complex num; 
} 

%token RAISED_TO_TOK PLUS_TOK MINUS_TOK TIMES_TOK DIVIDED_BY_TOK Z_TOK OPEN_PAREN_TOK CLOSE_PAREN_TOK COMMENT_TOK ERROR_TOK EOLN_TOK EOF_TOK 
%token SIN_TOK COS_TOK SINH_TOK COSH_TOK LOG_TOK EXP_TOK 
%token<num> NUMBER_TOK J_TOK
%type<expr>  expression 
%type<term> term 
%type<factor> factor 
%type<expn> exponential number 
%type<trig> trig_function
%start input

%error-verbose

%%

input
    : lines EOF_TOK     { YYACCEPT; }        
    ;

lines
    :
    | lines line
    ;
line 
    : expression EOLN_TOK           { 
        expression_list_push(expressions , $1 ) ;      
    } 
    | COMMENT_TOK
    | ERROR_TOK EOLN_TOK                { printf("error\n"); } 
    | EOLN_TOK                      
    ;

expression
    : term                              {
        expression_t *expr = new_expression(); 
        expression_set_term(expr, $1) ; 
        $$ = expr; 
    }
    | expression PLUS_TOK term              { 
        expression_t *expr = new_expression(); 
        expression_set_plus(expr, $1, $3 ) ; 
        $$ = expr; 
    } 
    | expression MINUS_TOK term             { 
        expression_t *expr = new_expression(); 
        expression_set_minus(expr, $1, $3 ) ; 
        $$ = expr; 
    }
    ; 
term
    : factor { 
        term_t *term = new_term(); 
        term_set_factor(term, $1 ) ; 
        $$ = term ; 
    }
    | term TIMES_TOK factor                 {
        term_t *term = new_term(); 
        term_set_times(term, $1, $3 ) ; 
        $$ = term ; 
    }
    | term DIVIDED_BY_TOK factor            { 
        term_t *term = new_term(); 
        term_set_divided_by(term, $1, $3); 
        $$ = term ;
    } 
    ; 
factor
    : exponential {                       
        factor_t *fact = new_factor(); 
        factor_set_exponential(fact,$1);
        $$ = fact; 
    }
    | exponential RAISED_TO_TOK exponential {
        factor_t *fact = new_factor(); 
        factor_set_raised_to(fact,$1,$3);
        $$ = fact; 
    } 
    ;
exponential
    : number                   
    | Z_TOK { 
        exponential_t *var = new_exponential(); 
        exponential_set_variable(var,'z'); 
        $$ = var; 
    } 
    | OPEN_PAREN_TOK expression CLOSE_PAREN_TOK { 
        exponential_t *exp = new_exponential(); 
        exponential_set_expression(exp,$2); 
        $$ = exp; 
    } 
    ;
number
    : NUMBER_TOK                     { 
        exponential_t *num = new_exponential(); 
        exponential_set_number(num,$1); 
        $$ = num; 
    } 
    | OPEN_PAREN_TOK MINUS_TOK NUMBER_TOK CLOSE_PAREN_TOK { 
        exponential_t *num = new_exponential(); 
        exponential_set_number(num,$3*-1); 
        $$ = num; 
    } 
    | J_TOK { 
        exponential_t *num = new_exponential(); 
        exponential_set_number(num,I); 
        $$ = num; 
    }
    ; 









%%

void yyerror(const char *msg) { fprintf(stderr, "parse error: %s\n" , msg) ; }

