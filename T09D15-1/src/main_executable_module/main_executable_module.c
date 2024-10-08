#include <stdio.h>
#include <stdlib.h>

#ifdef MACRO
#define TYPE_DOUBLE
#include "../data_libs/data_io_macro.h"
GENERATE_IO_FUNCTIONS
#else
#include "../data_libs/data_io.h"
#endif

#include "../data_module/data_process.h"
#include "../yet_another_decision_module/decision.h"
#include "data_sort.h"

int main() {
    double *data;
    int n;

    if (scanf("%d", &n) != 1 || n < 1) {
        printf("n/a");
        return 0;
    }

    // Don`t forget to allocate memory !
    data = malloc(n * sizeof(double));

    printf("LOAD DATA...\n");
    input(data, n);

    printf("RAW DATA:\n\t");
    output(data, n);

    printf("\nNORMALIZED DATA:\n\t");
    normalization(data, n);
    output(data, n);

    printf("\nSORTED NORMALIZED DATA:\n\t");
    sort(data, n);
    output(data, n);

    printf("\nFINAL DECISION:\n\t");
    if (make_decision(data, n))
        printf("YES");
    else
        printf("NO");

    free(data);

    return 0;
}
