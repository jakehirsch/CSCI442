#include <stdio.h>
#include <unistd.h>

// This function incorrectly returns a pointer to stack memory.
int *gen_array() {
    int arr[10]; // 'arr' is allocated on the stack 
    
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 10;
    }

    printf("Inside gen_array, arr is at address: %p\n",arr);
    
    // We return a pointer to 'arr', but 'arr' is destroyed when the function returns! 
    return arr;
}

int main(void) {
    int *my_arr = gen_array();
    
    printf("Inside main, my_arr points to address: %p\n", my_arr);

    // The printf call below reuses the stack space where 'arr' used to be.
    // So when we try to access my_arr[0], the data is gone!
    printf("Attempting to access my_arr[0]...\n");

    // This will print garbage data or crash (segmentation fault).
    printf("Value of my_arr[0]: %d\n", my_arr[0]);

    return 0;
}