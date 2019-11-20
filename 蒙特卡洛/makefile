CC=gcc

CFLAGS = -fopenmp\
	-ggdb\
	-Wall\
	-Werror\
	-O0

all:
	$(CC) run.c $(CFLAGS) -o run

test:
	$(CC) run.c $(CFLAGS) -fsanitize=address -o check
	./check
clean:
	rm run check

.PHONY: all test clean
