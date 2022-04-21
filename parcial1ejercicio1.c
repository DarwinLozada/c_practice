#include <stdio.h>

int main (void) {

    int dinero_en_la_cuenta = 520;
    int maximo_intentos = 3;

    int intentos = 0;

    // La clave por defecto es 1234.
    int clave_usuario = 1234;
    int clave_ingresada;

    printf("\nBienvenido al Sistema del Banco USM! \n\n");

    while (intentos <= maximo_intentos) {
        printf("Por favor ingrese su clave numerica: ");
        scanf("%d", &clave_ingresada);
        printf("\n");

        if (clave_usuario != clave_ingresada) {
            printf("Clave Incorrecta :( \n");
            intentos += 1;
        }

        if (clave_usuario == clave_ingresada) {
            break;
        }
    };

    if (clave_usuario == clave_ingresada) {

        printf("-------------------------------------------------");
        printf("\nBienvenido Usuario!\n");

        int seguir_en_el_sistema = 1;
        int opcion_elegida;

        while (seguir_en_el_sistema == 1) {
            
            printf("-------------------------------------------------\n");
            printf("Por favor elija la operacion que desea realizar: \n\n");

            printf("1- Consulta de saldo\n");
            printf("2- Retiro de dinero\n");
            printf("3- Deposito de dinero\n");
            printf("4- Cambiar clave\n");
            printf("5- Salir del sistema\n\n");

            scanf("%d", &opcion_elegida);
            printf("\n");

            if (opcion_elegida == 1) {
                printf("-> Este es su saldo actual: %d Bs\n\n", dinero_en_la_cuenta);
            }

            else if (opcion_elegida == 2) {
                int monto_a_retirar;

                printf("Que monto desea retirar?: ");
                scanf("%d", &monto_a_retirar);
                printf("\n");

                if (monto_a_retirar > dinero_en_la_cuenta) {
                    printf("-> Disculpe, ese valor supera el monto que posee en su cuenta \n\n");

                } else {
                    dinero_en_la_cuenta -= monto_a_retirar;
                    printf("-> Dinero retirado con exito. Saldo actual: %d Bs\n\n", dinero_en_la_cuenta);
                }
            }

            else if (opcion_elegida == 3) {
                int monto_a_depositar;

                printf("Que monto desea depositar?: ");
                scanf("%d", &monto_a_depositar);
                printf("\n");

                if (monto_a_depositar < 0) {
                    printf("-> No puede depositar una cantidad negativa\n\n");
                } else {
                    dinero_en_la_cuenta += monto_a_depositar;
                    printf("-> Dinero ingresado en su cuenta con exito! Saldo actual: %d Bs\n\n", dinero_en_la_cuenta);
                }
            }

            else if (opcion_elegida == 4) {

                int seguir_intentando = 1;
                int nueva_clave;

                while (seguir_intentando == 1) {
                    printf("Por favor ingrese su nueve clave. Debe ser de 4 digitos: ");
                    scanf("%d", &nueva_clave);
                    printf("\n");

                    if (1000 <= nueva_clave && nueva_clave <= 9999) {
                        clave_usuario = nueva_clave;
                        printf("Clave cambiada con exito!\n\n");
                        seguir_intentando = 0;

                    } else {
                        printf("Clave invalida...\n\n");
                    }
                }
            }

            else if (opcion_elegida == 5) {
                printf("Muchas gracias, que tenga un lindo dia :) \n");
                seguir_en_el_sistema = 0;
            }

            else {
                printf("-> Opcion Invalida, por favor ingresa una de las opciones listadas");
            }
        }
    }

    if (intentos > maximo_intentos) {
        printf("Ha superado el maximo numero de intentos, por favor intente mas tarde...\n");
    }

    return 0;
}