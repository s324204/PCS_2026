#include <iostream>
#include <vector>
#include <algorithm>
#include <optional>
#include <utility> // per std::swap()
#include <ctime>

#include "randfiller.h"
#include "bubble_sort.hpp"
#include "selection_sort.hpp"
#include "insertion_sort.hpp"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include "quicksort_modificato.hpp"
#include "is_sorted.hpp"

// COMPILARE INCLUDENTO TIMECOUNTER.CPP: g++ -std=c++20 measure_sorts.cpp timecounter.cpp -o measure_sorts

// per contare i tempi --> sarebbe meglio calcolare il tempo complessivo e poi fare la media
#include <chrono>
#include "timecounter.h"

// ESERCIT 5 - Mergesort e Quicksort //
// Si confrontino i tempi di Bubblesort, Selectionsort ed Insertionsort con i tempi di Quicksort 
// e di Mergesort su vettori piccoli (indicativamente, dimensioni inferiori a 100) e si determini se
// ESISTE UNA DIMENSIONE al di sotto della quale gli algoritmi quadratici (bubble, selection, insertion) 
// sono più veloci degli algoritmi logaritmici (mergesort, quicksort). Se sì, si proponga una 
// versione modificata di Quicksort che, al disotto di tale soglia,
// utilizzi l’algoritmo quadratico più veloce per fare l’ordinamento.

using namespace std;
int main() {
    randfiller rf;
    timecounter tc; // inizializzo il time counter per i tempi

    int n_vett=100; //vettori da ordinare in ogni box
    int dim_max=200;
    // Creo i 100 vettori riempiti causalmente
    for (int dim=4; dim<=dim_max; dim++) {
        vector<vector<int>> box_vecs;
        box_vecs.reserve(100);
        for (int i=0; i<n_vett; i++) {
            vector<int> vec(dim);
            rf.fill(vec, -100, 100);
            box_vecs.push_back(move(vec)); // a posto così hai creato e messo in box il 1° vettore
            //move(vec) sposta il vettore invece di copiarlo in box_vecs
        }
        
        //ora li ordini con un for su ogni box_vecs[i] applicando i 5+sort(?) algoritmi e calcolando i tempi
        
        // BUBBLE
        vector<vector<int>> box_vecsB = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            bubble_sort(box_vecsB[i]);
        }
        double tB_tot = tc.toc();
        double mediaB=tB_tot/n_vett;
        
        //SELECTION
        vector<vector<int>> box_vecsS = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            selection_sort(box_vecsS[i]); 
        }
        double tS_tot = tc.toc();
        double mediaS=tS_tot/n_vett;
        
        //INSERTION
        vector<vector<int>> box_vecsI = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            insertion_sort(box_vecsI[i]);
        }
        double tI_tot = tc.toc();
        double mediaI=tI_tot/n_vett;

        //MERGESORT
        vector<vector<int>> box_vecsM = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            int sM=0;
            int dM=dim-1;
            mergesort(box_vecsM[i], sM, dM);
        }
        double tM_tot = tc.toc();
        double mediaM=tM_tot/n_vett;

        //QUICKSORT
        vector<vector<int>> box_vecsQ = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            int sQ=0;
            int dQ=dim-1;
            quicksort(box_vecsQ[i], sQ, dQ);
        }
        double tQ_tot = tc.toc();
        double mediaQ=tQ_tot/n_vett;

        //QUICKSORT EFFICIENTE
        vector<vector<int>> box_vecsQ_modificato = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            quicksort_modificato(box_vecsQ_modificato[i], 0, dim-1);
        }
        double mediaQ_modificato=tc.toc()/n_vett;

        //STD::SORT()
        vector<vector<int>> box_vecsSORT = box_vecs;
        tc.tic();
        for (int i=0; i<n_vett; i++) {
            sort(box_vecsSORT[i].begin(), box_vecsSORT[i].end());
        }
        double tSORT_tot = tc.toc();
        double mediaSORT=tSORT_tot/n_vett;
        
        cout << "dim: " << dim << endl;
        cout << "Bubble: " << mediaB << endl; 
        cout << "Selection: " << mediaS << endl; 
        cout << "Insertion: " << mediaI << endl; 
        cout << "Mergesort: " << mediaM << endl; 
        cout << "Quicksort: " << mediaQ << endl;
        cout << "Quicksort modificato: " << mediaQ_modificato << endl;
        cout << "Sort: " << mediaSORT << endl;
        cout << endl;

        // La vera soglia è quando Quicksort batte l'Insertion Sort,
        // ovvero quando i quadratici sono più veloci di entrambi <=> appena uno dei log (il più 
        // rapido = Quick) diventa più veloce/batte uno dei quadratici (il più veloce = Insertion)
        //if (mediaM<mediaB && mediaM<mediaS && mediaM<mediaI && mediaQ<mediaB && mediaQ<mediaS && mediaQ<mediaI) {
        if (mediaQ<mediaI) {
            cout << "La dimensione limite è: " << dim << " (cioè al di sotto di questa, gli algoritmi quadratici -bubble, selection, insertion- sono tutti e 3 più veloci di quelli logaritmici -quick e mergesort-)" << endl;
            //dim=101; // se voglio interrompere dopo aver trovato la dimensione limite
            return 0;
            // così facendo mi dà sempre una soglia minore di 10, circa 7
        }
    }

    return EXIT_SUCCESS;
}