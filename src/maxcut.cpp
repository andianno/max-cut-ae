#include <iostream>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

// Struttura dati ottimizzata per la Cache (Adjacency List)
typedef vector<vector<int>> Graph;

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

int main() {
    // Intestazione del CSV per facilitare il parsing in Python
    cout << "N_Nodi,Algo,Taglio,CPU_Time_sec" << endl;

    // Impostazioni del Doubling Experiment
    vector<int> sizes = {500, 1000, 2000, 4000};
    double density = 0.05; 
    int iterazioni_random = 100; // Parametro I di Tuning

    for (int n : sizes) {
        Graph G = generate_random_graph(n, density);
        
        // --- Corsa 1: Randomized ---
        clock_t start_rand = clock();
        int cut_rand = randomized_max_cut(G, iterazioni_random);
        clock_t end_rand = clock();
        double time_rand = double(end_rand - start_rand) / CLOCKS_PER_SEC;
        
        cout << n << ",Random," << cut_rand << "," << time_rand << endl;

        // --- Corsa 2: Local Search ---
        clock_t start_ls = clock();
        int cut_ls = local_search_max_cut(G);
        clock_t end_ls = clock();
        double time_ls = double(end_ls - start_ls) / CLOCKS_PER_SEC;
        
        cout << n << ",LocalSearch," << cut_ls << "," << time_ls << endl;
    }

    return 0;
}