#include <stdio.h>
#include <string.h>

int multiplicar(int num1, int num2) {
    return num1 * num2;
}

void presentacion() {
    printf("Hola buenas tardes!");
}

void imprimir_mensaje(char mensaje[]) {
    int max_chars_por_linea = 20;
    int min_chars_por_linea = 4;
    int espaciado = 2;
    char character[] = "*";

    int lineas = strlen(mensaje) / max_chars_por_linea;
    int caracteres_restantes = strlen(mensaje);

    // Imprimir borde superior
    int tamano_horizontal_mensaje;
    int i;

    for (i = 0; i <= caracteres_restantes + min_chars_por_linea || i <= max_chars_por_linea; i++) {
        printf("%s", character);
    }

    tamano_horizontal_mensaje = i;

    // Imprimir mensaje

    for (int j = 0; j < espaciado + tamano_mensaje; j++) {
        if (j == 0){
            printf("*");
        }

        else if (j < espaciado) {
            printf(" ");
        }

        else {
            print();
        }
    }
    
    
}


int main(void) {
    imprimir_mensaje("Holaaaaaaaaaaaaa");

    return 0;
}