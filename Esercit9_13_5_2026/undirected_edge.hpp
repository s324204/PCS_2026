#pragma once
#include <iostream>
#include <ostream> //per l'operatore <<
#include <vector>
#include <algorithm>

//Si implementi una classe undirected_edge che rappresenta un arco in un grafo. 
//La classe deve: 
// 1. avere un costruttore che permette di specificare i due nodi connessi dall’arco, 
// 2. inoltre devono esserci due metodi from() e to() che restituiscono i due nodi; 
//    si faccia in modo che undirected_edge garantisca sempre che from è minore di to.
//Si implementi anche :
// 3. operator< per undirected_edge, affinché gli archi possano essere ordinabili,
// 4. operator== per undirected_edge
// 5. operator<< per undirected_edge

// implementare la classe template undirected_edge che rappresenti 
// l'arco (non direzionato) di un grafo
template<typename T>
class undirected_edge {
    T nodo_from; //1. costruttore che specifica nodo di partenza
    T nodo_to; //costruttore che specifica nodo di arrivo

public:
// 2.1) i metodi from() e to() che restituiscano i due nodi connessi dall'arco 
// 2.2) e si garantisca che from sia sempre minore di to.

// prima faccio il costruttore che mi garantisca che from<to:
    undirected_edge(const T& nodo1, const T& nodo2) {
        if (nodo1 < nodo2) {
            nodo_from = nodo1;
            nodo_to = nodo2;
        }
        else {
            nodo_from = nodo2;
            nodo_to = nodo1;
        }
    } // 2.2) inverte nodo_from e nodo_to se vengono dati "al contrario" nodo1 e nodo2

    // 2.1) metodi from() e to() che restituiscano i due nodi
    T from() const {
        return nodo_from;
    }
    T to() const {
        return nodo_to;
    }

// Gli operatori di confronto < e == devono restituire un valore booleano (bool), non un riferimento all'oggetto stesso (undirected_edge&):
// il compilatore si aspetta un true o false, ma tu non restituisci nulla (fai solo dei cout). Questo causa "undefined behavior" !!!

    // 3. implementare "<" --> serve al computer per ordinare gli elementi (con operazioni successive), non per stampare chi viene prima. 
    // Deve semplicemente rispondere alla domanda: "Io sono minore di quello che mi hai passato? Sì/No".
    bool operator<(const undirected_edge<T>& arco) const { // gli operatori di confronto non devono modificare l'oggetto --> devono essere marcati come const
        
        if (nodo_from != arco.nodo_from) {              //corretta anche così! più concisa
            return nodo_from < arco.nodo_from;          //Se il primo nodo è diverso, restituiamo il risultato del confronto tra i primi nodi.
        }
        return nodo_to < arco.nodo_to;                  // Se sono uguali, restituiamo il risultato del confronto tra i secondi.
         

        /* if (nodo_from < arco.nodo_from) {                        // corretta anche questa
            return true; // il primo che ho E' minore del secondo
        }
        else if (nodo_from == arco.nodo_from) {
            if (nodo_to < arco.nodo_to) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }*/
    }

    // 4. implementare == (se sono equivalenti??) --> NON: undirected_edge& operator==(const undirecte_edge& arco1) {
    bool operator==(const undirected_edge<T>& arco) const {
        return (nodo_from == arco.nodo_from && nodo_to==arco.nodo_to);  // giusta anche così (concisa): restituisce true o false
                                                                        // penso che qui usi il confronto "normale" (==) tra due oggetti, che è già implementato di default in c++
                                                                        // ma avendo introdotto un nuovo tipo di oggetto (gli archi) va definito il confronto pure fra archi
        
        /*if (nodo_from == arco.nodo_from && nodo_to==arco.nodo_to) {
            return true;
        }
        return false;*/
    }

    // 5. implementare << (la stampa degli archi) --> se usi i template, devi assicurarti che 
    // l'operatore "<<" sia gestito correttamente (spesso come friend).
    
    friend std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& arco) {
                // |-> perché questo operatore restituisce un output
        os << "(" << arco.nodo_from << "," << arco.nodo_to << ")" << std::endl;
        return os;
    }
};