
import Data.Complex 

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



