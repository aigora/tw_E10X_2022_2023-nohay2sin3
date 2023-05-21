CC = gcc
CFLAGS = -I.
DEPS = menu.h leerFichero.h
OBJ = main.o menu.o leerFichero.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

programa: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)