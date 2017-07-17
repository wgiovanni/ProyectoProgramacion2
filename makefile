# Makefile del Arbol Nario

# Variables
CC = g++
EJECUTABLE = primos

# Programa Principal
all: NodoN.h ArbolN.h main.cpp
	$(CC) main.cpp -o $(EJECUTABLE)


# Borrar los Archivos Objeto y el Ejecutable
clean:
	rm -rf *.o $(EJECUTABLE)
