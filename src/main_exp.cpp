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

    string output_filepath = "results/" + dataset_name + ".csv";
    Graph G;

    cout << "=== Avvio Esperimento Max-Cut: " << dataset_name << " ===" << endl;

    // 2. LOGICA DI CARICAMENTO E SPECCHIAMENTO DEI PARAMETRI
    // --- DATASET REALI ---
    if (dataset_name == "facebook") {
        G = read_graph_from_file("data/facebook_combined.txt"); 
    } else if (dataset_name == "enron") {
        G = read_graph_from_file("data/email-Enron.txt");
    } else if (dataset_name == "amazon") {
        G = read_graph_from_file("data/com-amazon.ungraph.txt");
    } else if (dataset_name == "youtube") {
        G = read_graph_from_file("data/com-youtube.ungraph.txt");
    }
    // --- MODELLI ERDŐS-RÉNYI (Specchiati sui reali) ---
    else if (dataset_name == "er_facebook") {
        cout << "[SYNTHETIC] Generazione Erdős-Rényi specchiato su Facebook (N=4039, p=0.0108)..." << endl;
        G = generate_random_graph(4039, 0.0108);
    } else if (dataset_name == "er_enron") {
        cout << "[SYNTHETIC] Generazione Erdős-Rényi specchiato su Enron (N=36692, p=0.0000108)..." << endl;
        G = generate_random_graph(36692, 0.0000108);
    } else if (dataset_name == "er_amazon") {
        cout << "[SYNTHETIC] Generazione Erdős-Rényi specchiato su Amazon (N=334863, p=0.0000165)..." << endl;
        G = generate_random_graph(334863, 0.0000165);
    } else if (dataset_name == "er_youtube") {
        cout << "[SYNTHETIC] Generazione Erdős-Rényi specchiato su YouTube (N=1134890, p=0.0000046)..." << endl;
        G = generate_random_graph(1134890, 0.0000046);
    }
    // --- MODELLI BARABÁSI-ALBERT (Specchiati sui reali) ---
    else if (dataset_name == "ba_facebook") {
        cout << "[SYNTHETIC] Generazione Barabási-Albert specchiato su Facebook (N=4039, m=22)..." << endl;
        G = generate_barabasi_albert_graph(4039, 22, 22);
    } else if (dataset_name == "ba_enron") {
        cout << "[SYNTHETIC] Generazione Barabási-Albert specchiato su Enron (N=36692, m=5)..." << endl;
        G = generate_barabasi_albert_graph(36692, 5, 5);
    } else if (dataset_name == "ba_amazon") {
        cout << "[SYNTHETIC] Generazione Barabási-Albert specchiato su Amazon (N=334863, m=3)..." << endl;
        G = generate_barabasi_albert_graph(334863, 3, 3);
    } else if (dataset_name == "ba_youtube") {
        cout << "[SYNTHETIC] Generazione Barabási-Albert specchiato su YouTube (N=1134890, m=3)..." << endl;
        G = generate_barabasi_albert_graph(1134890, 3, 3);
    } 
    else {
        cerr << "Errore: Dataset o Modello non riconosciuto!" << endl;
        return 1;
    }

    // 3. PREPARAZIONE DEL FILE CSV DI OUTPUT
    ofstream out_file(output_filepath);
    if (!out_file.is_open()) {
        cerr << "Errore: Impossibile creare il file di output!" << endl;
        return 1;
    }
    
    out_file << "Iterazioni,Algoritmo,Taglio,CPU_Time\n";

    // 4. LOGICA DI EARLY STOPPING (PAZIENZA)
    int min_iterations = 25;
    int current_iterations = 1; 
    int max_patience = 5;       
    int patience_counter = 0;
    int best_greedy_overall = 0;

    cout << "Inizio testing iterativo su " << dataset_name << "...\n" << endl;

    while (patience_counter < max_patience || current_iterations < min_iterations) {
        
        // --- 5. ESECUZIONE E MISURAZIONE RANDOM ---
        clock_t start_rand = clock();
        int rand_cut = randomized_max_cut(G, current_iterations);
        double time_rand = double(clock() - start_rand) / CLOCKS_PER_SEC;

        // --- 6. ESECUZIONE E MISURAZIONE GREEDY ---
        clock_t start_greedy = clock();
        int greedy_cut = local_search_max_cut(G, current_iterations);
        double time_greedy = double(clock() - start_greedy) / CLOCKS_PER_SEC;

        // --- 7. SCRITTURA SU CSV ---
        out_file << current_iterations << ",Random," << rand_cut << "," << time_rand << "\n";
        out_file << current_iterations << ",Greedy," << greedy_cut << "," << time_greedy << "\n";
        
        // Log a schermo per la telemetria in diretta
        cout << "Iter: " << current_iterations 
             << " | Taglio Greedy: " << greedy_cut 
             << " | T_Greedy: " << time_greedy << " s"
             << " | Pazienza: " << (max_patience - patience_counter) << endl;

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