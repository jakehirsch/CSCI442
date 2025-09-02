#include <stdio.h>
#include <stdlib.h> // Required for malloc and free

// This function correctly returns a pointer to heap memory.
int *gen_array() {
    // Allocate space for 10 integers on the heap 
    int *arr = malloc(10 * sizeof(int));

    // It's good practice to check if malloc succeeded.
    if (arr == NULL) {
        return NULL; // Return NULL if memory allocation fails
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i * 10;
    }

    printf("Inside gen_array, arr is at address: %p\n", arr);

    // This pointer is safe to return because heap memory persists across function calls.
    return arr;
}

int main(void) {
    int *my_arr = gen_array();

    printf("In main, returned my_arr is at address: %p\n", my_arr);

    if (my_arr != NULL) {
        printf("Value of my_arr[0]: %d\n", my_arr[0]);
        printf("Value of my_arr[5]: %d\n", my_arr[5]);

        // For every malloc, there must be a free! 
        // This returns the memory to the OS.
        free(my_arr); 
    }

    return 0;
}