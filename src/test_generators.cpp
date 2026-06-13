#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "../include/graph.h"

using namespace std;

// --- 1. Controlli di Integrità Strutturale (Sanity Checks) ---
bool run_sanity_checks(const Graph& G, const string& nome_modello) {
    bool passed = true;
    for (size_t u = 0; u < G.size(); ++u) {
        vector<int> vicini = G[u];
        
        // Controllo A: Nessun nodo deve essere collegato a se stesso (Auto-anelli)
        if (find(vicini.begin(), vicini.end(), u) != vicini.end()) {
            cerr << "[ERRORE] " << nome_modello << ": Trovato auto-anello sul nodo " << u << endl;
            passed = false;
        }
        
        // Controllo B: Non devono esserci due archi identici tra gli stessi due nodi
        sort(vicini.begin(), vicini.end());
        auto it = adjacent_find(vicini.begin(), vicini.end());
        if (it != vicini.end()) {
            cerr << "[ERRORE] " << nome_modello << ": Trovato arco duplicato tra " << u << " e " << *it << endl;
            passed = false;
        }
    }
    return passed;
}

// --- 2. Test per il Modello Erdős-Rényi ---
void test_erdos_renyi() {
    cout << "\n--- TEST ERDOS-RENYI ---" << endl;
    int n = 1000;
    double p = 0.5;
    
    Graph G = generate_random_graph(n, p);
    
    int archi_totali = 0;
    for (const auto& vicini : G) {
        archi_totali += vicini.size();
    }
    archi_totali /= 2; // Dividiamo per 2 perché il grafo è non orientato
    
    // Calcolo teorico di quanti archi dovremmo avere
    int combinazioni_possibili = (n * (n - 1)) / 2;
    int archi_attesi = combinazioni_possibili * p;
    
    cout << "Nodi: " << n << " | Probabilita' (p): " << p << endl;
    cout << "Archi attesi teorici: " << archi_attesi << endl;
    cout << "Archi effettivi generati: " << archi_totali << endl;
    
    // Verifichiamo che l'errore sia entro un margine di tolleranza ristretto (es. 5%)
    if (abs(archi_totali - archi_attesi) < (archi_attesi * 0.05)) {
        cout << "[PASS] Il volume degli archi rispetta la distribuzione statistica." << endl;
    } else {
        cout << "[FAIL] Anomalia statistica nel lancio della moneta!" << endl;
    }
    
    if (run_sanity_checks(G, "Erdos-Renyi")) {
        cout << "[PASS] Nessun auto-anello o arco duplicato rilevato." << endl;
    }
}

// --- 3. Test per il Modello Barabási-Albert ---
void test_barabasi_albert() {
    cout << "\n--- TEST BARABASI-ALBERT ---" << endl;
    int n = 10000; // Creiamo una rete bella grande per far emergere la legge di potenza
    int m0 = 5;
    int m = 5;
    
    Graph G = generate_barabasi_albert_graph(n, m0, m);
    
    // Esportiamo i dati in CSV per poterli tracciare in Python (Log-Log plot)
    string filename = "results/ba_degrees.csv";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "[ERRORE] Impossibile creare il file CSV in ../results/" << endl;
        return;
    }
    
    file << "NodeID,Degree\n";
    int archi_totali = 0;
    for (int i = 0; i < n; ++i) {
        file << i << "," << G[i].size() << "\n";
        archi_totali += G[i].size();
    }
    file.close();
    archi_totali /= 2;
    
    cout << "Nodi: " << n << " | Nodi Iniziali (m0): " << m0 << " | Nuovi Archi (m): " << m << endl;
    cout << "Archi totali generati: " << archi_totali << endl;
    cout << "[INFO] Dati esportati con successo in " << filename << endl;
    cout << "[INFO] Usare Python per verificare graficamente la Legge di Potenza (linea retta decrescente)." << endl;
    
    if (run_sanity_checks(G, "Barabasi-Albert")) {
        cout << "[PASS] Nessun auto-anello o arco duplicato rilevato." << endl;
    }
}

// --- 4. Main ---
int main() {
    cout << "=== AVVIO SUITE DI VALIDAZIONE DEI GENERATORI ===" << endl;
    test_erdos_renyi();
    test_barabasi_albert();
    cout << "\n=== VALIDAZIONE COMPLETATA ===" << endl;
    return 0;
}