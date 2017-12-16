#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} Node;

typedef struct stack_t * Stack;

struct stack_t {
    struct node_t *head;

    void (*print)(const void *self);
    int (*empty)(const void *self);
    size_t (*size)(const void *self);
    void (*push)(const void *self, int data);
    void (*pop)(const void *self);
    int (*top)(const void *self);
};

Stack new_stack()
{
    Stack self = (Stack)malloc(sizeof(struct stack_t));
    
    self->head = NULL;
    self->print = &print_stack;
    self->empty = &empty;
    self->size = &size;
    self->push = &push;
    self->pop = &pop;
    self->top = &top;

    return self;
}

void print_stack(const void *self)
{ 
    Node *current = ((Stack)self)->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int empty(const void *self)
{
    if (((Stack)self)->head != NULL)
        return 0;
    return 1;
}

size_t size(const void *self)
{
    size_t len = 0;
    Node *current = ((Stack)self)->head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void push(const void *self, int data)
{
    Stack stack = (Stack)self;
    Node *new_head = (Node *)malloc(sizeof(Node));
    new_head->data = data;
    new_head->next = stack->head;
    stack->head = new_head;
}

void pop(const void *self)
{
    Stack stack = (Stack)self;
    if (stack->empty(stack))
        return;  // error

    Node *old_head = stack->head;
    stack->head = old_head->next;
    free(old_head);
}

int top(const void *self)
{
    Stack stack = (Stack)self;
    if (stack->empty(stack))
        return INT_MIN;

    return stack->head->data;
}

