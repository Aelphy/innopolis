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

    // look for the existent node with city C1
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

void Graph::empty() {
    nodes.clear();
}

void Graph::output_path_and_cost(int C1, int C2, int P, int N, FILE *fw) {
    if (N == 1) {
        fprintf(fw, "Minimum Number of Trips = 0\n");
        fprintf(fw, "Route = -\n");
    } else {
        int i = 0;
        int j = 0;
        int min_capacity = P + 1;
        int number_of_trips = 0;
        int current_city = C1;
        Heap <edge> *heap = new Heap <edge>;
        edge e;
        vector <edge> explored_edges;
        vector <edge> path;

        while(current_city != C2) {
            for(i = 0; i < nodes.size(); ++i) {
                // start search for the path
                if (nodes[i].city == current_city) {
                    nodes[i].is_visited = true;

                    // fill the heap
                    for (j = 0; j < nodes[i].edges.size(); ++j) {
                        heap->insert(nodes[i].edges[j]);
                    }

                    // process the heap
                    e = heap->get_max();

                    // checks if we already have expanded the node in destination of e
                    while(current_city != e.distanation) {
                        // look for the node with the same city as in distanation of e
                        for(i = 0; i < nodes.size(); ++i) {
                            if (nodes[i].city == e.distanation) {
                                if(nodes[i].is_visited) {
                                    e = heap->get_max();
                                } else {
                                    current_city = e.distanation;
                                    explored_edges.push_back(e);
                                }

                                break;
                            }
                        }
                    }

                    break;
                }
            }
        }

        delete heap;

        current_city = C2;

        // build the path
        for(i = explored_edges.size() - 1; i >= 0; --i) {
            if(explored_edges[i].distanation == current_city) {
                path.push_back(explored_edges[i]);
                current_city = explored_edges[i].start;
            }
        }

        // detect the least width of the edges in the path
        for(i = 0; i < path.size(); ++i) {
            if (path[i].capacity < min_capacity) {
                min_capacity = path[i].capacity;
            }
        }

        // it was specially tested via changing edge weight and P
        number_of_trips = (P + min_capacity - 2) / (min_capacity - 1);

        fprintf(fw, "Minimum Number of Trips = %i\n", number_of_trips);
        fprintf(fw, "Route = %i", path[path.size() - 1].start);

        for(i = path.size() - 2; i >= 0; --i) {
            fprintf(fw, " - %i", path[i].start);
        }

        fprintf(fw, " - %i\n", path[0].distanation);
    }
}
