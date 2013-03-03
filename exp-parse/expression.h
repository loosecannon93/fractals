#include <complex.h> 

union expression_t; typedef union expression_t expression_t; 
union term_t;  typedef union term_t term_t; 
 union factor_t ;typedef union factor_t factor_t; 
union exponential_t; typedef union exponential_t exponential_t; 

typedef union expression_t { 
    term_t *term; 
    struct { 
        expression_t *expression;
        term_t *term ;
    } plus;
    struct { 
        expression_t *expression ;
        term_t *term; 
    } minus; 
} expression_t;  

typedef union term_t { 
    factor_t *factor; 
    struct { 
        term_t *term; 
        factor_t *factor; 
    } times; 
    struct { 
        term_t *term;
        factor_t *factor;
    } divided_by; 
} term_t; 

typedef union factor_t { 
    exponential_t *exponential; 
    struct { 
        exponential_t *base; 
        exponential_t *pow; 
    } raised_to; 
} factor_t; 

typedef union exponential_t { 
    complex number;
    struct { 
       char letter; 
       complex value; 
    } variable;  
    expression_t *expression; 
} exponential_t;


complex eval_exponential( exponential_t , complex
complex eval_expression( expression_t expr, complex z ); 

