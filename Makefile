CFLAGS += -std=c99 -O3 -Wall
LDFLAGS += -lm
BUILD_DIR = build
CC = gcc
TIME = "Total time: %e seconds"

$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

%.run: $(BUILD_DIR)/%.o $(BUILD_DIR)/euler_math.o $(BUILD_DIR)/euler_bitarray.o
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/euler_math.o $(BUILD_DIR)/euler_bitarray.o $(LDFLAGS) -o $(BUILD_DIR)/$*
	TIME=$(TIME) time $(BUILD_DIR)/$*

%.native: %.ml
	ocamlbuild -cflags '-I +zarith' -lflags '-I +zarith bigarray.cmxa zarith.cmxa' $*.native
	
%.run: %.ml
	ocamlbuild -cflags '-I +zarith' -lflags '-I +zarith bigarray.cmxa zarith.cmxa' $*.native
	TIME=$(TIME) time ./$*.native
	
%.run: %.py
	TIME=$(TIME) time python -u $<
	
