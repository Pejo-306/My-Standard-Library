#include <iostream>
#include <climits>

using namespace std;

struct Node {
    int data;
    Node *next;
};

struct Queue {
    Node *head, *tail;

    Queue()
    {
        head = NULL;
        tail = NULL;
    }

    void print()
    {
        Node *current = head;
        while (current != NULL) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    bool empty()
    {
        if (head != NULL)
            return false;
        return true;
    }

    size_t size()
    {
        size_t len = 0;
        Node *current = head;
        while (current != NULL) {
            len++;
            current = current->next;
        }
        return len;
    }

    void push(int data)
    {
        Node *new_element = new Node;
        new_element->data = data;
        new_element->next = NULL;
        
        if (empty()) {
            head = new_element;
            tail = new_element;
        } else {
            tail->next = new_element;
            tail = tail->next;
        }
    }

    void pop()
    {
        if (empty())
            return;  //error
        
        Node *old_head = head;
        head = old_head->next;
        free(old_head);        
    }

    int front()
    {
        if (empty())
            return INT_MIN;
        return head->data;
    }
};

