#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void range(int start, int stop, int step) {
    for (int i = start; i < stop; i += step) {
        printf("%d\n", i);
    }
}


int main(int argc, char* argv[]) {
    int start = 0;
    int stop = 0;
    int step = 1;
    switch (argc) {
    case 1:
        printf("./range {stop}\n");
        printf("./range {start} {stop} {step=1}\n");
        break;
    case 2:
        stop = atoi(argv[1]);
        range(start, stop, step);
        break;
    case 3:
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        range(start, stop, step);
        break;
    case 4:
        start = atoi(argv[1]);
        stop = atoi(argv[2]);
        step = atoi(argv[3]);
        range(start, stop, step);
        break;
    default:
        printf("range accepts 0..3 integer argumetns\n");
    }
    return 0;
}