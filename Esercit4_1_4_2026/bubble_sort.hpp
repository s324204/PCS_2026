#pragma once // serve se lo stesso header viene incluso in più file .cpp, 
// se no il compilatore vedrebbe la stessa definizione due volte, generando un errore di redefinizione
// (poiché i template devono essere interamente visibili al compilatore nel momento in cui vengono usati)
#include <iostream>
#include <optional>
#include <utility> // Per std::swap

// NON SI USA using namespace std NEI FILE HEADER !!!


/*Si implementino i tre algoritmi: bubble_sort, insertion_sort e selection_sort in modo generico (utilizzando
quindi funzioni template).*/

template<typename T>
void // al posto di std::optional<T> così non deve restituire nulla
bubble_sort(std::vector<T>& vec) {            // 1. non scrivere const in bubble_sort(const std::vector<T>& vec) perché questo dice che
                                              // il vettore non verrà modificato, invece viene modificato con swap
    int n=vec.size();
    for (int i=0; i<n-1; i++) {
        for (int j=n-1; j>=i+1; j--) {
            if (vec[j]<vec[j-1]) {
                //std::cout << vec[j-1] << "\n" << vec[j] << "\n";
                std::swap(vec[j],vec[j-1]);
            }
        }
    }
    //return; // 1. non return vec perché optional si aspetta un singolo elemento di tipo T; 
    // nemmeno se togli optional e lasci return vec non ti "stampa" il vettore perché in c++ non si stampa così facilmente un vettore
    // 2. return 0; --> return; (oppure nulla) perché scrivo void lassù
}