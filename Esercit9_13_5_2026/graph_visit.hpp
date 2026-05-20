#pragma once
#include <list>
#include <set>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "fifo.hpp"
#include "lifo.hpp"

// fifo - coda - bfs (ampiezza)       ----       lifo - pila - dfs (profondità)

/* Si implementi una SINGOLA funzione template graph_visit() che:
• Prende in input due parametri, il grafo da visitare ed il nodo sorgente;
• Prende un parametro template che specifica il tipo del contenitore da usare per effettuare la visita;
• Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita. La funzione, in base al contenitore passato come 
  parametro, deve effettuare una visita in ampiezza (BFS) oppure una visita in profondità (DFS). 
  Si ottengano le immagini dei due grafi usando GraphViz e si verifichi che è stata effettuata la visita richiesta. */

// nel main specifichi contenitore per la visita (lifo o fifo): lifo/fifo  s/q
template<typename T, typename container>                         // v0 sarà int (=val del nodo)
undirected_graph<T> graph_visit(const undirected_graph<T>& grafo, const T& v0, container& contenitore) {
  
  undirected_graph<T> albero_visita;
  
  std::set<T> reached; //x nodi; perché non vettore di true e false? --> xké è più difficile??! ma più efficiente: O(1)
    //vincolo su indici: se il grafo avesse nodi sparsi (es. tre nodi con ID 1, 500, 10000), il vettore dovrebbe allocare spazio 
    // fino all'indice 10000, sprecando memoria per gli indici intermedi inutilizzati.
  
  contenitore.put(v0); //inseriamo il nodo di partenza nella coda/pila
  reached.insert(v0); // e inseriamolo anche nella lista dei visitati
  
  while (!contenitore.empty()) {
    T u = contenitore.get(); // estraggo nodo secondo lifo/fifo
    if (reached.find(u) == reached.end()) { // se non lo trova
        reached.insert(u);
    }
    //for (const auto& w : lista_adiacenza[u])
    for (const T& w : grafo.neighbours(u)) { // per ogni nodo w vicino di u
      if (reached.find(w) == reached.end()) { // se non lo trova
        reached.insert(w);
        albero_visita.add_edge(u,w); //aggiungo arco all'albero (con put xké albero è undirected_graph)
        contenitore.put(w);
      }
    }
  }
  return albero_visita;
};