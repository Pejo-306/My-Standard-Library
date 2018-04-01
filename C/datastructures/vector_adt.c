#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define VECTOR_INITIAL_SIZE 10

typedef struct vector_t * Vector;

struct vector_t {
    size_t size;
    size_t count;
    int *arr;

    void (*print)(const void *self);
    void (*destroy)(const void *self);
    int (*empty)(const void *self);
    int (*full)(const void *self);
    int (*first)(const void *self);
    int (*last)(const void *self);
    int (*at)(const void *self, int index);
    int (*insert)(const void *self, int index, int item);
    int (*remove)(const void *self, int index);
    void (*push)(const void *self, int item);
    void (*pop)(const void *self);
    void (*push_front)(const void *self, int item);
    void (*pop_front)(const void *self);
    void (*reverse)(const void *self);
};

Vector new_vector();
void vector_print(const void *);
void vector_destroy(const void *);
int vector_empty(const void *);
int vector_full(const void *);
int vector_first(const void *);
int vector_last(const void *);
int vector_at(const void *, int);
int vector_insert(const void *, int, int);
int vector_remove(const void *, int);
void vector_push(const void *, int);
void vector_pop(const void *);
void vector_push_front(const void *, int);
void vector_pop_front(const void *);
void vector_reverse(const void *);

Vector new_vector()
{
    Vector self = (Vector)malloc(sizeof(struct vector_t));
    
    self->size = VECTOR_INITIAL_SIZE;
    self->count = 0;
    self->arr = (int *)malloc(sizeof(int) * self->size);

    self->print = vector_print;
    self->destroy = vector_destroy;
    self->empty = vector_empty;
    self->full = vector_full;
    self->first = vector_first;
    self->last = vector_last;
    self->at = vector_at;
    self->insert = vector_insert;
    self->remove = vector_remove;
    self->push = vector_push;
    self->pop = vector_pop;
    self->push_front = vector_push_front;
    self->pop_front = vector_pop_front;
    self->reverse = vector_reverse;

    return self;
}

void vector_print(const void *_self)
{
    Vector self = (Vector)_self;

    putchar('[');
    for (int i = 0; i < self->count; ++i)
        printf("%d%s", self->arr[i], (i == self->count-1) ? "" : ", ");
    printf("]\n");
}

void vector_destroy(const void *_self)
{
    Vector self = (Vector)_self;

    free(self->arr);
    free(self);
}

int vector_empty(const void *_self)
{
    Vector self = (Vector)_self;

    return self->count == 0;
}

int vector_full(const void *_self)
{
    Vector self = (Vector)_self;

    return self->count == self->size;
}

int vector_first(const void *_self)
{
    Vector self = (Vector)_self;

    return (!self->empty(self)) ? self->arr[0] : INT_MIN;
}

int vector_last(const void *_self)
{
    Vector self = (Vector)_self;

    return (!self->empty(self)) ? self->arr[self->count-1] : INT_MIN;
}

int vector_at(const void *_self, int index)
{
    Vector self = (Vector)_self;

    if (index < 0)
        return INT_MIN;
    else if (index >= self->count)
        return INT_MAX;
    return self->arr[index];
}

int vector_insert(const void *_self, int index, int item)
{
    Vector self = (Vector)_self;

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

int vector_remove(const void *_self, int index)
{
    Vector self = (Vector)_self;

    if (index < 0)
        return INT_MIN;
    else if (index >= self->count)
        return INT_MAX;

    for (int i = index; i < self->count - 1; ++i)
        self->arr[i] = self->arr[i+1];
    --self->count;
    return 0;
}

void vector_push(const void *_self, int item)
{
    Vector self = (Vector)_self;

    if (self->full(self)) {
        self->size *= 2;
        self->arr = (int *)realloc(self->arr, sizeof(int) * self->size);
    }

    self->arr[self->count++] = item;
}

void vector_pop(const void *_self)
{
    Vector self = (Vector)_self;

    if (!self->empty(self))
        self->count -= 1;
}

void vector_push_front(const void *_self, int item)
{
    Vector self = (Vector)_self;

    self->insert(self, 0, item);
}

void vector_pop_front(const void *_self)
{
    Vector self = (Vector)_self;

    self->remove(self, 0);
}

void vector_reverse(const void *_self)
{
    Vector self = (Vector)_self;
    int tmp;

    for (int i = 0; i < self->count / 2; ++i) {
        tmp = self->arr[i];
        self->arr[i] = self->arr[self->count-1-i];
        self->arr[self->count-1-i] = tmp;
    }
}

