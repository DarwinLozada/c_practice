#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

#define	MAX_NUM_LEN 20

enum tipos {
    DIGITO = 1,
    DOUBLE = 2,
    STRING = 3,
    ALFA = 4,
};

int validar(char variable[], int limite, enum tipos tipo) {

    if (tipo == DOUBLE) {
        char *endptr;
        double transformation = strtod(variable, &endptr);

        if (endptr == variable) {
            return 0;
        }

        if ((*endptr == '\0') || (isspace(*endptr) != 0)) return 1;

        return 0;
    };

	int index = 0;
	
	while(index <= limite - 1) {
		char caracter = variable[index];

		switch(tipo) {
			case DIGITO: 
				if (!isdigit(caracter)) return 0;
				break;
			case STRING:
				if (!isascii(caracter)) return 0;
				break;
			case ALFA:
				if (!isalpha(caracter)) return 0;
				break;
			default:
				return 0;
		}
		index++;
	}
	return 1;
}

void recibir_input(char variable[], int longitud) {
    fgets(variable, longitud, stdin);
	fflush(stdin);
}


int main(void) {
    int dinero = 0;
    int seguir_jugando = 1;
    int numero_de_caras = 6;

    printf("Bienvenido Al Tragamonedas!\n\n");


    // Loop principal.
    while(seguir_jugando == 1) {
        printf("Con cuanto dinero dispone?");
        recibir_input(dinero, 8);
        printf("%s\n", dinero);

        if (validar(dinero, MAX_NUM_LEN, DOUBLE) != 1) {
            printf("Digito invalido. Por favor ingrese de nuevo.");
        }

    }

}