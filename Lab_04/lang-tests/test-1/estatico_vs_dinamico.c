#include <stdio.h>

int main () {
    printf("Entre\n");

    int var = 10;

    char var2[10] = "Hola Mundo";

    var = var + var2;

    printf("Afuera\n");

    return 0;
}

// Si tira un error de compilacion es porque NO es de Tipado Dinamico 
