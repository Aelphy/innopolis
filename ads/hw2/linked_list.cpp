#include <stdio.h>
#include <string.h>
#include "error.h"
#include "linked_list.h"

Node::Node () {
    next = NULL;
    previous = NULL;
}

Node::Node(Node* n, Node* p) {
    next = n;
    previous = p;
}

Node::Node(double t) {
    arrival_time = t;
    next = previous = NULL;
}

Node* Node::get_next_node() {
    return next;
}

Node* Node::get_previous_node() {
    return previous;
}

double Node::get_arrival_time() {
    return arrival_time;
}

void Node::set_next_node(Node* n) {
    next = n;
}

void Node::set_previous_node(Node* p) {
    previous = p;
}



void Node::set_arrival_time(double time) {
    arrival_time = time;
}

LinkedList::LinkedList() {
    first_node = NULL;
    current_node = NULL;
    last_node = NULL;
}

Node* LinkedList::get_first_node() {
    current_node = first_node;

    return current_node;
}

Node* LinkedList::get_current_node() {
    return current_node;
}

Node* LinkedList::get_next_node() {
    current_node = current_node->get_next_node();
    return current_node;
}

Node* LinkedList::get_previous_node() {
    current_node = current_node->get_previous_node();
    return current_node;
}

Node* LinkedList::get_last_node() {
    current_node = last_node;
    return current_node;
}

void LinkedList::set_first_node(Node* f_n) {
    first_node = f_n;

    current_node = first_node;
}

void LinkedList::set_current_node(Node* c_n) {
    current_node = c_n;
}

void LinkedList::set_last_node(Node* l_n) {
    last_node = l_n;

    current_node = last_node;
}

void LinkedList::insert_element(Node* element) {
    element->set_next_node(NULL);
    element->set_previous_node(NULL);

    if (is_empty()) {
        first_node = element;
        current_node = element;
        last_node = element;
    } else {
        Node *buffer, *buffered_current_node;

        buffered_current_node = current_node;
        buffer = current_node->get_next_node();
        buffered_current_node->set_next_node(element);
        element->set_previous_node(buffered_current_node);
        element->set_next_node(buffer);

        if (buffer != NULL) {
            buffer->set_previous_node(element);
        } else {
            last_node = element;
        }

        current_node = element;
    }
}

void LinkedList::delete_element_after() {
    if (current_node == last_node) {
        error("cannot delete after last node");
    } else {
        Node *buffer;

        buffer = current_node->get_next_node();
        current_node->set_next_node(buffer->get_next_node());

        if (buffer == last_node) {
            last_node = current_node;
        } else {
            buffer->get_next_node()->set_previous_node(current_node);
        }

        delete buffer;
    }
}

void LinkedList::delete_element_before() {
    if (current_node == first_node) {
        error("cannot before first last node");
    } else {
        Node *buffer;

        buffer = current_node->get_previous_node();
        current_node->set_previous_node(buffer->get_previous_node());

        if (buffer == first_node) {
            first_node = current_node;
        } else {
            buffer->get_previous_node()->set_next_node(current_node);
        }

        delete buffer;
    }
}

bool LinkedList::is_empty() {
    if (first_node == NULL && current_node == NULL && last_node == NULL) {
        return true;
    } else {
        return false;
    }
};

void LinkedList::empty() {
    current_node = first_node;

    while(current_node != NULL) {
        Node *buffer;

        buffer = current_node;
        current_node = current_node->get_next_node();

        if (current_node != NULL) {
            current_node->set_previous_node(NULL);
        }

        delete buffer;
    }

    first_node = NULL;
    last_node = NULL;
}

void LinkedList::print() {
    current_node = first_node;

    printf("Contents of list: \n");

    while(current_node != NULL) {
        printf("%lf\n", current_node->get_arrival_time());
        current_node = current_node->get_next_node();
    }

    printf("---END OF LIST---\n");

    current_node = last_node;
}
