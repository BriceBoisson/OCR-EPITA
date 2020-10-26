ALL = init_neural_network.c walkthrough.c maths_functions.c cost_function.c training.c
CFLAGS = -Wall -Werror -Wextra

all : 
	gcc $(CFLAGS) -std=c99 -o out $(ALL) main.c -lm

testing :
	gcc $(CFLAGS) -std=c99 -o out $(ALL) test.c -lm

debugTest :
	gcc $(CFLAGS) -g -std=c99 -o out $(ALL) test.c -lm

debugMain :
	gcc $(CFLAGS) -g -std=c99 -o out $(ALL) main.c -lm

clean : 
	rm -f *.o out