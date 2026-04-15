#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility> // Per std::swap
#include "randfiller.h"
#include "insertion_sort.hpp"
#include "is_sorted.hpp"

// per contare i tempi:
#include <chrono>
#include "timecounter.h"

/* 
• Testare gli algoritmi di ordinamento su 100 vettori di dimensioni scelte a caso
• Per ognuna delle dimensioni si testi gli algoritmi su vettori riempiti in modo casuale e che
includano numeri sia negativi sia positivi.
• Si crei un vettore di std::string e lo si riempia con una decina di stringhe scelte a piacere,
si verifichi quindi che gli algoritmi ordinano correttamente anche le stringhe. */

using namespace std;

template<typename T>
void
print_vector(const std::vector<T>& v)
{
    int n=v.size();
    for (size_t i = 0; i < n; i++) {
        if (i==n-1) {
            std::cout << v[i];
        }
        else {
            std::cout << v[i] << ", ";
        }
    }
    std::cout << "}" << "\n";
}

int main() {
    /* come generare 100 numeri (=dimensioni) casuali */
    srand(unsigned(time(NULL)));
    int qta_vettori = 1;
    for (int i=0; i < qta_vettori; i++) {
        int dim = rand() % 100 +1; // : genero 100 numeri randomici tra 1 a 100 (con estremi inclusi)
        // 1. rand(): da 0 a inf
        // 2. numeri 0-99: rand() % 100 --> il resto di un numero rand() diviso per 100 dà numeri tra 0 e 99
        // 3. numeri tra -60 a +60 con estremi esclusi: (rand() % 100)-60 ; estremi inclusi: %101
        
        randfiller rf; /* instantiate a randfiller */
        vector<int> vec;
        vec.resize(dim);
        rf.fill(vec, -100, 100);
        cout << "dim: " << dim << endl;
        //cout << "Vettore " << i+1 << ": {";
        //print_vector(vec);

        /* Testiamo l'insertion sort */
        insertion_sort(vec);
        cout << "Vettore n°" << i+1 << ": ";
        //print_vector(vec);
        is_sorted(vec);

        /* Ordinare stringhe - insertion sort */
        vector<string> vec_string;
        vec_string = {"Luca", "Giovanni", "giorgia", "Sandra", "Enzo", "Laura", "barbara"}; // non funziona con le minuscole
        insertion_sort(vec_string);
        
        cout << "Vettore di stringhe (non ordina le minuscole :/): ";
        print_vector(vec_string);
        //is_sorted(vec);

    }
    return 0;
}