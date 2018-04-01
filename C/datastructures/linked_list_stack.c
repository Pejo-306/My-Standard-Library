#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t * Node;

struct node_t {
    int data;
    struct node_t *next;
};

typedef struct stack_t * Stack;

struct stack_t {
    struct node_t *head;

    
    size_t (*size)(const void *self);
    void (*print)(const void *self);
    void (*destroy)(const void *self);
    int (*empty)(const void *self);
    int (*top)(const void *self);
    void (*push)(const void *self, int data);
    void (*pop)(const void *self);
};

Stack new_stack();
size_t size(const void *);
void print_stack(const void *);
void destroy(const void *);
int empty(const void *);
int top(const void *);
void push(const void *, int);
void pop(const void *);

Stack new_stack()
{
    Stack self = (Stack)malloc(sizeof(struct stack_t));
    
    self->head = NULL;

    self->size = size;
    self->print = print_stack;
    self->destroy = destroy;
    self->empty = empty;
    self->top = top;
    self->push = push;
    self->pop = pop;

    return self;
}

size_t size(const void *_self)
{
    Stack self = (Stack)_self;
    Node current = self->head;
    size_t len = 0;

    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void print_stack(const void *_self)
{ 
    Stack self = (Stack)_self;
    Node current = self->head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void destroy(const void *_self)
{
    Stack self = (Stack)_self;
    Node previous = NULL;
    Node current = self->head;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
    free(self);
}

int empty(const void *_self)
{
    Stack self = (Stack)_self;

    return (self->head == NULL) ? 1 : 0;
}

int top(const void *_self)
{
    Stack self = (Stack)_self;

    return (self->empty(self)) ? INT_MIN : self->head->data;
}

void push(const void *_self, int data)
{
    Stack self = (Stack)_self;
    Node new_head = (Node)malloc(sizeof(struct node_t));

    new_head->data = data;
    new_head->next = self->head;
    self->head = new_head;
}

void pop(const void *_self)
{
    Stack self = (Stack)_self;
    Node old_head;

    if (self->empty(self))
        return;  // error

    old_head = self->head;
    self->head = old_head->next;
    free(old_head);
}

