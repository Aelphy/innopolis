class Node {
    public:

    Node ();

    Node(Node* n, Node* p);

    Node(double t);

    Node* get_next_node();

    Node* get_previous_node();

    char* get_value();

    double get_arrival_time();

    void set_next_node(Node* n);

    void set_previous_node(Node* p);

    void set_value(char* string);

    void set_arrival_time(double time);

    private:

    Node *next;
    Node *previous;
    char *value;
    double arrival_time;
};

class LinkedList {
    public:

    LinkedList();

    Node* get_first_node();

    Node* get_current_node();

    Node* get_next_node();

    Node* get_previous_node();

    Node* get_last_node();

    void set_first_node(Node* f_n);

    void set_current_node(Node* c_n);

    void set_last_node(Node* l_n);

    void insert_element(Node* element);

    void delete_element_after();

    void delete_element_before();

    bool is_empty();

    void empty();

    void print();

    private:

    Node *first_node;
    Node *current_node;
    Node *last_node;
};
