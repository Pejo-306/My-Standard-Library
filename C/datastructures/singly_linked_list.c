#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t {
    int data;
    struct node_t *next;
} Node;

void print_list(Node *head)
{
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node * input_list(const char *delim)
{
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

    Node *result = pre_head->next;
    free(pre_head);
    return result;
}

Node * insert(Node *head, int data, int position)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    pre_head->next = head;
    Node *current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;

    Node *temp = current->next;
    current->next = (Node *)malloc(sizeof(Node));
    current->next->data = data;
    current->next->next = temp;

    Node *result = pre_head->next;
    free(pre_head);
    return result;
}

Node * delete_from_list(Node *head, int position)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    pre_head->next = head;
    Node *current = pre_head;
    for (int i = 0; i < position; i++)
        current = current->next;
   
    Node *temp = current->next->next;
    free(current->next);
    current->next = temp;
    
    Node *result = pre_head->next;
    free(pre_head);
    return result;
}

int list_cmp(Node *headA, Node *headB)
{
    Node *currentA = headA, *currentB = headB;
    while (currentA != NULL && currentB != NULL) {
        if (currentA->data != currentB->data)
            return 0;

        currentA = currentA->next;
        currentB = currentB->next;
    }
    if (currentA == NULL && currentB == NULL)
        return 1;
    return 0;
}

Node * reverse_list(Node *head)
{
    Node *next = head, *current, *previous = NULL;
    while (next != NULL) {
        current = next;
        next = next->next;
        current->next = previous;
        previous = current;
    }
    return current;
}

Node * merge_lists(Node *headA, Node *headB)
{
    Node *pre_head = (Node *)malloc(sizeof(Node));
    Node *current = pre_head;
    Node *currentA = headA, *currentB = headB;

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

    Node *result = pre_head->next;
    free(pre_head);
    return result;
}

