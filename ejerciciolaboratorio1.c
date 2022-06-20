#include <stdio.h>

int multiplicar(int num1, int num2) {
    return num1 * num2;
}

void presentacion() {
    printf("Hola buenas tardes!");
}

void imprimir_mensaje(char mensaje[]) {
    int max_chars_por_mensaje = 200;
    int max_chars_por_linea = 40;

    int espaciado = 2;
    char character[] = "*";

    // Imprimir borde superior
    int tamano_horizontal_mensaje;
    int i;

    for (i = 0; i < max_chars_por_linea + espaciado; i++) {
        printf("%s", character);
    }
    
    printf("\n");

    // Imprimir mensaje
    
    int j;

    for (j = 0; j < max_chars_por_linea; j++) {
        if (j == 0){
            printf("%s ", character);
        }

        else if (j == max_chars_por_linea - 1) {
        	printf(" %s", character);
        }

        else {
            printf(" ");
        }
    }
    
    
}


int main(void) {
    imprimir_mensaje("Holaaaaaaaaaaaaa");

    return 0;
}
