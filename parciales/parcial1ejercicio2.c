#include <stdio.h>

int main (void) {
    int num1;
    int num2;

    int variable_auxiliar;

    int seguir_en_el_sistema = 1;

    int opcion_del_usuario;

    printf("\nBienvenido usuario!\n\n");

    while (seguir_en_el_sistema == 1) {
        printf("Por favor ingrese el valor de la PRIMERA variable (num1) : ");
        scanf("%d", &num1);
        
        printf("\n");

        printf("Por favor ingrese el valor de la SEGUNDA variable (num2) : ");
        scanf("%d", &num2);

        printf("\nPermutando..!\n\n");

        variable_auxiliar = num1;
        num1 = num2;
        num2 = variable_auxiliar;

        if (num1 == num2) {
            printf("Las dos variables tienen el mismo valor... Eso no tiene mucho sentido...\n\n");

        } else {
            printf("Ahora el valor de la PRIMERA variable (num1) es: %d\n", num1);

            printf("Y el valor de la SEGUNDA variable (num2) es: %d\n\n ", num2);
        }

        printf("Desea volver a intentarlo?: \n");

        printf("1- Si quiero!\n");
        printf("2- No, ya me canse\n\n");

        scanf("%d", &opcion_del_usuario);
        printf("\n");

        if (opcion_del_usuario == 2) {
            printf("Bye, que tenga un buen dia");
            seguir_en_el_sistema = 0;
        }

    }

    return 0;
}