#ifndef GRAPH_H  // Header Guard: impedisce di includerlo due volte
#define GRAPH_H

#include <vector>
#include <string>

// Definiamo il tipo Graph una volta sola per tutto il progetto
typedef std::vector<std::vector<int>> Graph;

// --- Funzioni di Utilità (staranno in utils.cpp) ---
int calculate_cut(const Graph& G, const std::vector<bool>& in_A);
Graph generate_random_graph(int n, double p);
Graph read_graph_from_file(const std::string& filename);
Graph generate_barabasi_albert_graph(int n, int m0, int m);

// --- Algoritmi (staranno nei rispettivi .cpp) ---
int randomized_max_cut(const Graph& G, int iterations);
int local_search_max_cut(const Graph& G, int iterations);
int exact_max_cut(const Graph& G);

#endif