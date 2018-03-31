#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VECTOR_INITIAL_SIZE 10

typedef struct vector_t * Vector;

struct vector_t {
    int size;
    int count;
    int *arr;

    void (*print)(const void *self);
    void (*destroy)(const void *self);
    int (*empty)(const void *self);
    int (*full)(const void *self);
    int (*first)(const void *self);
    int (*last)(const void *self);
    int (*at)(const void *self, int index);
    void (*push)(const void *self, int item);
    void (*pop)(const void *self);
    int (*insert)(const void *self, int index, int item);
    void (*push_front)(const void *self, int item);
};

Vector new_vector();
void print_vector(const void *);
void destroy(const void *);
int empty(const void *);
int full(const void *);
int first(const void *);
int last(const void *);
int at(const void *, int);
void push(const void *, int);
void pop(const void *);
int insert(const void *, int, int);
void push_front(const void *, int);

Vector new_vector()
{
    Vector self = (Vector)malloc(sizeof(struct vector_t));
    
    self->size = VECTOR_INITIAL_SIZE;
    self->count = 0;
    self->arr = (int *)malloc(sizeof(int) * self->size);

    self->print = print_vector;
    self->destroy = destroy;
    self->empty = empty;
    self->full = full;
    self->first = first;
    self->last = last;
    self->at = at;
    self->push = push;
    self->pop = pop;
    self->insert = insert;
    self->push_front = push_front;

    return self;
}

void print_vector(const void *this)
{
    Vector self = (Vector)this;

    putchar('[');
    for (int i = 0; i < self->count; ++i)
        printf("%d%s", self->arr[i], (i == self->count-1) ? "" : ", ");
    printf("]\n");
}

void destroy(const void *this)
{
    Vector self = (Vector)this;

    free(self->arr);
    free(self);
}

int empty(const void *this)
{
    Vector self = (Vector)this;

    return self->count == 0;
}

int full(const void *this)
{
    Vector self = (Vector)this;

    return self->count == self->size;
}

int first(const void *this)
{
    Vector self = (Vector)this;

    return (!self->empty(self)) ? self->arr[0] : INT_MIN;
}

int last(const void *this)
{
    Vector self = (Vector)this;

    return (!self->empty(self)) ? self->arr[self->count-1] : INT_MIN;
}

int at(const void *this, int index)
{
    Vector self = (Vector)this;

    if (index < 0)
        return INT_MIN;
    else if (index >= self->count)
        return INT_MAX;
    return self->arr[index];
}

void push(const void *this, int item)
{
    Vector self = (Vector)this;

    if (self->full(self)) {
        self->size *= 2;
        self->arr = (int *)realloc(self->arr, sizeof(int) * self->size);
    }

    self->arr[self->count++] = item;
}

void pop(const void *this)
{
    Vector self = (Vector)this;

    if (!self->empty(self))
        self->count -= 1;
}

int insert(const void *this, int index, int item)
{
    Vector self = (Vector)this;

    if (index < 0)
        return INT_MIN;
    else if (index >= self->count)
        return INT_MAX;

    if (self->full(self)) {
        self->size *= 2;
        self->arr = (int *)realloc(self->arr, sizeof(int) * self->size);
    }

    for (int i = self->count - 1; i >= index; --i)
        self->arr[i+1] = self->arr[i];
    self->arr[index] = item;
    ++self->count;
    return 0;
}

void push_front(const void *this, int item)
{
    Vector self = (Vector)this;

    self->insert(self, 0, item);
}

