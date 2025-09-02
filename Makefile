# Makefile for C Language Exercises

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall: Enable all common warnings
# -Wextra: Enable extra warnings
# -w: No warnings
# -g: Include debugging information in the binary
# -std=c11: Use the C11 standard
CFLAGS = -w -g 

# List all the target executable files you want to build.
TARGETS = hello arrays stack_error heap_solution strings_printf person

# The 'all' target is the default.
# Running 'make' or 'make all' will build all executables listed in TARGETS.
all: $(TARGETS)

# --- Explicit Rules for Each Target ---
# Here you can map each target executable to its specific .c source file.
# Just change the C file name on the right side of the colon.
# $@ is an automatic variable for the target name (e.g., 'hello').
# $< is an automatic variable for the first prerequisite (e.g., '1-hello.c').

hello: 1-hello.c
	$(CC) $(CFLAGS) $< -o $@

arrays: 2-arrays.c
	$(CC) $(CFLAGS) $< -o $@

stack_error: 3-stack_error.c
	$(CC) $(CFLAGS) $< -o $@

heap_solution: 4-heap_solution.c
	$(CC) $(CFLAGS) $< -o $@

strings_printf: 5-strings_printf.c
	$(CC) $(CFLAGS) $< -o $@

person: 6-person.c
	$(CC) $(CFLAGS) $< -o $@


# The 'clean' target is used to remove all compiled files.
# Running 'make clean' will delete all the files listed in TARGETS.
clean:
	rm -f $(TARGETS)

# By declaring these targets as .PHONY, we tell make that these are
# special commands, not actual files to be built.
.PHONY: all clean