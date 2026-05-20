#pragma once
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
// lifo - pila - dfs (profondità)

// mi sa che non usa una lifo --> sfrutta lo stack delle chiamate del sistema (Call Stack): ogni volta che una funzione chiama se stessa, 
// il computer "salva" automaticamente lo stato corrente in una pila invisibile e ci ritorna quando la funzione figlia termina.

// nel main dovrò creare reached e albero_visita, che se lo stamperò alla fine mi darà la visita!
template<typename T> // perché void??
void dfs_ricorsivo(const undirected_graph<T>& grafo, const T& v0, std::set<T>& reached, undirected_graph<T>& albero_visita) {
    reached.insert(v0);
    for (const T& w : grafo.neighbours(v0)) { // per ogni w vicino di v0
        if (reached.find(w) == reached.end()) { // se non lo trova
            albero_visita.add_edge(v0,w);
            dfs_ricorsivo(grafo, w, reached, albero_visita);
        }
    }
    //return albero_visita; //non returnare niente??
    // la funzione è void perché modifica albero_visita per riferimento
};