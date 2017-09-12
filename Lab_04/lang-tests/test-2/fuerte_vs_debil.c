#include <stdio.h>

float g(float m) {
    return m + 1.5;
}

int main(void) {
    int a = 2.3;
    float c = 2.3;
    char b = 'm';

    c = a + b + c;

    printf("%f\n", g(a));
    printf("%f\n", c);

    return 0;
}
