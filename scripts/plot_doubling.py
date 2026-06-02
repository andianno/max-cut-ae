import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def main():
    # 1. PARSING DELL'ARGOMENTO
    dataset_name = "facebook"
    if len(sys.argv) > 1:
        dataset_name = sys.argv[1].lower()

    csv_filename = f"results/{dataset_name}_d.csv"
    plot_filename = f"results/plot_doubling_completo_{dataset_name}.png"

    if not os.path.exists(csv_filename):
        print(f"[ERRORE] Il file {csv_filename} non esiste.")
        sys.exit(1)

    print(f"Lettura dei dati da {csv_filename}...")
    
    # 2. CARICAMENTO DATI E SEPARAZIONE
    df = pd.read_csv(csv_filename)
    df_random = df[df["Algoritmo"] == "Random"]
    df_greedy = df[df["Algoritmo"] == "Greedy"]

    # 3. CONFIGURAZIONE ESTETICA (Griglia 3x2)
    sns.set_theme(style="whitegrid")
    palette = {"Random": "#6495ED", "Greedy": "#8B0000"} 
    
    fig, axes = plt.subplots(3, 2, figsize=(16, 18))
    fig.suptitle(f"Doubling Experiment: Analisi Completa (Log2)\nDataset: {dataset_name.capitalize()}", 
                 fontsize=20, weight='bold')

    # Valori esatti delle X per forzare i tick sul grafico
    x_ticks = df_greedy["Iterazioni"].tolist()

    # Funzione Helper (Clean Code): applica scala log e tick a ogni singolo grafico
    def format_log_axis(ax, title, ylabel, xlabel=""):
        ax.set_title(title, fontsize=14)
        ax.set_ylabel(ylabel, fontsize=12)
        ax.set_xlabel(xlabel, fontsize=12)
        # Forza la scala logaritmica in base 2 per rispettare il raddoppio
        ax.set_xscale("log", base=2)
        ax.set_xticks(x_ticks)
        ax.set_xticklabels(x_ticks, rotation=45)

    # --- RIGA 1: CONFRONTO GLOBALE ---
    sns.lineplot(data=df, x="Iterazioni", y="CPU_Time", hue="Algoritmo", palette=palette, marker="o", linewidth=2, ax=axes[0, 0])
    format_log_axis(axes[0, 0], "Confronto Globale: Costo Computazionale", "CPU Time (Secondi)")

    sns.lineplot(data=df, x="Iterazioni", y="Taglio", hue="Algoritmo", palette=palette, marker="s", linewidth=2, ax=axes[0, 1])
    format_log_axis(axes[0, 1], "Confronto Globale: Qualità della Soluzione", "Dimensione del Taglio")

    # --- RIGA 2: ZOOM SUL RANDOM ---
    sns.lineplot(data=df_random, x="Iterazioni", y="CPU_Time", color="#6495ED", marker="o", linewidth=2, ax=axes[1, 0])
    format_log_axis(axes[1, 0], "Dettaglio Random: Costo Computazionale", "CPU Time (Secondi)")

    sns.lineplot(data=df_random, x="Iterazioni", y="Taglio", color="#6495ED", marker="s", linewidth=2, ax=axes[1, 1])
    format_log_axis(axes[1, 1], "Dettaglio Random: Qualità della Soluzione", "Dimensione del Taglio")

    # --- RIGA 3: ZOOM SUL GREEDY ---
    sns.lineplot(data=df_greedy, x="Iterazioni", y="CPU_Time", color="#8B0000", marker="o", linewidth=2, ax=axes[2, 0])
    format_log_axis(axes[2, 0], "Dettaglio Greedy: Costo Computazionale", "CPU Time (Secondi)", "Iterazioni (Scala Log2)")

    sns.lineplot(data=df_greedy, x="Iterazioni", y="Taglio", color="#8B0000", marker="s", linewidth=2, ax=axes[2, 1])
    format_log_axis(axes[2, 1], "Dettaglio Greedy: Legge dei Rendimenti Decrescenti", "Dimensione del Taglio", "Iterazioni (Scala Log2)")

    # 4. OTTIMIZZAZIONE E SALVATAGGIO
    plt.tight_layout()
    plt.subplots_adjust(top=0.94) 
    plt.savefig(plot_filename, dpi=300, bbox_inches='tight')
    
    print(f"Grafico 3x2 del Doubling generato con successo: {plot_filename}")

if __name__ == "__main__":
    main()