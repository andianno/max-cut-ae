#!/bin/bash

# Ferma lo script se qualcosa va storto
set -e 

echo "========================================================="
echo "🚀 AVVIO REPLICAZIONE TOTALE DELL'ESPERIMENTO MAX-CUT"
echo "========================================================="

echo ""
echo "🐍 1. Creazione ambiente virtuale e installazione librerie..."
python3 -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt

echo ""
echo "🛠️ 2. Compilazione del codice sorgente C++..."
make clean
make

echo ""
echo "🔍 3. Validazione statistica e strutturale dei generatori..."
./test_generators

echo ""
echo "🏃 4. Esecuzione algoritmo Esatto (NP-Hardness)..."
./run_nphard

echo ""
echo "🏃 5. Esecuzione Esperimenti Standard (Early Stopping)..."
echo "   -> Facebook..."
./run_experiments facebook
echo "   -> Amazon..."
./run_experiments amazon
echo "   -> YouTube..."
./run_experiments youtube

echo ""
echo "🏃 6. Esecuzione Doubling Experiment (Incremento Logaritmico)..."
echo "   -> Facebook..."
./run_experiments_d facebook
echo "   -> Amazon..."
./run_experiments_d amazon
echo "   -> YouTube..."
./run_experiments_d youtube

echo ""
echo "📊 7. Generazione di tutti i grafici Python..."
echo "   -> Grafico Validazione Barabási-Albert..."
cd scripts
python3 plot_ba.py
cd ..

echo "   -> Grafici NP-Hardness..."
python3 scripts/plot_nphard.py

echo "   -> Grafici Esperimenti Standard..."
python3 scripts/plot_exp.py facebook
python3 scripts/plot_exp.py amazon
python3 scripts/plot_exp.py youtube

echo "   -> Grafici Doubling Experiment..."
python3 scripts/plot_doubling.py facebook
python3 scripts/plot_doubling.py amazon
python3 scripts/plot_doubling.py youtube

echo ""
echo "========================================================="
echo "✅ ESPERIMENTO REPLICATO AL 100%!"
echo "Tutti i file CSV e i grafici PNG sono pronti."
echo "========================================================="