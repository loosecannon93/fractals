CFLAGS=-std=c99 
LDFLAGS=-lm
YACC=bison
LEX=flex 

complez: lex.yy.c func.tab.c 
	gcc $(CFLAGS) lex.yy.c func.tab.c $(LDFLAGS) 
lex.yy.c: tokens.l 
	flex tokens.l
func.tab.c: func.y
	bison -d func.y
