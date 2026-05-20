#pragma once //impedisce che lo stesso file venga incluso più di una volta nello stesso progetto. 
// senza di esso, se includessi undirected_edge.hpp sia nel main che in undirected_graph.hpp, 
// il compilatore vedrebbe due definizioni della classe undirected_edge e darebbe un errore di "redefinition"
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm> // per std::find()
#include <cassert> // per l'assert del punto 6.
#include "undirected_edge.hpp"

template<typename T>
class undirected_graph { // map: elenco di coppie del tipo (nodo, {vicini}) cioè associazione chiave-valore, com chiavi uniche e ordinate
    // map permette di trovare un valore partendo dalla sua chiave in modo molto efficiente.
    std::map<T, std::set<T>> lista_adiacenza; // [lista_adiacenza = array + lista] per neighbours() e all_nodes() --> modo di rappr grafo 
    std::vector<undirected_edge<T>> archi; //per edge_at() e edge_number

public:
/* Costruttore di default: è un costruttore che non accetta argomenti (o che ha parametri con valori predefiniti per tutti gli argomenti).
   Serve a creare un oggetto "vuoto" o con uno stato iniziale standard. Se non definisci alcun costruttore nella tua classe, il compilatore ne genera uno automaticamente per te (detto implicit default constructor).
   Esempio: se hai una classe Gatto, il costruttore di default potrebbe impostare l'età a 0 e il nome a "Senza nome". */
    
   // a) costruttore di default 
    undirected_graph() = default; // inizializzo il grafo vuoto: anche la lista_adiacenza e il vettore di archi saranno vuoti


    /* Il costruttore di copia è un costruttore che crea un nuovo oggetto come copia esatta di un oggetto esistente della stessa classe. 
   Ha tipicamente la firma NomeClasse(const NomeClasse& altro) --> x clonare un oggetto esistente.        Class Gatto {
   Viene invocato in tre situazioni principali:                                                           public:
   - quando dichiari un oggetto inizializzandolo con un altro (Gatto g2 = g1;).                             Gatto(const Gatto& altro) {
   - quando passi un oggetto a una funzione per valore.                                                       this->eta = altro.eta; }
   - quando una funzione restituisce un oggetto per valore.                                               }; // copio i dati dal gatto "altro" a quello nuovo */
                                                                                              //          Gatto g1; 
   // b) costruttore di copia (??)                                                            //          Gatto g2(g1); //chiamo il costruttore di copia
    undirected_graph(const undirected_graph<T>& altro_grafo) { 
        (*this).lista_adiacenza = altro_grafo.lista_adiacenza; // this->lista_adiacenza = altro_grafo.lista_adiacenza;
        (*this).archi = altro_grafo.archi; // this->archi = altro_grafo.archi
    } // this->lista_ == (*this).lista_

    // 1. metodo neighbours() che, dato un nodo, restituisce i suoi vicini
    std::set<T> neighbours(const T& nodo) const {
        auto itor = lista_adiacenza.find(nodo); // itor sarà LA posizione (nella lista) dove trova "nodo"
        if (itor != lista_adiacenza.end()) {
            return (*itor).second; // accediamo al secondo elemento della coppia (nella lista di adiacenza=map) (nodo, {vicini})
        }
        return {}; // altrimenti restituisce un insieme vuoto se il nodo non esiste
    }
    // 2. metodo add_edge(): per aggiungere un arco al grafo
    void add_edge(const T& nodo1, const T& nodo2) {
        undirected_edge<T> nuovo_arco(nodo1, nodo2);
        if (std::find(archi.begin(), archi.end(), nuovo_arco) == archi.end()) { // se find scorre tutto il vettore e non lo trova, quindi "restituisce" come indice end() (cioè 1 posizione fuori dal vettore)
            archi.push_back(nuovo_arco); //xké archi è un vettore
            lista_adiacenza[nuovo_arco.from()].insert(nuovo_arco.to()); //posso usare insert perché set (dentro map) ha un metodo predefinito chiamato insert!
            lista_adiacenza[nuovo_arco.to()].insert(nuovo_arco.from());
        }
    }

    // 3. metodo all_edges() che restituisce tutti gli archi del grafo
    std::vector<undirected_edge<T>> all_edges() const {
        return archi;
    }

    // 4. metodo all_nodes() che restituisce tutti i nodi del grafo
    std::set<T> all_nodes() const {
        std::set<T> tutti_nodi; //creo un contenitore (set) vuoto che riempirò con i nodi scorrendo l'itor
        for (auto itor = lista_adiacenza.begin(); itor != lista_adiacenza.end(); itor++) { //sarebbe uguale scrivere ++itor ma più efficiente! xké deve solo incrementare itor e poi lo restituisce subito!
        // mentre itor++ deve: 1. copiare l'iteratore in una var temporanea --> 2. incrementare l'originale --> 3. e poi restituisce la copia temporanea di prima
            tutti_nodi.insert((*itor).first); //inserisce, nel set vuoto, l'elemento in "posiz" itor --> il primo elemento della coppia
        } //insert si può usare perché in set è predefinito
        return tutti_nodi;
    }

    // 5. metodo edge_number() che, dato un arco, ti restituisce la sua numerazione all’interno del grafo
    // (il numero in "classifica": se è il 1°, il 2° arco del grafo, ecc)
    int edge_number(const undirected_edge<T>& arco) const {
        // se esiste: restituisco l'enumerazione
        // vogliamo iterare su un vettore --> usiamo puntatore normale i
        int n=archi.size(); //xké .size() restituisce un tipo che non è intero, ma size_t ovvero "senza segno"
        for (int i=0; i<n; i++) {
            if (archi[i]==arco) {
                return i;
            }
        }
        // se non esiste: dai errore restituendo qualcosa di diverso da 0:
        return -1;
    }

    // 6. metodo edge_at() che, dato un numero/indice d’arco (quello sopra), restituisce il corrispondente oggetto arco all’interno del grafo ((nodo_from, nodo_to))
    undirected_edge<T> edge_at(int i) const {
        int n=archi.size();
        assert (i>=0 && i<n); // se l'assert fallisce (= l'indice sfora) --> il programma si interrompe con un messaggio di errore che indica file e riga
        return archi[i];      // è utile in fase di test (debug), ma se compili in modalità "Release" (ottimizzata), gli assert vengono ignorati per velocità
    }

    // 7. operator-(), che permette di calcolare la differenza tra due grafi: dati G e G′,
    // la differenza G−G′ è data dagli archi presenti in G e non presenti in G′.
    undirected_graph<T> operator-(const undirected_graph<T>& altro) const {
        undirected_graph<T> grafo_differenza;
        //for (const auto& arco : (*this).archi) {
        int n=archi.size();
        for (int i=0; i<n; i++) {
            if (std::find(altro.archi.begin(), altro.archi.end(), archi[i]) == altro.archi.end()) {
                grafo_differenza.add_edge(archi[i].from(), archi[i].to());
            }
        }
        return grafo_differenza;

        /* oppure:
        for (const auto& arco : archi) = itera su ogni elemento dentro "archi", dove ": archi" indica su cosa ciclare
            // Cerchiamo l'arco del grafo attuale dentro gli archi del grafo 'altro'
            auto it = std::find(altro.archi.begin(), altro.archi.end(), arco); //la "posiz" a cui trova arco
            
            if (it == altro.archi.end()) {
                // Se non lo trova, lo aggiungiamo al risultato
                risultato.add_edge(arco.get_node1(), arco.get_node2());
            }
        }
        return risultato; */  
    }

// fine
};