 class ExpressionParser

 rule
    input: lines EOFTOK 
    lines: 
        | lines line 
    line: expression EOLN_TOK 
        | COMMENT_TOK 
        | ERROR_TOK 
        | EOLN_TOK 

    expression: term 
              | expression PLUS_TOK term 
              | expression MINUS_TOK term 
    term: factor 
        | term TIMES_TOK factor 
        | term DIVIDED_BY_TOK factor 
    factor: exponential 
          | exponential RAISED_TO exponential 
    exponential: number 
               | Z_TOK 
               | OPEN_PAREN_TOK expression CLOSE_PAREN_TOK 
    number: NUMBER_TOK 
          | OPEN_PAREN_TOK  MINUS_TOK NUMBER_TOK CLOSE_PAREN_TOK 
          | J_TOK 

