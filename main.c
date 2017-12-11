#include <stdio.h>
#include <stdlib.h>

int INPUT_SIZE     = 3;
int INPUT_VECTOR[] = {0, 10, 12};

void print_items(int* items, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", items[i]);
    }

    printf("\n");
}

int* map(int* items, int size, int (*f)(int)) {

    int* start = malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {
        start[i] = f(items[i]);
    }

    return start;
}

int reduce(int* items, int size, int (*agg)(int, int), int initial) {
    int result = initial;

    for(int i = 0; i < size; i++) {
        result = agg(result, items[i]);
    }

    return result;
}

int twice(int i) {
    return 2 * i;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    print_items(INPUT_VECTOR, INPUT_SIZE);

    int* mapped_items = map(INPUT_VECTOR, INPUT_SIZE, twice);
    print_items(mapped_items, INPUT_SIZE);

    int reduced_item = reduce(mapped_items, INPUT_SIZE, sum, 0);
    printf("%d\n", reduced_item);

    free(mapped_items);
    return 0;
}
