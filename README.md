## Step 1: The Basics (Hello, World\!)

This first step mirrors the "Hello World" section of your slides (slides 33-44) and gets students comfortable with the basic compile-and-run cycle.

**Goal:** Write, compile, and run a basic C program. Understand the `main` function and `printf`.

1.  Create a file named `hello.c` and add the following code:

    ```c
    #include <stdio.h>

    [cite_start]// main is the entry point to the program [cite: 35]
    // argc: argument count, argv: argument vector (list of strings)
    int main(int argc, char *argv[]) {
        [cite_start]// printf prints formatted text to standard output [cite: 36]
        printf("Hello, World!\n");

        [cite_start]// Return 0 to indicate success [cite: 37]
        return 0;
    }
    ```

2.  **Compile the program** using `gcc`. The `-o` flag names the output executable file.

    ```bash
    gcc 1-hello.c -o hello
    ```

3.  **Run the executable.**

    ```bash
    ./hello
    ```

4.  **Expected Output:**

    ```
    Hello, World!
    ```

-----

## Step 2: Arrays, Pointers, and Memory Bugs

This step demonstrates array access and the classic "out-by-one" error mentioned in your slides (slides 45-54, 60-62), showing how C gives you the power to make mistakes.

**Goal:** Understand the relationship between array notation and pointer arithmetic, and see how easy it is to cause memory corruption.

1.  Create a file named `arrays.c` with this code:

    ```c
    #include <stdio.h>

    int main(void) {
        int more[3] = {1, 2, 3}; [cite_start]// Array of 3 integers [cite: 48]
        int other_var = 99;

        printf("Initial value of other_var: %d\n", other_var);
        printf("The second element is: %d\n", more[1]);
        
        [cite_start]// Let's write out of bounds, just like in the slides [cite: 53]
        printf("Writing '77' to more[3] (the 4th element)...\n");
        more[3] = 77; // Corruption! This memory likely belongs to other_var

        // The result of this is technically "undefined", but on many systems,
        // it will overwrite the adjacent variable on the stack.
        printf("Value of other_var is now: %d\n", other_var);

        [cite_start]// Demonstrate that array access is just pointer arithmetic [cite: 62]
        // more[1] is the same as *(more + 1)
        printf("Accessing the second element using a pointer: %d\n", *(more + 1));

        return 0;
    }
    ```

2.  **Compile and run:**

    ```bash
    gcc 2-arrays.c -o arrays
    ./arrays
    ```

3.  **Expected Output** (may vary slightly depending on the compiler):

    ```
    Initial value of other_var: 99
    The second element is: 2
    Writing '77' to more[3] (the 4th element)...
    Value of other_var is now: 77
    Accessing the second element using a pointer: 2
    ```

    **Discussion Point:** Highlight how `other_var`'s value changed unexpectedly. [cite\_start]This is the **corruption** mentioned in your slides [cite: 54]—a difficult bug to track down.

-----

## Step 3: The Stack Memory Pitfall

This is a live demonstration of the exact problem shown in the "What's wrong with this picture?" slides (slides 71-77, 88-91).

**Goal:** Show students why returning a pointer to a local variable is a critical error.

1.  Create a file named `stack_bad.c`:

    ```c
    #include <stdio.h>

    // This function incorrectly returns a pointer to stack memory.
    int *gen_array() {
        int arr[10]; [cite_start]// 'arr' is allocated on the stack [cite: 79]
        printf("Inside gen_array, arr is at address: %p\n", arr);

        for (int i = 0; i < 10; i++) {
            arr[i] = i * 10;
        }

        [cite_start]// We return a pointer to 'arr', but 'arr' is destroyed when the function returns! [cite: 91]
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
    ```

    *Note: Your compiler will likely issue a warning about this, which is a great teaching moment.*

2.  **Compile and run:**

    ```bash
    gcc 3-stack_error.c -o stack_error
    ./stack_error
    ```

3.  **Expected Output** (the specific value will be garbage):

    ```
    Inside gen_array, arr is at address: 0x7ffc...
    Inside main, my_arr points to address: 0x7ffc...
    Attempting to access my_arr[0]...
    Value of my_arr[0]: 32764 
    ```

    **Discussion Point:** Emphasize that the memory addresses are the same, but the data is invalid because the stack frame for `gen_array` was reclaimed.

-----

## Step 4: The Heap Memory Solution

Now, you'll fix the previous example using `malloc`, as suggested in your slides (slides 92, 95-97).

**Goal:** Demonstrate correct dynamic memory allocation with `malloc` and `free`.

1.  Create a file named `heap_good.c`:

    ```c
    #include <stdio.h>
    #include <stdlib.h> // Required for malloc and free

    // This function correctly returns a pointer to heap memory.
    int *gen_array() {
        [cite_start]// Allocate space for 10 integers on the heap [cite: 96]
        int *arr = malloc(10 * sizeof(int));
        
        // It's good practice to check if malloc succeeded.
        if (arr == NULL) {
            return NULL; // Return NULL if memory allocation fails
        }
        
        for (int i = 0; i < 10; i++) {
            arr[i] = i * 10;
        }

        // This pointer is safe to return because heap memory persists across function calls.
        return arr;
    }

    int main(void) {
        int *my_arr = gen_array();
        
        if (my_arr != NULL) {
            printf("Value of my_arr[0]: %d\n", my_arr[0]);
            printf("Value of my_arr[5]: %d\n", my_arr[5]);
            
            [cite_start]// For every malloc, there must be a free! [cite: 189]
            // This returns the memory to the OS.
            free(my_arr); [cite_start]// [cite: 97]
        }
        
        return 0;
    }
    ```

2.  **Compile and run:**

    ```bash
    gcc 4-heap_good.c -o heap_solution
    ./heap_solution
    ```

3.  **Expected Output:**

    ```
    Value of my_arr[0]: 0
    Value of my_arr[5]: 50
    ```

    **Discussion Point:** Explain that `malloc` allocates memory from the heap, which is not tied to a function's lifetime. Then, challenge the students: "What happens if I comment out the `free(my_arr)` line?" [cite\_start](Answer: a memory leak [cite: 100]).

-----

## Step 5 : A Deeper Dive into C Strings and `printf`

This step covers C strings in more detail, from stack-based character arrays to dynamically allocated strings on the heap. We will also explore several common string library functions and expand our use of `printf` to format different data types.

**Goal:** Understand how strings are represented as `char` arrays, how to allocate them dynamically, how to use key string functions, and how to format various data types for output.

1.  Create a file named `5-strings_printf.c` and add the following code:

    ```c
    #include <stdio.h>
    #include <string.h> // Required for string functions like strlen, strcmp, etc.
    #include <stdlib.h> // Required for malloc and free

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
    ```

2.  **Compile and run** the program:

    ```bash
    gcc 5-strings_printf.c -o strings_printf
    ./strings_printf
    ```

-----

## Step 6: Putting It Together with Structs

This final step combines several concepts. We will define a `struct`, create a "constructor" function that allocates a `struct` on the heap, initialize its members (including a dynamically allocated string), and then free all associated memory.

**Goal:** Define and use a `struct`. Dynamically allocate a `struct` and handle its members safely.

1.  Create a file named `6-person.c`:

    ```c
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h> // Required for strdup

    struct person {
        char *name;
        int id;
    };

    struct person *create_person(const char *name, int id) {
        struct person *p = malloc(sizeof(struct person));
        if (p == NULL) return NULL;

        p->name = strdup(name);
        p->id = id;
        return p;
    }

    void free_person(struct person *p) {
        if (p != NULL) {
            free(p->name); // Free the duplicated string
            free(p);       // Free the struct itself
        }
    }

    int main(void) {
        struct person *bob = create_person("Bob", 42);
        printf("Created person: Name=%s, ID=%d\n", bob->name, bob->id);
        free_person(bob);
        printf("Person data has been freed.\n");
        return 0;
    }
    ```

2.  **Compile and run:**

    ```bash
    gcc 6-person.c -o person
    ./person
    ```