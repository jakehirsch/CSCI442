#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello World!");
    return 0;

    // what is the difference between:
        // %s
        // %d
        // %p
}

int main(viod){
    int more[3] = {1, 2, 3};
    int other_var = 99;

    printf("Initial value of other_var is:%d\n", other_var);
    printf("The second element is:%d\n", more[1]);

    //print the elements of more and its elememnts
    printf("Address of more is:%p\n", more);
    printf("Address of more is:%p\n", more+1);
    printf("Address of other is:%d\n", &other_var);

    printf("Accessing the second element using a pointer: %d\n", *(more+1));

    // Change the second element
    more[1] = 100;
    printf("The second elememnt is now: %d\n", more[1]);

    // Change the second element in another way
    *(more+1) = 200;
    printf("The second elememnt is now: %d\n", more[1]);

    //Lets write out of the bounds of our list
    printf("Writing '77' to more[3] the 4th element of the list...");
    //actually other var is at var[-1]
    *(more-1) = 77;

    printf("Other var is now: %d\n", other_var);
}

void double_int(int *input){
    *input = *input * 2;
}

int foo(void){
    int a = 10;
    double_int(&a);
    // a in now 20
}



