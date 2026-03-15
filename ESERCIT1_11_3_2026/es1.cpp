#include <fstream>
#include <iostream>

using namespace std;


int main() {
    //string filename = "input_es1.txt";
    cout << "Inserisci il nome del file da leggere: \n"; // aggiunta io
    string filename; // aggiunta io
    cin >> filename; // aggiunta io --> assegni la variabile / prendi ciò che ho scritto in input 
                        // e lo metti nella variabile filename
    ifstream ifs(filename); // metti filename in un flusso; è per dirgli di trattarlo come un file
    
    
    if (!ifs.is_open()) // check if file successfully opened
        cout << "Errore nell'apertura del file " << filename << endl;
    else { 
        while(!ifs.eof()) {
            string citta; // definisco le variabili
            double t1;
            double t2;
            double t3;
            double t4;

            ifs >> citta >> t1 >> t2 >> t3 >> t4; // le scorro/leggo assegnando alla 
            // prima stringa che incontra l'etichetta "citta", alla seconda "t1" e così via
            double media=(t1+t2+t3+t4)/4;                                              // .\n"; e bom
            cout << "Nella città di " << citta << " ci sono in media " << media << " gradi." << endl;
            // stampo sul terminale scrivendo  g++ -o prog es1.cpp  e a capo  ./prog
        }

    }
    return 0;    
}