CFLAGS += -std=c99 -O3 -Wall
LDFLAGS += -lm
CC = gcc
TIME = "Total time: %e seconds"

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.run: %.o euler_math.o euler_bitarray.o
	$(CC) $(CFLAGS) $< euler_math.o euler_bitarray.o $(LD_FLAGS) -o $*
	TIME=$(TIME) time ./$*
