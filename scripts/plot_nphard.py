import pandas as pd
import matplotlib.pyplot as plt

# 1. Leggiamo il CSV
df = pd.read_csv('results/esperimento_nphard.csv')

# 2. Separiamo i dati dei tre algoritmi
df_random = df[df['Algo'] == 'Random']
df_ls = df[df['Algo'] == 'LocalSearch']
df_exact = df[df['Algo'] == 'Exact']

# 3. Creiamo la figura con due grafici affiancati
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# --- GRAFICO 1: Tempi di esecuzione (Il Muro Esponenziale) ---
ax1.plot(df_random['N_Nodi'], df_random['CPU_Time_sec'], marker='o', label='Random', color='blue')
ax1.plot(df_ls['N_Nodi'], df_ls['CPU_Time_sec'], marker='s', label='Greedy Local Search', color='red')
ax1.plot(df_exact['N_Nodi'], df_exact['CPU_Time_sec'], marker='^', label='Exact (Brute Force)', color='black', linewidth=2)

ax1.set_title('Dimostrazione NP-Hard: CPU Time')
ax1.set_xlabel('Numero di Nodi (N)')
ax1.set_ylabel('CPU Time (Secondi)')
ax1.legend()
ax1.grid(True)

# --- GRAFICO 2: Qualità della soluzione ---
ax2.plot(df_random['N_Nodi'], df_random['Taglio'], marker='o', label='Random', color='blue')
ax2.plot(df_ls['N_Nodi'], df_ls['Taglio'], marker='s', label='Greedy Local Search', color='red')
ax2.plot(df_exact['N_Nodi'], df_exact['Taglio'], marker='^', label='Exact (Ottimo Globale)', color='black', linewidth=2, linestyle='--')

ax2.set_title('Qualità del Taglio (Ottimo Globale vs Locali)')
ax2.set_xlabel('Numero di Nodi (N)')
ax2.set_ylabel('Dimensione del Taglio (Archi)')
ax2.legend()
ax2.grid(True)

# Salvataggio e visualizzazione
plt.suptitle('Analisi di Complessità: Euristica vs Esatto', fontsize=16)
plt.tight_layout()
plt.savefig('results/nphard_plots.png', dpi=300)
plt.show()

print("Grafici NP-Hard generati in results/nphard_plots.png!")