CC=gcc
CPPFLAGS= -MMD `pkg-config --cflags gtk+-3.0`
CFLAGS= -Wall -Wextra -std=c99 -g -D_XOPEN_SOURCE=600
LDLIBS= `pkg-config --libs gtk+-3.0` -lSDL2 -lm -rdynamic -fsanitize=address
EXEC= OCR


all: $(EXEC)


OCR: main.o segmentation.o cleanerimage.o tools.o display.o extraction.o extractchar.o structure.o training.o toolsnetworks.o traitement.o Load.o
	$(CC) -o OCR main.o segmentation.o cleanerimage.o tools.o display.o extraction.o extractchar.o structure.o training.o toolsnetworks.o Load.o traitement.o $(LDLIBS)
	rm -rf *.o *.d


main.o: main.c
	$(CC) -o main.o -c main.c $(CFLAGS) $(CPPFLAGS)

segmentation.o: ImageTreatment/Segmentation/segmentation.c
	$(CC) -o segmentation.o -c ImageTreatment/Segmentation/segmentation.c $(CFLAGS) $(CPPFLAGS)

cleanerimage.o: ImageTreatment/Filter/cleanerimage.c
	$(CC) -o cleanerimage.o -c ImageTreatment/Filter/cleanerimage.c $(CFLAGS) $(CPPFLAGS)

tools.o: ImageTreatment/Tools/tools.c
	$(CC) -o tools.o -c ImageTreatment/Tools/tools.c $(CFLAGS) $(CPPFLAGS) -lm

display.o: ImageTreatment/display.c
	$(CC) -o display.o -c ImageTreatment/display.c $(CFLAGS) $(CPPFLAGS)

extraction.o: ImageTreatment/extraction/extraction.c
	$(CC) -o extraction.o -c ImageTreatment/extraction/extraction.c $(CFLAGS) $(CPPFLAGS)

extractchar.o: ImageTreatment/extraction/extractchar.c
	$(CC) -o extractchar.o -c ImageTreatment/extraction/extractchar.c $(CFLAGS) $(CPPFLAGS)

structure.o: NeuralNetwork/structure.c
	$(CC) -o structure.o -c NeuralNetwork/structure.c $(CFLAGS) $(CPPFLAGS)

training.o: NeuralNetwork/training.c
	$(CC) -o training.o -c NeuralNetwork/training.c $(CFLAGS) $(CPPFLAGS)

toolsnetworks.o: NeuralNetwork/toolsnetworks.c
	$(CC) -o toolsnetworks.o -c NeuralNetwork/toolsnetworks.c $(CFLAGS) $(CPPFLAGS)

traitement.o: NeuralNetwork/traitement.c
	$(CC) -o traitement.o -c NeuralNetwork/traitement.c $(CFLAGS) $(CPPFLAGS)

Load.o: NeuralNetwork/Load.c
	$(CC) -o Load.o -c NeuralNetwork/Load.c $(CFLAGS) $(CPPFLAGS)



Test: main.c
	$(CC) -o main.o -c main.c $(CFLAGS) $(CPPFLAGS)
	

clean:
	rm -rf *.o *.d


	