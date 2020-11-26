ALL = structure.c tools.c training.c traitement.c
CFLAGS = -Wall -Werror -Wextra

all : 
	gcc $(CFLAGS) -std=c99 -o XOR $(ALL) main.c -lm

testing :
	gcc $(CFLAGS) -std=c99 -o XOR $(ALL) test.c -lm

debugTest :
	gcc $(CFLAGS) -g -std=c99 -o XOR $(ALL) test.c -lm

debugMain :
	gcc $(CFLAGS) -g -std=c99 -o XOR $(ALL) main.c -lm

clean : 
	rm -f *.o XOR
