#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>

#define MAX_NUM 1000000
#define	MAX_NUM_LEN 8
#define MAX_JUGADAS 10
#define GIROS_A_LA_RULETA 10
#define CANTIDAD_SIMBOLOS 7
#define SLOTS 3
#define LINEAS_ARCHIVO 3
#define MAX_CHAR_LEN 256

enum tipos {
    DIGITO = 1,
    ENTERO = 2,
    COMA_FLOTANTE = 3,
    STRING = 4,
    ALFA = 5,
};

char archivos_lineas[LINEAS_ARCHIVO][40] = {"TOTAL DE JUGADAS: ", "TOTAL DE DINERO INGRESADO: ", "TOTAL DE DINERO RETIRADO: "};


int validar(char buffer[], int limite, enum tipos tipo) {
    int buffer_length = strlen(buffer);

    // Validación para tanto numeros enteros como decimales.

    if (tipo == COMA_FLOTANTE || tipo == ENTERO) {
        if (
            buffer_length > MAX_NUM_LEN || 
            buffer_length <= 0
        ) {
            return 0;
        }
    }

    if (tipo == COMA_FLOTANTE) {
        char *endptr;
        double transformation = strtod(buffer, &endptr);

        if (
            endptr == buffer || 
            transformation <= 0 || 
            transformation > MAX_NUM
        ) {
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

int recibir_input(char buffer[], int longitud) {
    fgets(buffer, longitud, stdin);
	fflush(stdin);

    int buffer_length = strlen(buffer);

    if (buffer[buffer_length - 1] == '\n' || buffer[buffer_length - 1] == 0x20) {
		buffer[--buffer_length] = '\0';
	}

    return buffer_length;
}

int recibir_int(char mensaje_entrada[], char mensaje_error[], int min, int max) {
    char buffer[MAX_NUM_LEN];
    int es_valido = 0;

    while(es_valido == 0) {
        printf("%s", mensaje_entrada);
        recibir_input(buffer, MAX_NUM_LEN);

        if (validar(buffer, 1, ENTERO) == 1) {
            int numero = atoi(buffer);

            if (min <= numero && numero <= max) {
                es_valido = 1;
                return numero;
            }
        }

        printf("%s", mensaje_error);
    }
}

double recibir_double(char mensaje_entrada[], char mensaje_error[]) {
    char buffer[MAX_NUM_LEN];
    int es_valido = 0;
    char *endptr;

    while(es_valido == 0) {
        printf("%s", mensaje_entrada);
        int buffer_length = recibir_input(buffer, MAX_NUM_LEN);

        if (validar(buffer, MAX_NUM_LEN, COMA_FLOTANTE) == 1) {
            es_valido = 1;
            return strtod(buffer, &endptr);
        }

        printf("%s", mensaje_error);
    }
}

int random_num(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void imprimir_ruletas(char primer[], char segundo[], char tercer[]) {
    printf("| %s | %s | %s |", primer, segundo, tercer);
}

// void reescribir_linea(FILE *file, char path[], int linea, double valor_a_sumar) {
//     int index = 0;
//     double valor_a_actualizar;
//     char buffer[MAX_CHAR_LEN];
//     char primera_linea[MAX_CHAR_LEN];
//     char segunda_linea[MAX_CHAR_LEN];
//     char tercera_linea[MAX_CHAR_LEN];

//     while (fgets(buffer, MAX_CHAR_LEN, file)) {
//         printf("%s", buffer);

//         if (index == 0) strcat(primera_linea, buffer);
//         if (index == 1) strcat(segunda_linea, buffer);
//         if (index == 2) strcat(tercera_linea, buffer);


//         if (linea == index) {
//             char *endpointer;

//             char numero_extraido[MAX_NUM_LEN];

//             int idx;
//             for (idx = 0; idx < strlen(buffer); idx++) {
//                 if (isdigit(buffer[idx]) || buffer[idx] == '.') {
//                     strcat(numero_extraido, &buffer[idx]);
//                 }
//             }

//             valor_a_actualizar = atof(numero_extraido);
//             valor_a_actualizar += valor_a_sumar;
//         }

//         index += 1;
//     }

//     fclose(file);

//     file = fopen(path, "w");

//     char valor_en_string[MAX_NUM_LEN];

//     snprintf(valor_en_string, MAX_NUM_LEN, "%f", valor_a_actualizar);

//     for (index = 0; index < LINEAS_ARCHIVO; index++) {
//         char temp_string[40];
//         char valor_en_string[MAX_NUM_LEN];

//         if (index == linea) {
//             strcpy(temp_string, archivos_lineas[index]);
//             strcat(temp_string, valor_en_string);
//             fprintf(file, "%s\n", temp_string);

//         } else {
//             if (index == 0) fprintf(file, "%s\n", primera_linea);
//             if (index == 1) fprintf(file, "%s\n", segunda_linea);
//             if (index == 2) fprintf(file, "%s\n", tercera_linea);
//         }
//     }
// }

void imprimir_jugada() {

}

void guardar(int jugadas, double dinero_ingresado, double dinero_retirado) {
    FILE *file;
    char directorio[100];

    if (getcwd(directorio, sizeof(directorio)) == NULL) {
        printf("\nError obteniendo directorio de trabajo.\n");
        return;
    }

    time_t raw_time = time(0);
    struct tm hora_fecha = *localtime(&raw_time);
    
    char nombre_archivo[15];
    char nombre_y_path[100];
    char time_de_la_jugada[20];

    snprintf(nombre_archivo, 15, "%d_%02d_%02d.txt", hora_fecha.tm_year + 1900, hora_fecha.tm_mon + 1, hora_fecha.tm_mday);
    snprintf(nombre_y_path, 100, "%s\\%s", directorio, nombre_archivo);
    snprintf(time_de_la_jugada, 20, "%d-%d-%d %d:%d", hora_fecha.tm_mday, hora_fecha.tm_mon + 1, hora_fecha.tm_year + 1900, hora_fecha.tm_hour, hora_fecha.tm_min);

    file = fopen(nombre_y_path, "a");

    fprintf(file, "---------------------------------------------------------------\n");
    fprintf(file, "| JUGADAS | DINERO INGRESADO | DINERO RETIRADO | HORA Y FECHA |\n");
    fprintf(file, "|---------|------------------|-----------------|--------------|\n");
    fprintf(file, "|  %d            %.2f                %.2f                %s       |\n", jugadas, dinero_ingresado, dinero_retirado, time_de_la_jugada);
    fprintf(file, "|_________|__________________|_________________|______________|\n");
    fprintf(file, "\n");

    fclose(file);

    // if (file == NULL) {
    //     fclose(file);
    //     file = fopen(nombre_y_path, "w");
    
    //     int indice;
    //     fprintf(file, "MAYBEEEEEE");

        // for (indice = 0; indice < LINEAS_ARCHIVO; indice++) {
        //     fprintf(file, "%s\n 0", archivos_lineas[indice]);
        //     fprintf(file, "%s\n 0", archivos_lineas[indice]);
        //     fprintf(file, "%s\n 0", archivos_lineas[indice]);
        // }

    //     fclose(file);
    // }

    // Guardar y reescribir datos.
    // reescribir_linea(file, nombre_y_path, 0, jugadas);
    // reescribir_linea(file, nombre_y_path, 1, dinero_ingresado);
    // reescribir_linea(file, nombre_y_path, 2, dinero_retirado);

    Sleep(2000);
}

int realizar_jugada(double *dinero, double *dinero_que_entra, double *dinero_que_sale) {
    system("cls");

    int primera_rueda;
    int segunda_rueda;
    int tercera_rueda;

    char *simbolos[CANTIDAD_SIMBOLOS] = {"L", "R", "T", "U", "V", "B", "Z"};

    int i;

    for (i = 0; i < GIROS_A_LA_RULETA; i++) {

        primera_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);
        segunda_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);
        tercera_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);

        imprimir_ruletas(simbolos[primera_rueda], simbolos[segunda_rueda], simbolos[tercera_rueda]);

        Sleep(300);
        system("cls");
    }

    // Giro decisivo.

    primera_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);
    segunda_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);
    tercera_rueda = random_num(0, CANTIDAD_SIMBOLOS - 1);

    imprimir_ruletas(simbolos[primera_rueda], simbolos[segunda_rueda], simbolos[tercera_rueda]);

    printf("\n\n");

    if (simbolos[primera_rueda] == simbolos[segunda_rueda] && simbolos[segunda_rueda] == simbolos[tercera_rueda]) {
    // Ganar triple.
        printf("Ganastes el triple!");

        *dinero = *dinero * 3;
        *dinero_que_sale += *dinero * 3;

    } else if (
        simbolos[primera_rueda] == simbolos[segunda_rueda] || 
        simbolos[segunda_rueda] == simbolos[tercera_rueda] || 
        simbolos[primera_rueda] == simbolos[tercera_rueda]
    ) {
    // Ganar doble. 
        printf("Ganastes el doble!");
        *dinero = *dinero * 2;

        *dinero_que_sale += *dinero * 2;

    } else {
    // Perder.
        printf("Perdistes :(");
        *dinero = *dinero / 2;
        *dinero_que_entra += *dinero / 2;
    }

    printf("\n\n");
}

void jugar() {
    system("cls");

    double dinero_que_entra;
    double dinero_que_sale;

    // Sembrar semilla para generador de números aleatorios.
    srand(time(NULL));

    double dinero = recibir_double("Con cuanto dinero dispone? (Maximo 1 millon) -> ", "Monto invalido. Por favor ingrese de nuevo.\n\n"); 
    double dinero_inicial = dinero;

    system("cls");
    int jugadas = recibir_int(
                            "Por favor ingrese el numero de jugadas que desea hacer. (MAX 10) -> ", 
                            "Entrada invalida. Por favor ingrese un numero entre 1 y 10. \n\n", 
                            1, 
                            MAX_JUGADAS
                        );

    int jugadas_realizadas; 

    for (jugadas_realizadas = 0; jugadas_realizadas < jugadas; jugadas_realizadas++) {
        int opcion_elegida;

        realizar_jugada(&dinero, &dinero_que_entra, &dinero_que_sale);

        printf("Dinero actual -> %.2f\n\n", dinero);
        
        if (jugadas_realizadas == jugadas - 1){
            Sleep(2000);

            system("cls");
            if (dinero > dinero_inicial) printf("Has ganado %.2f!\n", dinero - dinero_inicial);
            else if (dinero_inicial == dinero) printf("Quedastes igual...");
            else printf("Perdistes un total de %f :(\n", dinero_inicial - dinero);

            Sleep(3000);

        } else {
            printf("1- Continuar.\n");
            printf("2- Retirarse.\n\n");

            opcion_elegida = recibir_int(
                            "Que desea hacer? -> ", 
                            "Entrada invalida. Por favor ingrese una opcion valida. \n\n", 
                            1,
                            2
                        );
                            
            if (opcion_elegida == 2) {
                break;
            }
        }
    }

    guardar(jugadas_realizadas, dinero_que_entra, dinero_que_sale);
}

int main(void) {
    system("cls");
    int seguir_jugando = 1;
    int numero_de_caras = 6;

    printf("¡Bienvenido/a Al Tragamonedas!\n\n");

    // Loop principal.
    while(seguir_jugando == 1) {
        int en_el_menu = 1;

        while(en_el_menu == 1) {
            int opcion_elegida;

            system("cls");
            printf("✧✧ MENU ✧✧\n\n");

            printf("1- ¡Jugar!\n");
            printf("2- Leer registros de jugadas.\n");
            printf("3- Salir.\n\n");

            opcion_elegida = recibir_int("Eliga una opcion -> ", "\nOpcion incorrecta, por favor eliga de nuevo.\n", 1, 3);

            switch (opcion_elegida) {
                case 1:
                    jugar();
                    break;

                case 2:
                    continue;

                case 3:
                    system("cls");
                    printf("\n Que tenga buen dia!\n\n");
                    en_el_menu = 0;
                    seguir_jugando = 0;

                default:
                    break;
            }
        }

    }
}