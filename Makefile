   # Compuler name
CC = clang

   # Defining linker
LDFLAGS = -lncurses

SRCS  = main.c util.c mechanix.c

   # Exe file name
EXEC = snake

   # Default rule to build program, its phony target
all: $(EXEC)

   # Rule to create exe file
$(EXEC): $(SRCS)
	$(CC) $(SRCS) -o $(EXEC) $(LDFLAGS)

   # Rule to clean exe which arent required 
clean:
	rm -f $(EXEC)


