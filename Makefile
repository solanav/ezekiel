# FLAGS
CC = g++
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
ezekiel.o: $(SRCPATH)ezekiel.cpp
	$(CC) $(CFLAGS) -c $(SRCPATH)ezekiel.cpp -o $(OBJPATH)ezekiel.o 

# COMMANDS

all: clean $(ALL_EXEC)

clean:
	rm -rf $(OBJPATH)* $(BINPATH)*