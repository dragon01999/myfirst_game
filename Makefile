CC:= gcc
OBJ = main.o game.o render.o
all: snake

snake: $(OBJ)
	$(CC) -O2 $(OBJ) -o snake -lncurses
	rm -f $(OBJ)

%.o: %.c
	$(CC) -c $< -o $@
