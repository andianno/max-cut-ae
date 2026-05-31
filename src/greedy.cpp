#include <vector>
#include <random>
#include "../include/graph.h" 

using namespace std;

// 2. IL COMPETITOR: Multi-Start Greedy Local Search (Esplorazione + Sfruttamento)
int local_search_max_cut(const Graph& G, int iterations) {
    int n = G.size();
    int best_cut_overall = 0;
    
    // Setup del generatore casuale
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    // Eseguiamo l'algoritmo K volte partendo da punti diversi
    for (int i = 0; i < iterations; ++i) {
        vector<bool> in_A(n);
        
        // 1. Fase di Esplorazione: Partenza casuale per questa iterazione
        for (int u = 0; u < n; ++u) in_A[u] = dis(gen);

        bool improved = true;
        
        // 2. Fase di Sfruttamento: Scaliamo la collina locale
        while (improved) {
            improved = false;
            for (int u = 0; u < n; ++u) {
                int neighbors_in_A = 0;
                int neighbors_in_B = 0;
                
                for (int v : G[u]) {
                    if (in_A[v]) neighbors_in_A++;
                    else neighbors_in_B++;
                }
                
                if (in_A[u] && neighbors_in_A > neighbors_in_B) {
                    in_A[u] = false;
                    improved = true;
                } else if (!in_A[u] && neighbors_in_B > neighbors_in_A) {
                    in_A[u] = true;
                    improved = true;
                }
            }
        }
        
        // 3. Valutazione: Confrontiamo la vetta raggiunta col record globale
        int current_cut = calculate_cut(G, in_A);
        if (current_cut > best_cut_overall) {
            best_cut_overall = current_cut;
        }
    }
    
    return best_cut_overall;
}