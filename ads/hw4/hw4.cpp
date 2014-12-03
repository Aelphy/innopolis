#include <iostream>
#include "ds.h"

#define DEBUG 1
#define MAX_STOPS_COUNT 11

using namespace std;

/*
  travellingSalesmanApplication.cpp - application file for the solution of the travelling saleman problem by exhaustive search using backtracking

  CS-CO-412 Algorithms and Data Structures Assignment No. 4

  See travellingSalesman.h for details of the problem

  David Vernon
  17 November 2014

  Usvyatsov Mikhail
  3 December 2014
*/
int main() {
    int k;                                           // number of test cases
    int n;                                           // number of shops
    int i, j, q;                                        // counters
    char buffer[250];                                // string buffer
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

        /* read the number of test cases */
        fscanf(fr, "%i", &k);

        if (DEBUG == 1) {
            printf("%d\n", k);
        }

        /* main processing loop, one iteration for each test case */
        for (i = 0; i < k; ++i) {
            /* read the data for each test case  */
            /* --------------------------------  */

            /* number of shops */
            fscanf(fr, "%i", &n);

            if (DEBUG == 1) {
                printf("%i\n", n);
            }

            if (n >= 10) {
                throw Error("too big amount of shops.\n");
            } else {
                Shop *shops = new Shop[n];

                /* get the shop names and the car name */
                for (j = 0; j < n + 1; ++j) {
                    fscanf(fr, " %250[^\n]", buffer);

                    strcpy(shops[j].name, buffer);

                    if (DEBUG == 1) {
                        printf("%s\n", shops[j].name);
                    }
                }

                /* get the matrix of distances */
                for (q = 0; q < n + 1; ++q) {
                    for (j = 0; j < n + 1; ++j) {
                        fscanf(fr, "%d", &(distances[q][j]));
                    }
                }

                if (DEBUG == 1) {
                    for (q = 0; q < n + 1; ++q) {
                        for (j = 0; j < n + 1; ++j) {
                            printf("%3d ", distances[q][j]);
                        }

                        printf("\n");
                    }
                }
            }


            /* main processing begins here */
            /* --------------------------- */
        }

        fclose(fr);
        fclose(fw);
    }   catch (exception const &ex) {
        cerr << "Exception: " << ex.what() << endl;

        fclose(fr);
        fclose(fw);

        return -1;
    }
}
