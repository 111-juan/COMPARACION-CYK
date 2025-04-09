
### 📁 Estructura del proyecto

- ├── cyk.c               # Código fuente en C con el algoritmo CYK
- ├── cyk_times.csv       # Archivo generado con los tiempos de ejecución
- ├── graficar_cyk.py     # Script de Python para graficar los tiempos
### 🧠 Descripción del Algoritmo
El algoritmo CYK es un algoritmo de análisis sintáctico para gramáticas libres de contexto en CNF. Este algoritmo tiene una complejidad temporal de O(n³), donde n es la longitud de la cadena.

Gramática utilizada
La gramática en CNF utilizada para el lenguaje L = { 0ⁿ1ⁿ } es:
```bash
S → A X | A B  
X → S B  
A → '0'  
B → '1'
```

### 🛠️ Compilación y Ejecución
Requisitos
-Un compilador de C (por ejemplo, gcc)
-Python 3.x
-Biblioteca matplotlib para Python

### Compilar y ejecutar el programa en C
```
gcc -o cyk cyk.c
./cyk
```
Esto generará el archivo cyk_times.csv con los resultados de tiempo de ejecución para diferentes longitudes de cadena.

Ejecutar el script de Python para graficar
```
python3 graficar_cyk.py
```
Se mostrará una gráfica con los puntos medidos y una curva de ajuste cúbico.

### 📊 Resultado Esperado
La gráfica muestra cómo el tiempo de ejecución del algoritmo CYK crece de manera cúbica respecto a la longitud de la cadena, lo que confirma su complejidad teórica de O(n³).

### 🧪 Pruebas Realizadas
El programa evalúa cadenas de las siguientes longitudes:

-100 (50 '0's y 50 '1's)

-200

-600

-1400

-1800

-2200

-3000

(Se pueden ajustar fácilmente dentro del código fuente cyk.c.)

### 📌 Notas
El archivo CSV se sobrescribirá cada vez que se ejecute el programa C.

La memoria máxima permitida para la tabla CYK depende de MAX_LEN. Aumentar este valor permite trabajar con cadenas más largas, pero puede requerir más memoria RAM.


