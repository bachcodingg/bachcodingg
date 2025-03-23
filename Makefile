CC = gcc
CFLAGS = -Wall

OBJ = main.o Tree.o Node.o

HEADERS = Node.h Tree.h

TARGET = project

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

Tree.o: Tree.c Tree.h Node.h
	$(CC) $(CFLAGS) -c $<

Node.o: Node.c Node.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean