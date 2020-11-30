CC=gcc 
CFLAGS=-Wall -Werror -Wextra -O0 
LDFLAGS= -lSDL2
EXEC= ImageTreatment



all: $(EXEC)


ImageTreatment: main.o segmentation.o cleanerimage.o tools.o display.o extraction.o 
	$(CC) -o ImageTreatment main.o segmentation.o cleanerimage.o tools.o display.o extraction.o $(LDFLAGS) -MMD


main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS)

segmentation.o: Segmentation/segmentation.c
	$(CC) -o segmentation.o -c Segmentation/segmentation.c $(CFLAGS)

cleanerimage.o: Filter/cleanerimage.c
	$(CC) -o cleanerimage.o -c Filter/cleanerimage.c $(CFLAGS)

tools.o: Tools/tools.c
	$(CC) -o tools.o -c Tools/tools.c $(CFLAGS)

display.o: display.c
	$(CC) -o display.o -c display.c $(CFLAGS)

extraction.o: extraction/extraction.c
	$(CC) -o extraction.o -c extraction/extraction.c $(CFLAGS)

clean:
	rm -rf *.o



	