#include "implementation.h"

// trow error with a message
Error::Error(string information) {
    message = information;
}

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
bool permutate(int *a, int n) {
    int i, k, l;            // counters
    bool finished = true;   // end flag

    // look for avaliable permutation
    for(i = n - 2; i >= 0; --i) {
        if (a[i] < a[i + 1]) {
            k = i;
            finished = false;
            break;
        }
    }

    l = 0;

    if (finished) {
        return false;
    }   else {
        for(i = n - 1; i > 0; --i) {
            if (a[k] < a[i]) {
                l = i;
                break;
            }
        }

        swap(a, k, l);
        reverse(a, k + 1, n - 1);

        return true;
    }
}
