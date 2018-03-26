CC = gcc
CFLAGS = -Wall --pedantic --std=c11
HEADERS = input.h vartype.h

all: cvar_display.c $(HEADERS) input.o vartype.o
	$(CC) $(CFLAGS) input.o vartype.o cvar_display.c -o cvar_display

input.o: input.c input.h
	$(CC) $(CFLAGS) -c input.c

vartype.o: vartype.c vartype.h input.h
	$(CC) $(CFLAGS) -c vartype.c

clean:
	rm -f *.o
	rm -f cvar_display

