#include <stdio.h>

int x = 0;

int g(void) {
    return x;
}

int main(void) {
    int x = 1;
    if (g()) {
        printf("dinamico\n");
    }
    else {
        printf("estatico\n");
    }
    return 0;
}
