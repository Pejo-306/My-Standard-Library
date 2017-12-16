#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} Node;

typedef struct singly_linked_list_t * List;

struct singly_linked_list_t {
    struct node_t *head;

    void (*print)(const void *self);
    void (*insert)(const void *self, int data, int position);
    void (*remove)(const void *self, int position);
    size_t (*length)(const void *self);
    void (*reverse)(const void *self);
};

List new_list()
{
    List self = (List)malloc(sizeof(struct singly_linked_list_t));
 
    self->head = NULL;
    self->print = &print_list;   
    self->insert = &insert;
    self->remove = &delete_from_list;
    self->length = &list_length;
    self->reverse = &reverse_list;

    return self;
}

void print_list(const void *self)
{
    Node *current = ((List)self)->head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void insert(const void *self, int data, int position)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    pre_head->next = ((List)self)->head;
    Node *current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;

    Node *temp = current->next;
    current->next = (Node *)malloc(sizeof(Node));
    current->next->data = data;
    current->next->next = temp;

    ((List)self)->head = pre_head->next;
    free(pre_head);
}

void delete_from_list(const void *self, int position)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    pre_head->next = ((List)self)->head;
    Node *current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;
   
    Node *temp = current->next->next;
    free(current->next);
    current->next = temp;
    
    ((List)self)->head = pre_head->next;
    free(pre_head);
}

size_t list_length(const void *self) {
    size_t len = 0;
    Node *current = ((List)self)->head;
    while (current != NULL) {
        len++;
        current = current->next;
    }
    return len;
}

void reverse_list(const void *self)
{
    Node *next = ((List)self)->head, *current, *previous = NULL;
    while (next != NULL) {
        current = next;
        next = next->next;
        current->next = previous;
        previous = current;
    }
    ((List)self)->head = current;
}

List input_list(const char *delim)
{
    // note: doesn't work with negative integers
    Node *pre_head = (Node *)malloc(sizeof(Node));
    Node *current = pre_head;

    char line[1024];
    fgets(line, 1024, stdin);
    strtok(line, "\n");  // remove newline after fgets

    char *token = strtok(line, delim);
    while (token != NULL && strcmp(token, "NULL") != 0) {  // NULL shows the end of the list
        current->next = (Node *)malloc(sizeof(Node));
        current->next->data = atoi(token);
        current = current->next;
        token = strtok(NULL, delim);
    }
    current->next = NULL;

    List list = new_list();
    list->head = pre_head->next;
    free(pre_head);
    return list;
}

List merge_lists(List listA, List listB)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    Node *current = pre_head;
    Node *currentA = listA->head, *currentB = listB->head;

    while (currentA != NULL && currentB != NULL) {
        if (currentA->data < currentB->data) {
            current->next = currentA;
            current = current->next;
            currentA = currentA->next;
        } else {
            current->next = currentB;
            current = current->next;
            currentB = currentB->next;
        }
    }

    while (currentA != NULL) {
        current->next = currentA;
        current = current->next;
        currentA = currentA->next;
    }

    while (currentB != NULL) {
        current->next = currentB;
        current = current->next;
        currentB = currentB->next;
    }

    List result = new_list();
    result->head = pre_head->next;
    free(pre_head);
    return result;
}

