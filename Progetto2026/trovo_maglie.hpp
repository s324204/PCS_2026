#pragma once
#include <iostream>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "graph_visit.hpp"
#include "lifo.hpp"
#include <algorithm> // per sort, min
#include "dijkstra.hpp"
#include <cmath> // per INFINITY

// Costruire sistema=matrice per trovare le correnti e poi V=RI con:
// • L’elemento diagonale A(i,i) si ottiene come:
//   A(i,i) = sommatoria di tutte le resistenze della maglia i
// • L’elemento fuori diagonale A(i,j), con i ̸= j, si ottiene come:
//   A(i,j) = −(sommatoria delle resistenze condivise tra le maglie i e j)

//posso calcolare le maglie con la DFS (cicli minimi e non)
template<typename T>
bool findpath(const undirected_graph<T>& tree, const T& u, const T& v, std::set<T>& visited, std::vector<T>& percorso) {
    //se def qui visited e percorso si azzerano ogni volta --> li do in input
    visited.insert(u); 
    percorso.push_back(u);

    if (u==v) {
        return true;
    }
    // per set, map, list: .find(elem) trova l'iteratore (la "poszione" di elem); 
    // per vector: std::find(archi.begin() = iteratore all'inizio, archi.end()  = iteratore alla fine, nuovo_arco = cosa dobbiamo trovare)
    for (const T& w: tree.neighbours(u)) {
        if (visited.find(w) == visited.end()) { //se w non è stato visitato
            if (findpath(tree, w, v, visited, percorso)) {
                return true;
            }
        }
    }
    percorso.pop_back();
    return false;
};

template<typename T> // lista di (|E|-|V|+1) cicli
std::vector<std::vector<T>> maglie_dfs(const undirected_graph<T>& grafo) {
    std::vector<std::vector<T>> maglie;
    lifo<T> pila;
    std::set<T> nodi = grafo.all_nodes();
    T v0 = *(nodi.begin()); // parte dal primo nodo, ma è indifferente tanto vogliamo trovare tutte le maglie
    undirected_graph<T> tree = graph_visit(grafo, v0, pila); // tree col dfs
    undirected_graph<T> coalbero = grafo-tree;
    std::vector<undirected_edge<T>> archi_coalbero = coalbero.all_edges();
    int n=archi_coalbero.size();
    for (int i=0; i<n; i++) { // per ogni arco nel coalbero
        T& u=archi_coalbero[i].from();
        T& v=archi_coalbero[i].to();
        std::set<T> visited; 
        std::vector<T> percorso;
        //cerca il percorso anche nell'albero tree
        if (findpath(tree, u, v, visited, percorso)) { //se è vera findpath
            percorso.push_back(u);
            maglie.push_back(percorso);
        }
    }
    return maglie; // se non esiste un cammino, restituisce un vettore vuoto
};



//Ora troviamo le maglie che sono cicli minimi --> De Pina
template<typename T>
std::map<std::vector<T>, std::vector<int>> de_pina(const undirected_graph<T>& grafo) {
    std::set<T> nodi = grafo.all_nodes();
    int num_nodi = nodi.size();
    T u = *(nodi.begin());
    lifo<T> pila;
    undirected_graph<T> tree = graph_visit(grafo, u, pila); // tree col dfs
    undirected_graph<T> coalbero = grafo-tree;
    std::vector<undirected_edge<T>> archi_coalbero = coalbero.all_edges();
    
    std::vector<undirected_edge<T>> archi_grafo = grafo.all_edges();
    // ordino in modo lessicografico gli archi all'interno del vettore degli archi di coalbero
    std::sort(archi_grafo.begin(), archi_grafo.end());
    int n = archi_grafo.size();
    int k = archi_coalbero.size();

    // definisco cosa c'è dentro S: ogni elemento di S è un vettore S_j
    std::vector<std::vector<int>> S;
    for (int j=0; j<k; j++) {
        std::vector<int> S_j(n,0); //li poniamo tutti uguali a zero all'inizio
        S.push_back(S_j);
    }
    
    // costruzione dei vettori S_j
    std::vector<int> inseriti;
    for (int j=0; j<k; j++) { // per ogni S_j in S
        for (int i=0; i<n; i++) { // per ogni arco del grafo
            if (std::find(inseriti.begin(), inseriti.end(), i) == inseriti.end()) { // se i non appartiene a inseriti
                if (std::find(archi_coalbero.begin(), archi_coalbero.end(), archi_grafo[i]) != archi_coalbero.end()) {
                    (S[j])[i]=1;
                    inseriti.push_back(i);
                    i=n;
                    // esce dal ciclo degli i ed entra in quello dei j, passando quindi al S_j successivo (j+1)
                }
            }
        }
    }
// ora abbiamo ufficialmente creato gli S_j


//adesso creaimo G' grafo ausiliario che continee tutti i nodi, originali e duplicati
    std::map<std::vector<T>, std::vector<int>> mappa;
    std::vector<std::vector<int>> B;
    for (int j=0; j<k; j++) { // per ogni S[j] in S
        undirected_graph<T> grafo2;
        std::map<undirected_edge<T>, double> pesi;
        for (int i=0; i<n; i++) { // per ogni arco del grafo
            if ((S[j])[i]==1) {                                     //supponiamo che i nodi siano INTERI !!!
                grafo2.add_edge(archi_grafo[i].from(), archi_grafo[i].to() + num_nodi); // (u+, v-)
                pesi[undirected_edge<int>(archi_grafo[i].from(), archi_grafo[i].to() + num_nodi)] = 1.0;
                grafo2.add_edge(archi_grafo[i].from() + num_nodi, archi_grafo[i].to()); // (u-, v+)
                pesi[undirected_edge<int>(archi_grafo[i].from() + num_nodi, archi_grafo[i].to())] = 1.0;
            }
            else {
                grafo2.add_edge(archi_grafo[i].from(), archi_grafo[i].to()); // (u+, v+)
                pesi[undirected_edge<int>(archi_grafo[i].from(), archi_grafo[i].to())] = 1.0;
                grafo2.add_edge(archi_grafo[i].from() + num_nodi, archi_grafo[i].to() + num_nodi); // (u-, v-)
                pesi[undirected_edge<int>(archi_grafo[i].from() + num_nodi, archi_grafo[i].to() + num_nodi)] = 1.0;
            }
        }


        // per ogni nodo v del grafo, trovo cammino minimo tra v+ e v- con Dijkstra (che nel grafo "originale" corrisponde ad un ciclo):
        std::vector<std::vector<T>> cammini_minimi; //metterò qua il cammino minimo di ogni nodo di grafo2 = G'
        
        for (const T& v: grafo.all_nodes()) { // per ogni nodo del grafo
            T sorgente = v + num_nodi; //sarebbe la nostra v-
            std::map<T,T> predecessori;
            std::map<T,double> distanze;
            dijkstra(grafo2, sorgente, pesi, predecessori, distanze);
            T nodo_finale = v; //la nostra v+
            
            // !!! Prima di risalire, ci assicuriamo che il nodo finale sia raggiungibile
            const double inf = std::numeric_limits<double>::infinity();
            if (distanze[nodo_finale] == inf) {
                // il nodo non è raggiungibile, salto questo cammino per evitare loop infiniti
                continue; 
            }
            T corrente = nodo_finale;
            std::vector<T> cammino;
        
            // risaliamo la catena dei predecessori all'indietro fino a tornare alla sorgente
            std::set<T> risaliti; // per evitare cicli infiniti nella risalita
            while (corrente != sorgente) {
                // se incontriamo un nodo già inserito nella risalita, c'è un ciclo nei predecessori!
                if (risaliti.find(corrente) != risaliti.end()) {
                    break;
                }
                risaliti.insert(corrente);
                cammino.push_back(corrente);
                corrente = predecessori[corrente]; // aggiorno i predecessori
            }
            cammino.push_back(sorgente); // aggiungiamo la sorgente alla fine del vettore

            // NON SERVE che invertiamo il cammino per memorizzarlo nel verso giusto (da v+ a v-) perché è già giusto, 
            // essendo che i nodi vengono salvati in cammino da destinazione = v+ a sorgente = v-
            cammini_minimi.push_back(cammino);
        }
        
        //scegliere quale fra i cammini minimi ha la lunghezza minore
        int lunghezza=cammini_minimi.size();
        std::vector<T> cammino_scelto = cammini_minimi[0];
        // questi (i cammini_minimi) sono i C_mu dello pseudo-codice
        for (int i=1; i<lunghezza; i++) {
            if(cammini_minimi[i].size() < cammino_scelto.size()) {
                cammino_scelto = cammini_minimi[i];
            }            
        }
        
        // scrivo il vettore di bool che è C_i
        // con 1 in corrispondenza di ogni arco del cammino (minimo) appena scelto
        std::vector<int> C_i(n,0); //inizializzo tutto a zero così non lo devo fare dopo
        // per ogni arco del grafo in posizione i {
        //     se l'archi_grafo[i] == arco formato da 1° e 2° elem di cammino_scelto {
        //         metti 1 in posizione i in C_i
        
        //(ricordiamo che n = archi_grafo.size() == numero di archi del grafo originario)
        // aggiorniamo cammino scelto mettendo per ogni v- il suo corrispondente v+
        int cs_size = cammino_scelto.size();
        for (int p=0; p<cs_size; p++) {
            if (cammino_scelto[p] > num_nodi) {
                cammino_scelto[p] -= num_nodi;
            }
        }
        for (int a=1; a<cs_size; a++) { //scorro ogni "arco" sulla lunghezza di cammino_scelto
            T u_vero = cammino_scelto[a-1];
            T v_vero = cammino_scelto[a];
            undirected_edge<T> arco_vero(u_vero, v_vero);
            for (int i=0; i<n; i++) { //per ogni arco del grafo --> scorro su C_i
                if (archi_grafo[i]==arco_vero) {
                    C_i[i]=1;
                    i=n; // se sei qui, in else non ci entra
                }
                else {
                    if (C_i[i]==1) {
                        C_i[i]=1;
                    }
                    else {
                        C_i[i]=0;
                    }
                }
            }
        }
        // così ho costruito il vettore C_i di uni (1) e zeri (0)
        B.push_back(C_i);

        // aggiorno l'S_j successivo solo se <C_i,S_j>=1
        for (int h=j+1; h<k; h++) { // per ogni elemento di S
            int prod_scalare = 0;
            for (int m=0; m<n; m++) { //per ogni elemento di C_i e S_j
                prod_scalare ^= (C_i[m] & (S[h])[m]); // <-- C_i[m] & (S[h])[m] è il prodotto scalare: se uno dei due è 0 fa 0; altrimenti 1
            } // ^= : così si indica differenza simmetrica

            if (prod_scalare == 1) {
                //aggiorno l'S_j successivo, ovvero S[h] 
                for (int m=0; m<n; m++) {
                    (S[h])[m] ^= (S[j])[m];
                }
            }
        }
        mappa[cammino_scelto]=C_i;
    }
    return mappa;
};