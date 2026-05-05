#pragma once
#include <iostream>
#include <optional> // gestisce elegantemente il caso in cui il vettore abbia lunghezza = 0

// NON SI USA using namespace std NEI FILE HEADER !!!


/* Si scriva una funzione template is_sorted() che prenda per parametro un vettore di elementi di
tipo T e che verifichi se è ordinato. Un vettore di lunghezza zero è per definizione ordinato.
Tipo questa (che trova max):

#include <optional>
template<typename T>
std::optional<T>
max_elem(const std::vector<T>& vec)
{
    if (vec.size() == 0) {
    return {};
    }
    T vec_max = vec[0];
    for (int i = 1; i < vec.size(); i++) {
    vec_max = std::max(vec_max, vec[i]);
    }
    return vec_max;
}
*/

template<typename T>
void
is_sorted(const std::vector<T>& vec) {
    bool ordinato=true;
    int n=vec.size();
    for (int i=1; i<n; i++) {
        if (vec[i-1]>vec[i]) { 
// se scorre tutti gli indici e non entra nell'if perché non trova che c'è un elemento prima 
// più grande di un elemento dopo, ordinato rimane "true"
            ordinato=false;
            break;
        }
    }
    if (ordinato) {
        std::cout << "Il vettore è ordinato" << "\n";
    }
    else {
        std::cout << "Il vettore non è ordinato" << "\n";
    }
    //return;
}