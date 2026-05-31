import pandas as pd
import matplotlib.pyplot as plt

# 1. Leggiamo il CSV
df = pd.read_csv('results/esperimento_nphard.csv')

# 2. Separiamo i dati cercando ESATTAMENTE le stringhe presenti nel file
df_exact = df[df['Algo'] == 'Exact']

# Filtri per il Random
df_random_1 = df[df['Algo'] == 'Random']
df_random_100 = df[df['Algo'] == 'Random 100 iterations']

# Filtri per la Local Search (Greedy)
df_ls_1 = df[df['Algo'] == 'LocalSearch']
df_ls_100 = df[df['Algo'] == 'LocalSearch 100 iterations']

# 3. Creiamo la figura con due grafici affiancati
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

# --- GRAFICO 1: Tempi di esecuzione (Il Muro Esponenziale in LOG) ---

# LA MAGIA DELL'INGEGNERE: Scala logaritmica sull'asse Y
ax1.set_yscale('log')

# Plottiamo le 5 curve (usiamo il tratteggio per K=1)
ax1.plot(df_random_1['N_Nodi'], df_random_1['CPU_Time_sec'], marker='o', linestyle='--', label='Random (K=1)', color='cornflowerblue')
ax1.plot(df_random_100['N_Nodi'], df_random_100['CPU_Time_sec'], marker='o', label='Random (K=100)', color='darkblue')

ax1.plot(df_ls_1['N_Nodi'], df_ls_1['CPU_Time_sec'], marker='s', linestyle='--', label='Greedy (K=1)', color='lightcoral')
ax1.plot(df_ls_100['N_Nodi'], df_ls_100['CPU_Time_sec'], marker='s', label='Greedy (K=100)', color='darkred')

ax1.plot(df_exact['N_Nodi'], df_exact['CPU_Time_sec'], marker='^', label='Exact (Brute Force)', color='black', linewidth=2)

ax1.set_title('Dimostrazione NP-Hard: CPU Time (Scala Log)')
ax1.set_xlabel('Numero di Nodi (N)')
ax1.set_ylabel('CPU Time (Secondi) - Log Scale')
ax1.legend()
# Miglioriamo la griglia per far leggere bene la scala logaritmica
ax1.grid(True, which="both", ls="--", alpha=0.5) 

# --- GRAFICO 2: Qualità della soluzione ---

ax2.plot(df_random_1['N_Nodi'], df_random_1['Taglio'], marker='o', linestyle='--', label='Random (K=1)', color='cornflowerblue')
ax2.plot(df_random_100['N_Nodi'], df_random_100['Taglio'], marker='o', label='Random (K=100)', color='darkblue')

ax2.plot(df_ls_1['N_Nodi'], df_ls_1['Taglio'], marker='s', linestyle='--', label='Greedy (K=1)', color='lightcoral')
ax2.plot(df_ls_100['N_Nodi'], df_ls_100['Taglio'], marker='s', label='Greedy (K=100)', color='darkred')

ax2.plot(df_exact['N_Nodi'], df_exact['Taglio'], marker='^', label='Exact (Ottimo Globale)', color='black', linewidth=2, linestyle=':')

ax2.set_title('Qualità del Taglio (Esplorazione vs Sfruttamento)')
ax2.set_xlabel('Numero di Nodi (N)')
ax2.set_ylabel('Dimensione del Taglio (Archi)')
ax2.legend()
ax2.grid(True)

# Salvataggio e visualizzazione
plt.suptitle('Analisi di Complessità: Trade-off Iterazioni (K=1 vs K=100)', fontsize=16)
plt.tight_layout()
plt.savefig('results/nphard_plots_log.png', dpi=300)
plt.show()

print("Grafici NP-Hard definitivi generati in results/nphard_plots_log.png!")