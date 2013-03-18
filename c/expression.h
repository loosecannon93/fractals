#ifndef EXPRESSION_H 
#define EXPRESSION_H 

#include <complex.h> 

struct expression_t; typedef struct expression_t expression_t; 
struct term_t;  typedef struct term_t term_t; 
struct factor_t ;typedef struct factor_t factor_t; 
struct exponential_t; typedef struct exponential_t exponential_t;
struct trig_t;      typedef struct trig_t trig_t; 

enum EXP_TYPE { TERM, PLUS, MINUS , // expression types 
                FACTOR, TIMES, DIVIDED_BY ,  //term types
                EXPONENTIAL , RAISED_TO , // facor types 
                NUMBER, VARIABLE, EXPRESSION, TRIG ,// exponential types  
                SIN, COS, SINH, COSH, EXP, LOG, 
                UNDEFINED } ; //type not yet set 


typedef struct expression_t {
    enum EXP_TYPE type;  
    union { 
        term_t *term; 
        struct plus { 
            expression_t *expression;
            term_t *term ;
        } plus;
        struct minus { 
            expression_t *expression ;
            term_t *term; 
        } minus; 
    } data;
} expression_t;  

typedef struct term_t { 
    enum EXP_TYPE type;  
    union { 
        factor_t *factor; 
        struct times { 
            term_t *term; 
            factor_t *factor; 
        } times; 
        struct divided_by { 
            term_t *term;
            factor_t *factor;
        } divided_by; 
    } data; 
} term_t; 

typedef struct factor_t { 
    enum EXP_TYPE type;  
    union { 
        exponential_t *exponential; 
        struct raised_to { 
            exponential_t *base; 
            exponential_t *pow; 
        } raised_to; 
    } data; 
} factor_t; 

typedef struct exponential_t { 
    enum EXP_TYPE type;  
    union { 
        complex number;
        char variable;  
        expression_t *expression; 
        trig_t  *trig;
    } data; 
} exponential_t;

typedef struct trig_t { 
    enum EXP_TYPE type; 
    union { 
        expression_t *sin; 
        expression_t *cos; 
        expression_t *sinh; 
        expression_t *cosh; 
        expression_t *exp; 
        expression_t *log;
    } data; 
} trig_t; 


//linked list of exprssions 
typedef struct expression_list_node { 
    expression_t *contents; 
    struct expression_list_node *next; 
} expression_list_node ; 
typedef struct expression_list { 
    expression_list_node *start; 
} expression_list;

// setter functions, set the type when updated
void expression_set_term(expression_t *e, term_t *t ) ;
void expression_set_plus(expression_t *e,  expression_t *a, term_t *b)  ;
void expression_set_minus(expression_t *e, expression_t *a, term_t *b);

void term_set_factor(term_t *t , factor_t *f) ; 
void term_set_times(term_t  *t, term_t *a , factor_t *b ); 
void term_set_divided_by(term_t *t , term_t *divedend, factor_t *divisor); 

void factor_set_exponential(factor_t *f , exponential_t *exp); 
void factor_set_raised_to(factor_t *f, exponential_t *base, exponential_t *power  ) ; 

void exponential_set_number( exponential_t *e , complex abi ) ; 
void exponential_set_variable( exponential_t *e , const char name/*, complex value*/ ) ; 
void exponential_set_expression( exponential_t *e , expression_t *expr ) ; 
void exponential_set_trig(exponential_t *e , trig_t *func) ; 

void trig_set_sin(trig_t *t, expression_t *argument ) ; 
void trig_set_cos(trig_t *t, expression_t *argument ) ; 
void trig_set_sinh(trig_t *t, expression_t *argument ) ; 
void trig_set_cosh(trig_t *t, expression_t *argument ) ; 
void trig_set_log(trig_t *t, expression_t *argument ) ; 
void trig_set_exp(trig_t *t, expression_t *argument ) ; 


// getters, check the type and Exit if we do anything with the wrong type 
term_t *expression_get_term(expression_t *e) ;
struct plus *expression_get_plus(expression_t *e); 
struct minus *expression_get_minus(expression_t *e);

factor_t *term_get_factor(term_t *t ) ; 
struct times *term_get_times(term_t  *t); 
struct divided_by *term_get_divided_by(term_t *t ); 

exponential_t *factor_get_exponential(factor_t *f ) ;
struct raised_to *factor_get_raised_to(factor_t *f ) ; 

complex exponential_get_number( exponential_t *e  ) ; 
char exponential_get_variable( exponential_t *e ) ; 
expression_t *exponential_get_expression( exponential_t *e ) ; 
trig_t *exponential_get_trig( exponential_t *e ) ; 

expression_t *trig_get_sin(trig_t *t) ;
expression_t *trig_get_cos(trig_t *t) ;
expression_t *trig_get_sinh(trig_t *t) ;
expression_t *trig_get_cosh(trig_t *t) ;
expression_t *trig_get_exp(trig_t *t) ;
expression_t *trig_get_log(trig_t *t) ;


// evaluate our exquation 
complex eval_exponential( exponential_t *exp, complex z ); 
complex eval_factor( factor_t *factor , complex z ) ; 
complex eval_term( term_t *term, complex z ) ; 
complex eval_expression( expression_t *expr, complex z ); 
complex eval_trig( trig_t *function, complex z ) ; 

// allocate and free
expression_t *new_expression(void) ; 
void free_expression(expression_t *e) ; 

term_t *new_term(void); 
void free_term(term_t *t) ; 

factor_t *new_factor(void); 
void free_factor(factor_t *f) ; 

exponential_t *new_exponential(void); 
void free_exponential(exponential_t *e) ; 

trig_t *new_trig(void); 
void free_trig(trig_t *t);

expression_list_node *new_expression_list_node(void); 
// freed by overlaying list 

expression_list *new_expression_list(void); 
void free_expression_list(expression_list *list) ; 

// list operations
void expression_list_push(expression_list *list, expression_t *expr ) ; 
expression_t *expression_list_pop(expression_list* list) ; 


void type_error(char *expected_name, int expected_value, int actual_value ) ; 

void print_expression(expression_t *expression, FILE *out);
void print_term(term_t *term, FILE *out);
void print_factor(factor_t *factor, FILE *out);
void print_exponential(exponential_t *exponential, FILE *out);

#endif // EXPRESSION_H 
