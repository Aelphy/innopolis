#include <stdlib.h>
#include <math.h>
#include "poisson_distribution.h"

// Find the number of pointed distributed events per period given the lambda ratio(mean)
int poison_distributed_events_number(double lambda) {
    int count;
    double product;
    double border;

    count = 0;
    product = (double) rand() / RAND_MAX;
    border = exp(-lambda);

    while (product > border) {
        count++;
        product = (double) rand() * product / RAND_MAX;
    }

    return(count);
}
