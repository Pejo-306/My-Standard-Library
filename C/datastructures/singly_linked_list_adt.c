#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define INPUT_BUFFER_SIZE 20
#define MAXLINE 1024

typedef struct node_t * Node;

struct node_t {
    int data;
    struct node_t *next;
};

typedef struct singly_linked_list_t * LinkedList;

struct singly_linked_list_t {
    struct node_t *head;

    size_t (*length)(const void *self);
    void (*print)(const void *self);
    void (*destroy)(const void *self);
    int (*empty)(const void *self);
    int (*first)(const void *self);
    int (*last)(const void *self);
    int (*at)(const void *self, int position);
    int (*insert)(const void *self, int position, int data);
    int (*remove)(const void *self, int position);
    void (*push)(const void *self, int data);
    void (*pop)(const void *self);
    void (*push_front)(const void *self, int data);
    void (*pop_front)(const void *self);
    void (*reverse)(const void *self);
};

LinkedList input_list(const char *);
LinkedList merge_lists(LinkedList, LinkedList);
LinkedList new_list();
size_t list_length(const void *);
void list_print(const void *);
void list_destroy(const void *);
int list_empty(const void *);
int list_first(const void *);
int list_last(const void *);
int list_at(const void *, int);
int list_insert(const void *, int, int);
int list_remove(const void *, int);
void list_push(const void *, int);
void list_pop(const void *);
void list_push_front(const void *, int);
void list_pop_front(const void *);
void list_reverse(const void *);

LinkedList input_list(const char *delimiter)
{
    Node pre_head, current;
    char line[MAXLINE], buffer[INPUT_BUFFER_SIZE];
    LinkedList list;

    pre_head = (Node)malloc(sizeof(struct node_t));
    current = pre_head;

    fgets(line, MAXLINE, stdin);
    strtok(line, "\n");  // remove newline after fgets
    for (int i = 0, j = 0; i < strlen(line); ++i, ++j) {
        if (strncmp(line+i, delimiter, strlen(delimiter)) == 0) {
            buffer[j] = '\0';
            j = -1;
            i += strlen(delimiter) - 1;
            
            current->next = (Node)malloc(sizeof(struct node_t));
            current->next->data = atoi(buffer);
            current = current->next;
        } else {
            buffer[j] = line[i];
        }
    }
    current->next = NULL;

    list = new_list();
    list->head = pre_head->next;
    free(pre_head);
    pre_head = NULL;
    return list;
}

LinkedList merge_lists(LinkedList listA, LinkedList listB)
{
    Node pre_head, current, currentA, currentB;

    pre_head = (Node)malloc(sizeof(struct node_t));
    current = pre_head;
    currentA = listA->head;
    currentB = listB->head;
    while (currentA != NULL && currentB != NULL) {
        if (currentA->data < currentB->data) {
            current->next = (Node)malloc(sizeof(struct node_t));
            current->next->data = currentA->data;
            current = current->next;
            currentA = currentA->next;
        } else {
            current->next = (Node)malloc(sizeof(struct node_t));
            current->next->data = currentB->data;
            current = current->next;
            currentB = currentB->next;
        }
    }
    while (currentA != NULL) {
        current->next = (Node)malloc(sizeof(struct node_t));
        current->next->data = currentA->data;
        current = current->next;
        currentA = currentA->next;
    }
    while (currentB != NULL) {
        current->next = (Node)malloc(sizeof(struct node_t));
        current->next->data = currentB->data;
        current = current->next;
        currentB = currentB->next;
    }
    current->next = NULL;

    LinkedList merged_list = new_list();
    merged_list->head = pre_head->next;
    free(pre_head);
    return merged_list;
}

LinkedList new_list()
{
    LinkedList self = (LinkedList)malloc(sizeof(struct singly_linked_list_t));
 
    self->head = NULL;

    self->length = list_length;
    self->print = list_print;   
    self->destroy = list_destroy;
    self->empty = list_empty;
    self->first = list_first;
    self->last = list_last;
    self->at = list_at;
    self->insert = list_insert;
    self->remove = list_remove;
    self->push = list_push;
    self->pop = list_pop;
    self->push_front = list_push_front;
    self->pop_front = list_pop_front;
    self->reverse = list_reverse;

    return self;
}

size_t list_length(const void *_self)
{
    LinkedList self = (LinkedList)_self;
    Node current = self->head;
    size_t len = 0;

    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void list_print(const void *_self)
{
    LinkedList self = (LinkedList)_self;
    Node current = self->head;

    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void list_destroy(const void *_self)
{
    LinkedList self = (LinkedList)_self;
    Node previous = NULL;
    Node current = self->head;

    while (current != NULL) {
        previous = current;
        current = current->next;
        free(previous);
    }
    free(self);
}

int list_empty(const void *_self)
{
    LinkedList self = (LinkedList)_self;

    return (self->head == NULL) ? 1 : 0;
}

int list_first(const void *_self)
{
    LinkedList self = (LinkedList)_self;

    return self->head->data;
}

int list_last(const void *_self)
{
    LinkedList self = (LinkedList)_self;
    Node current;

    for (current = self->head; current->next != NULL; current = current->next);
    return current->data;
}

int list_at(const void *_self, int position)
{
    LinkedList self = (LinkedList)_self;
    Node current;

    if (position < 0)
        return INT_MIN;
    else if (position >= self->length(self))
        return INT_MAX;

    current = self->head;
    for (int i = 0; i < position; ++i)
        current = current->next;
    return current->data;
}

int list_insert(const void *_self, int position, int data)
{
    LinkedList self = (LinkedList)_self;
    Node pre_head, current, temp;

    if (position < 0)
        return INT_MIN;
    else if (position > self->length(self))
        return INT_MAX;

    pre_head = (Node)malloc(sizeof(struct node_t));
    pre_head->next = self->head;
    current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;

    temp = current->next;
    current->next = (Node)malloc(sizeof(struct node_t));
    current->next->data = data;
    current->next->next = temp;

    self->head = pre_head->next;
    free(pre_head);
    return 0;
}

int list_remove(const void *_self, int position)
{
    LinkedList self = (LinkedList)_self;
    Node pre_head, current, temp;

    if (position < 0)
        return INT_MIN;
    else if (position >= self->length(self))
        return INT_MAX;

    pre_head = (Node)malloc(sizeof(struct node_t));
    pre_head->next = self->head;
    current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;
   
    temp = current->next->next;
    free(current->next);
    current->next = temp;
    
    self->head = pre_head->next;
    free(pre_head);
    return 0;
}

void list_push(const void *_self, int data)
{
    LinkedList self = (LinkedList)_self;

    self->insert(self, self->length(self), data);
}

void list_pop(const void *_self)
{
    LinkedList self = (LinkedList)_self;

    self->remove(self, self->length(self)-1);
}

void list_push_front(const void *_self, int data)
{
    LinkedList self = (LinkedList)_self;
    
    self->insert(self, 0, data);
}

void list_pop_front(const void *_self)
{
    LinkedList self = (LinkedList)_self;

    self->remove(self, 0);
}

void list_reverse(const void *_self)
{
    LinkedList self = (LinkedList)_self;
    Node previous, next, current;

    previous = NULL;
    next = self->head;
    while (next != NULL) {
        current = next;
        next = next->next;
        current->next = previous;
        previous = current;
    }
    self->head = current;
}

