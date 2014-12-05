/*
 ============================================================================
 Name        : hw4
 Author      : Usvyatsov Mikhail
 ============================================================================
*/

#include <iostream>
#include "implementation.h"

//#define DEBUG
#define MAX_STOPS_COUNT 10
#define MAX_STRING_LENGTH 250

using namespace std;

/*
  travellingSalesmanApplication.cpp - application file for the solution of the travelling saleman problem by exhaustive
  search using backtracking

  CS-CO-412 Algorithms and Data Structures Assignment No. 4

  See travellingSalesman.h for details of the problem

  David Vernon
  17 November 2014

  Usvyatsov Mikhail
  3 December 2014
*/

int main() {
    int n;                                           // number of shops
    int k;                                           // number of test cases
    int i, j, q;                                     // counters
    int path[MAX_STOPS_COUNT];                       // best path
    int current_path[MAX_STOPS_COUNT];               // current path
    int total;                                       // best path cost
    int current_total;                               // current cost
    char buffer[MAX_STRING_LENGTH];                  // string buffer
    int distances[MAX_STOPS_COUNT][MAX_STOPS_COUNT]; // adjacency matrix
    FILE *fr, *fw;                                   // input and output file pointers

    try {
        /* open input and output files */
        if ((fr = fopen("input.txt", "r")) == NULL) {
            throw Error("cannot open the input file.\n");
        }

        if ((fw = fopen("output.txt", "w")) == NULL) {
            throw Error("cannot open the output file.\n");
        }

        fprintf(fw, "Usvyatsov Mikhail\n");

        /* read the number of test cases */
        if (fscanf(fr, "%i", &k) != 1) {
            throw Error("cannot read k.\n");
        }

#ifdef DEBUG
        printf("%d\n", k);
#endif

        /* main processing loop, one iteration for each test case */
        for (i = 0; i < k; ++i) {
            /* read the data for each test case  */
            /* --------------------------------  */

            /* number of shops */
            if (fscanf(fr, "%i", &n) != 1) {
                throw Error("cannot read n.\n");
            }

#ifdef DEBUG
            printf("%i\n", n);
#endif

            // check size of the problem
            if (n >= MAX_STOPS_COUNT) {
                throw Error("too big amount of shops.\n");
            } else {
                Shop *shops = new Shop[n]; // array of shops

                // costs initialization
                total = 0;
                current_total = 0;

                // get the shop and car names
                for (j = 0; j < n + 1; ++j) {
                    if (fscanf(fr, " %250[^\n]", buffer) < 1) {
                        throw Error("cannot read name.\n");
                    }

                    strcpy(shops[j].name, buffer);

#ifdef DEBUG
                    printf("%s\n", shops[j].name);
#endif
                }

                // get the matrix of distances
                for (q = 0; q < n + 1; ++q) {
                    for (j = 0; j < n + 1; ++j) {
                        fscanf(fr, "%d", &(distances[q][j]));
                    }
                }

#ifdef DEBUG
                for (q = 0; q < n + 1; ++q) {
                    for (j = 0; j < n + 1; ++j) {
                        printf("%3d ", distances[q][j]);
                    }

                    printf("\n");
                }
#endif

                // initialize paths
                for (j = 0; j < n + 1; ++j) {
                    path[j] = j;
                    current_path[j] = j;
                }

                // initialize cost
                total = distances[path[n]][path[0]];

                // add cost of initial permutation
                for (q = 0; q < n; ++q) {
                    total += distances[path[q]][path[q + 1]];
                }

                // add way to the car
                total += distances[path[n]][n];

                // process each permutation
                while(permutate(current_path, n)) {
                    // compute current_cost
                    current_total = distances[current_path[n]][current_path[0]];

                    for (q = 0; q < n; ++q) {
                        current_total += distances[current_path[q]][current_path[q + 1]];

                        // pruning
                        if (current_total > total) {
                            break;
                        }
                    }

                    // add way to the car
                    current_total += distances[current_path[n]][n];

                    // if current_path is better - swap
                    if (total > current_total) {
                        total = current_total;

                        for (q = 0; q < n + 1; ++q) {
                            path[q] = current_path[q];
                        }
                    }

                }

                fprintf(fw, "%i \n", i + 1);
                fprintf(fw, "%i \n", total);
                fprintf(fw, "%s \n", shops[n].name);

                for (j = 0; j < n; ++j) {
                    fprintf(fw, "%s \n", shops[path[j]].name);
                }

                fprintf(fw, "%s", shops[n].name);

                fprintf(fw, "\n");
            }
        }

        fclose(fr);
        fclose(fw);

        return 0;
    }   catch (exception const &ex) {
        cerr << "Exception: " << ex.what() << endl;

        fclose(fr);
        fclose(fw);

        return -1;
    }
}
