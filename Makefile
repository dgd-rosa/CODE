TARGET = tuktuk
CC = gcc
CFLAGS = -Wall -std=c99 -O3
LIBS = -lm
HEADERS = findWay.h file.h heap.h defs.h
OBJECTS = main.c findWay.c file.c heap.c
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all
FILES = ${file}

.PHONY: clean $(TARGET)

.DEFAULT_GOAL := $(TARGET)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LIBS)

clean:
	-rm -f $(TARGET) *.o

run:
	$(VALGRIND) ./$(TARGET) $(FILES)

all:	clean $(TARGET) run clean

#para executar: make file=<nome do ficheiro>
