# Engineering Approximation Algorithms for Maximum Cut

**Corso:** Algorithm Engineering (A.A. 2025/2026)  
**Studente:** Andrea Iannotti (Matricola: 302222)  

## 📌 Abstract
Questo progetto implementa e valuta sperimentalmente algoritmi di approssimazione per il problema **Maximum Cut (Max-Cut)** su grafi di grandi dimensioni. Il focus dell'esperimento è l'analisi dei *runtime trade-offs* (Qualità della soluzione vs CPU Time) mettendo a confronto un algoritmo basato su partizionamento casuale (Randomized Max-Cut) con un'euristica deterministica (Greedy Local Search). 

Il progetto segue le rigorose metodologie di Algorithm Engineering. Oltre all'utilizzo di dataset reali provenienti da reti SNAP (Facebook, Enron, Amazon, YouTube), il sistema genera reti sintetiche speculari (modelli Erdős-Rényi e Barabási-Albert) per dimostrare empiricamente come le dinamiche di *preferential attachment* descrivano accuratamente le topologie sociali reali.

L'analisi si snoda attraverso quattro fasi sperimentali:
1. **NP-Hardness:** Dimostrazione dell'esplosione combinatoria tramite confronto con un Algoritmo Esatto su grafi di taglia ridotta.
2. **Early Stopping:** Analisi del trade-off temporale su iterazioni lineari con interruzione anticipata.
3. **Doubling Experiment (Iterazioni):** Studio della convergenza asintotica e della legge dei rendimenti decrescenti tramite incremento logaritmico delle iterazioni.
4. **Scalability Experiment (Nodi):** Misurazione dell'impatto della dimensione dell'input sulle prestazioni, raddoppiando sistematicamente il numero di nodi.

---

## 📂 Struttura della Repository

Il progetto è organizzato seguendo il principio di separazione delle responsabilità, isolando le interfacce, i motori di calcolo, la validazione e gli esperimenti:

```text
max-cut-ae/
├── include/
│   └── graph.h              # Contratto: definizioni del grafo e firme delle funzioni
├── src/
│   ├── utils.cpp            # Parser file SNAP e generatori (Erdős-Rényi, Barabási-Albert)
│   ├── randomized.cpp       # Euristica Random (Costo lineare, 0.5-Approximation)
│   ├── greedy.cpp           # Euristica Multi-Start Greedy Local Search
│   ├── exact.cpp            # Algoritmo Esatto Brute Force (Costo esponenziale)
│   ├── test_generators.cpp  # Validazione strutturale e statistica dei generatori di grafi
│   ├── main_nphard.cpp      # Esperimento 1: NP-Hardness su grafi piccoli
│   ├── main_exp.cpp         # Esperimento 2: Reti reali con Early Stopping lineare
│   ├── main_exp_d.cpp       # Esperimento 3: Doubling Experiment su scala logaritmica
│   └── main_scale.cpp       # Esperimento 4: Scalabilità temporale con raddoppio dei nodi
├── scripts/
│   ├── plot_ba.py           # Verifica visiva (Log-Log plot) della Legge di Potenza
│   ├── plot_exp.py          # Generazione griglia analitica per test Early Stopping
│   ├── plot_doubling.py     # Generazione grafici con asse X in scala Log2
│   ├── plot_scale.py        # Generazione curve di scalabilità dimensionale
│   └── plot_nphard.py       # Visualizzazione del muro esponenziale e qualità del taglio
├── data/                    # Dataset scaricati (es. facebook_combined.txt)
├── results/                 # Output testuali (CSV) e visuali (PNG)
├── Makefile                 # Regole di compilazione ottimizzata (-O3) per target multipli
├── run_experiments.sh       # Automazione bash: dalla compilazione alla generazione grafici
├── requirements.txt         # Dipendenze Python per la riproducibilità dell'ambiente
└── .gitignore               # Esclusione di binari, dataset massivi e virtual environment