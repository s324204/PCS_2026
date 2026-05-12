#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"

int main() {
    // creo un grafo vuoto e qualche arco
    undirected_graph<int> grafo;
    undirected_edge<int> a1(2,1);

    // lo riempio aggiungendo archi col metodo add_edge()
    // 2. add_edge()
    grafo.add_edge(a1.from(), a1.to());
    grafo.add_edge(3,1);
    grafo.add_edge(4,5);

    // 3. stampo tutti gli archi = vettore di archi
    std::vector<undirected_edge<int>> tutti_archi = grafo.all_edges(); // questo metodo, per come l'hai implementato, ti restiutisce un vettore di archi
    int n = tutti_archi.size();
    std::cout << "Tutti gli archi:" << std::endl;
    for (int i=0; i<n; i++) {
        std::cout << tutti_archi[i] << std::endl; //tutti_archi[i] è un arco e con '<<' lo stampiamo
    }

    // 4. stampo tutti i nodi = set
    std::set<int> tutti_nodi = grafo.all_nodes(); // questo metodo, per come l'hai implementato, ti restiutisce un set
    std::cout << "Tutti i nodi:" << std::endl;
    for (auto itor = tutti_nodi.begin(); itor != tutti_nodi.end(); itor++) {
        std::cout << *itor << std::endl; // mentre (*itor).tutti_nodi cercherebbe di accede ad una proprietà chiamata tuttu u nodi dentro ad un intero che è *itor
    }

    // 1. neighbours() --> set
    std::set<int> vicini_1 = grafo.neighbours(1);
    std::cout << "I vicini di 1 sono: " << std::endl;
    for (auto itor = vicini_1.begin(); itor != vicini_1.end(); itor++) {
        std::cout << *itor << std::endl; // mentre (*itor).tutti_nodi cercherebbe di accede ad una proprietà chiamata tuttu u nodi dentro ad un intero che è *itor
    }

    // 5. edge_number()
    undirected_edge<int> arco_4_5(4,5);
    int enumerazione_arco_4_5 = grafo.edge_number(arco_4_5);
    std::cout << "L'arco (4,5) è all'indice " << enumerazione_arco_4_5 << " nel vettore di archi" << std::endl;

    // 6. edge_at()
    undirected_edge<int> arco_at_1 = grafo.edge_at(1);
    std::cout << "L'arco all'indice 1 è " << arco_at_1 << std::endl;

    // 7. operator-()
    undirected_graph<int> grafo2;
    grafo2.add_edge(3,1); //c'è anche in grafo
    grafo2.add_edge(2,5); //non c'è in grafo
    undirected_graph<int> diff1_2 = grafo - grafo2;
    std::vector<undirected_edge<int>> archi_diff1_2 = diff1_2.all_edges(); // questo metodo, per come l'hai implementato, ti restiutisce un vettore di archi
    int m = archi_diff1_2.size();
    std::cout << "Gli archi del grafo differenza sono:" << std::endl;
    for (int i=0; i<m; i++) {
        std::cout << archi_diff1_2[i] << std::endl; //tutti_archi[i] è un arco e con '<<' lo stampiamo
    }

    return EXIT_SUCCESS;
}