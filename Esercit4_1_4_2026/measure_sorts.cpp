#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility> // per std::swap
#include <ctime>

#include "randfiller.h"
#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "insertion_sort.hpp"
#include "is_sorted.hpp"

// per contare i tempi --> sarebbe meglio calcolare il tempo complessivo e poi fare la media
#include <chrono>
#include "timecounter.h"

using namespace std;
int main() {
    randfiller rf;
    timecounter tc; // inizializzo il time counter per i tempi
    double tempoB=0;
    double tempoS=0;
    double tempoI=0;
    double tempoTOT_sort=0;
    double volte=0;

    // Creo i vettori causali
    for (int dim=4; dim<=8192; dim *= 2) {
        vector<int> vec;
        vec.resize(dim);
        rf.fill(vec, -100, 100);

    // Ordino con bubble e conto il tempo
        vector<int> vecB=vec;
        tc.tic();
        bubble_sort(vecB);
        double tempo_bubble = tc.toc();
        //cout << "Tempo bubblesort: " << tempo_bubble << endl;
        tempoB += tempo_bubble;  

    // Ordino con selection e conto il tempo
        vector<int> vecS=vec;
        tc.tic();
        selection_sort(vecS);
        double tempo_selection = tc.toc();
        tempoS += tempo_selection;
    
    // Ordino con insertion e conto il tempo
        vector<int> vecI=vec;
        tc.tic();
        insertion_sort(vecI);
        double tempo_insertion = tc.toc();
        tempoI += tempo_insertion;
        
    // Ordino con sort() e conto il tempo
        vector<int> vec_sort=vec;
        tc.tic();
        sort(vec_sort.begin(), vec_sort.end());
        double tempo_sort = tc.toc();        
        tempoTOT_sort += tempo_sort;

        volte+=1;
    }
    
    double mediaB= tempoB/volte;
    cout << "Tempo medio bubblesort: " << mediaB << "s" << endl;
    double mediaS= tempoS/volte;
    cout << "Tempo medio selection sort: " << mediaS << "s" << endl;
    double mediaI= tempoI/volte;
    cout << "Tempo medio insertion sort: " << mediaI << "s" << endl;
    double media_sort= tempoTOT_sort/volte;
    cout << "Tempo medio sort(): " << media_sort << "s" << endl;
    
    return EXIT_SUCCESS;
}