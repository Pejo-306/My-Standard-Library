#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} Node;

typedef struct queue_t * Queue;

struct queue_t {
    struct node_t *head, *tail;

    void (*print)(const void *self);
    int (*empty)(const void *self);
    size_t (*size)(const void *self);
    void (*push)(const void *self, int data);
    void (*pop)(const void *self);
    int (*front)(const void *self);
};

Queue new_queue()
{
    Queue self = (Queue)malloc(sizeof(struct queue_t));

    self->head = NULL;
    self->tail = NULL;
    self->print = &print_queue;
    self->empty = &empty;
    self->size = &size;
    self->push = &push;
    self->pop = &pop;
    self->front = &front;
    
    return self; 
}

void print_queue(const void *self)
{
    Node *current = ((Queue)self)->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int empty(const void *self)
{
    if (((Queue)self)->head != NULL)
        return 0;
    return 1;
}

size_t size(const void *self)
{
    size_t len = 0;
    Node *current = ((Queue)self)->head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void push(const void *self, int data)
{
    Node *new_element = (Node *)malloc(sizeof(Node));
    new_element->data = data;
    new_element->next = NULL;

    Queue queue = (Queue)self;
    if (queue->empty(queue)) {
        queue->head = new_element;
        queue->tail = new_element;
    } else {
        queue->tail->next = new_element;
        queue->tail = queue->tail->next;
    }
}

void pop(const void *self)
{
    Queue queue = (Queue)self;
    if (queue->empty(queue))
        return;  // error

    Node *old_head = queue->head;
    queue->head = old_head->next;
    free(old_head);
}

int front(const void *self)
{
    Queue queue = (Queue)self;
    if (queue->empty(queue))
        return INT_MIN;

    return queue->head->data;
}
 
