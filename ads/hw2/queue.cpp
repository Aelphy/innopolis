#include <stdlib.h>
#include "queue.h"
#include "error.h"

Queue::Queue() {
    storage = new LinkedList;
}

Node* Queue::dequeue() {
    Node* first = storage->get_first_node();

    if (first == NULL) {
        error("cannot dequeue empty queue");
    } else {
        storage->set_first_node(first->get_next_node());

        if (storage->get_first_node() == NULL) {
            storage->set_current_node(NULL);
            storage->set_last_node(NULL);
        } else {
            storage->get_first_node()->set_previous_node(NULL);
        }

        first->set_next_node(NULL);
        first->set_previous_node(NULL);

        return first;
    }
}

void Queue::enqueue(Node* node) {
    // set current pointer to the last list node
    storage->get_last_node();

    storage->insert_element(node);
}

int Queue::length() {
    int counter = 0;
    Node *node = storage->get_first_node();

    if (node != NULL) {
        counter = 1;
    }

    while (node != storage->get_last_node()) {
        node = node->get_next_node();
        counter++;
    }

    return counter;
}

void Queue::print() {
    storage->print();
}

void Queue::empty() {
    storage->empty();
}
