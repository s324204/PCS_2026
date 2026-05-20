//#include <iostream>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "fifo.hpp"
#include "lifo.hpp"
#include "graph_visit.hpp"
#include "dfs_ricorsivo.hpp"
#include "dijkstra.hpp"

int main() {
    // creo un grafo come quello mostrato a esercitazione
    undirected_graph<int> grafo;
    
    grafo.add_edge(1,2);
    grafo.add_edge(1,3);
    grafo.add_edge(1,4);
    grafo.add_edge(1,6);

    grafo.add_edge(2,4);
    grafo.add_edge(2,5);
    grafo.add_edge(2,7);

    grafo.add_edge(3,6);

    grafo.add_edge(4,6);
    grafo.add_edge(4,7);

    grafo.add_edge(5,7);

    grafo.add_edge(6,7);
    grafo.add_edge(6,8);

    grafo.add_edge(7,9);
    grafo.add_edge(8,9);


    // visita in ampiezza
    fifo<int> coda;
    auto visita_BFS = graph_visit(grafo, 1, coda); //albero
    std::cout << "Archi per cui siamo passati con la visita in ampiezza (BFS):" << std::endl;
    for (const auto& arco: visita_BFS.all_edges()) {
        std::cout << arco << std::endl;
    }
    
    // visita in profondità
    lifo<int> pila;
    auto visita_DFS = graph_visit(grafo, 1, pila);
    std::cout << "Archi per cui siamo passati con la visita in profondità (DFS):" << std::endl;
    for (const auto& arco: visita_DFS.all_edges()) {
        std::cout << arco << std::endl;
    }

    // visita col DFS ricorsivo
    std::set<int> visitati; //vuoto
    undirected_graph<int> albero_visita; //vuoto
    dfs_ricorsivo(grafo, 1, visitati, albero_visita);
    std::cout << "Archi visitati usando l'algoritmo ricorsivo di visita in profondità (DFS):" << std::endl;
    for (const auto& arco: albero_visita.all_edges()) {
        std::cout << arco << std::endl;
    }

    // Algoritmo Dijkstra
    // do dei pesi a caso ad ogni arco:
    std::map<undirected_edge<int>, double> pesi;
    pesi[undirected_edge<int>(1, 2)] = 2.0;
	pesi[undirected_edge<int>(1, 3)] = 5.0;
	pesi[undirected_edge<int>(1, 4)] = 9.0;
	pesi[undirected_edge<int>(1, 6)] = 12.0;
	
	pesi[undirected_edge<int>(2, 4)] = 4.0;
	pesi[undirected_edge<int>(2, 5)] = 3.0;
	pesi[undirected_edge<int>(2, 7)] = 8.0;
	
	pesi[undirected_edge<int>(3, 6)] = 4.0;
	
	pesi[undirected_edge<int>(4, 6)] = 3.0;
	pesi[undirected_edge<int>(4, 7)] = 1.0; 
	
	pesi[undirected_edge<int>(5, 7)] = 6.0;
	
	pesi[undirected_edge<int>(6, 7)] = 2.0;
	pesi[undirected_edge<int>(6, 8)] = 5.0;
	
	pesi[undirected_edge<int>(7, 9)] = 3.0;
	
	pesi[undirected_edge<int>(8, 9)] = 1.0;

    std::map<int,int> predecessori;
    std::map<int,double> distanze;
    int sorgente = 1;

    dijkstra(grafo, sorgente, pesi, predecessori, distanze);
    int nodo_finale = 9;
    int corrente = nodo_finale;
    std::vector<int> cammino;
    
    // risaliamo la catena dei predecessori all'indietro fino a tornare alla sorgente
    while (corrente != sorgente) {
        cammino.push_back(corrente);
        corrente = predecessori[corrente]; // aggiorno i predecessori
    }
    cammino.push_back(sorgente); // Aggiungiamo la sorgente alla fine del vettore

    // stampiamo il vettore cammino al contrario per leggerlo nel verso giusto (da 1 a 9)
    std::cout << "Cammino minimo con l'algoritmo Dijkstra: " << std::endl;
    for (int i = cammino.size() - 1; i >= 0; i--) {
        std::cout << cammino[i];
        if (i > 0) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl << "Costo totale del percorso: " << distanze[nodo_finale] << std::endl;

    return 0;
}