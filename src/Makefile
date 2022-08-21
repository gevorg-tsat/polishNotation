.PHONY: build check clean run
CALCULATE=calc.c
CALCULATE_HEADER=$(CALCULATE:.c=.h)

OPERATION_STACK=operation_stack.c
OPERATION_STACK_HEADER=$(OPERATION_STACK:.c=.h)

BUILD_DIR=build_dir

SRCS=$(CALCULATE) $(OPERATION_STACK) parsing.c stack.c print_graph.c

FILES=$(CALCULATE) $(CALCULATE_HEADER)  $(OPERATION_STACK) $(OPERATION_STACK_HEADER) main.c


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
	rm -rf build_dir

run:
	$(BUILD_DIR)/$(CALCULATE:.c=)
