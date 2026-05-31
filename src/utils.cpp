#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include "../include/graph.h" // Includiamo il nostro contratto!

using namespace std;

// Funzione di utilità per calcolare la grandezza del taglio
int calculate_cut(const Graph& G, const vector<bool>& in_A) {
    int cut_size = 0;
    for (size_t u = 0; u < G.size(); ++u) {
        if (in_A[u]) {
            for (int v : G[u]) {
                if (!in_A[v]) cut_size++;
            }
        }
    }
    return cut_size;
}

// Generatore di Istanze Random per il Doubling Experiment
Graph generate_random_graph(int n, double p) {
    Graph G(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (dis(gen) < p) {
                G[i].push_back(j);
                G[j].push_back(i);
            }
        }
    }
    return G;
}

// Parser robusto per i dataset SNAP di Stanford
Graph read_graph_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "ERRORE CRITICO: Impossibile aprire il file " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    int max_node_id = -1;
    vector<pair<int, int>> edges;

    // Fase 1: Scansione sicura del file
    while (getline(file, line)) {
        // Ignora righe vuote o commenti (iniziano con '#')
        if (line.empty() || line[0] == '#') continue;

        stringstream ss(line);
        int u, v;
        // Se riesce a leggere due interi correttamente
        if (ss >> u >> v) {
            edges.push_back({u, v});
            // Teniamo traccia dell'ID più alto per allocare la RAM correttamente
            max_node_id = max({max_node_id, u, v});
        }
    }
    file.close();

    // Fase 2: Allocazione sicura della Lista di Adiacenza
    // Dimensione = max_node_id + 1 (per includere lo zero)
    Graph G(max_node_id + 1);

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        
        // Popoliamo entrambe le direzioni (Grafo non orientato)
        G[u].push_back(v);
        G[v].push_back(u); 
    }

    cerr << "[INFO] Dataset caricato: " << filename << endl;
    cerr << "[INFO] Nodi (Max ID): " << max_node_id << " | Archi letti: " << edges.size() << endl;

    return G;
}