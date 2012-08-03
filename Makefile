CFLAGS += -std=c99 -O3 -lm -Wall
CC = gcc
TIME = "Total time: %e seconds"

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.run: %.c euler_math.o
	$(CC) $(CFLAGS) $< euler_math.o -o $*
	TIME=$(TIME) time ./$*
