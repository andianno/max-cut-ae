import pandas as pd
import matplotlib.pyplot as plt

# Leggiamo il CSV generato dal C++
df = pd.read_csv('results/esperimento_doubling.csv')

# Separiamo i dati dei due algoritmi
df_random = df[df['Algo'] == 'Random']
df_local_search = df[df['Algo'] == 'LocalSearch']

# Creiamo una figura con due grafici affiancati
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# --- GRAFICO 1: Solution Quality (Taglio) ---
ax1.plot(df_random['N_Nodi'], df_random['Taglio'], marker='o', label='Random (100 iter)', color='blue')
ax1.plot(df_local_search['N_Nodi'], df_local_search['Taglio'], marker='s', label='Greedy Local Search', color='red')
ax1.set_title('Solution Quality: Max-Cut Size vs N')
ax1.set_xlabel('Numero di Nodi (N)')
ax1.set_ylabel('Dimensione del Taglio (Archi)')
ax1.legend()
ax1.grid(True)

# --- GRAFICO 2: Runtime Trade-off (CPU Time) ---
ax2.plot(df_random['N_Nodi'], df_random['CPU_Time_sec'], marker='o', label='Random (100 iter)', color='blue')
ax2.plot(df_local_search['N_Nodi'], df_local_search['CPU_Time_sec'], marker='s', label='Greedy Local Search', color='red')
ax2.set_title('Runtime Trade-off: CPU Time vs N')
ax2.set_xlabel('Numero di Nodi (N)')
ax2.set_ylabel('CPU Time (Secondi)')
ax2.legend()
ax2.grid(True)

# Mettiamo un titolo generale e salviamo l'immagine
plt.suptitle('Analisi Sperimentale Max-Cut: Random vs Local Search', fontsize=16)
plt.tight_layout()
plt.savefig('results/doubling_experiment_plots.png', dpi=300)
plt.show()

print("Grafici generati con successo in results/doubling_experiment_plots.png!")