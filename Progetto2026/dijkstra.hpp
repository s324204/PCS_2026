#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <limits> //per infinity
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"

// cammino più corto da source a ognuno degli altri nodi
template<typename T>
void dijkstra(const undirected_graph<T>& grafo, const T& source, std::map<undirected_edge<T>, double> weights, std::map<T, T>& predecessori, std::map<T, double>& distanze) {//, w = vettore dei pesi associati agli archi?
    std::set<T> nodi = grafo.all_nodes();
    //int n = nodi.size();
    std::vector<undirected_edge<T>> archi = grafo.all_edges(); // (vettore di) m archi

    const double inf = std::numeric_limits<double>::infinity();

    // Glieli passo SOLO per riferimento se no il main non funziona! Quindi non devo scrivere QUI le seguenti cose:
    //std::map<T, double> distanze; //associa a ogni nodo T il suo peso/distanza da source
    //std::map<T, T> predecessori;

    for (const T& nodo : nodi) { //per ogni elemento nel set "nodi"
        //predecessori[nodo] = -1; // Se T fosse una stringa (es. "Milano"), il compilatore darebbe errore.
        distanze[nodo] = inf;
    }

    // source è un numero che nel set nodi è ordinato in ordine crescente
    predecessori[source]=source;
    distanze[source]=0.0; //distanza source da se stessa è 0

    std::set<std::pair<double, T>> PQ;
    PQ.insert({0.0, source});

    while (!PQ.empty()) {
        auto primo = *(PQ.begin()); //memorizzo il primo nodo che ha minima distanza
        PQ.erase(PQ.begin()); // e poi lo tolgo tramite erase (a cui devo dare iteratori)
        
        //double dist_min = primo.first; //alla fine non l'ho usata
        T nodo = primo.second;

        for (const T& vicino : grafo.neighbours(nodo)) {
            double peso_arco = weights[undirected_edge<T>(nodo, vicino)];
            if (distanze[vicino] > distanze[nodo] + peso_arco) {
                distanze[vicino] = distanze[nodo] + peso_arco;
                predecessori[vicino] = nodo;

                // Inseriamo la nuova coppia aggiornata nella PQ (che sarà ordinata in modo cresc)
                PQ.insert({distanze[vicino], vicino});
            }
        }
    }    
    return;
}