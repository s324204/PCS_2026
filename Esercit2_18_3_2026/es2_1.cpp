#include <iostream>
using namespace std; // std indica che le ""funzioni"" si prendono dalla libreria standard
int main()
{
    double ad[4]={0.0, 1.1, 2.2, 3.3}; // ogni numero tiene 8 byte
    float af[8]={0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7}; //4 byte
    int ai[3]={0,1,2}; // ogni intero tiene 4 byte
    
    int x=1;
    float y=1.1;
/*
    cout << "Indirizzo del double ad[4]: " << &ad[0] << " ; elemento 2: " << &ad[1] << endl;
    cout << "Indirizzo del floating point af[8]: " << &af[0] << " ; elemento 2: " << &af[1] << endl;
    cout << "Indirizzo dell'intero ai[3]: " << &ai[0] << " ; elemento 2: " << &ai[1] << endl;
    cout << "indirizzo di x: " << &x << "\n" << "indirizzo di y: " << &y << endl;
    
    y (float) è allocata ad un indirizzo prima di x (int) */

    (&y)[1]=0; //è un undefined behaviour

    cout << x << "\n";
    // la y vive esattamente prima della x, e quando facciamo questa istruzione ( (&y)[1]=0 ?) andiamo a sovrascrivere la x
 
    return 0;
}