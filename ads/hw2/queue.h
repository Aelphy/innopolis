#include "linked_list.h"

class Queue {
    public:

    Queue();

    Node* dequeue();

    Node* get_first_node();

    Node* get_next_node();

    Node* get_current_node();

    void enqueue(Node* node);

    int length();

    void print();

    bool is_empty();

    void empty();

    private:

    LinkedList *storage;
};
