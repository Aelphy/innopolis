/*
 ============================================================================
 Name        : hw4
 Author      : Usvyatsov Mikhail
 ============================================================================
*/

#include <iostream>
#include "ds.h"

#define DEBUG 1
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

// swap elements of array
void swap(int *a, int i, int j) {
    int buffer = a[i];

    a[i] = a[j];
    a[j] = buffer;
}

// reverse array a from i upto j elements
void reverse(int *a, int i, int j) {
    int q;

    // if left less than right
    if (i < j) {
        // swap every item from the left with the pare from the right
        for (q = 0; q <= (j - i) / 2; ++q) {
            swap(a, i + q, j - q);
        }
    }
}

// generate next permutation
void permutate(int *a, int n) {
    int i, k, l;
    bool finished = true;

    for(i = n - 2; i >= 0; --i) {
        if (a[i] < a[i + 1]) {
            k = i;
            finished = false;
            break;
        }
    }

    if (finished) {
        return;
    }   else {
        for(i = n - 1; i > 0; --i) {
            if (a[k] < a[i]) {
                l = i;
                break;
            }
        }

        swap(a, k, l);
        reverse(a, k + 1, n - 1);
    }
}

// compute factorial
int factorial(int i) {
    if (i <= 1) {
        return 1;
    } else {
        return i * factorial(i - 1);
    }
}

int main() {
    int n;                                           // number of shops
    int k;                                           // number of test cases
    long long int i, j, q;                           // counters
    int path[MAX_STOPS_COUNT];                       // best path
    int current_path[MAX_STOPS_COUNT];               // current path
    int total;                                       // best path cost
    int current_total;                               // current cost
    long long int permutations_count;                // amount of permutations
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

                total = 0;
                current_total = 0;
                permutations_count = factorial(n);

                // get the shop names
                for (j = 0; j < n + 1; ++j) {
                    fscanf(fr, " %250[^\n]", buffer);

                    strcpy(shops[j].name, buffer);

                    if (DEBUG == 1) {
                        printf("%s\n", shops[j].name);
                    }
                }

                // get the matrix of distances
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

                // initialize paths
                for (j = 0; j < n + 1; ++j) {
                    path[j] = j;
                    current_path[j] = j;
                }

                // initialize cost
                total = distances[path[n]][path[0]];

                for (q = 0; q < n; ++q) {
                    total += distances[path[q]][path[q + 1]];
                }

                total += distances[path[n]][n];

                // process each permutation
                for (j = 1; j < permutations_count; ++j) {
                    permutate(current_path, n);

                    // compute current_cost
                    current_total = distances[current_path[n]][current_path[0]];

                    for (q = 0; q < n; ++q) {
                        current_total += distances[current_path[q]][current_path[q + 1]];

                        // pruning
                        if (current_total > total) {
                            break;
                        }
                    }

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
    }   catch (exception const &ex) {
        cerr << "Exception: " << ex.what() << endl;

        fclose(fr);
        fclose(fw);

        return -1;
    }
}
