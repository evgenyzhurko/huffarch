C_FLAGS = -c -Wall -pedantic

all: huff

huff: main
	gcc option.o huffman.o huff.o utils.o -o huff

main: message.o option.o huffman.o utils.o
	gcc huff.c $(C_FLAGS) -o huff.o

option.o:
	gcc option.c $(C_FLAGS) -o option.o

huffman.o:
	gcc huffman.c $(C_FLAGS) -o huffman.o

utils.o:
	gcc utils.c $(C_FLAGS) -o utils.o

message.o: message.h

clean:
	rm huff *.o