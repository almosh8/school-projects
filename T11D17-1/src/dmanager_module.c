#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "door_struct.h"

#define DOORS_COUNT 15
#define MAX_ID_SEED 10000

void initialize_doors(door* doors);
void sort_doors(door doors[], int n);

int main() {
    door doors[DOORS_COUNT];

    initialize_doors(doors);

    sort_doors(doors, DOORS_COUNT);

    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].status = 0;
    }

    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i < DOORS_COUNT - 1) printf("\n");
    }

    return 0;
}

// doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(door* doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}

void sort_doors(door doors[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (doors[i].id > doors[j].id) {
                door temp = doors[j];
                doors[j] = doors[i];
                doors[i] = temp;
            }
        }
    }
}