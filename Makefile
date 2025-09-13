# Compiler name and flags
CC = clang
CFLAGS = -g -Wall -Wextra

# Linker flags (goes to the linker, not the compiler)
LDFLAGS = -lncurses

# Source and object files
SRCS = main.c util.c mechanix.c
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = snake

.PHONY: all clean

all: $(EXEC)

# Rule to create the executable from object files
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS)

# Generic rule to compile a .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean all intermediate and executable files
clean:
	rm -f $(EXEC) $(OBJS)



