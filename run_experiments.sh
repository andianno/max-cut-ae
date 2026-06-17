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
./test_generators > results/validazione_generatori.csv

echo ""
echo "🏃 4. Esecuzione algoritmo Esatto (NP-Hardness)..."
./run_nphard > results/esperimento_nphard.csv

echo ""
echo "🏃 5. Esecuzione Esperimenti Standard (Early Stopping)..."
for data in facebook enron amazon youtube er_facebook ba_facebook ba_enron ba_amazon ba_youtube
do
    echo "   -> Esecuzione su $data..."
    ./run_experiments $data
done

echo ""
echo "🏃 6. Esecuzione Doubling Experiment (Incremento Iterazioni)..."
for data in facebook enron amazon youtube er_facebook ba_facebook ba_enron ba_amazon ba_youtube
do
    echo "   -> Esecuzione su $data..."
    ./run_experiments_d $data
done

echo ""
echo "🏃 7. Esecuzione Scalability Experiment (Doubling Nodi)..."
./run_scale

echo ""
echo "📊 8. Generazione di tutti i grafici Python..."
echo "   -> Grafico Validazione Barabási-Albert..."
# cd scripts
python3 scripts/plot_ba.py
# cd ..

echo "   -> Grafici NP-Hardness..."
python3 scripts/plot_nphard.py

echo "   -> Grafici Esperimenti Standard..."
for data in facebook enron amazon youtube er_facebook ba_facebook ba_enron ba_amazon ba_youtube
do
    python3 scripts/plot_exp.py $data
done

echo "   -> Grafici Doubling Experiment (Iterazioni)..."
for data in facebook enron amazon youtube er_facebook ba_facebook ba_enron ba_amazon ba_youtube
do
    python3 scripts/plot_doubling.py $data
done

echo "   -> Grafici Scalability Experiment (Nodi)..."
python3 scripts/plot_scale.py

echo ""
echo "========================================================="
echo "✅ ESPERIMENTO REPLICATO AL 100%!"
echo "Tutti i file CSV e i grafici PNG sono pronti."
echo "========================================================="