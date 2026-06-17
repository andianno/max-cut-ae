#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>
#include "../include/graph.h"

using namespace std;

int main(int argc, char *argv[])
{
    string dataset_name = "facebook";
    if (argc > 1) {
        dataset_name = argv[1];
    }

    string output_filepath = "results/" + dataset_name + "_d.csv";
    Graph G;

    cout << "=== Avvio Doubling Experiment (Iterazioni): " << dataset_name << " ===" << endl;

    // CARICAMENTO O GENERAZIONE SPECCHIATA
    if (dataset_name == "facebook") {
        G = read_graph_from_file("data/facebook_combined.txt");
    } else if (dataset_name == "enron") {
        G = read_graph_from_file("data/email-Enron.txt");
    } else if (dataset_name == "amazon") {
        G = read_graph_from_file("data/com-amazon.ungraph.txt");
    } else if (dataset_name == "youtube") {
        G = read_graph_from_file("data/com-youtube.ungraph.txt");
    } else if (dataset_name == "er_facebook") {
        G = generate_random_graph(4039, 0.0108);
    } else if (dataset_name == "er_enron") {
        G = generate_random_graph(36692, 0.0000108);
    } else if (dataset_name == "er_amazon") {
        G = generate_random_graph(334863, 0.0000165);
    } else if (dataset_name == "er_youtube") {
        G = generate_random_graph(1134890, 0.0000046);
    } else if (dataset_name == "ba_facebook") {
        G = generate_barabasi_albert_graph(4039, 22, 22);
    } else if (dataset_name == "ba_enron") {
        G = generate_barabasi_albert_graph(36692, 5, 5);
    } else if (dataset_name == "ba_amazon") {
        G = generate_barabasi_albert_graph(334863, 3, 3);
    } else if (dataset_name == "ba_youtube") {
        G = generate_barabasi_albert_graph(1134890, 3, 3);
    } else {
        cerr << "Errore: Dataset non riconosciuto." << endl;
        return 1;
    }

    ofstream out_file(output_filepath);
    if (!out_file.is_open()) {
        cerr << "Errore: Impossibile creare il file di output!" << endl;
        return 1;
    }

    out_file << "Iterazioni,Algoritmo,Taglio,CPU_Time\n";

    int iterations = 128; 
    int current_iterations = 1;
    int best_greedy_overall = 0;

    while (current_iterations <= iterations) {
        clock_t start_rand = clock();
        int rand_cut = randomized_max_cut(G, current_iterations);
        double time_rand = double(clock() - start_rand) / CLOCKS_PER_SEC;

        clock_t start_greedy = clock();
        int greedy_cut = local_search_max_cut(G, current_iterations);
        double time_greedy = double(clock() - start_greedy) / CLOCKS_PER_SEC;

        out_file << current_iterations << ",Random," << rand_cut << "," << time_rand << "\n";
        out_file << current_iterations << ",Greedy," << greedy_cut << "," << time_greedy << "\n";

        cout << "Iter: " << current_iterations << " | Taglio Greedy: " << greedy_cut << " | T_Greedy: " << time_greedy << " s" << endl;

        if (greedy_cut > best_greedy_overall) {
            best_greedy_overall = greedy_cut;
        }
        current_iterations *= 2;
    }

    out_file.close();
    cout << "\nEsperimento concluso! Dati salvati in: " << output_filepath << endl;
    return 0;
}