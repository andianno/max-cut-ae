#include <iostream>
#include <vector>
#include <ctime>
#include "../include/graph.h" // Includiamo il nostro contratto!

using namespace std;

int main() {
    cout << "N_Nodi,Algo,Taglio,CPU_Time_sec" << endl;

    // ATTENZIONE: Dimensioni piccolissime per l'Algoritmo Esatto
    // Già a 30 nodi potrebbe metterci diversi secondi o minuti.
    vector<int> sizes = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28}; 
    double density = 0.5; // Grafo molto denso per metterlo sotto stress
    int iterazioni = 100; //appositamente basso per vedere la qualità del taglio anche con poche iterazioni
    int baseline_iter = 1;// Iterazioni per Randomized e Local Search (basso per vedere la qualità del taglio anche con poche iterazioni) 

    for (int n : sizes) {
        Graph G = generate_random_graph(n, density);
        
        // 1. Corsa Randomized
        clock_t start = clock();
        int cut = randomized_max_cut(G, baseline_iter);
        double time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << n << ",Random," << cut << "," << time << endl;

        // 2. Corsa Local Search
        start = clock();
        cut = local_search_max_cut(G, baseline_iter);
        time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << n << ",LocalSearch," << cut << "," << time << endl;

        // 3. Corsa EXACT (Il mostro esponenziale)
        start = clock();
        cut = exact_max_cut(G);
        time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << n << ",Exact," << cut << "," << time << endl;

        // 4. Corsa Randomized high iterations (per vedere la qualità del taglio con più iterazioni)
        start = clock();
        cut = randomized_max_cut(G, iterazioni);
        time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << n << ",Random " << iterazioni << " iterations," << cut << "," << time << endl;

        // 5. Corsa Local Search high iterations (per vedere la qualità del taglio con più iterazioni)
        start = clock();
        cut = local_search_max_cut(G, iterazioni);
        time = double(clock() - start) / CLOCKS_PER_SEC;
        cout << n << ",LocalSearch " << iterazioni << " iterations," << cut << "," << time << endl;
    }

    return 0;
}