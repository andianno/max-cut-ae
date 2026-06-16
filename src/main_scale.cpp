#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include "../include/graph.h"

using namespace std;

int main() {
    string output_filepath = "results/scalability_nodes.csv";
    ofstream out_file(output_filepath);
    
    if (!out_file.is_open()) {
        cerr << "Errore: Impossibile creare il file di output!" << endl;
        return 1;
    }

    // Intestazione
    out_file << "N_Nodi,Topologia,Algoritmo,CPU_Time\n";

    int max_nodes = 64000;
    int iterazioni_fisse = 10; // Fissiamo le iterazioni per isolare il peso della dimensione del grafo

    cout << "=== Avvio Scalability Experiment (Raddoppio dei Nodi) ===" << endl;

    for (int n = 1000; n <= max_nodes; n *= 2) {
        cout << "Test su N = " << n << " nodi in corso..." << endl;

        // 1. Test su Modello Erdős-Rényi
        // Manteniamo il grado medio costante a 10 riducendo la probabilità man mano che il grafo cresce
        double p = 10.0 / n; 
        Graph G_ER = generate_random_graph(n, p);
        
        clock_t start = clock();
        randomized_max_cut(G_ER, iterazioni_fisse);
        double time_rand_er = double(clock() - start) / CLOCKS_PER_SEC;
        out_file << n << ",Erdos-Renyi,Random," << time_rand_er << "\n";

        start = clock();
        local_search_max_cut(G_ER, iterazioni_fisse);
        double time_greedy_er = double(clock() - start) / CLOCKS_PER_SEC;
        out_file << n << ",Erdos-Renyi,Greedy," << time_greedy_er << "\n";

        // 2. Test su Modello Barabási-Albert
        // Parametri m0 e m fissi per simulare una rete scale-free standard
        Graph G_BA = generate_barabasi_albert_graph(n, 5, 5);
        
        start = clock();
        randomized_max_cut(G_BA, iterazioni_fisse);
        double time_rand_ba = double(clock() - start) / CLOCKS_PER_SEC;
        out_file << n << ",Barabasi-Albert,Random," << time_rand_ba << "\n";

        start = clock();
        local_search_max_cut(G_BA, iterazioni_fisse);
        double time_greedy_ba = double(clock() - start) / CLOCKS_PER_SEC;
        out_file << n << ",Barabasi-Albert,Greedy," << time_greedy_ba << "\n";
    }

    out_file.close();
    cout << "\nEsperimento sulla Scalabilità concluso! Dati salvati in: " << output_filepath << endl;
    return 0;
}