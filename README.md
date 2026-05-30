# Engineering Approximation Algorithms for Maximum Cut

**Corso:** Algorithm Engineering (A.A. 2025/2026)  
**Studente:** Andrea Iannotti (Matricola: 302222)  

## 📌 Abstract
Questo progetto implementa e valuta sperimentalmente algoritmi di approssimazione per il problema **Maximum Cut (Max-Cut)** su grafi di grandi dimensioni. Il focus dell'esperimento è l'analisi dei *runtime trade-offs* (Qualità della soluzione vs CPU Time) mettendo a confronto un algoritmo basato su partizionamento casuale (Randomized Max-Cut) con un'euristica deterministica (Greedy Local Search). 

Il progetto segue le metodologie di Algorithm Engineering, includendo l'uso di dataset reali (reti SNAP), una rigorosa misurazione del CPU Time per isolare le prestazioni del codice, e una dimostrazione empirica dell'esplosione combinatoria (NP-Hardness) tramite il confronto con un Algoritmo Esatto su grafi di taglia ridotta.

---

## 📂 Struttura della Repository (Architettura Modulare)

Il progetto è stato riorganizzato seguendo il principio di separazione delle responsabilità, isolando le interfacce, i motori di calcolo e gli esperimenti:

```text
max-cut-ae/
├── include/
│   └── graph.h              # "Contratto": definizioni del grafo e firme delle funzioni
├── src/
│   ├── utils.cpp            # Parser dei file SNAP e funzioni di supporto (es. calculate_cut)
│   ├── randomized.cpp       # Euristica Random (Costo: lineare)
│   ├── greedy.cpp           # Euristica Greedy Local Search (Costo: dipendente dalla soluzione)
│   ├── exact.cpp            # Algoritmo Esatto Brute Force (Costo: esponenziale)
│   ├── main_nphard.cpp      # Eseguibile 1: Test del muro esponenziale su grafi piccoli
│   └── main_exp.cpp         # Eseguibile 2: Test su reti reali e Doubling Experiment
├── scripts/
│   ├── plot_results.py      # Script Python per i grafici del Doubling Experiment
│   └── plot_nphard.py       # Script Python per i grafici dell'algoritmo Esatto
├── data/                    # Dataset (ignorati da Git. Si consiglia di usare le reti di Stanford SNAP)
├── results/                 # File CSV e grafici PNG autogenerati
├── Makefile                 # Regole per la compilazione intelligente a oggetti separati (.o)
├── .gitignore               # Regole di pulizia della repository (ignora eseguibili e dataset)
└── README.md