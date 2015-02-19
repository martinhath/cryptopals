CC = clang
FLAGS = -Weverything -g -O2
LIBS = -L$(shell pwd)/lib -lssl -lcrypto -lhcrypto -Wl,-rpath=$(shell pwd)/lib

LIB_SRC = src/libhcrypto.c
LIB_FLAGS = -fPIC
LIB_BUILD_FLAGS = -shared -Wl,-soname,libhcrypto.so

FILES = src/tuple.c

CHALLENGES = 3 5
CHALLENGES_INPUT = 6 7

all:
	@echo "Usage:"
	@echo -e "Make lib\t\tfor creating the library."
	@echo -e "Make [challenge]\tfor creating challenge executables."
	@echo -e "Make test\t\tfor running the tests (see tests/)."

lib:
	@mkdir -p lib
	@$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c -o libhcrypto.o;
	@$(CC) $(LIB_BUILD_FLAGS) -o lib/libhcrypto.so libhcrypto.o;
	@rm libhcrypto.o;

test: lib
	@$(CC) $(FLAGS) $(LIBS) tests/test.c -o test 2> /dev/null
	@./test

$(CHALLENGES): lib
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge$@ $(FILES) src/challenge$@.c
	@echo ""
	@bin/challenge$@ #> output

$(CHALLENGES_INPUT): lib
	$(CC) $(FLAGS) $(LIBS) -o bin/challenge$@ $(FILES) src/challenge$@.c
	@echo ""
	@bin/challenge$@ < data/$@ > output


clean:
	ls **/*.o

.PHONY: lib test
