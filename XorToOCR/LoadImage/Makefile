
CC=gcc 
CFLAGS=-Wall -Werror -Wextra -O0
LDFLAGS= -lSDL2
EXEC=main



all: $(EXEC)


main: main.o 
	$(CC) -o main.o $(LDFLAGS) -MMD


main.o: Load.c
	$(CC) -o main.o -c Load.c $(CFLAGS)


clean:
	rm -rf *.o



	
