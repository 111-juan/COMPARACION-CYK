%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void yyerror(const char *s);
int yylex();

clock_t start_time, end_time;

// Para almacenar la cadena actual
char current_input[1024];
int input_length = 0;

void guardar_dato_csv(int longitud, double tiempo) {
    FILE *f = fopen("datos.csv", "a");
    if (f == NULL) {
        perror("No se pudo abrir datos.csv");
        return;
    }
    fprintf(f, "%d,%.6f\n", longitud, tiempo);
    fclose(f);
}
%}

%token A B NEWLINE

%%

input:
      /* vacío */
    | input linea
    ;

linea:
    S NEWLINE { 
        end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Cadena válida.\n"); 
        printf("Tiempo de análisis: %.6f segundos\n\n", time_taken);
        guardar_dato_csv(input_length, time_taken);
        input_length = 0; // reiniciar
    }
  | NEWLINE { 
        end_time = clock();
        double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
        printf("Cadena vacía.\n"); 
        printf("Tiempo de análisis: %.6f segundos\n\n", time_taken);
        guardar_dato_csv(0, time_taken);
        input_length = 0;
    }
  ;

S:
    A { start_time = clock(); } X
  | A { start_time = clock(); } B
  ;

X:
    S B
  ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    // Limpiar archivo al comenzar
    FILE *f = fopen("datos.csv", "w");
    if (f) {
        fprintf(f, "Longitud,Tiempo\n");
        fclose(f);
    }

    printf("Ingresa una cadena por línea (Ctrl+D para salir):\n");
    yyparse();
    return 0;
}
