#include <stdio.h>

// main is the entry point to the program 
// argc: argument count, argv: argument vector (list of strings)
int main(int argc, char *argv[]) {
  // printf prints formatted text to standard output 
  printf("Hello, World!\n");

  // Print the number of arguments and the first argument
  printf("argc:%d\n", argc);
  printf("argv[0]:%s\n", argv[0]);

  // Return 0 to indicate success 
  return 0;
}