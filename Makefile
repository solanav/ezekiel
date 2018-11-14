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
ALL_EXEC = core

# EXEC CREATION
core: core.o utils.o
	$(CC) $(CFLAGS) -o $(BINPATH)ezekiel $(OBJPATH)core.o $(OBJPATH)utils.o $(LDLIBS)

# OBJECT CREATION
core.o: $(SRCPATH)core.c $(HDRPATH)core.h $(HDRPATH)utils.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)core.c -o $(OBJPATH)core.o 

utils.o: $(SRCPATH)utils.c $(HDRPATH)utils.h $(HDRPATH)types.h
	$(CC) $(CFLAGS) -c $(SRCPATH)utils.c -o $(OBJPATH)utils.o 

# COMMANDS

all: clean $(ALL_EXEC)

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./bin/ezekiel

clean:
	rm -rf $(OBJPATH)* $(BINPATH)*