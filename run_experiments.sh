#!/bin/bash

# Interrompe lo script se c'è un errore
set -e 

echo "🛠️ 1. Compilazione del Workhorse C++..."
make

echo "🏃 2. Esecuzione del Doubling Experiment..."
./maxcut > results/esperimento_doubling.csv

echo "📊 3. Generazione dei grafici in Python..."
# Attiva il venv e lancia lo script
source .venv/bin/activate
python3 scripts/plot_results.py

echo "✅ Pipeline completata! Controlla la cartella results/"