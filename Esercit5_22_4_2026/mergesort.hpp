#pragma once 
#include <iostream>
// #include <optional>
// #include <utility> // per std::swap
#include <cmath> // per il floor()

// NON SI USA using namespace std NEI FILE HEADER !!!

template<typename T>
void // p=s, q=centro, r=destra
// merge riordina i cubetti dei vettori (la primissima volta che viene applicato sarà su 2 cubetti singoli)
merge(std::vector<T>& vec, int s, int centro, int d) {
    int n1 = centro - s + 1; // dopo lo split, è la dim del nuovo sottovettore di sinistra
    int n2 = d - centro; // dim del sottovettore di dx dopo lo split da centro
    std::vector<T> vecL(n1), vecR(n2);
    for (int i=0; i < n1; i++) {
        vecL[i]=vec[s + i];
    }
    for (int j=0; j < n2; j++) {
        vecR[j]=vec[centro + j + 1];
    }
    // Potrei aggiungere un valore infinito alla fine dei vettori di sx e dx, 
    // così quando uso tutti gli elementi di un vettore (sx o dx) e quelli dell'altro li confronto 
    // con l'ultimo elemento di questo che è inf, sarà sicuro più grande di un qualsiasi numero.
    // Creo vecL[n1+1] e vecR[n2+1] con uno spazio in più ,
    // così metto il "valore inf" che per c++ è: std::numeric_limits<int>::max();
    // se no avrei anche potuto calcolare il max (?) del primo e secondo vettore e mettere in ultima posizione di entrambi i rispettivi max+1
    int i=0;
    int j=0;
    
    for (int k=s; k<=d; k++) {
        if (i<n1 && j<n2) {
            if (vecL[i]<=vecR[j]) {
                vec[k]=vecL[i];
                i++;
            }
            else {
                vec[k]=vecR[j];
                j++;
            }
        }
        else if (i>=n1 && j<n2) {
            vec[k]=vecR[j];
            j++;
        }
        else if (j>=n2 && i<n1) {
            vec[k]=vecL[i];
            i++;
        }
        
    }
    // return 0; ho il void: non restituisco nulla
}

template<typename T>
void // al posto di std::optional<T> così non deve restituire nulla
mergesort(std::vector<T>& vec, int s, int d) { // s/d= (puntatore di) sinistra/destra
    if (s<d) {
        int centro = floor((s+d)/2);
        mergesort(vec, s, centro);
        mergesort(vec, centro+1, d);
        merge(vec, s, centro, d);
    }
}