--module Expression 

import Data.Complex 
import Text.ParserCombinators.ReadP 
import Data.Char

data Expression = Expression Term 
                | Plus Expression Term  
                | Minus Expression Term 
                deriving ( Show, Eq ) 

data Term = Term Factor
          | Times Term Factor 
          | DividedBy Term Factor 
          deriving ( Show, Eq ) 

data Factor = Factor Exponential 
            | RaisedTo Exponential Exponential 
            deriving ( Show, Eq ) 

data Exponential = Number ( Complex Double )  
                 | Variable
                 | SubExpression Expression
                 deriving ( Show, Eq ) 

evalExpression :: Expression -> Complex Double -> Complex Double 
evalExpression (Expression term) z = evalTerm term z
evalExpression (Plus e t) z = (evalExpression e z ) + (evalTerm t z ) 
evalExpression (Minus e t) z = (evalExpression e z ) - (evalTerm t z ) 

evalTerm :: Term -> Complex Double -> Complex Double 
evalTerm (Term factor ) z = evalFactor factor z 
evalTerm (Times term factor) z = (evalTerm term z )  * (evalFactor factor z ) 
evalTerm (DividedBy term factor ) z  = (evalTerm term z )  / (evalFactor factor z )  

evalFactor :: Factor -> Complex Double -> Complex Double 
evalFactor (Factor expn ) z  = evalExponential expn z
evalFactor (RaisedTo base pow ) z = (evalExponential base z ) ** ( evalExponential pow z ) 

evalExponential :: Exponential -> Complex Double -> Complex Double 
evalExponential (Number c) _ = c 
evalExponential Variable z = z 
evalExponential (SubExpression expr) z = evalExpression expr z 


instance Read Expression where 
    readsPrec _ = readP_to_S expression where 
        expression = naked_term +++ plus +++ minus where 
            naked_term = do 
                t <- term 
                return ( Expression t  ) 
            plus = do 
                e <- expression 
                plus_sign 
                t <- term 
                return ( Plus e t ) 
            minus = do 
                e <- expression 
                minus_sign 
                t <- term 
                return (Minus e t ) 
        term = naked_factor +++ times +++ divided_by where 
            naked_factor = do 
                f <- factor 
                return ( Term  f ) 
            times = do 
                t <- term 
                times_sign 
                f <- factor 
                return (Times t f ) 
            divided_by = do 
                t <- term 
                division_sign 
                f <- factor 
                return (DividedBy t f ) 
        factor = naked_exponential +++ raised_to where 
            naked_exponential = do 
                e <- exponential 
                return (Factor e ) 
            raised_to = do 
                base <- exponential 
                power_sign 
                power <- exponential 
                return (RaisedTo base power ) 
        exponential = number +++ variable +++ paren_expression where 
            number = integer +++ imaginary 
            variable = do 
                optional skipSpaces 
                satisfy isAlpha 
                optional skipSpaces 
                return Variable 
            paren_expression = do 
                sub <- between (char '(' ) (char '(' ) expression  
                return $  SubExpression sub  
            integer = do 
                int <-  munch1 isDigit
                optional $ char '.' 
                fractional <- option "0" (munch1 isDigit) 
                let double = read ( int ++ "." ++ fractional )::Double 
                return ( Number ( double :+ 0 ) ) 
            imaginary = do 
                char 'i' +++ char 'I' 
                return ( Number ( 0.0 :+ 1 ) ) 
            


            
        plus_sign = do 
            optional skipSpaces  
            char '+' 
            optional skipSpaces  
        minus_sign = do 
            optional skipSpaces  
            char '-' 
            optional skipSpaces  
        times_sign = do 
            optional skipSpaces  
            char '*' 
            optional skipSpaces  
        division_sign = do 
            optional skipSpaces  
            char '/' 
            optional skipSpaces  
        power_sign = do 
            optional skipSpaces  
            char '^' 
            optional skipSpaces  
        

            
            
            

                   

