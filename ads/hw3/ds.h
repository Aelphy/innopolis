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
        void empty();
        void output_path_and_cost(int C1, int C2, int P, int N, FILE *fw);
};

template <class T>
class Heap {
    public:
        Heap() {  }

        // insert element to the heap
        void insert(T e) {
            storage.push_back(e);

            sift_up(storage.size() - 1);
        }

        // get maximum element
        T get_max() {
            T result = storage[0];

            storage[0] = storage[storage.size() - 1];
            storage.pop_back();
            sift_down(0);

            return result;
        }

    private:
        vector <T> storage;

        // process heap with one error from bottom to the up
        void sift_up(int i) {
            int parent = i / 2;

            // unless there is an error in the heap
            while(parent >= 0 && storage[parent] < storage[i]) {
                swap(parent, i);
                i = parent;
                parent = i / 2;
            }
        }

        // process heap with one error from up to the bottom
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

        // swap i and j elements in a storage
        void swap(int i, int j) {
            T temp = storage[i];

            storage[i] = storage[j];
            storage[j] = temp;
        }
};
