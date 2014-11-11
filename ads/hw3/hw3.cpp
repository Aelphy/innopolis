/*
 ============================================================================
 Name        : hw3
 Author      : Usvyatsov Mikhail
 ============================================================================
*/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "ds.h"

int main() {
    FILE *fr, *fw;
    int N = 0;
    int R = 0;
    int i = 0;
    int C1 = -1, C2 = -1, P = -1;
    int simulation_count = 0;
    Graph *graph = new Graph;

    try {
        // check input file
        if ((fr = fopen("input.txt", "r")) == NULL) {
            throw Error("cannot open the input file.\n");
        }

        // check output file
        if ((fw = fopen("output.txt", "w")) == NULL) {
            throw Error("cannot open the output file.\n");
        }

        fprintf(fw, "Usvyatsov Mikhail\n");

        // process input case by case
        while (true) {
            C1 = C2 = P = -1;

            // assign N and R
            // if there is no N or R in input file then exit with error code
            if (fscanf(fr, "%d %d", &N, &R) != 2) {
                throw Error("Cannot read N and R.\n");
            }

            // check end of input condition
            // stop if double zero string was founded
            if (N == 0 && R == 0) {
                break;
            }

            // check that N has valid value
            if (!(N >= 1 && N <= 100)) {
                throw Error("N is wrong.\n");
            }

            // fill the graph
            for (i = 0; i < R; ++i) {
                // assign graph data to temporary variables
                if (fscanf(fr, "%d %d %d", &C1, &C2, &P) != 3) {
                    throw Error("cannot read line.\n");
                }

                // add data to graph
                graph->insert(C1, C2, P);
                graph->insert(C2, C1, P);
            }

            // assign start, destination and amount of people
            if (fscanf(fr, "%d %d %d", &C1, &C2, &P) != 3) {
                throw Error("cannot read destination line.\n");
            }

            fprintf(fw, "Scenario #%i\n", simulation_count + 1);

            // find path and cost
            graph->output_path_and_cost(C1, C2, P, N, fw);

            fprintf(fw, "\n");

            // empty the graph
            graph->empty();

            // increase simulations count
            ++simulation_count;
        }

        delete graph;

        return 0;
    }   catch (exception const &ex) {
        cerr << "Exception: " << ex.what() << endl;

        delete graph;

        return -1;
    }
}
