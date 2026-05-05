#pragma once 
#include <iostream>
#include <optional>
#include <utility> // Per std::swap

template<typename T>
void
insertion_sort(std::vector<T>& vec) {
    int n=vec.size();
    for (int i=1; i<n; i++) {
        T value = vec[i];
        int j=i-1;
        while (j>=0 && vec[j]>value) {
            std::swap(vec[j+1],vec[j]);
            j=j-1;
        }
        vec[j+1]=value;
    }
    //return;
}