#include "queue.h"

int main() {
    Queue* q1 = new Queue;
    q1->enqueue(new Node);
    Node *n = new Node;
    n->set_value("first node");
    q1->enqueue(n);
    q1->dequeue();
    q1->dequeue();

    Node *n1 = new Node;
    n1->set_value("second node");
    q1->enqueue(n);
    q1->print();

    return 0;
}