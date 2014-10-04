#include <stdlib.h>
#include <stdio.h>
#include "error.h"

void error(const char *message) {
    printf("Error: %s\n", message);
    exit(1);
}
