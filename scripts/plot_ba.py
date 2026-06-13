import pandas as pd
import matplotlib.pyplot as plt
from collections import Counter

# 1. Legge il file CSV generato dal C++
df = pd.read_csv('results/ba_degrees.csv')

# 2. Conta quanti nodi hanno un determinato grado
degree_counts = Counter(df['Degree'])

# Prepara i dati per il grafico (X = grado, Y = frequenza)
degrees = list(degree_counts.keys())
frequencies = list(degree_counts.values())

# 3. Disegna il grafico in scala Log-Log
plt.figure(figsize=(8, 6))
plt.scatter(degrees, frequencies, color='blue', alpha=0.7, edgecolors='black')
plt.xscale('log')
plt.yscale('log')

plt.title('Distribuzione dei Gradi - Modello Barabási-Albert')
plt.xlabel('Grado del nodo (Log)')
plt.ylabel('Frequenza (Log)')
plt.grid(True, which="both", ls="--", alpha=0.5)

# 4. Salva l'immagine
plt.savefig('results/barabasi_power_law.png', dpi=300)
print("[INFO] Grafico salvato in results/barabasi_power_law.png")