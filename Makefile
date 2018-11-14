# FLAGS
CC = gcc
CFLAGS = -g -Wall
LDLIBS =

# PATHS
SRCPATH = ./src/
HDRPATH = ./include/
OBJPATH = ./build/
BINPATH = ./bin/

# BINARIES
ALL_EXEC = ezekiel

# EXEC CREATION
ezekiel: ezekiel.o
	$(CC) $(CFLAGS) -o $(BINPATH)ezekiel $(OBJPATH)ezekiel.o $(LDLIBS)

# OBJECT CREATION
ezekiel.o: $(SRCPATH)ezekiel.c
	$(CC) $(CFLAGS) -c $(SRCPATH)ezekiel.c -o $(OBJPATH)ezekiel.o 

# COMMANDS

all: clean $(ALL_EXEC)

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./bin/ezekiel

clean:
	rm -rf $(OBJPATH)* $(BINPATH)*