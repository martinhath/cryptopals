CC = gcc
FLAGS = -Wall -Wextra -pedantic -g -O
LIB = src/libcrypto.c
CHALLENGES = 3 6

all:
	echo "Huheue"
	
$(CHALLENGES):
	$(CC) $(FLAGS) $(LIB) -o bin/challenge$@ src/challenge$@.c 

