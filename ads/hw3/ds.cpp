#include "ds.h"

// trow error with a message
Error::Error(string information) {
    message = information;
}

// add new data to graph
void Graph::insert(int C1, int C2, int P) {
    int i = 0;
    int is_found = 0;
    edge e;

    e.start = C1;
    e.distanation = C2;
    e.capacity = P;

    for(i = 0; i < nodes.size(); ++i) {
        if (nodes[i].city == C1) {
            nodes[i].edges.push_back(e);

            is_found = 1;

            break;
        }
    }

    if (is_found == 0) {
        node n;

        n.city = C1;
        n.is_visited = false;

        n.edges.push_back(e);

        nodes.push_back(n);
    }
}

void Graph::print() {
    int i = 0;
    int j = 0;

    for(i = 0; i < nodes.size(); ++i) {
        printf("%i -> [\n", nodes[i].city);

        for(j = 0; j < nodes[i].edges.size(); ++j) {
            printf("city: %i - capacity: %i\n", nodes[i].edges[j].start, nodes[i].edges[j].capacity);
        }

        printf("]\n");
    }
}

void Graph::empty() {
    nodes.clear();
}

void Graph::output_path_and_cost(int C1, int C2, int P, int N) {
    if (N == 1) {
        printf("Minimum Number of Trips = 0\n");
        printf("Route = %i\n", C1);
    } else {
        int i = 0;
        int j = 0;
        Heap <edge> *heap = new Heap <edge>;

        for(i = 0; i < nodes.size(); ++i) {
            // start search for the path
            if (nodes[i].city == C1) {
                // fill the heap
                for (j = 0; j < nodes[i].edges.size(); ++j) {
                    heap->insert(nodes[i].edges[j]);
                }

                // process the heap

                break;
            }
        }

        delete heap;
    }
}
