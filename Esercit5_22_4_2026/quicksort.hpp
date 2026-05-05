#pragma once 
#include <iostream>
#include <optional> // per std::optional<T> per poter returnare un elemento di tipo T
#include <utility> // per std::swap()
#include <cmath> // per il floor()

// NON SI USA using namespace std NEI FILE HEADER !!!

template<typename T>
int // per poter returnare un elemento di tipo T
partition(std::vector<T>& vec, int s, int d) { 
    // p=sinistra (s)=1° indice del vec (=0), r=destra (d)=ultimo indice del vec
    T pivot=vec[d];
    /* tolgo la parte sotto che ora non serve
    if (pivot!=d) {
        std::swap(pivot,vec[d]);
        pivot=vec[d];
    } */
    int i=s-1;
    for (int j=s; j<d; j++) {
        if (vec[j]<=pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    if (i!=d) {
        std::swap(vec[i+1], pivot);
    }
    return i+1; //rango;
}

template<typename T>
void
quicksort(std::vector<T>& vec, int s, int d) {
    if (s<d) {
        //T pivot= vec[rand(s,d)]; // o meglio pivot=vec[d] --> ma lo def direttam nel partition
        int rango = partition(vec, s, d);
        quicksort(vec, s, rango-1);
        quicksort(vec, rango+1, d);
    }
}