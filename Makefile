CC = clang
FLAGS = -Weverything -g -O2
LIBS = -L$(shell pwd)/lib -lcrypto -Wl,-rpath=$(shell pwd)/lib
LIB_SRC = src/libcrypto.c
LIB_FLAGS = -fPIC
CHALLENGES = 3 5 6

all:
	@echo "Usage:"
	@echo -e "Make lib\t\tfor creating the library."
	@echo -e "Make [challenge]\tfor creating challenge executables."

lib: 
	@mkdir -p lib
	$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c -o libcrypto.o;
	gcc -shared -Wl,-soname,libcrypto.so -o lib/libcrypto.so libcrypto.o;
	rm libcrypto.o;

test: lib
	@$(CC) $(FLAGS) $(LIBS) tests/test.c -o test 2> /dev/null
	@./test

$(CHALLENGES): lib
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge$@ src/challenge$@.c 
	bin/challenge$@.sh > output

# All challenges that require special treatment
6:
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge6 src/tuple.c src/challenge6.c 
	bin/challenge$@.sh > output

clean:
	ls **/*.o

.PHONY: lib test
