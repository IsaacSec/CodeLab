/*  Chapter 1: Object-Oriented Programming with Classes
    
    ABSTRACTION

    Abstraction is the creation of a well-defined interface for an object.
    Proper abstraction separates the implementation of an object from its 
    interface. 
        In C, abstraction involves wrapping a data structure with 
        a functional interface.

    ENCAPSULATION

    Encapsulation means keeping the implementation details of your 
    abstractions private. 
        In C, you keep details private by hiding them in a separate file.

    HIERARCHY

    Where one object uses others in its implementation is called "composition"
    because we compose larger objects out of smaller ones. 
    The other kind of hierarchy found in OOP languages is called "derivation" 
    (or inheritance). Derivation allows an abstraction to reuse not only the 
    implementation, but also the interface of another abstraction.

    POLYMORPHISM

    Code is said to be polymorphic if it can be transparently used on 
    instances of different types. Polymorphism allows us to write code in 
    terms of a generic class and have it work correctly for any actual class. 


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

/* This functios are only visible for stack.c also called 
*  private functions
*/

int compare (const void *a, const void *b){
    int int_a = *((int*)(a));
    int int_b = *((int*)(b));

    if (int_a > int_b){
        return 1;
    } else if (int_a == int_b){
        return 0;
    } else {
        return -1;
    }
}

int * arraycpy (const int * src, int length){
    int *cpy = (int *) malloc(sizeof(int) * length);
    for (int i=0; i<length; i++)
    {
        cpy[i] = src[i];
    }
    return cpy;
}

/* End of private functions */

/* Inititalize the stack */
void init (Stack *s){
    s->top = 0;
}

/* Push onto the stack */
void push (Stack *s, int i){
    if (s->top == STACKSIZE){
        printf("Stack error: Limit Reached\n");
    } else{
        s->items[s->top++] = i;
    }
}

/* Pop an element off the stack */
int pop (Stack *s){
    return s->items[--s->top];
}

/* Clean up the stack when it is not required anymore */
void cleanup (Stack *s){
    do{
        s->items[s->top--] = 0;
    }while (s->top != 0);
}

/* Prints all the elements in the stack */
void print (const Stack *s){
    if (s->top == 0){
        printf("[Empty]\n");
        return;
    }

    printf("[");
    for (int i=0; i<s->top; i++){
        if (i == s->top-1){
            printf("%d]\n",s->items[i]);
        } else{
            printf("%d, ",s->items[i]);
        }
    }
}

/* Functions for Inherited struct StatStack */

/* New functions */

int mean (StatStack *s){
    int total = 0;
    int index = 0;

    Stack *stack = &s->basic_stack;
    int *items = s->basic_stack.items;
    int size = stack->top;

    while (index < size){
        total += items[index++];
    }

    return total/s->basic_stack.top;
}

int median (StatStack *s){
    Stack *stack = &s->basic_stack;
    int size = stack->top;
    int *items = arraycpy(&s->basic_stack.items[0], size);
    int median_value;

    qsort (items, size, sizeof (int), compare);

    if (size % 2 == 0){
        median_value = (items[size/2 - 1] + items[size/2])/2;
    } else{
        median_value = items[size/2];
    }

    free(items);
    return median_value;
}

int mode (StatStack *s){
    Stack *stack = &s->basic_stack;
    int size = stack->top;
    int *items = arraycpy(&s->basic_stack.items[0], size);

    int mode_value = items[0];
    int max = 0;
    int counter = 0;
    qsort (items, size, sizeof (int), compare);

    for (int i=0; i<size-1; i++){
        if (items[i] == items[i+1]){
            ++counter;
        }else{
            if (counter > max){
                max = counter;
                mode_value = items[i];
            }
            counter = 0;
        }
    }

    free(items);
    return mode_value;
}

/* Inherited functions*/

void ss_init (StatStack *s){
    init (&s->basic_stack);
}

void ss_push (StatStack *s, int i){
    push (&s->basic_stack, i);
}

void ss_pop (StatStack *s){
    pop (&s->basic_stack);
}

void ss_cleanup (StatStack *s){
    cleanup (&s->basic_stack);
}

void ss_print (const StatStack *s){
    print (&s->basic_stack);
}