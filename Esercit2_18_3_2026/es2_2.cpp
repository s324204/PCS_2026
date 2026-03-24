#include <iostream>
#include <algorithm> //min-max
#include <vector>
#include <cmath> //pow
#include <limits>

// g++ -Werror=vla -o prog es2.cpp

using namespace std; // std indica che le ""funzioni"" si prendono dalla libreria standard

int main()
{
    static const int N=4;
    double arr[N]={0.0, 1.1, 2.2, 3.3};
    double minimo=0.0;
    double massimo=0.0;
    double somma=0.0;
    for (int i=0; i<N; i++) {
        minimo=min(minimo,arr[i]);
        massimo=max(massimo,arr[i]);
        somma=(arr[i])+somma;
    }
    double media=somma/N;
    double quadrato=0.0;
    for (int i=0; i<N; i++) {
        quadrato=pow(arr[i]-media,2)+quadrato; //non devi di nuovo scrivere double 
    }
    double dev_stand=sqrt(quadrato/N);

    cout << "Minimo: " << minimo << "\n";
    cout << "Massimo: " << massimo << "\n";
    cout << "Media: " << media << "\n";
    cout << "Deviazione standard: " << dev_stand << "\n";

    return 0;
}