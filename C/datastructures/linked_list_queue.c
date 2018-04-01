#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t * Node;

struct node_t {
    int data;
    struct node_t *next;
};

typedef struct queue_t * Queue;

struct queue_t {
    struct node_t *head, *tail;

    size_t (*size)(const void *self);
    void (*print)(const void *self);
    void (*destroy)(const void *self);
    int (*empty)(const void *self);
    int (*front)(const void *self);
    void (*push)(const void *self, int data);
    void (*pop)(const void *self);
};

Queue new_queue();
size_t size(const void *);
void print_queue(const void *);
void destroy(const void *);
int empty(const void *);
int front(const void *);
void push(const void *, int);
void pop(const void *);

Queue new_queue()
{
    Queue self = (Queue)malloc(sizeof(struct queue_t));

    self->head = NULL;
    self->tail = NULL;

    self->size = size;
    self->print = print_queue;
    self->destroy = destroy;
    self->empty = empty;
    self->front = front;
    self->push = push;
    self->pop = pop;
    
    return self; 
}

size_t size(const void *_self)
{
    Queue self = (Queue)_self;
    Node current = self->head;
    size_t len = 0;

    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void print_queue(const void *_self)
{
    Queue self = (Queue)_self;
    Node current = self->head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void destroy(const void *_self)
{
    Queue self = (Queue)_self;
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
    Queue self = (Queue)_self;

    return (self->head == NULL) ? 1 : 0;
}

int front(const void *_self)
{
    Queue self = (Queue)_self;

    return (self->empty(self)) ? INT_MIN : self->head->data;
}
 
void push(const void *_self, int data)
{
    Queue self = (Queue)_self;
    Node new_element = (Node)malloc(sizeof(struct node_t));
    new_element->data = data;
    new_element->next = NULL;

    if (self->empty(self)) {
        self->head = new_element;
        self->tail = new_element;
    } else {
        self->tail->next = new_element;
        self->tail = self->tail->next;
    }
}

void pop(const void *_self)
{
    Queue self = (Queue)_self;
    Node old_head;

    if (self->empty(self))
        return;  // error

    old_head = self->head;
    self->head = old_head->next;
    free(old_head);
}

