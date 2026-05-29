# Engineering Approximation Algorithms for Maximum Cut

**Corso:** Algorithm Engineering (A.A. 2025/2026)  
**Studente:** Andrea Iannotti (Matricola: 302222)  

## 📌 Abstract
Questo progetto implementa e valuta sperimentalmente algoritmi di approssimazione per il problema **Maximum Cut (Max-Cut)** su grafi di grandi dimensioni. Il focus dell'esperimento è l'analisi dei *runtime trade-offs* (Qualità della soluzione vs CPU Time) mettendo a confronto un algoritmo basato su partizionamento casuale (Randomized Max-Cut) con un'euristica deterministica (Greedy Local Search). 

Il progetto segue le metodologie di Algorithm Engineering, includendo *Doubling Experiments* su generatori random, validazione su reti reali (SNAP), tuning del compilatore e misurazione rigorosa del CPU Time per isolare gli artefatti sperimentali.

---

## 📂 Struttura della Repository

Il progetto è strutturato per separare nettamente il motore di calcolo (C++ Workhorse) dall'analisi dei dati (Python):

```text
max-cut-ae/
├── src/
│   └── maxcut.cpp           # Implementazione C++ degli algoritmi e misurazione CPU Time
├── scripts/
│   └── plot_results.py      # Script Python per la generazione dei grafici
├── data/                    # Dataset (ignorati da git, vedi istruzioni sotto)
│   └── toy_graph.txt        # Piccolo grafo di test per la validazione (Correctness)
├── results/                 # File CSV generati dal C++ e grafici PNG
├── Makefile                 # Regole di compilazione con ottimizzazione -O3
├── run_experiments.sh       # Pipeline automatizzata per test e plot
└── README.md