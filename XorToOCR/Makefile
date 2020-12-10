ALL = structure.c tools.c training.c traitement.c Load.c
CFLAGS = -Wall -Werror -Wextra
LDFLAGS= -lSDL2 -lSDL2_image

all : 
	gcc  $(CFLAGS) -std=c99 -o XOR $(ALL) main.c $(LDFLAGS) -lm

testing :
	gcc $(CFLAGS) -std=c99 -o XOR $(ALL) test.c -lm

debugTest :
	gcc $(CFLAGS) -g -std=c99 -o XOR $(ALL) test.c -lm

debugMain :
	gcc $(CFLAGS) -g -std=c99 -o XOR $(ALL) main.c -lm

clean : 
	rm -f *.o XOR
