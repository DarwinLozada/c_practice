#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>

#define	MAX_NUM_LEN 8
#define MAX_JUGADAS 10
#define GIROS_A_LA_RULETA 8
#define CANTIDAD_SIMBOLOS 7
#define SLOTS 3

enum tipos {
    DIGITO = 1,
    ENTERO = 2,
    DOUBLE = 3,
    STRING = 4,
    ALFA = 5,
};

int validar(char buffer[], int limite, enum tipos tipo) {

    if (tipo == DOUBLE) {
        char *endptr;
        double transformation = strtod(buffer, &endptr);

        if (endptr == buffer) {
            return 0;
        }

        if ((*endptr == '\0') || (isspace(*endptr) != 0)) return 1;

        return 0;
    };

	int index = 0;

    if (tipo == ENTERO) {
        if (atoi(buffer) == 0) return 0;
        return 1;
    }
	
	while(index <= limite - 1) {
		char caracter = buffer[index];

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

char recibir_input(char buffer[], int longitud) {
    fgets(buffer, longitud, stdin);
	fflush(stdin);
}

int recibir_int(char mensaje_entrada[], char mensaje_error[], int min, int max) {
    char buffer[MAX_NUM_LEN];
    int es_valido = 0;

    while(es_valido == 0) {
        printf("%s", mensaje_entrada);
        recibir_input(buffer, MAX_NUM_LEN);

        if (validar(buffer, 1, ENTERO) == 1 && min <= buffer && buffer <= max) {
            es_valido = 1;
            return atoi(buffer);
        }

        printf("%s", mensaje_error);
    }
}

int random_num(int min, int max) {
    srand(time(NULL)); 
    return (rand() % (max - min + 1)) + min;
}

double recibir_double(char mensaje_entrada[], char mensaje_error[]) {
    char buffer[MAX_NUM_LEN];
    int es_valido = 0;

    while(es_valido == 0) {
        printf("%s", mensaje_entrada);
        recibir_input(buffer, MAX_NUM_LEN);

        if (validar(buffer, MAX_NUM_LEN, DOUBLE) == 1) {
            es_valido = 1;
            char *endptr;
            return strtod(buffer, &endptr);
        }

        printf("%s", mensaje_error);
    }
}

int dar_a_la_ruleta(int buffer[SLOTS]) {
    sleep(1);

    int simbolos[CANTIDAD_SIMBOLOS] = {"😈", "🙃", "😙", "🤩", "👽", "👩‍❤️‍👩", "😷"};

    int i;

    for (i = 0; i < GIROS_A_LA_RULETA; i++) {

        int primera_rueda = random_num(0, CANTIDAD_SIMBOLOS);
        int segunda_rueda = random_num(0, CANTIDAD_SIMBOLOS);
        int tercera_rueda = random_num(0, CANTIDAD_SIMBOLOS);

        

    }
}

void darle_ruleta() {
    system("cls");
}

void jugar() {
    system("cls");
    int jugadas = recibir_int(
                            "Por favor ingrese el número de jugadas que desea hacer. -> ", 
                            "Entrada inválida. Por favor ingrese un número entero.", 
                            1, 
                            MAX_JUGADAS
                        );
    
    int index; 

    for (index = 0; index < jugadas - 1; index++) {
        
    }
}

int main(void) {
    double dinero_inicial = 0;
    int seguir_jugando = 1;
    int numero_de_caras = 6;

    printf("¡Bienvenido Al Tragamonedas!\n\n");

    // Loop principal.
    while(seguir_jugando == 1) {
        dinero_inicial = recibir_double("¿Con cuánto dinero dispone? ", "Digito inválido. Por favor ingrese de nuevo.\n\n");

        int en_el_menu = 1;

        while(en_el_menu == 1) {
            int opcion_elegida;

            system("cls");
            printf("✧✧ MENÚ ✧✧\n\n");

            printf("1- ¡Jugar!");
            printf("2- Leer registros de jugadas.");
            printf("3- Salir.");

            opcion_elegida = recibir_int("¿Qué desea hacer? -> ", "\n\nOpción incorrecta, por favor eliga de nuevo.", 1, 3);

            switch (opcion_elegida) {
                case 1:

                    break;
                case 2:

                case 3:
                    printf("\n ¡Que tenga buen día!");
                default:
                    break;
            }
        }

    }
}