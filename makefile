.SILENT:
CC = gcc
FLAGS = -g -O0
TARGET = bin/binDis


SOURCES = $(wildcard src/*.c)
OBJS = $(SOURCES:.c=.o)


all :

	mkdir -p bin
	$(CC) -o $(TARGET) $(SOURCES) $(FLAGS)

clean : 
	rm -rf bin/

run : 
	./$(TARGET)

dev : 
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) run 
	$(MAKE) clean
