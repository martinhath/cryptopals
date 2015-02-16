CC = clang
FLAGS = -Weverything -g -O 
LIBS = -L$(shell pwd)/lib -lcrypto -Wl,-rpath=$(shell pwd)/lib
LIB_SRC = src/libcrypto.c
LIB_FLAGS = -fPIC
CHALLENGES = 3 6

all:
	@echo "Usage:"
	@echo -e "Make lib\t\tfor creating the library."
	@echo -e "Make [challenge]\tfor creating challenge executables."

lib: 
	@mkdir -p lib
	$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c -o libcrypto.o;
	gcc -shared -Wl,-soname,libcrypto.so -o lib/libcrypto.so libcrypto.o;
	rm libcrypto.o;
	
$(CHALLENGES):
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge$@ src/challenge$@.c 

.PHONY: lib
