CC = gcc
FLAGS = -g -O0
TARGET = binDis


SOURCES = $(wildcard *.c)
OBJS = $(SOURCES:.c=.o)


all : $(TARGET)


$(TARGET): $(SOURCES)
	$(CC) -o $@ $^ $(FLAGS)

src/%.o: src/%.c 
	$(CC) -c -o $@ $< $(FLAGS) 

clean : 
	rm -rf $(TARGET)

run : $(TARGET) 
	./$(TARGET)

dev : 
	$(MAKE) clean
	$(MAKE) all
	$(MAKE) run 
	$(MAKE) clean
