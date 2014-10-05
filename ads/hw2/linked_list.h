class Node {
    public:

    // default constructor
    Node ();

    // constructor with next and previous
    Node(Node* n, Node* p);

    // constructor with arrival time
    Node(double t);

    // returns the node after the current node
    Node* get_next_node();

    // returns the node before the current node
    Node* get_previous_node();

    // get value of node
    char* get_value();

    // get arrival time of node
    double get_arrival_time();

    // set the node after the current
    void set_next_node(Node* n);

    // set the node before the current
    void set_previous_node(Node* p);

    // set value of the node
    void set_value(char* string);

    // set arrival time of the node
    void set_arrival_time(double time);

    private:

    // pointer to the next node
    Node *next;
    // pointer to the previous node
    Node *previous;
    // pointer to store value string
    char *value;
    // arrival time
    double arrival_time;
};

class LinkedList {
    public:

    // constructor
    LinkedList();

    // returns the first node of the list
    Node* get_first_node();

    // returns the current node of the list
    Node* get_current_node();

    // returns the next node of the list
    Node* get_next_node();

    // returns the previous node of the list
    Node* get_previous_node();

    // returns the last node of the list
    Node* get_last_node();

    // set the first node of the list
    void set_first_node(Node* f_n);

    // set the current node of the list
    void set_current_node(Node* c_n);

    // set the last node of the list
    void set_last_node(Node* l_n);

    // insert element after the current in the list
    void insert_element(Node* element);

    // delete element after the current
    void delete_element_after();

    // delete element before the current
    void delete_element_before();

    // check is the list empty
    bool is_empty();

    // empty the list
    void empty();

    // print all the nodes of the list
    void print();

    private:

    // the first node
    Node *first_node;
    // the current node
    Node *current_node;
    // the last node
    Node *last_node;
};
