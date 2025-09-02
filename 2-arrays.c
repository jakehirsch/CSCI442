#include <stdio.h>

int main(void) {
  int more[3] = {1, 2, 3}; // Array of 3 integers 
  int other_var = 99;

  printf("Initial value of other_var: %d\n", other_var);
  printf("The second element is: %d\n", more[1]);

  // Print the addresses of the array and its elements
  printf("Address of more: %p\n", more);
  printf("Address of more+1: %p\n", more+1);
  printf("Address of other_var: %p\n", &other_var);

  // Demonstrate that array access is just pointer arithmetic 
  // more[1] is the same as *(more + 1)
  printf("Accessing the second element using a pointer: %d\n", *(more + 1));

  // Change the second element
  more[1] = 100;
  printf("The second element is now: %d\n", more[1]);
  
  // Change the second element in another way
  *(more+1) = 200;
  printf("The second element is now: %d\n", more[1]);

  // Let's write out of bounds, just like in the slides 
  printf("Writing '77' to more[3] (the 4th element)...\n");
  more[3] = 77; // Corruption! This memory likely belongs to other_var

  // The result of this is technically "undefined", but on many systems,
  // it will overwrite the adjacent variable on the stack.
  printf("Value of other_var is now: %d\n", other_var);



  return 0;
}