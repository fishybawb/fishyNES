CC = gcc

SRC = $(wildcard *.c)
OBJ = $(SRC:.c = .o)

CFLAGS = `sdl2-config --cflags` -Wall
LIBS = `sdl2-config --libs`

PROG = test

$(PROG): $(OBJ)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

$(OBJ):
	$(CC) -c $< -o $@

.PHONY: clean

clean:
	rm -f *.o $(PROG)
