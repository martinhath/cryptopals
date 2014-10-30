CC = gcc
FLAGS = -Wall -Wextra -pedantic -g -O 
LIBS = -L$(shell pwd)/lib -lcrypto -Wl,-rpath=$(shell pwd)/lib
LIB_SRC = src/libcrypto.c
LIB_FLAGS = -fPIC
CHALLENGES = 3 6

all:
	echo "Huheue"

lib: 
	$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c -o libcrypto.o;
	gcc -shared -Wl,-soname,libcrypto.so -o lib/libcrypto.so libcrypto.o;
	rm libcrypto.o;
	
$(CHALLENGES):
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge$@ src/challenge$@.c 

.PHONY: lib
