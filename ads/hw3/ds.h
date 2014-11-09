#include <exception>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

typedef struct Edge {
    public:
        int start;
        int distanation;
        int capacity;

        bool operator > (const Edge &val) {
            return capacity > val.capacity;
        }

        bool operator < (const Edge &val) {
            return capacity < val.capacity;
        }
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
        void output_path_and_cost(int C1, int C2, int P, int N);
};

template <class T>
class Heap {
    public:
        Heap() {  }

        void insert(T e) {
            storage.push_back(e);

            sift_up(storage.size() - 1);
        }

        void sift_up(int i) {
            int parent = (i - 1) / 2;

            while(parent >= 0 && storage[parent] < storage[i]) {
                swap(parent, i);
                i = parent;
                parent = (i - 2) / 2;
            }
        }

        void sift_down(int i) {
            int lft = 2 * i + 1;
            int rgt = lft + 1;
            bool finished = false;

            while(!finished) {
                finished = true;

                if((rgt < storage.size() && lft < storage.size() && (storage[i] < storage[rgt] || storage[i] < storage[lft]))) {
                    if(storage[lft] < storage[rgt]) {
                        swap(rgt, i);
                        i = rgt;
                        lft = 2 * i + 1;
                        rgt = lft + 1;
                        finished = false;
                    } else {
                        swap(lft, i);
                        i = lft;
                        lft = 2 * i + 1;
                        rgt = lft + 1;
                        finished = false;
                    }
                } else {
                    if (lft < storage.size() && storage[i] < storage[lft]) {
                        swap(lft, i);
                        i = lft;
                        lft = 2 * i + 1;
                        rgt = lft + 1;
                        finished = false;
                    }

                    if (rgt < storage.size() && storage[i] < storage[rgt]) {
                        swap(rgt, i);
                        i = rgt;
                        lft = 2 * i + 1;
                        rgt = lft + 1;
                        finished = false;
                    }
                }
            }
        }

        void print() {
            int i = 0;

            for(i = 0; i < storage.size(); ++i) {
                printf("%i ", storage[i]);
            }

            printf("\n");
        }

        void swap(int i, int j) {
            T temp = storage[i];

            storage[i] = storage[j];
            storage[j] = temp;
        }

        T get_max() {
            T result = storage[0];

            storage[0] = storage[storage.size() - 1];
            storage.pop_back();
            sift_down(0);

            return result;
        }

    private:
        vector <T> storage;
};
