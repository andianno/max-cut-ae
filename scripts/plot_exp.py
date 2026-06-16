import sys
import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

def format_title_name(name):
    """Formatta il nome del dataset per renderlo presentabile nei titoli dei grafici."""
    if name.startswith("er_"):
        return f"Erdős-Rényi (Specchiato su {name[3:].capitalize()})"
    elif name.startswith("ba_"):
        return f"Barabási-Albert (Specchiato su {name[3:].capitalize()})"
    else:
        return name.capitalize()

def main():
    # 1. PARSING DELL'ARGOMENTO
    dataset_name = "facebook"
    if len(sys.argv) > 1:
        dataset_name = sys.argv[1].lower()

    csv_filename = f"results/{dataset_name}.csv"
    plot_filename = f"results/plot_completo_{dataset_name}.png"

    if not os.path.exists(csv_filename):
        print(f"[ERRORE] Il file {csv_filename} non esiste.")
        sys.exit(1)

    print(f"Lettura dei dati da {csv_filename}...")
    
    # 2. CARICAMENTO DATI
    df = pd.read_csv(csv_filename)
    df_random = df[df["Algoritmo"] == "Random"]
    df_greedy = df[df["Algoritmo"] == "Greedy"]

    # 3. CONFIGURAZIONE ESTETICA (Griglia 3x2)
    sns.set_theme(style="whitegrid")
    palette = {"Random": "#6495ED", "Greedy": "#8B0000"} 
    
    fig, axes = plt.subplots(3, 2, figsize=(16, 18))
    
    # Usa la nuova funzione per un titolo accademico pulito
    display_name = format_title_name(dataset_name)
    fig.suptitle(f"Analisi Prestazionale e Trend Line - Rete: {display_name}", 
                 fontsize=20, weight='bold')

    # --- RIGA 1: CONFRONTO GLOBALE (Senza regressione, per purezza visiva) ---
    sns.lineplot(data=df, x="Iterazioni", y="CPU_Time", hue="Algoritmo", palette=palette, marker="o", ax=axes[0, 0])
    axes[0, 0].set_title("Confronto Globale: Costo Computazionale", fontsize=14)
    axes[0, 0].set_ylabel("CPU Time (Secondi)", fontsize=12)
    axes[0, 0].set_xlabel("")

    sns.lineplot(data=df, x="Iterazioni", y="Taglio", hue="Algoritmo", palette=palette, marker="s", ax=axes[0, 1])
    axes[0, 1].set_title("Confronto Globale: Qualità della Soluzione", fontsize=14)
    axes[0, 1].set_ylabel("Dimensione del Taglio", fontsize=12)
    axes[0, 1].set_xlabel("")

    # --- RIGA 2: ZOOM SUL RANDOM (Con Regressione) ---
    # Tempo (Dati + Trend)
    sns.lineplot(data=df_random, x="Iterazioni", y="CPU_Time", color="#6495ED", marker="o", alpha=0.4, ax=axes[1, 0])
    sns.regplot(data=df_random, x="Iterazioni", y="CPU_Time", scatter=False, color="#00008B", line_kws={"linestyle":"--", "linewidth":2}, ax=axes[1, 0])
    axes[1, 0].set_title("Dettaglio Random: Trend Computazionale", fontsize=14)
    axes[1, 0].set_ylabel("CPU Time (Secondi)", fontsize=12)
    axes[1, 0].set_xlabel("")

    # Qualità (Dati + Trend)
    sns.lineplot(data=df_random, x="Iterazioni", y="Taglio", color="#6495ED", marker="s", alpha=0.4, ax=axes[1, 1])
    sns.regplot(data=df_random, x="Iterazioni", y="Taglio", scatter=False, color="#00008B", line_kws={"linestyle":"--", "linewidth":2}, ax=axes[1, 1])
    axes[1, 1].set_title("Dettaglio Random: Trend di Qualità", fontsize=14)
    axes[1, 1].set_ylabel("Dimensione del Taglio", fontsize=12)
    axes[1, 1].set_xlabel("")

    # --- RIGA 3: ZOOM SUL GREEDY (Con Regressione) ---
    # Tempo (Dati + Trend)
    sns.lineplot(data=df_greedy, x="Iterazioni", y="CPU_Time", color="#8B0000", marker="o", alpha=0.4, ax=axes[2, 0])
    sns.regplot(data=df_greedy, x="Iterazioni", y="CPU_Time", scatter=False, color="#4A0000", line_kws={"linestyle":"--", "linewidth":2}, ax=axes[2, 0])
    axes[2, 0].set_title("Dettaglio Greedy: Trend Computazionale", fontsize=14)
    axes[2, 0].set_ylabel("CPU Time (Secondi)", fontsize=12)
    axes[2, 0].set_xlabel("Numero di Iterazioni", fontsize=12)

    # Qualità (Dati + Trend)
    sns.lineplot(data=df_greedy, x="Iterazioni", y="Taglio", color="#8B0000", marker="s", alpha=0.4, ax=axes[2, 1])
    sns.regplot(data=df_greedy, x="Iterazioni", y="Taglio", scatter=False, color="#4A0000", line_kws={"linestyle":"--", "linewidth":2}, ax=axes[2, 1])
    axes[2, 1].set_title("Dettaglio Greedy: Trend di Qualità", fontsize=14)
    axes[2, 1].set_ylabel("Dimensione del Taglio", fontsize=12)
    axes[2, 1].set_xlabel("Numero di Iterazioni", fontsize=12)

    # 4. OTTIMIZZAZIONE E SALVATAGGIO
    plt.tight_layout()
    plt.subplots_adjust(top=0.94)
    plt.savefig(plot_filename, dpi=300, bbox_inches='tight')
    
    print(f"Grafico con rette di regressione generato: {plot_filename}")

if __name__ == "__main__":
    main()