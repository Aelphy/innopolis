#include "linked_list.h"

class Queue {
    public:

    // constructor
    Queue();

    // pop
    Node* dequeue();

    // push
    void enqueue(Node* node);

    // get length of the queue
    int length();

    // output all the queue
    void print();

    // clear the queue
    void empty();

    private:

    // linked list that stores all the data
    LinkedList *storage;
};
