CC = gcc
CFLAGS = -I.
DEPS = menu.h leerFichero.h estadistica.h
OBJ = main.o menu.o leerFichero.o estadistica.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

programa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)