#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LEN 3000
#define MAX_NONTERMINALS 10
#define MAX_RULES 50

typedef struct {
    int parent;
    int left;
    int right;
} BinaryProduction;

typedef struct {
    int nonTerminal;
    char terminal;
} TerminalProduction;

int table[MAX_LEN][MAX_LEN][MAX_NONTERMINALS];

BinaryProduction binaryRules[MAX_RULES];
int binaryRuleCount = 0;

TerminalProduction terminalRules[MAX_RULES];
int terminalRuleCount = 0;

int numNonTerminals = 0;
char nonTerminalNames[MAX_NONTERMINALS];

int getNonTerminalIndex(char c) {
    for (int i = 0; i < numNonTerminals; ++i) {
        if (nonTerminalNames[i] == c) return i;
    }
    if (numNonTerminals < MAX_NONTERMINALS) {
        nonTerminalNames[numNonTerminals] = c;
        return numNonTerminals++;
    } else {
        printf("Error: Número máximo de no terminales alcanzado.\n");
        exit(1);
    }
}

void addBinaryRule(char parent, char left, char right) {
    if (binaryRuleCount < MAX_RULES) {
        binaryRules[binaryRuleCount++] = (BinaryProduction){
            .parent = getNonTerminalIndex(parent),
            .left = getNonTerminalIndex(left),
            .right = getNonTerminalIndex(right)
        };
    } else {
        printf("Error: Número máximo de reglas binarias alcanzado.\n");
        exit(1);
    }
}

void addTerminalRule(char nonTerminal, char terminal) {
    if (terminalRuleCount < MAX_RULES) {
        terminalRules[terminalRuleCount++] = (TerminalProduction){
            .nonTerminal = getNonTerminalIndex(nonTerminal),
            .terminal = terminal
        };
    } else {
        printf("Error: Número máximo de reglas terminales alcanzado.\n");
        exit(1);
    }
}

int cyk(const char* input) {
    int n = strlen(input);
    memset(table, 0, sizeof(table));

    for (int i = 0; i < n; ++i) {
        for (int r = 0; r < terminalRuleCount; ++r) {
            if (terminalRules[r].terminal == input[i]) {
                table[i][0][terminalRules[r].nonTerminal] = 1;
            }
        }
    }

    for (int l = 2; l <= n; ++l) {
        for (int i = 0; i <= n - l; ++i) {
            for (int k = 1; k < l; ++k) {
                for (int r = 0; r < binaryRuleCount; ++r) {
                    int p = binaryRules[r].parent;
                    int left = binaryRules[r].left;
                    int right = binaryRules[r].right;
                    if (table[i][k-1][left] && table[i+k][l-k-1][right]) {
                        table[i][l-1][p] = 1;
                    }
                }
            }
        }
    }

    int startSymbol = getNonTerminalIndex('S');
    return table[0][n-1][startSymbol];
}

void evaluate(int n, FILE* csvFile) {
    char* input = malloc(2 * n + 1);
    for (int i = 0; i < n; i++) input[i] = '0';  // Llenar con 0's
    for (int i = n; i < 2 * n; i++) input[i] = '1';  // Llenar con 1's
    input[2 * n] = '\0';

    clock_t start = clock();
    int result = cyk(input);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    // Escribir en el archivo CSV
    fprintf(csvFile, "%d,%f\n", 2 * n, time_spent);

    free(input);
}

int main() {
    // Abrir archivo CSV para escritura
    FILE* csvFile = fopen("cyk_times.csv", "w");
    if (csvFile == NULL) {
        printf("Error al abrir el archivo CSV.\n");
        return 1;
    }

    // Escribir encabezado
    fprintf(csvFile, "Longitud de la cadena,Tiempo de ejecución (segundos)\n");

    // Definir la gramática para L = { 0ⁿ1ⁿ | n ≥ 1 }
    addBinaryRule('S', 'A', 'X');
    addBinaryRule('S', 'A', 'B');
    addBinaryRule('X', 'S', 'B');
    addTerminalRule('A', '0');
    addTerminalRule('B', '1');

    // Ejecutar pruebas con diferentes longitudes y guardar los resultados en el archivo CSV
    evaluate(50, csvFile);
    evaluate(100, csvFile);
    evaluate(300, csvFile);
    evaluate(700, csvFile);
    evaluate(900, csvFile);
    evaluate(1100, csvFile);
    evaluate(1500, csvFile);

    // Cerrar el archivo CSV
    fclose(csvFile);

    printf("Los tiempos de ejecución se han guardado en 'cyk_times.csv'.\n");

    return 0;
}
