### 🧠 Análisis Sintáctico con Bison y Flex + Gráfica de Rendimiento
Este proyecto implementa un analizador sintáctico utilizando Bison y Flex para reconocer cadenas del lenguaje L = { 0ⁿ1ⁿ | n ≥ 1 } y medir el tiempo de análisis por cada cadena ingresada. Luego, se generan gráficos para visualizar cómo varía el tiempo de análisis según la longitud de la cadena.

### 📁 Contenido del Proyecto

-├── parser.y               # Archivo Bison con reglas gramaticales y lógica de temporización
-├── lexer.l                # Archivo Flex para el análisis léxico
-├── datos.csv              # Archivo generado con los tiempos de análisis
-├── graficar_bison.py      # Script de Python para graficar los tiempos
-├── README.md              # Este archivo

### 📜 Gramática Reconocida
El analizador está diseñado para aceptar cadenas del lenguaje:

```
L = { 0ⁿ1ⁿ | n ≥ 1 }
```
Utiliza una gramática en BNF (extendida para Bison):

```
S → A X
S → A B
X → S B
A → '0'
B → '1'
```
### ⚙️ Cómo Compilar y Ejecutar
### ✅ Requisitos
-flex y bison instalados en tu sistema
-gcc u otro compilador de C
-Python 3.x con matplotlib y pandas instalados

🔧 Compilar
```
bison -d parser.y
flex lexer.l
gcc -o analizador parser.tab.c lex.yy.c -lfl
```
### 🚀 Ejecutar
```
./analizador
```
Ingresa cadenas por línea (ej. 000111) y presiona Enter. Para finalizar, presiona Ctrl+D.

### 🧪 Ejemplo de uso
```
Ingresa una cadena por línea (Ctrl+D para salir):
111000
Cadena válida.
Tiempo de análisis: 0.000002 segundos

10
Cadena válida.
Tiempo de análisis: 0.000001 segundos

000111000111
Cadena inválida.
```
Cada análisis registra la longitud y el tiempo en datos.csv.

### 📊 Gráfica del Rendimiento
El script graficar_bison.py genera una gráfica lineal con los datos almacenados en datos.csv para mostrar cómo varía el tiempo de análisis con la longitud de la cadena.

### ▶️ Ejecutar el script de Python
```
python3 graficar_bison.py
```
Esto generará y mostrará una gráfica, además de guardar la imagen como grafica_lineal_bison.png.

### 🖼️ Resultado Esperado
Una gráfica con puntos conectados que muestra el tiempo de análisis en función de la longitud de la cadena.

Se espera un comportamiento lineal (o casi lineal) en comparación con algoritmos cúbicos como CYK.

### 📌 Notas
El archivo datos.csv se sobrescribe al iniciar una nueva ejecución.

Se puede modificar fácilmente el código para automatizar pruebas generando cadenas automáticamente.

