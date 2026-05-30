#include <vector>
#include <random>
#include "../include/graph.h" // Includiamo il nostro contratto!
using namespace std;

// 2. IL COMPETITOR: Greedy Local Search (Intelligente ma rischia ottimi locali)
int local_search_max_cut(const Graph& G) {
    int n = G.size();
    vector<bool> in_A(n);
    
    // Partenza casuale (Seed iniziale)
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    for (int u = 0; u < n; ++u) in_A[u] = dis(gen);

    bool improved = true;
    
    // Algorithmic Tuning: Early Abort se nessun nodo migliora il taglio
    while (improved) {
        improved = false;
        for (int u = 0; u < n; ++u) {
            int neighbors_in_A = 0;
            int neighbors_in_B = 0;
            
            // Sfruttiamo la Spatial Locality per scorrere i vicini velocemente
            for (int v : G[u]) {
                if (in_A[v]) neighbors_in_A++;
                else neighbors_in_B++;
            }
            
            // Mossa Greedy: sposta il nodo se conviene
            if (in_A[u] && neighbors_in_A > neighbors_in_B) {
                in_A[u] = false;
                improved = true;
            } else if (!in_A[u] && neighbors_in_B > neighbors_in_A) {
                in_A[u] = true;
                improved = true;
            }
        }
    }
    return calculate_cut(G, in_A);
}