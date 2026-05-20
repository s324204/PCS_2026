#pragma once
#include <iostream>
#include <list>
#include <algorithm>

// classe FIFO: First In First Out (il primo che entra è il primo che esce) = coda
template<typename T>
class fifo {         // list: https://cppreference.com/cpp/container/list
    std::list<T> coda;  // soluzione è con lista xké inserire o rimuovere elementi in qualsiasi punto è velocissimo (basta cambiare
    // i collegamenti dei puntatori), a patto di avere già l'iteratore sulla posizione --> per frequenti inserimenti e rimozioni
public:
    // 1. costruttore di default
    fifo() = default;
    
    // 2. metodo put(): inserisco l'elemento alla fine della coda
    void put(const T& elem) {
        coda.push_back(elem);
        return;
    }

    // 3. metodo get(): rimuovo dal davanti della lista e ottengo il primo elemento del contenitore/quello in testa alla coda
    T get() {
        T primo_entrato = coda.front();
        coda.pop_front();
        return primo_entrato;
    }
    
    // 4. metodo empty(): è vuoto?
    bool empty() const {
        if (coda.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }
};