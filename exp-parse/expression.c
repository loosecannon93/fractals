#include <complex.h> 
#include "expression.h" 


///////////////////////////////////////////////////////////
//// SETTER functions, set the type when updated //////////
//////////////////////////////////////////////////////////

/// expression setters /// 
void expression_set_term(expression_t *e, term_t *t ){ 
    e->type =TERM; 
    e->data.term= t;
}
void expression_set_plus(expression_t *e,  expression_t *a, term_t *b) { 
    e->type = PLUS ; 
    e->data.plus.expression = a ; 
    e->data.plus.term = b ;
} 
void expression_set_minus(expression_t *e, expression_t *a, term_t *b) { 
    e->type = MINUS ; 
    e->data.minus.expression = a ; 
    e->data.minus.term = b ; 
} 

/// term setters ///
void term_set_factor(term_t *t , factor_t *f){ 
    t->type = FACTOR; 
    t->data.factor = f ; 
} 
void term_set_times(term_t  *t, term_t *a , factor_t *b ){ 
    t->type = TIMES; 
    t->data.times.term = a ; 
    t->data.times.factor = b ; 
} 
void term_set_divided_by(term_t *t , term_t *dividend, factor_t *divisor){ 
    t->type = DIVIDED_BY; 
    t->data.divided_by.term = dividend; 
    t->data.divided_by.factor = divisor;
}

/// factor setters /// 
void factor_set_exponential(factor_t *f , exponential_t *exp) { 
    f->type= EXPONENTIAL; 
    f->data.exponential = exp ; 
} 
void factor_set_raised_to(factor_t *f, exponential_t *base, exponential_t *power  ) { 
    f->type = RAISED_TO ; 
    f->data.raised_to.base= base ; 
    f->data.raised_to.pow = power; 
}

/// xponential setters ///
void exponential_set_number( exponential_t *e , complex abi ) { 
    e->type = NUMBER; 
    e->data.number = abi; 
} 
void exponential_set_variable( exponential_t *e , const char name, complex value ) {
    e->type = VARIABLE; 
    e->data.variable.letter = name ; 
    e->data.variable.value = value; 
} 
void exponential_set_expresion( exponential_t *e , expression_t *expr ) { 
    e->type = EXPRESSION; 
    e->data.expression = expr; 
} 
///////////////////////////////////////////////////////////
///////////// END SETTERS /////////////////////////////////
//////////////////////////////////////////////////////////
/*
// getters, check the type and Exit if we do anything with the wrong type 
void *expression_get_term(expression_t *e) ;
struct plus *expression_get_plus(expression_t *e); 
struct minus *expression_get_minus(expression_t *e);

factor_t *term_get_factor(term_t *t ) ; 
struct times *term_get_times(term_t  *t); 
struct divided_by *term_get_divided_by(term_t *t ); 

exponential_t *factor_get_exponential(factor_t *f ) ;
struct raised_to *factor_get_raised_to(factor_t *f ) ; 

complex *exponential_get_number( exponential_t *e  ) ; 
struct variable *exponential_get_variable( exponential_t *e ) ; 
expression_t *exponential_get_expresion( exponential_t *e ) ; 


// evaluate our exquation 
complex eval_exponential( exponential_t exp, complex z ); 
complex eval_factor( factor_t factor , complex z ) ; 
complex eval_term( term_t term, complex z ) ; 
complex eval_expression( expression_t expr, complex z ); 

// allocate and free
expression_t *new_expression(void) ; 
void free_expression(expression_t *e) ; 

term_t new_term(void); 
void free_term(term_t *t) ; 

factor_t new_factor(void); 
void free_factor(factor_t *f) ; 

exponential_t new_exponential(void); 
void free_exponential(exponential_t *e) ; 
*/

