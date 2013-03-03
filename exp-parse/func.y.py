# %{
#     // parse.y
# 
# #include <stdio.h>
# #include <stdlib.h>
# #include <complex.h> 
# 
# void yyerror(char *);
# int yylex(void);
# 
# complex z = 0; 
# %}
start = 'input'
tokens =  ['RAISED_TO', 'PLUS', 'MINUS', 'TIMES', 'DIVIDED_BY', 'OPEN_PAREN', 'CLOSE_PAREN', 'ERROR', 'EOLN', 'EOFTOK', 'J', 'Z', 'NUMBER']

precedence =  []

# -------------- RULES ----------------

def p_input_1(p):
    '''input : lines EOFTOK'''
    # { YYACCEPT; }

def p_lines_1(p):
    '''lines : '''

def p_lines_2(p):
    '''lines : lines line'''

def p_line_1(p):
    '''line : expression EOLN'''
    # { printf("%f , %f \n", creal($$), cimag($$) ) ; }

def p_line_2(p):
    '''line : ERROR EOLN'''
    # { printf("error\n"); }

def p_line_3(p):
    '''line : EOLN'''
    # { printf("err\n");}

def p_expression_1(p):
    '''expression : term'''
    # { $$ = $1 }

def p_expression_2(p):
    '''expression : expression PLUS term'''
    # { $$ = $1 + $3 }

def p_expression_3(p):
    '''expression : expression MINUS term'''
    # { $$ = $1 - $3 }

def p_term_1(p):
    '''term : factor'''
    # { $$ = $1  }

def p_term_2(p):
    '''term : term TIMES factor'''
    # { $$ = $1 * $3 }

def p_term_3(p):
    '''term : term DIVIDED_BY factor'''
    # { $$ = $1 / $3 }

def p_factor_1(p):
    '''factor : exponential'''
    # { $$ = $1 }

def p_factor_2(p):
    '''factor : exponential RAISED_TO exponential'''
    # { $$ = cpow($1,$3) }

def p_exponential_1(p):
    '''exponential : number'''
    # { $$ = $1; }

def p_exponential_2(p):
    '''exponential : Z'''
    # { $$ = z ; }

def p_exponential_3(p):
    '''exponential : OPEN_PAREN expression CLOSE_PAREN'''
    # { $$ = $2; }

def p_number_1(p):
    '''number : NUMBER'''
    # { $$ = $1; }

def p_number_2(p):
    '''number : OPEN_PAREN MINUS NUMBER CLOSE_PAREN'''
    # { $$ = -1*$3 ; }

def p_number_3(p):
    '''number : J'''
    # { $$ = I; }

# -------------- RULES END ----------------
# 
# 
# void yyerror(char *msg) {}
# int main() { 
#     yyparse(); 
# } 

if __name__ == '__main__':
    from ply import *
    yacc.yacc()

