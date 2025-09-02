#include <stdio.h>
#include <stdlib.h> // Required for malloc and free
#include <string.h> // Required for string functions like strlen, strcmp, etc.

int main(void) {
  // --- Part 1: Char arrays and strings ---
  char stack_str[] = "Alice";
  printf("--- Stack Strings ---\n");
  printf("A string on the stack: %s\n", stack_str);

  // --- Part 2: Example use of string functions ---
  printf("\n--- C String Functions ---\n");
  size_t len = strlen(stack_str);
  printf("strlen(\"%s\") = %zu\n", stack_str, len);

  if (strcmp(stack_str, "Alice") == 0) {
    printf("strcmp() confirms that stack_str is equal to \"Alice\".\n");
  }
  printf("The address of stack_str is: %p\n", stack_str);

  // --- Part 3: Dynamic allocation of C strings ---
  printf("\n--- Heap Strings (Dynamic Allocation) ---\n");
  char *heap_str = malloc(len + 1); // +1 for the null terminator
  if (heap_str != NULL) {
    strncpy(heap_str, stack_str, len + 1);
    printf("Successfully copied to a new string on the heap: %s\n", heap_str);
    free(heap_str);
    printf("Heap memory has been freed.\n");
  }

  // --- Part 4: More examples of printf ---
  printf("\n--- Advanced printf Formatting ---\n");
  float temperature = 98.6f;
  int item_count = 255;
  char grade = 'A';
  int *ptr = &item_count;

  printf("Float: Today's temperature is %f degrees.\n", temperature);
  printf("Float (formatted): Or more precisely, %.2f degrees.\n", temperature);
  printf("Hexadecimal: %d items is 0x%x in hex.\n", item_count, item_count);
  printf("Character: The student's grade is %c.\n", grade);
  printf("Pointer: The variable 'item_count' is stored at address %p.\n", ptr);
  printf("Literal: We are 100%% ready to code in C!\n");

  return 0;
}