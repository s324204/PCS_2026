#pragma once 
#include <iostream>
#include <optional>
#include <utility> // Per std::swap

template<typename T>
void
selection_sort(std::vector<T>& vec) {
    int n=vec.size();
    for (int i=0; i<n-1; i++) {
        int min_index=i;
        for (int j=i+1; j<n; j++) {
            if (vec[j]<vec[min_index]) {
                min_index=j;
            }
        }
        if (min_index != i) {
            std::swap(vec[i],vec[min_index]);
        }
    }
    //return;
}