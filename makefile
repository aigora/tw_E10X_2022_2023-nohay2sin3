CC = gcc
CFLAGS = -I.
DEPS = menu.h
OBJ = main.o menu.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

programa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)