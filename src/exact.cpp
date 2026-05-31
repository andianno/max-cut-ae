#include <vector>
#include "../include/graph.h" // Il nostro contratto!

using namespace std;

// Funzione ricorsiva "nascosta" che fa il lavoro sporco dell'albero delle decisioni
void exact_max_cut_recursive(const Graph& G, int u, vector<bool>& in_A, int& best_cut) {
    // Caso base: abbiamo assegnato tutti i nodi (siamo in fondo all'albero)
    // u.size() è un warning se confrontato con size_t, ma in_A.size() è uguale a G.size()
    if ((size_t)u == G.size()) {
        int current_cut = calculate_cut(G, in_A); // La trova grazie a graph.h
        if (current_cut > best_cut) {
            best_cut = current_cut;
        }
        return;
    }

    // Ramo Sinistro: provo a mettere il nodo 'u' nel gruppo B (false)
    in_A[u] = false;
    exact_max_cut_recursive(G, u + 1, in_A, best_cut);
    
    // Ramo Destro: provo a mettere il nodo 'u' nel gruppo A (true)
    in_A[u] = true;
    exact_max_cut_recursive(G, u + 1, in_A, best_cut);
}

// 3. IL COMPETITOR ESATTO: Il "Muro" Brute Force
int exact_max_cut(const Graph& G) {
    int n = G.size();
    if (n == 0) return 0; // Protezione contro grafi vuoti
    vector<bool> in_A(n, false); // Vettore di partenza tutto a false
    int best_cut = 0;

    // OTTIMIZZAZIONE SIMMETRIA: Fissiamo il nodo 0 nel gruppo A (true)
    in_A[0] = true;
    
    // Faccio partire la ricorsione dal nodo 0
    exact_max_cut_recursive(G, 1, in_A, best_cut);
    
    return best_cut;
}