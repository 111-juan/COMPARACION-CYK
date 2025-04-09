import pandas as pd
import matplotlib.pyplot as plt

# Leer archivo CSV
datos = pd.read_csv("datos.csv")

# Ordenar por longitud por si están desordenados
datos = datos.sort_values(by="Longitud")

# Crear gráfica lineal: puntos unidos por líneas
plt.figure(figsize=(10, 6))
plt.plot(
    datos["Longitud"],
    datos["Tiempo"],
    marker='o',
    linestyle='-',
    color='blue',
    label="Tiempo por longitud"
)

# Etiquetas
plt.title("Tiempo de Análisis vs Longitud de Cadena (Bison)")
plt.xlabel("Longitud de la Cadena")
plt.ylabel("Tiempo (segundos)")
plt.grid(True)
plt.legend()
plt.tight_layout()

# Guardar y mostrar
plt.savefig("grafica_lineal_bison.png")
plt.show()
