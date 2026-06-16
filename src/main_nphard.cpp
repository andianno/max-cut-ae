#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include "../include/graph.h" // Includiamo il nostro contratto!

using namespace std;

// Funzione di supporto per eseguire tutti i test su un singolo grafo
void run_suite(const Graph& G, int n, const string& topologia, int baseline_iter, int iterazioni) {
    // 1. Corsa Randomized
    clock_t start = clock();
    int cut = randomized_max_cut(G, baseline_iter);
    double time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << n << "," << topologia << ",Random," << cut << "," << time << endl;

    // 2. Corsa Local Search
    start = clock();
    cut = local_search_max_cut(G, baseline_iter);
    time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << n << "," << topologia << ",LocalSearch," << cut << "," << time << endl;

    // 3. Corsa EXACT (Il mostro esponenziale)
    start = clock();
    cut = exact_max_cut(G);
    time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << n << "," << topologia << ",Exact," << cut << "," << time << endl;

    // 4. Corsa Randomized high iterations
    start = clock();
    cut = randomized_max_cut(G, iterazioni);
    time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << n << "," << topologia << ",Random " << iterazioni << " iterations," << cut << "," << time << endl;

    // 5. Corsa Local Search high iterations
    start = clock();
    cut = local_search_max_cut(G, iterazioni);
    time = double(clock() - start) / CLOCKS_PER_SEC;
    cout << n << "," << topologia << ",LocalSearch " << iterazioni << " iterations," << cut << "," << time << endl;
}

int main() {
    // Aggiunta la colonna Topologia per distinguere i due generatori
    cout << "N_Nodi,Topologia,Algo,Taglio,CPU_Time_sec" << endl;

    // Dimensioni piccolissime per l'Algoritmo Esatto
    vector<int> sizes = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}; 
    
    // Parametri per Erdős-Rényi
    double density = 0.5; 
    
    // Parametri per Barabási-Albert
    // Essendo grafi molto piccoli (partono da 10), impostiamo un nucleo e un grado iniziale bassi
    int m0 = 4; 
    int m = 4;  
    
    int iterazioni = 100;
    int baseline_iter = 1;

    for (int n : sizes) {
        // Generazione e test Modello Erdős-Rényi
        Graph G_ER = generate_random_graph(n, density);
        run_suite(G_ER, n, "Erdos-Renyi", baseline_iter, iterazioni);
        
        // Generazione e test Modello Barabási-Albert
        Graph G_BA = generate_barabasi_albert_graph(n, m0, m);
        run_suite(G_BA, n, "Barabasi-Albert", baseline_iter, iterazioni);
    }

    return 0;
}