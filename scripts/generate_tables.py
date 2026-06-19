import pandas as pd
import os

def genera_tabella_latex(file_path, algoritmo, titolo, label):
    try:
        df = pd.read_csv(file_path)
    except FileNotFoundError:
        return f"% Errore: File {file_path} non trovato.\n"

    df_alg = df[df['Algoritmo'] == algoritmo].copy()
    
    if df_alg.empty:
        return f"% Nessun dato trovato per l'algoritmo {algoritmo} in {file_path}\n"
    
    # Formattazione numerica per lo standard italiano
    df_alg['Taglio'] = df_alg['Taglio'].apply(lambda x: f"{int(x):,}").str.replace(',', '.')
    df_alg['CPU_Time'] = df_alg['CPU_Time'].apply(lambda x: f"{float(x):.5f}")
    
    latex_str = f"\\begin{{table}}[htbp]\n"
    latex_str += f"    \\centering\n"
    latex_str += f"    \\begin{{tabular}}{{ccc}}\n"
    latex_str += f"        \\toprule\n"
    latex_str += f"        \\textbf{{Iterazioni}} & \\textbf{{Taglio Ottenuto}} & \\textbf{{Tempo CPU (s)}} \\\\\n"
    latex_str += f"        \\midrule\n"
    
    for _, row in df_alg.iterrows():
        latex_str += f"        {row['Iterazioni']} & {row['Taglio']} & {row['CPU_Time']} \\\\\n"
        
    latex_str += f"        \\bottomrule\n"
    latex_str += f"    \\end{{tabular}}\n"
    latex_str += f"    \\caption{{{titolo}}}\n"
    latex_str += f"    \\label{{{label}}}\n"
    latex_str += f"\\end{{table}}\n"
    
    return latex_str

def main():
    # Directory contenente i file CSV
    cartella_risultati = "results"
    
    configurazioni = [
        # --- FACEBOOK (Reale + Sintetici ER/BA) ---
        ("facebook.csv", "Random", "Risultati Randomizzato su Rete Reale (Facebook) - Incremento Lineare", "tab:fb_rand"),
        ("facebook.csv", "Greedy", "Risultati Greedy su Rete Reale (Facebook) - Incremento Lineare", "tab:fb_greedy"),
        ("facebook_d.csv", "Random", "Risultati Randomizzato su Rete Reale (Facebook) - Raddoppio Esponenziale", "tab:fb_rand_d"),
        ("facebook_d.csv", "Greedy", "Risultati Greedy su Rete Reale (Facebook) - Raddoppio Esponenziale", "tab:fb_greedy_d"),
        
        ("er_facebook.csv", "Random", "Risultati Randomizzato su Modello Erd\\H{o}s-R\\'enyi - Incremento Lineare", "tab:er_fb_rand"),
        ("er_facebook.csv", "Greedy", "Risultati Greedy su Modello Erd\\H{o}s-R\\'enyi - Incremento Lineare", "tab:er_fb_greedy"),
        ("er_facebook_d.csv", "Random", "Risultati Randomizzato su Modello Erd\\H{o}s-R\\'enyi - Raddoppio Esponenziale", "tab:er_fb_rand_d"),
        ("er_facebook_d.csv", "Greedy", "Risultati Greedy su Modello Erd\\H{o}s-R\\'enyi - Raddoppio Esponenziale", "tab:er_fb_greedy_d"),
        
        ("ba_facebook.csv", "Random", "Risultati Randomizzato su Modello Barab\\'asi-Albert - Incremento Lineare", "tab:ba_fb_rand"),
        ("ba_facebook.csv", "Greedy", "Risultati Greedy su Modello Barab\\'asi-Albert - Incremento Lineare", "tab:ba_fb_greedy"),
        ("ba_facebook_d.csv", "Random", "Risultati Randomizzato su Modello Barab\\'asi-Albert - Raddoppio Esponenziale", "tab:ba_fb_rand_d"),
        ("ba_facebook_d.csv", "Greedy", "Risultati Greedy su Modello Barab\\'asi-Albert - Raddoppio Esponenziale", "tab:ba_fb_greedy_d"),

        # --- ENRON (Solo Rete Reale) ---
        ("enron.csv", "Random", "Risultati Randomizzato su Rete Reale (Enron) - Incremento Lineare", "tab:enron_rand"),
        ("enron.csv", "Greedy", "Risultati Greedy su Rete Reale (Enron) - Incremento Lineare", "tab:enron_greedy"),
        ("enron_d.csv", "Random", "Risultati Randomizzato su Rete Reale (Enron) - Raddoppio Esponenziale", "tab:enron_rand_d"),
        ("enron_d.csv", "Greedy", "Risultati Greedy su Rete Reale (Enron) - Raddoppio Esponenziale", "tab:enron_greedy_d"),

        # --- AMAZON (Solo Rete Reale) ---
        ("amazon.csv", "Random", "Risultati Randomizzato su Rete Reale (Amazon) - Incremento Lineare", "tab:amazon_rand"),
        ("amazon.csv", "Greedy", "Risultati Greedy su Rete Reale (Amazon) - Incremento Lineare", "tab:amazon_greedy"),
        ("amazon_d.csv", "Random", "Risultati Randomizzato su Rete Reale (Amazon) - Raddoppio Esponenziale", "tab:amazon_rand_d"),
        ("amazon_d.csv", "Greedy", "Risultati Greedy su Rete Reale (Amazon) - Raddoppio Esponenziale", "tab:amazon_greedy_d"),

        # --- YOUTUBE (Solo Rete Reale) ---
        ("youtube.csv", "Random", "Risultati Randomizzato su Rete Reale (YouTube) - Incremento Lineare", "tab:yt_rand"),
        ("youtube.csv", "Greedy", "Risultati Greedy su Rete Reale (YouTube) - Incremento Lineare", "tab:yt_greedy"),
        ("youtube_d.csv", "Random", "Risultati Randomizzato su Rete Reale (YouTube) - Raddoppio Esponenziale", "tab:yt_rand_d"),
        ("youtube_d.csv", "Greedy", "Risultati Greedy su Rete Reale (YouTube) - Raddoppio Esponenziale", "tab:yt_greedy_d"),
    ]

    with open("tabelle_tesi_complete.tex", "w") as f:
        for csv_file, alg, titolo, label in configurazioni:
            # Costruisce il percorso relativo: results/nomefile.csv
            file_path = os.path.join(cartella_risultati, csv_file)
            tabella = genera_tabella_latex(file_path, alg, titolo, label)
            f.write(tabella)
            f.write("\n\n")

    print("Generazione completata: le tabelle sono state salvate in 'tabelle_tesi_complete.tex'")

if __name__ == "__main__":
    main()