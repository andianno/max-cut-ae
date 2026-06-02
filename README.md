# Engineering Approximation Algorithms for Maximum Cut

**Corso:** Algorithm Engineering (A.A. 2025/2026)  
**Studente:** Andrea Iannotti (Matricola: 302222)  

## 📌 Abstract
Questo progetto implementa e valuta sperimentalmente algoritmi di approssimazione per il problema **Maximum Cut (Max-Cut)** su grafi di grandi dimensioni. Il focus dell'esperimento è l'analisi dei *runtime trade-offs* (Qualità della soluzione vs CPU Time) mettendo a confronto un algoritmo basato su partizionamento casuale (Randomized Max-Cut) con un'euristica deterministica (Greedy Local Search). 

Il progetto segue le metodologie di Algorithm Engineering, includendo l'uso di dataset reali (reti SNAP), una rigorosa misurazione del CPU Time per isolare le prestazioni del codice, e una dimostrazione empirica dell'esplosione combinatoria (NP-Hardness) tramite il confronto con un Algoritmo Esatto su grafi di taglia ridotta.

---

## 📂 Struttura della Repository (Architettura Modulare)

Il progetto è organizzato seguendo il principio di separazione delle responsabilità, isolando le interfacce, i motori di calcolo e gli esperimenti:

```text
max-cut-ae/
├── include/
│   └── graph.h              # "Contratto": definizioni del grafo e firme delle funzioni
├── src/
│   ├── utils.cpp            # Parser dei file SNAP e funzioni di supporto
│   ├── randomized.cpp       # Euristica Random (Costo: lineare, 0.5-Approximation)
│   ├── greedy.cpp           # Euristica Multi-Start Greedy Local Search
│   ├── exact.cpp            # Algoritmo Esatto Brute Force (Costo: esponenziale)
│   ├── main_nphard.cpp      # Esperimento 1: NP-Hardness su grafi piccoli
│   ├── main_exp.cpp         # Esperimento 2: Reti reali con Early Stopping lineare
│   └── main_exp_d.cpp       # Esperimento 3: Doubling Experiment su scala logaritmica
├── scripts/
│   ├── plot_exp.py          # Generazione griglia analitica per test Early Stopping
│   ├── plot_doubling.py     # Generazione grafici con asse X logaritmico (Log2)
│   └── plot_nphard.py       # Visualizzazione del muro esponenziale
├── data/                    # Dataset (es. facebook_combined.txt, com-amazon.ungraph.txt)
├── results/                 # Output testuali (CSV) e visuali (PNG)
├── Makefile                 # Regole di compilazione ottimizzata (-O3) per i target multipli
├── requirements.txt         # Dipendenze Python per la riproducibilità dell'ambiente
├── .gitignore               # Esclusione di binari, dataset massivi e venv
└── README.md