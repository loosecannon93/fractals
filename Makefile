LDFLAGS=-lm
CFLAGS=-std=c99 -O3
newt:  newt.c 
	gcc $(CFLAGS) newt.c -o newt $(LDFLAGS) 
 
