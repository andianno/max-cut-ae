import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import os
import sys

def plot_scalability(df_topo, topo_name, out_filename):
    """Genera e salva il grafico di scalabilità per una specifica topologia."""
    plt.figure(figsize=(10, 6))

    palette = {"Random": "#6495ED", "Greedy": "#8B0000"}

    # Tracciamento delle curve
    sns.lineplot(data=df_topo, x='N_Nodi', y='CPU_Time', hue='Algoritmo', 
                 palette=palette, marker='o', linewidth=2.5, markersize=8)

    plt.title(f'Test di Scalabilità (Crescita dei Nodi) - {topo_name}', fontsize=16, weight='bold')
    plt.xlabel('Numero di Nodi (N) - Scala Log2', fontsize=12)
    plt.ylabel('CPU Time (Secondi)', fontsize=12)

    # Impostazione della scala logaritmica in base 2 per l'asse X
    plt.xscale('log', base=2)
    
    # Formattazione per mostrare i numeri interi sull'asse X invece della notazione scientifica
    from matplotlib.ticker import ScalarFormatter
    ax = plt.gca()
    ax.xaxis.set_major_formatter(ScalarFormatter())
    plt.xticks(df_topo['N_Nodi'].unique()) 

    plt.legend(title='Algoritmo', fontsize=11, title_fontsize=12)
    plt.grid(True, which="both", ls="--", alpha=0.5)

    plt.tight_layout()
    plt.savefig(out_filename, dpi=300)
    plt.close()
    
    print(f"[OK] Grafico salvato: {out_filename}")

def main():
    csv_file = 'results/scalability_nodes.csv'
    
    if not os.path.exists(csv_file):
        print(f"[ERRORE] File {csv_file} non trovato. Esegui prima ./run_scale")
        sys.exit(1)

    print(f"Lettura dei dati da {csv_file}...")
    df = pd.read_csv(csv_file)

    sns.set_theme(style="whitegrid")

    # Separazione dei dati in base alla topologia
    df_er = df[df['Topologia'] == 'Erdos-Renyi']
    df_ba = df[df['Topologia'] == 'Barabasi-Albert']

    # Generazione dei due grafici separati
    plot_scalability(df_er, 'Erdős-Rényi', 'results/scalability_er.png')
    plot_scalability(df_ba, 'Barabási-Albert', 'results/scalability_ba.png')

if __name__ == "__main__":
    main()