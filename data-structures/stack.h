/* This file works as Encapsulation
*  Hides the implementation of stack.c 
*/

#define STACKSIZE 100

typedef struct _stack{
    int items[STACKSIZE];
    int top;
} Stack;

void init (Stack *s);

void cleanup (Stack *s);

int pop (Stack *s);

void push (Stack *s, int i);

void print (const Stack *s);

/* New Stack struct with new features */

typedef struct _stat_stack{
    Stack basic_stack;
} StatStack;

/* New functions */

int mean (StatStack *s);

int median (StatStack *s);

int mode (StatStack *s);

/* Inherited functions*/

void ss_init (StatStack *s);

void ss_push (StatStack *s, int i);

void ss_pop (StatStack *s);

void ss_cleanup (StatStack *s);

void ss_print (const StatStack *s);
