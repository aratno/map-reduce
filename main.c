#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int INPUT_SIZE     = 3;
int INPUT_VECTOR[] = {0, 10, 12};

void print_items(int* items, int size) {
    for(int i = 0; i < size; i++)
        printf("%d ", items[i]);

    printf("\n");
}

int* map(int* items, int size, int (*f)(int)) {

    int* start = malloc(sizeof(int) * size);

    for(int i = 0; i < size; i++) {

        int fds[] = {0, 0};
        pipe(fds);

        pid_t pid = fork();
        if( pid != 0 ){
            // Parent
            printf("Process %d spawned child %d with PID: %d\n", getpid(), i, pid);
            printf("Main process writing to pipe...\n");
            close(fds[0]);

            int outbound = i;
            write(fds[1], &outbound, sizeof(int));

            int raw_status = 0;
            waitpid(pid, &raw_status, 0);
            int exit_status = WEXITSTATUS(raw_status);

            printf("Main process saw process %d terminate with status %d\n", pid, exit_status);
            start[i] = exit_status;

        } else {
            // Child

            pid = getpid();
            close(fds[1]);

            int inbound = 0;
            read(fds[0], &inbound, sizeof(int));

            printf("Child process %d read: %d\n", pid, inbound);

            int result = f(items[inbound]);
            printf("Child process %d exiting with result: %d\n", pid, result);
            exit(result);

            return NULL;
        }

        start[i] = f(items[i]);
    }

    return start;
}

int reduce(int* items, int size, int (*agg)(int, int), int initial) {
    int result = initial;

    for(int i = 0; i < size; i++)
        result = agg(result, items[i]);

    return result;
}

int twice(int i) {
    return 2 * i;
}

int sum(int a, int b) {
    return a + b;
}

int main() {
    pid_t main_pid = getpid();
    printf("Main process has PID: %d\n", main_pid);

    int* mapped = map(INPUT_VECTOR, INPUT_SIZE, twice);

    printf("Mapped: ");
    print_items(mapped, INPUT_SIZE);

    int reduced = reduce(mapped, INPUT_SIZE, sum, 0);
    printf("Reduced: %d\n", reduced);

    return 0;
}
