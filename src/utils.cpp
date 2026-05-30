#include <vector>
#include <random>
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