import matplotlib.pyplot as plt
import numpy as np
import csv

# Leer los datos del archivo CSV
longitudes = []
tiempos = []

with open('cyk_times.csv', 'r') as csvfile:
    csvreader = csv.reader(csvfile)
    next(csvreader)  # Saltar encabezado
    for row in csvreader:
        longitudes.append(int(row[0]))  # Longitud de la cadena
        tiempos.append(float(row[1]))   # Tiempo de ejecución

# Convertir listas a arrays de numpy para facilidad de cálculo
longitudes = np.array(longitudes)
tiempos = np.array(tiempos)

# Ajustar los datos a una curva cúbica
# Para una curva cúbica, ajustamos los datos a la forma: tiempo = a * (longitud^3) + b
coeffs = np.polyfit(longitudes**3, tiempos, 1)  # Ajuste cúbico

# Generar valores ajustados para la curva cúbica
ajuste_cubico = np.polyval(coeffs, longitudes**3)

# Graficar los resultados
plt.figure(figsize=(10, 6))
plt.plot(longitudes, tiempos, 'bo', label='Datos reales', markersize=8)
plt.plot(longitudes, ajuste_cubico, 'r-', label=f'Ajuste cúbico: $y = {coeffs[0]:.4f} x^3 + {coeffs[1]:.4f}$')

# Etiquetas y título
plt.xlabel('Longitud de la cadena (n)')
plt.ylabel('Tiempo de ejecución (segundos)')
plt.title('Comparación de tiempos de ejecución (CYK)')
plt.legend()

# Mostrar el gráfico
plt.grid(True)
plt.show()
