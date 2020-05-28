#
# Makefile que crea y corre las pruebas
#
CC = gcc
CFLAGS = -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

lista:
	$(CC) *.c -o lista_se -g $(CFLAGS)

valgrind:
	valgrind $(VFLAGS) ./lista_se

clean:
	rm -f lista_se
