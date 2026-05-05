#pragma once 
#include <iostream>
#include <optional> // per std::optional<T> per poter returnare un elemento di tipo T
#include <utility> // per std::swap()
#include <cmath> // per il floor()

// NON SI USA using namespace std NEI FILE HEADER !!!

template<typename T>
void
quicksort_modificato(std::vector<T>& vec, int s, int d) {
    int dim_vec=vec.size();
    if (dim_vec < 8) { //dato che la mia soglia è circa
        insertion_sort(vec);
    }
    else {
        if (s<d) {
            int rango = partition(vec, s, d);
            quicksort_modificato(vec, s, rango-1);
            quicksort_modificato(vec, rango+1, d);
        }
    }
}