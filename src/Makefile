C_FLAGS = -c -Wall -pedantic -std=c99
all: huff

huff: main
	gcc option.o huffman.o huff.o utils.o binary_tree.o heap.o code_table.o -o huff

main: message.o option.o huffman.o utils.o binary_tree.o heap.o code_table.o
	gcc huff.c $(C_FLAGS) -o huff.o

option.o:
	gcc option.c $(C_FLAGS) -o option.o

huffman.o:
	gcc huffman.c $(C_FLAGS) -o huffman.o

utils.o:
	gcc utils.c $(C_FLAGS) -o utils.o

binary_tree.o:
	gcc binary_tree.c $(C_FLAGS) -o binary_tree.o

heap.o:
	gcc heap.c $(C_FLAGS) -o heap.o

code_table.o:
	gcc code_table.c $(C_FLAGS) -o code_table.o

message.o: message.h

clean:
	rm huff *.o