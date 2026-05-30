#include <random>
#include <vector>
#include "../include/graph.h" // Includiamo il nostro contratto!

using namespace std;

// 1. IL COMPETITOR: Randomized Max-Cut (Veloce ma rumoroso)
int randomized_max_cut(const Graph& G, int iterations) {
    int n = G.size();
    int best_cut = 0;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);

    for (int i = 0; i < iterations; ++i) {
        vector<bool> in_A(n);
        for (int u = 0; u < n; ++u) {
            in_A[u] = dis(gen); // Lancia la moneta
        }
        
        int current_cut = calculate_cut(G, in_A);
        if (current_cut > best_cut) {
            best_cut = current_cut;
        }
    }
    return best_cut;
}