#include <stdio.h> 
#include <stdlib.h> 
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
void exponential_set_variable( exponential_t *e , const char name ) {
    e->type = VARIABLE; 
    e->data.variable = name ; 
} 
void exponential_set_expression( exponential_t *e , expression_t *expr ) { 
    e->type = EXPRESSION; 
    e->data.expression = expr; 
} 
///////////////////////////////////////////////////////////
///////////// END SETTERS /////////////////////////////////
//////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////// GETTERS /////////////////////////
////// getters, check the type and return the value ///////
///////Exit if we do anything with the wrong type /////////
///////////////////////////////////////////////////////////

// expression getters 
term_t *expression_get_term(expression_t *e) { 
    if ( e->type != TERM ) { type_error("TERM", TERM, e->type ) ; } 
    return (e->data.term); 
}
struct plus *expression_get_plus(expression_t *e) { 
    if ( e->type != PLUS ) { type_error("PLUS", PLUS, e->type ) ; } 
    return &(e->data.plus); 
} 
struct minus *expression_get_minus(expression_t *e) { 
    if ( e->type != MINUS ) { type_error("MINUS", MINUS, e->type ) ; } 
    return &(e->data.minus); 
} 

// term getters 
factor_t *term_get_factor(term_t *t ) { 
    if ( t->type != FACTOR ) { type_error("FACTOR", FACTOR, t->type ) ; } 
    return (t->data.factor); 
} 
struct times *term_get_times(term_t  *t) { 
    if ( t->type != TIMES ) { type_error("TIMES", TIMES, t->type ) ; } 
    return &(t->data.times); 
}
struct divided_by *term_get_divided_by(term_t *t )  {
    if ( t->type != DIVIDED_BY ) { type_error("DIVIDED_BY", DIVIDED_BY, t->type ) ; } 
    return &(t->data.divided_by); 
}

// factor getters
exponential_t *factor_get_exponential(factor_t *f ) { 
    if ( f->type != EXPONENTIAL ) { type_error("EXPONENTIAL", EXPONENTIAL, f->type ) ; } 
    return (f->data.exponential) ; 
} 
struct raised_to *factor_get_raised_to(factor_t *f ) { 
    if ( f->type != RAISED_TO ) { type_error("RAISED_TO", RAISED_TO, f->type ) ; } 
    return &(f->data.raised_to) ;  
} 

// exponential getters
complex exponential_get_number( exponential_t *e  ) { 
    if ( e->type != NUMBER ) {  type_error("NUMBER", NUMBER, e->type ) ; } 
    return (e->data.number ); 
}
char exponential_get_variable( exponential_t *e ) { 
    if ( e->type != VARIABLE ) {  type_error("VARIABLE", VARIABLE, e->type ) ; } 
    return e->data.variable;
} 
expression_t *exponential_get_expression( exponential_t *e ) {
    if ( e->type != EXPRESSION ) {  type_error("EXPRESSION", EXPRESSION, e->type ) ; } 
    return (e->data.expression ) ; 
} 
//////////////////////////////////////////////////////////////////////////////////////
/////////////////END GETTERS /////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
///////////// EVALUATION //////////////////////////////////////
//////////////////////////////////////////////////////////////

// evaluate our exquation 
complex eval_expression( expression_t *expr, complex z ) { 
    switch(expr->type) { 
        case TERM: 
        {
            term_t *term = expression_get_term(expr); 
            return eval_term(term, z);break; 
        }
        case PLUS: 
        { 
            struct plus *plus = expression_get_plus(expr); 
            return eval_expression(plus->expression,z) + eval_term(plus->term,z); break; 
        } 
        case MINUS:  
        { 
            struct minus *minus = expression_get_minus(expr) ; 
            return eval_expression(minus->expression,z) - eval_term(minus->term,z ) ; break ; 
        }
        default: 
            fprintf(stderr, "expression of noninitialized type . Aborting. \n" ) ; 
            exit(3) ; 
    }
}
complex eval_term( term_t *term, complex z ) { 
    switch(term->type) { 
        case FACTOR: 
        {
            factor_t *factor = term_get_factor(term); 
            return eval_factor(factor, z) ; break ; 
        }
        case TIMES: 
        { 
            struct times *times = term_get_times(term) ; 
            return eval_term(times->term,z) * eval_factor(times->factor,z) ; 
        }
        case DIVIDED_BY: 
        {
            struct divided_by *divided_by = term_get_divided_by(term); 
            return eval_term(divided_by->term,z) / eval_factor(divided_by->factor,z) ; 
        }
        default: 
            fprintf(stderr, "term of noninitialized type . Aborting. \n" ) ; 
            exit(3) ; 
    } 
}
complex eval_factor( factor_t *factor , complex z ) { 
    switch(factor->type) { 
        case EXPONENTIAL: 
        { 
            exponential_t *exponential = factor_get_exponential(factor); 
            return eval_exponential(exponential,z) ;
        } 
        case RAISED_TO : 
        { 
            struct raised_to *raised_to = factor_get_raised_to(factor) ; 
            complex base = eval_exponential(raised_to->base, z) ; 
            complex pow = eval_exponential(raised_to->pow, z) ; 
            return cpow(base, pow ); //complex power 
        }
        default: 
            fprintf(stderr, "factor of noninitialized type . Aborting. \n" ) ; 
            exit(3) ; 
    }
}
complex eval_exponential( exponential_t *exp, complex z ){ 
    switch(exp->type) { 
        case NUMBER: 
        {
            complex num = exponential_get_number(exp) ; 
            return num ; 
        }
        case VARIABLE: 
        { 
            //could add support for multiple variables, idk why though, would be fun to learn variadic functions  
            return z; 
        } 
        default: 
            fprintf(stderr, "exponential of noninitialized type . Aborting. \n" ) ; 
            exit(3) ; 
    }
}
////////////////////////////////////////////////
////////////////END EVAL ///////////////////////
///////////////////////////////////////////////


///////////////////////////////////////////////
//////// ALLOC / FREE ////////////////////////
//////////////////////////////////////////////

// allocate and free
expression_t *new_expression(void) { 
    expression_t *result =(expression_t*) malloc(sizeof(expression_t) ) ; 
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating expression\n" ) ; exit(4); } 

    result->type = UNDEFINED; 
    return result; 
} 
void free_expression(expression_t *expr) { 
  switch(expr->type) { 
        case TERM: 
        { 
            free_term(expr->data.term); 
            break; 
        }
        case PLUS: 
        { 
            free_expression(expr->data.plus.expression) ;
            free_term(expr->data.plus.term); 
            break; 
        } 
        case MINUS:  
        { 
            free_expression(expr->data.minus.expression) ;
            free_term(expr->data.minus.term); 
            break; 
        }
        default: 
            break;
    }
  free((void*) expr) ; 
}

term_t *new_term(void){ 
    term_t *result = (term_t*) malloc(sizeof(term_t)) ; 
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating term\n" ) ; exit(4); } 
    
    result->type = UNDEFINED; 
    return result; 
}    
void free_term(term_t *term) { 
    switch(term->type) { 
        case FACTOR: 
        { 
            free_factor(term->data.factor); 
            break; 
        }
        case TIMES: 
        { 
            free_term(term->data.times.term) ;
            free_factor(term->data.times.factor); 
            break; 
        } 
        case DIVIDED_BY:  
        { 
            free_term(term->data.divided_by.term) ;
            free_factor(term->data.divided_by.factor); 
            break; 
        }
        default: 
            break;
    }
  free((void*) term) ; 
}

factor_t *new_factor(void) { 
    factor_t *result = (factor_t*) malloc(sizeof(factor_t) ) ; 
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating factor\n" ) ; exit(4); } 

    result->type = UNDEFINED; 
    return result; 
} 
void free_factor(factor_t *factor) { 
    switch(factor->type) { 
        case EXPONENTIAL: 
        { 
            free_exponential(factor->data.exponential) ; 
            break;
        }
        case RAISED_TO: 
        {   
            free_exponential(factor->data.raised_to.base); 
            free_exponential(factor->data.raised_to.pow); 
            break; 
        } 
        default: 
            break; 
    } 
    free((void*) factor); 
}

exponential_t *new_exponential(void) { 
    exponential_t *result = (exponential_t*) malloc(sizeof(exponential_t)) ; 
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating exponential\n" ) ; exit(4); } 

    result->type  = UNDEFINED; 

    return result; 
} 

void free_exponential(exponential_t *e) { 
    if (e->type == EXPRESSION ) { 
        free_expression(e->data.expression) ; 
    }
    free((void* ) e) ; 
} 

expression_list *new_expression_list(void) { 
    expression_list *result = (expression_list*) malloc(sizeof(expression_list)) ;
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating list \n" ) ; exit(4); } 

    result->start = NULL; 

    return result; 
} 
void free_expression_list(expression_list *list ) { 
    expression_list_node *node = list->start; 
    while(node != NULL ) { 
        expression_list_node *temp_node = node; 
        free_expression(node->contents); 
        node = node->next;
        free((void*)temp_node); 
    } 
    free((void*) list ) ; 
    list = NULL ;
}
expression_list_node *new_expression_list_node() { 
    expression_list_node *result = malloc(sizeof(expression_list_node)); 
    if(result == NULL ) { fprintf(stderr, "Mem Error allocating list_node \n" ) ; exit(4); } 

    result->contents = NULL ; 
    result->next = NULL ; 

    return result; 
} 


///////////////////////////////////////////////////////
//////////////// END ALLOC ///////////////////////////
/////////////////////////////////////////////////////

// list operations 

void expression_list_push(expression_list *list, expression_t *expr) { 
    if ( list->start == NULL ) { // initialize if empty 
        list->start = new_expression_list_node();  
        list->start->contents = expr ; 
        return ; 
    } else {        
        expression_list_node *node = list->start; 
        while(node->next != NULL )  { 
            node = node->next; 
        } 
        node->next = new_expression_list_node(); 
        node->next->contents = expr; 
    }
} 
expression_t *expression_list_pop(expression_list *list) { 
    // pop from front of queue make it a FIFO
    if ( list->start == NULL ) { return NULL ;  fprintf(stderr, "Cannot pop from empty list\n" ) ;/* exit(5);*/ } 

    expression_t *expr = list->start->contents ;
    expression_list_node *new_start = list->start->next;
    free((void*)list->start) ;
    list->start = new_start;
    return expr; 
} 




/////// ERROR HANDLING ////////
void type_error(char *expected_name , int expected_value, int actual_value ) { 
    fprintf(stderr, "TypeMisMatch: Expected %s(%d) got %d instead. Aborted\n" , expected_name, expected_value, actual_value ); 
    exit(2) ; 
}

void print_expression(expression_t *expr ) { 
    printf("(E:  " ) ; 
    switch(expr->type ) { 
        case TERM: 
            printf("(" );
            print_term(expression_get_term(expr) ); 
            printf(")") ; 
            break; 
        case PLUS: 
        {
            struct plus *plus = expression_get_plus(expr) ; 
            printf("("); 
            print_expression(plus->expression); 
            printf("+"); 
            print_term(plus->term) ; 
            printf(")");
            break;
        }
        case MINUS: 
        {
            struct minus *minus = expression_get_minus(expr) ; 
            printf("("); 
            print_expression(minus->expression); 
            printf("-"); 
            print_term(minus->term) ; 
            printf(")");
            break;
        }
        default: 
            printf("?expr type unknowm?"); 
            break; 
    }
    printf(")"); 
} 
void print_term(term_t *term ) { 
    printf("(T:" ) ; 
    switch (term->type) { 
        case FACTOR: 
        printf("(") ; 
        print_factor(term_get_factor(term)) ; 
        printf(")"); 
        break;
        case TIMES: 
        {
            struct times *times = term_get_times(term); 
            printf("(");
            print_term(times->term) ; 
            printf("*");
            print_factor(times->factor) ; 
            printf(")"); 
            break;
        }
        case DIVIDED_BY : 
        { 
            struct divided_by *div = term_get_divided_by(term); 
            printf("("); 
            print_term(div->term) ; 
            printf("/");
            print_factor(div->factor) ; 
            printf(")"); 
            break;
        }
        default : 
            printf("?term type unknown?"); 
            break; 
    }
    printf(")"); 
}
void print_factor(factor_t *factor ) { 
    printf("(F:" ) ; 
    switch (factor->type) { 
        case EXPONENTIAL: 
        printf("(") ; 
        print_exponential(factor_get_exponential(factor)) ; 
        printf(")"); 
        break;
        case RAISED_TO: 
        {
            struct raised_to *raised_to = factor_get_raised_to(factor); 
            printf("(");
            print_exponential(raised_to->base)  ; 
            printf("^");
            print_exponential(raised_to->pow) ; 
            printf(")"); 
            break;
        }
        default : 
            printf("?factor type unknown?"); 
            break; 
    }
    printf(")"); 
}
void print_exponential(exponential_t *exp) { 
    printf("(EXP:" );
    switch(exp->type) { 
        case NUMBER: 
        {
            complex num = exponential_get_number(exp) ;
            printf("%f + %fi", creal(num) , cimag(num ) ) ; 
            break;
        } 
        case VARIABLE: 
            putchar(exponential_get_variable(exp)) ; 
            break; 
        case EXPRESSION: 
            print_expression(exponential_get_expression(exp)) ; 
            break; 
        default:
            printf("?exponential type unknown?" ) ; 
            break;
    }
    printf("("); 
} 




            





