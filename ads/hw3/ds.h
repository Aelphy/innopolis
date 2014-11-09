#include <exception>
#include <string>
#include <vector>

using namespace std;

typedef struct Edge {
    int start;
    int distanation;
    int capacity;
} edge;

typedef struct Node {
    int city;
    bool is_visited;
    vector <edge> edges;
} node;

class Error : public exception {
public:
    string message;

    Error() {};
    Error(string information);

    virtual const char * what () const throw () {
        return message.c_str();
    }
};

class Graph {
    public:
        vector <node> nodes;

        Graph() {}

        void insert(int C1, int C2, int P);
        void print();
        void empty();
        void output_path_and_cost(int C1, int C2, int P);
};

template <class T>
class Heap {
    public:
        Heap() {}

        void insert(edge e) {
            
        }
    private:
        vector <vector <T> > storage;
};
