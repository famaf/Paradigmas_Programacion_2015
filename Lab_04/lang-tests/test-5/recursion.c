#include <stdio.h>

// C no tiene optimizacion de llamada a la cola, pero si le pasamos el flag
// -O2 (quedaria asi a la hora de compilar gcc -O2 -o NAME_EXECUTABLE FILE.c)
// Hace que el compilador de C haga la optimizacion de la llamada a la cola
// Con el siguiente programa, sin ese flag, llega un punto en el que el stack "explota"
// por lo que tira un seg fault, en cambio si colocamos ese flag al compilar
// no tirara ningun error.

int g(int x) {
    if (x == 0) {
        return 0;
    }
    else {
        return g(x - 1);
    }
}

int main() {
    g(100000000000000);

    return 0;
}
