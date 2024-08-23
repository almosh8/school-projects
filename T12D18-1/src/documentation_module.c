#include "documentation_module.h"

#include <stdarg.h>
#include <stdlib.h>

int* check_available_documentation_module(int (*validate)(char*), int document_count, ...) {
    // Allocate memory for the availability array
    int* availability = calloc(document_count, sizeof(int));

    // Get the document names from the variable arguments
    va_list args;
    va_start(args, document_count);

    for (int i = 0; i < document_count; i++) {
        char* document_name = va_arg(args, char*);
        availability[i] = (*validate)(document_name);
    }

    va_end(args);

    return availability;
}

int validate(char* data) {
    int validation_result = !strcmp(data, Available_document);
    return validation_result;
}