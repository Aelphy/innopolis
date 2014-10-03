#include <stdio.h>
#include <string.h>
#include "error.h"

class Node {
    public:

    Node () {
        next = NULL;
        previous = NULL;
    }

    Node(Node* n, Node* p) {
        next = n;
        previous = p;
    }

    Node* get_next_node() {
        return next;
    }

    Node* get_previous_node() {
        return previous;
    }

    char* get_value(){
        return value;
    }

    void set_next_node(Node* n) {
        next = n;
    }

    void set_previous_node(Node* p) {
        previous = p;
    }

    void set_value(char* string) {
        value = string;
    }

    private:

    Node *next;
    Node *previous;
    char *value;
};

class LinkedList {
    public:

    LinkedList() {
        first_node = NULL;
        current_node = NULL;
        last_node = NULL;
    }

    LinkedList(Node* n1, Node* n2, Node* n3) {
        first_node = n1;
        current_node = n2;
        last_node = n3;
    }

    Node* get_first_node() {
        current_node = first_node;

        return current_node;
    }

    Node* get_current_node() {
        return current_node;
    }

    Node* get_next_node() {
        current_node = current_node->get_next_node();
        return current_node;
    }

    Node* get_previous_node() {
        current_node = current_node->get_previous_node();
        return current_node;
    }

    Node* get_last_node() {
        current_node = last_node;
        return current_node;
    }

    void set_first_node(Node* f_n) {
        first_node = f_n;

        current_node = first_node;
    }

    void set_current_node(Node* c_n) {
        current_node = c_n;
    }

    void set_last_node(Node* l_n) {
        last_node = l_n;

        current_node = last_node;
    }

    void insert_element(Node* element) {
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

            current_node = element;
        }
    }

    void delete_element_after() {
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

    void delete_element_before() {
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

    bool is_empty() {
        if (first_node == NULL && current_node == NULL && last_node == NULL) {
            return true;
        } else {
            return false;
        }
    };

    void empty() {
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

    void print() {
        current_node = first_node;

        printf("Contents of list: \n");

        while(current_node != NULL) {
            printf("%s\n", current_node->get_value());
            current_node = current_node->get_next_node();
        }

        printf("---END OF LIST---\n");

        current_node = last_node;
    }

    private:

    Node *first_node;
    Node *current_node;
    Node *last_node;
};
