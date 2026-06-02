#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "../include/graph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // 1. PARSING DEGLI ARGOMENTI
    string dataset_name = "facebook"; 
    
    if (argc > 1) {
        dataset_name = argv[1];
    }

    string input_filepath;
    string output_filepath = "results/" + dataset_name + ".csv";

    if (dataset_name == "facebook") {
        input_filepath = "data/facebook_combined.txt"; 
    } else if (dataset_name == "amazon") {
        input_filepath = "data/com-amazon.ungraph.txt";
    } else if (dataset_name == "youtube") {
        input_filepath = "data/com-youtube.ungraph.txt";
    } else {
        cerr << "Errore: Dataset non riconosciuto." << endl;
        return 1;
    }

    cout << "=== Avvio Esperimento Max-Cut sui Dataset ===" << endl;
    
    Graph G = read_graph_from_file(input_filepath);

    // 2. PREPARAZIONE DEL FILE CSV DI OUTPUT
    ofstream out_file(output_filepath);
    if (!out_file.is_open()) {
        cerr << "Errore: Impossibile creare il file di output!" << endl;
        return 1;
    }
    
    // INTESTAZIONE (CPU_Time in secondi)
    out_file << "Iterazioni,Algoritmo,Taglio,CPU_Time\n";

    // 3. LOGICA DI EARLY STOPPING (PAZIENZA)
    int min_iterations = 50;
    int current_iterations = 1; 
    int max_patience = 5;       
    int patience_counter = 0;
    int best_greedy_overall = 0;

    cout << "Inizio testing iterativo su " << dataset_name << "...\n" << endl;

    while (patience_counter < max_patience || current_iterations < min_iterations) {
        
        // --- 4. ESECUZIONE E MISURAZIONE RANDOM ---
        clock_t start_rand = clock();
        int rand_cut = randomized_max_cut(G, current_iterations);
        clock_t end_rand = clock();
        double time_rand = double(end_rand - start_rand) / CLOCKS_PER_SEC;

        // --- 5. ESECUZIONE E MISURAZIONE GREEDY ---
        clock_t start_greedy = clock();
        int greedy_cut = local_search_max_cut(G, current_iterations);
        clock_t end_greedy = clock();
        double time_greedy = double(end_greedy - start_greedy) / CLOCKS_PER_SEC;

        // --- 6. SCRITTURA SU CSV ---
        out_file << current_iterations << ",Random," << rand_cut << "," << time_rand << "\n";
        out_file << current_iterations << ",Greedy," << greedy_cut << "," << time_greedy << "\n";
        
        // Log a schermo per la telemetria in diretta
        cout << "Iter: " << current_iterations 
             << " | Taglio Greedy: " << greedy_cut 
             << " | T_Greedy: " << time_greedy << " s"
             << " | Pazienza: " << (max_patience - patience_counter) << endl;

        // 7. CONTROLLO DELLO STALLO (Sempre basato sul Greedy)
        if (greedy_cut > best_greedy_overall) {
            best_greedy_overall = greedy_cut;
            patience_counter = 0; 
        } else {
            patience_counter++;   
        }

        current_iterations += 1; 
    }

    out_file.close();
    cout << "\nEsperimento concluso! Dati salvati in: " << output_filepath << endl;

    return 0;
}