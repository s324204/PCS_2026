#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility> // per std::swap
#include <ctime>

#include "randfiller.h"
#include "bubble_sort.hpp"
#include "is_sorted.hpp"

// per contare i tempi --> sarebbe meglio calcolare il tempo complessivo e poi fare la media
#include <chrono>
#include "timecounter.h"


// COMPILARE INCLUDENTO TIMECOUNTER.CPP: g++ -std=c++20 test_bubblesort.cpp timecounter.cpp -o test_bubble


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
    srand(unsigned(time(NULL))); // per generare 100 numeri (=dimensioni) casuali
    int qta_vettori = 100;
    randfiller rf; //instantiate a randfiller

    for (int i=0; i < qta_vettori; i++) {
        int dim = rand() % 100 +1; // : genero 100 numeri randomici tra 1 a 100 (con estremi inclusi)
        // 1. rand(): da 0 a inf
        // 2. numeri 0-99: rand() % 100 --> il resto di un numero rand() diviso per 100 dà numeri tra 0 e 99
        // 3. numeri tra -60 a +60 con estremi esclusi: (rand() % 100)-60 ; estremi inclusi: %101
        
        vector<int> vec;
        vec.resize(dim);
        rf.fill(vec, -100, 100);
        //cout << "dim: " << dim << endl;
        //cout << "Vettore " << i+1 << ": {";
        // print_vector(vec);

        // 1. Testiamo il bubble sort
        bubble_sort(vec);
        cout << "Vettore n°" << i+1 << " (bubble): ";
        is_sorted(vec);
       
    }
    
// Testiamo su vettore di stringhe:
    vector<string> vec_string;
    vec_string = {"Luca", "Giovanni", "Giorgia", "Sandra", "Enzo", "Laura", "Barbara"};

    // Ordinare stringhe - bubblesort
    bubble_sort(vec_string);
    cout << "Vettore di stringhe (bubble): ";
    is_sorted(vec_string);

    return EXIT_SUCCESS;
}
