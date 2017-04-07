C_FLAGS = -c -Wall -pedantic -Werror -std=c99
TMP_DIR = out
CODE_DIR = src
OUTPUT_NAME = huff

all: start $(OUTPUT_NAME)

start:
	mkdir $(TMP_DIR)

$(OUTPUT_NAME): huff.o option.o huffman.o utils.o binary_tree.o heap.o code_table.o
	gcc $(addprefix $(TMP_DIR), $(addprefix /, $^)) -o $@

%.o: $(addprefix $(CODE_DIR), $(addprefix /, %.c))
	gcc $^ $(C_FLAGS) -o $(addprefix $(TMP_DIR), $(addprefix /, $@))

clean:
	rm $(OUTPUT_NAME) $(addprefix $(TMP_DIR), $(addprefix /, *.o)) -d $(TMP_DIR)