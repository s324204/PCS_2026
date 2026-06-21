#pragma once
#include <iostream>
#include <list>
#include <algorithm>

// classe LIFO: Last In First Out (l'ultimo che entra -dal fondo- è il primo che esce -dal fondo-) = pila/stack
template<typename T>
class lifo {
    std::list<T> pila;
public:
    // 1. costruttore di default
    lifo() = default;
    
    // 2. metodo put(): inserisco l'elemento in cima alla pila, cioè al fondo della lista
    void put(const T& elem) {
        pila.push_back(elem);
        return;
    }

    // 3. metodo get(): rimuovo dalla lista e ottengo l'elemento in cima alla pila, cioè al fondo della lista
    T get() {
        T ultimo_entrato = pila.back();
        pila.pop_back();
        return ultimo_entrato;
    }

    // 4. metodo empty(): è vuoto?
    bool empty() const {
        if (pila.size() == 0) {
            return true;
        }
        else {
            return false;
        }
    }
};