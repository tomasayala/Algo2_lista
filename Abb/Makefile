#
# Makefile que crea y corre las pruebas
#
CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

abb:
	$(CC) *.c -o abb -g $(CFLAGS)

valgrind:
	valgrind $(VFLAGS) ./abb

clean:
	rm -f abb
