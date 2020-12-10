# Makefile

CC=gcc
CPPFLAGS= -MMD  `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -g
LDFLAGS=
LDLIBS= `pkg-config --libs gtk+-3.0` -lSDL2 -lm -rdynamic

SRC=	main.c

OBJ= ${SRC:.c=.o}
DEP= ${SRC:.c=.d}


all: main

-include ${DEP}

main: ${OBJ}

clean:
	rm -f ${OBJ} ${DEP} main

# END
