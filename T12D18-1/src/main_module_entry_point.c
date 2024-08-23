#include <stdio.h>
#include <stdlib.h>

#ifdef DOC
#include "documentation_module.h"
#else
#include "print_module.h"
#endif

int main() {
#ifdef DOC
    int* availability = check_available_documentation_module(validate, Documents_count, Documents);

    char* docs[] = {Documents};
    for (int i = 0; i < Documents_count; i++) {
        printf("[%-15s: %s]\n", docs[i], availability[i] ? "available" : "unavailable");
    }

    free(availability);
#else
    print_log(print_char, Module_load_success_message);
#endif

    return 0;
}
