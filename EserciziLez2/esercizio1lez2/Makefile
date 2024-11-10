CC = gcc #variabile che definisce il compilatore
CFLAGS = -g 
INCLUDES = *.h #variabile che definisce gli header da includere
COMMON_DEPS = $(INCLUDES) Makefile folders #$(INCLUDES) è una variabile che contiene tutti gli header da includere

all: bin/main

build/%.o: %.c $(COMMON_DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main: build/main.o build/listFile.o $(COMMON_DEPS)
	$(CC) -o bin/main build/main.o build/listFile.o

folders:
	mkdir -p bin/ build/ #serve per creare le cartelle build e bin, -p serve a non dare errore se la cartella esiste già

clean:
	rm -rf build/ bin/

rebuild: clean all




