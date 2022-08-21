.PHONY: build check clean run
CALCULATE=calc.c
CALCULATE_HEADER=$(CALCULATE:.c=.h)

OPERATION_STACK=operation_stack.c
OPERATION_STACK_HEADER=$(OPERATION_STACK:.c=.h)
PARSING=parsing.c
PARSING_HEADER=$(PARSING:.c=.h)
STACK_FOR_PARSING=stack.c
STACK_FOR_PARSING_HEADER=$(STACK_FOR_PARSING:.c=.h)
PRINT_GRAPH=print_graph.c
PRINT_GRAPH_HEADER=$(PRINT_GRAPH:.c=.h)
BUILD_DIR=../build

SRCS=$(CALCULATE) $(OPERATION_STACK) $(PARSING) $(STACK_FOR_PARSING) $(PRINT_GRAPH)

FILES=$(SRCS) $(CALCULATE_HEADER) $(OPERATION_STACK_HEADER) $(PRINT_GRAPH_HEADER) $(PARSING_HEADER) $(STACK_FOR_PARSING_HEADER) main.c

check:
	python3 ../materials/linters/cpplint.py --extensions=c $(FILES)
	cppcheck --enable=all --suppress=missingIncludeSystem $(FILES)
# clang-tidy $(FILES)


build: $(BUILD_DIR)/$(CALCULATE:.c=)

#CFLAGS+= -Werror -Wextra -Wall -Wimplicit -Wpedantic


$(BUILD_DIR)/$(CALCULATE:.c=): $(SRCS:.c=.o) main.o | $(BUILD_DIR) $(CALCULATE_HEADER)
	$(CC) -o $@ $^


$(BUILD_DIR):
	mkdir $@

clean:
	rm -rf *.o
	rm -rf $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(CALCULATE:.c=)
