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

void recibir_enter(char mensaje_entrada[]) {
    int entrada;

    do {
        printf("%s", mensaje_entrada);
        entrada = getchar();
    } while(entrada != '\n' && entrada != EOF );
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

        system("cls");

        printf("%s", mensaje_error);
        recibir_enter("\nPresione Enter para continuar... ");

        system("cls");
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

        system("cls");

        printf("%s", mensaje_error);
        recibir_enter("\nPresione Enter para continuar");

        system("cls");   
    }
}

int random_num(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void imprimir_ruletas(char primer[], char segundo[], char tercer[]) {
    printf("\n");
    printf("                -------------\n");
    printf("                | %s | %s | %s |\n", primer, segundo, tercer);
    printf("                -------------\n");
}

int obtener_ruta_del_archivo(char ruta_del_archivo[100], int ano, int mes, int dia) {
    /*
        Retorna 0 si hubo un error al encontrar el archivo. 1 si se ha encontrado con exito.
    */
    char directorio[100];

    char nombre_archivo[15];

    if (getcwd(directorio, sizeof(directorio)) == NULL) {
        printf("\nError obteniendo directorio de trabajo.\n\n");
        return 0;
    }

    snprintf(nombre_archivo, 15, "%d_%d_%d.txt", ano, mes, dia);
    snprintf(ruta_del_archivo, 100, "%s\\%s", directorio, nombre_archivo);
}

void guardar(int jugadas, double dinero_ingresado, double dinero_retirado) {
    FILE *archivo;
    char path_del_archivo[100];

    time_t raw_time = time(0);
    struct tm hora_fecha = *localtime(&raw_time);
    char time_de_la_jugada[20];
    
    snprintf(time_de_la_jugada, 20, "%d-%d-%d %d:%d", hora_fecha.tm_mday, hora_fecha.tm_mon + 1, hora_fecha.tm_year + 1900, hora_fecha.tm_hour, hora_fecha.tm_min);

    int exito = obtener_ruta_del_archivo(path_del_archivo, hora_fecha.tm_year + 1900, hora_fecha.tm_mon + 1, hora_fecha.tm_mday);

    if (exito == 0) {
        return;
    }

    archivo = fopen(path_del_archivo, "a");

    fprintf(archivo, "---------------------------------------------------------------------------------------------\n");
    fprintf(archivo, "|  JUGADAS   |      DINERO INGRESADO     |       DINERO RETIRADO     |      HORA Y FECHA     |\n");
    fprintf(archivo, "----------------------------------------------------------------------------------------------\n");
    fprintf(archivo, "    %d                %.2f                       %.2f                  %s     \n", jugadas, dinero_ingresado, dinero_retirado, time_de_la_jugada);
    fprintf(archivo, "______________________________________________________________________________________________\n");
    fprintf(archivo, "\n");

    fclose(archivo);
}

void leer_jugadas() {
    FILE *archivo;

    int index, dia, mes, ano;
    char ruta_del_archivo[100];

    for (index = 0; index <= 2; index++) {
        system("cls");

        if (index == 0) dia = recibir_int("De que fecha desea saber obtener la data?\n\nDia -> ", "Por favor introduzca un dia valido (1 - 31)\n", 1, 31);
        if (index == 1) mes = recibir_int("De que fecha desea saber obtener la data?\n\nMes -> ", "Por favor introduzca un mes valido (1 - 12)\n", 1, 12);
        if (index == 2) ano = recibir_int("De que fecha desea saber obtener la data?\n\nAno -> ", "Por favor introduzca un ano valido (2022 - 2022)\n", 2022, 2022);

        printf("\n");
    }
    
    int exito = obtener_ruta_del_archivo(ruta_del_archivo, ano, mes, dia);

    if (exito == 0) {
        return;
    }

    archivo = fopen(ruta_del_archivo, "r");

    // Checkeamos si el archivo existe
    if (archivo == NULL) {
        system("cls");
        printf("\nError! El registro no existe.\n");

        recibir_enter("\nPresione ENTER para continuar... ");
        return;
    }

	char tmp[1024];


    // Leer contenido del archivo.
    while(fgets(tmp, 1024, archivo) != NULL) {
		while(tmp[strlen(tmp) - 1] == '\n' || tmp[strlen(tmp) - 1] == '\r' ) {
			tmp[strlen(tmp) - 1] = '\0';
		}
		
		printf("%s\n", tmp);
	}

    fclose(archivo);
    recibir_enter("\nPresione ENTER para continuar...");
}

int realizar_jugada(double *dinero, double *dinero_que_entra, double *dinero_que_sale) {
    system("cls");

    double dinero_apostado = *dinero / 2;
    *dinero -= dinero_apostado;

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

        *dinero += dinero_apostado * 3;
        *dinero_que_sale += dinero_apostado * 3;

    } else if (
        simbolos[primera_rueda] == simbolos[segunda_rueda] || 
        simbolos[segunda_rueda] == simbolos[tercera_rueda] || 
        simbolos[primera_rueda] == simbolos[tercera_rueda]
    ) {
    // Ganar doble. 
        printf("Ganastes el doble!");

        *dinero += dinero_apostado * 2;
        *dinero_que_sale += dinero_apostado * 2;

    } else {
    // Perder.
        printf("Perdistes :(");
        *dinero_que_entra += dinero_apostado;
    }
}

void imprimir_resultados(double dinero, double dinero_inicial) {
    system("cls");
    if (dinero > dinero_inicial) printf("Has ganado %.2f!\n", dinero - dinero_inicial);
    else if (dinero_inicial == dinero) printf("Quedastes igual...");
    else printf("Perdistes un total de %.2f :(\n", dinero_inicial - dinero);

    recibir_enter("\n\nPresione ENTER para continuar...");
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

    for (jugadas_realizadas = 0; jugadas_realizadas < jugadas;) {
        int opcion_elegida;

        realizar_jugada(&dinero, &dinero_que_entra, &dinero_que_sale);
        jugadas_realizadas++;

        printf("             Dinero actual -> %.2f\n\n", dinero);
        
        if (jugadas_realizadas == jugadas){
            imprimir_resultados(dinero, dinero_inicial);

        } else {
            printf("Jugadas restantes -> %d\n\n", jugadas - jugadas_realizadas);
            opcion_elegida = recibir_int("1- Continuar.\n2- Retirarse.\n\nQue desea hacer? -> ", "Entrada invalida. Por favor ingrese una opcion valida. \n\n", 1, 2);
                            
            if (opcion_elegida == 2) {
                imprimir_resultados(dinero, dinero_inicial);

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

    // Loop principal.
    while(seguir_jugando == 1) {
        int en_el_menu = 1;

        while(en_el_menu == 1) {
            int opcion_elegida;

            system("cls");

            opcion_elegida = recibir_int("+++ TRAGAMONEDAS EL CHIGUIRE +++\n\n1- Jugar!\n2- Leer registros de jugadas.\n3- Salir.\n\nEliga una opcion -> ", "\nOpcion incorrecta, por favor eliga de nuevo.\n", 1, 3);

            switch (opcion_elegida) {
                case 1:
                    jugar();
                    break;

                case 2:
                    leer_jugadas();
                    continue;

                case 3:
                    system("cls");
                    printf("\n Que tenga un buen dia!\n\n");
                    en_el_menu = 0;
                    seguir_jugando = 0;

                default:
                    break;
            }
        }

    }
}
