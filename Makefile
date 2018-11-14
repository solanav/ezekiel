# FLAGS
CC = gcc
CFLAGS = -c -g -O3 -Wall -Wextra -pedantic
LDLIBS =

TARGET = "ezekiel"

# PATHS
SRCPATH = src/
INCLUDE = include/
OBJPATH = build/

OBJECTS = $(OBJPATH)core.o $(OBJPATH)utils.o

all: $(TARGET)

# EXEC CREATION
$(TARGET): $(OBJPATH) $(OBJPATH) $(OBJECTS)
	@echo "Linking objects..."
	@$(CC) $(OBJECTS) -o $@ $(LDLIBS)

$(OBJPATH):
	@mkdir $(OBJPATH)

# OBJECT CREATION
$(OBJPATH)%.o: $(SRCPATH)%.c
	@echo "Building $@..."
	@$(CC) -I $(INCLUDE) $(CFLAGS) $< -o $@ 

# COMMANDS
valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all $(TARGET)

clean:
	@echo "Removing objects files"
	@rm -rf $(OBJPATH) $(TARGET)