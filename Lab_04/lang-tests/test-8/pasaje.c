#include <stdio.h>

// C por defecto tiene pasaje por valor, el pasaje por referencia
// se consigue pasando explicitamente las dirrecciones de memoria
// de dichos parametros.

// VAMOS A HACER UN PROGRAMA QUE DE OPCION DE ELEGIR EL PASAJE DE PARAMETRO A USAR


void interchange_reference(int *x1, int *y1) {
    int z1;

    z1 = *x1;
    *x1 = *y1;
    *y1 = z1;
}


void interchange_value(int x1, int y1) {
    int z1;

    z1 = x1;
    x1 = y1;
    y1 = z1;
}


int main() {
    int x = 50, y = 70;

    int change;

    printf("\nIngrese '0' si quiere Pasaje por Valor\nIngrese '1' si quiere Pasaje por Referencia\nIngrese la opcion: ");
    scanf("%d", &change);

    printf("\nANTES DE interchange: x = %d, y = %d\n", x, y);

    if (change == 0) {
        interchange_value(x, y);
    }
    else if (change == 1) {
        interchange_reference(&x, &y);
    }

    printf("\nDESPUES DE interchange: x = %d, y = %d\n\n", x, y);

    return 0;
}
