import pandas as pd
import matplotlib.pyplot as plt

# 1. Leggiamo il CSV
df = pd.read_csv('results/esperimento_nphard.csv')

# Funzione per generare e salvare i grafici per una specifica topologia
def crea_grafici_topologia(df_topo, nome_topologia, file_out):
    # 2. Separiamo i dati filtrando per l'algoritmo
    df_exact = df_topo[df_topo['Algo'] == 'Exact']
    df_random_1 = df_topo[df_topo['Algo'] == 'Random']
    df_random_100 = df_topo[df_topo['Algo'] == 'Random 100 iterations']
    df_ls_1 = df_topo[df_topo['Algo'] == 'LocalSearch']
    df_ls_100 = df_topo[df_topo['Algo'] == 'LocalSearch 100 iterations']

    # 3. Creiamo la figura con due grafici affiancati
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(14, 6))

    # --- GRAFICO 1: Tempi di esecuzione (Il Muro Esponenziale in LOG) ---
    ax1.set_yscale('log')

    # Plottiamo le 5 curve
    ax1.plot(df_random_1['N_Nodi'], df_random_1['CPU_Time_sec'], marker='o', linestyle='--', label='Random (K=1)', color='cornflowerblue')
    ax1.plot(df_random_100['N_Nodi'], df_random_100['CPU_Time_sec'], marker='o', label='Random (K=100)', color='darkblue')

    ax1.plot(df_ls_1['N_Nodi'], df_ls_1['CPU_Time_sec'], marker='s', linestyle='--', label='Greedy (K=1)', color='lightcoral')
    ax1.plot(df_ls_100['N_Nodi'], df_ls_100['CPU_Time_sec'], marker='s', label='Greedy (K=100)', color='darkred')

    ax1.plot(df_exact['N_Nodi'], df_exact['CPU_Time_sec'], marker='^', label='Exact (Brute Force)', color='black', linewidth=2)

    ax1.set_title(f'Tempi di Esecuzione: CPU Time (Scala Log)')
    ax1.set_xlabel('Numero di Nodi (N)')
    ax1.set_ylabel('CPU Time (Secondi) - Log Scale')
    ax1.legend()
    ax1.grid(True, which="both", ls="--", alpha=0.5) 

    # --- GRAFICO 2: Qualità della soluzione ---
    ax2.plot(df_random_1['N_Nodi'], df_random_1['Taglio'], marker='o', linestyle='--', label='Random (K=1)', color='cornflowerblue')
    ax2.plot(df_random_100['N_Nodi'], df_random_100['Taglio'], marker='o', label='Random (K=100)', color='darkblue')

    ax2.plot(df_ls_1['N_Nodi'], df_ls_1['Taglio'], marker='s', linestyle='--', label='Greedy (K=1)', color='lightcoral')
    ax2.plot(df_ls_100['N_Nodi'], df_ls_100['Taglio'], marker='s', label='Greedy (K=100)', color='darkred')

    ax2.plot(df_exact['N_Nodi'], df_exact['Taglio'], marker='^', label='Exact (Ottimo Globale)', color='black', linewidth=2, linestyle=':')

    ax2.set_title(f'Qualità del Taglio')
    ax2.set_xlabel('Numero di Nodi (N)')
    ax2.set_ylabel('Dimensione del Taglio (Archi)')
    ax2.legend()
    ax2.grid(True)

    # Salvataggio e chiusura
    plt.suptitle(f'Analisi NP-Hardness: {nome_topologia}', fontsize=16)
    plt.tight_layout()
    plt.savefig(file_out, dpi=300)
    plt.close() # Fondamentale per pulire la memoria tra un grafico e l'altro

# 4. Filtriamo il dataset generale in base alla colonna 'Topologia'
df_er = df[df['Topologia'] == 'Erdos-Renyi']
df_ba = df[df['Topologia'] == 'Barabasi-Albert']

# 5. Generiamo i due output richiamando la funzione
crea_grafici_topologia(df_er, 'Erdős-Rényi', 'results/nphard_plots_er.png')
crea_grafici_topologia(df_ba, 'Barabási-Albert', 'results/nphard_plots_ba.png')

print("Grafici NP-Hard definitivi generati con successo in results/!")