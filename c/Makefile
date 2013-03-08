CC=gcc
LDFLAGS= -lm
YACC=bison 
LEX=flex
CFLAGS= -std=c99 -D_GNU_SOURCE -g 
YFLAGS= -d 
EXEC=newt
OBJ=newt.o expression_parse.tab.o expression.o lex.yy.o 

default: all 

all: $(EXEC) 

${EXEC}: ${OBJ} 
	${CC} ${CFLAGS} -o ${EXEC} ${OBJ} ${LDFLAGS}

expression_parse.tab.c : expression_parse.y
	${YACC} ${YFLAGS} expression_parse.y
expression_parse.tab.h: expression_parse.y
expression_parse.tab.o: expression_parse.tab.c expression.o
expression.o: expression.c 
lex.yy.o: expression_parse.tab.h lex.yy.c 
lex.yy.c: tokens.l expression_parse.tab.h
	$(LEX) tokens.l
newt.o: newt.c expression_parse.tab.o

cleanup: 
	rm -f *.o 
	rm -f lex.yy.c 
	rm -f *.tab.* 

clean: 
	rm -f $(EXEC) 
	rm -f *.o 
	rm -f lex.yy.c 
	rm -f *.tab.* 

install: clean all cleanup 

build: clean all

