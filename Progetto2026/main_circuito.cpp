#include <fstream>
#include <iostream>
#include "trovo_maglie.hpp"
#include "metodo_gradiente_coniugato.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>

using namespace std;

int main() {
    cout << "Inserisci il nome del file da leggere: ";
    string filename;
    cin >> filename;
    ifstream ifs(filename);
    
    
    if (!ifs.is_open()) { // check if file successfully opened
        cout << "Errore nell'apertura del file " << filename << endl;
        return 1;
    }
    
    undirected_graph<int> grafo;
    map<undirected_edge<int>, string> nomi;
    map<undirected_edge<int>, double> pesi;
    map<undirected_edge<int>, int> nodo_positivo_netlist;

    int num_generatori = 0;
    int num_resistori = 0;

    while(!ifs.eof()) { //per ogni riga del file finché non arriva all'ultima --> eof = end of file
        string componente; // definisco le variabili
        double valore;
        int nodo1;
        int nodo2;

        ifs >> componente >> valore >> nodo1 >> nodo2; // le scorro/leggo assegnando alla 
        // prima stringa che incontra l'etichetta "componente", alla seconda "valore" e così via
        grafo.add_edge(nodo1,nodo2);
        undirected_edge<int> arco(nodo1,nodo2);
        nomi[arco] = componente;
        
        // elimino la vecchia mappa "pesi" che metteva +/- al valore, a seconda che l'arco venisse memorizzato come nella netlist o al contrario
        pesi[arco] = valore; //lascia il valore invariato

        //PROBLEMA: ORIENTAMENTO RESISTENZE
        // noi abbiamo interpretato che per le resistenze il nodo a cui è collegato il terminale positivo è il nodo di indice minore,
        // mentre per i generatori l'ordine nella netlist conta e infatti il primo nodo della netlist è quello del terminale positivo

        // vado a memorizzare solo qual è il nodo del terminale positivo per ogni generatore/resistore IN UNA MAPPA!
        nodo_positivo_netlist[arco] = nodo1;

        if (componente[0]=='V') { //generatori sono da + a - sempre, senza contare l'ordine crescente dei nodi: come sono messi nella netlist, lì va da + a -
            num_generatori += 1;
        }
        else if (componente[0]=='R') { // + è il nodo minore
            if (nodo1>nodo2) {
                nodo_positivo_netlist[arco] = nodo2;
            }
            num_resistori += 1;
        }
        else {
            cout << "Componente " << componente << " non riconosciuta!" << endl;
            return 1;
        }
    }
    // abbiamo costruito il grafo coi pesi

    // costruzione dei cicli fondamentali:
    std::map<std::vector<int>, std::vector<int>> mappa = de_pina(grafo);
    
    vector<undirected_edge<int>> archi = grafo.all_edges();
    int num_archi = archi.size();

    vector<vector<int>> tutte_maglie;
    for (const auto& coppia: mappa) {
        vector<int> maglia = coppia.first; //prima maglia
        tutte_maglie.push_back(maglia);
    }
    int num_maglie = tutte_maglie.size();

    //controllo numero maglie = |E|-|V|+1
    int num_nodi = (grafo.all_nodes()).size();
    if (num_maglie != num_archi - num_nodi + 1) {
        cout << "Numero di maglie errato!" << endl;
        return 1; 
    }


    //costruiamo B matrice incidenza
    // 1. verso di percorrenza di quella maglia: com'è stato trovato il cammino minimo in de pina
    // 2. in che verso sono messe le resistenze (+ e -)? percorse da nodo minore a nodo maggiore
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> B = Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>::Zero(num_resistori, num_maglie); //matrice di double
      
    vector<undirected_edge<int>> archi_resistori;
    for (const auto& arco: archi) {
        if ((nomi[arco])[0]=='R') {
            archi_resistori.push_back(arco);
        }
    }
    // riempio B:
    for (int colonna=0; colonna<num_maglie; colonna++) { // per ogni maglia
        vector<int> maglia = tutte_maglie[colonna];
        int n = maglia.size();
        for (int riga=0; riga<num_resistori; riga++) { // per ogni resistore
            undirected_edge<int> arco_res = archi_resistori[riga];
            int nodo_pos = nodo_positivo_netlist[arco_res];
            for (int j=1; j<n; j++) {
                int nodo_da = maglia[j-1];
                int nodo_a = maglia[j];
                undirected_edge<int> arco_maglia(nodo_da, nodo_a);
                if (arco_res == arco_maglia) { // se appartiene alla maglia, in particolare all'arco
                    if (nodo_pos == nodo_da) { // se R viene percorso da + a - => dà contributo positivo
                        B(riga,colonna)=1.0;
                    }
                    else {
                        B(riga,colonna)=-1.0;
                    }
                }
            }
        }
    }
    
    /*
    cout << endl;
    //stampo matrice B per vedere gli errori
    cout << "Matrice B:" << endl;
    for (int i=0; i<num_resistori; i++) {
        for (int j=0; j<num_maglie; j++) {
            cout << B(i,j) << "   ";
            if (j==num_maglie-1) {
                cout << endl;
            }
        }
    }
    cout << endl;
    */

    //memorizzo i pesi/valori delle resistenze in un vettore
    vector<double> valori_R;
    for (const auto& arco: archi_resistori) {
        valori_R.push_back(pesi[arco]);
    }
    
    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(num_resistori,num_resistori); //riempio la matrice R
    for (int i=0; i<num_resistori; i++) {
        R(i,i)=valori_R[i];
    }



    //stessa cosa per vettore v
    Eigen::VectorXd v = Eigen::VectorXd::Zero(num_maglie); //inizializzo il vettore v
    
    vector<undirected_edge<int>> archi_generatori;
    for (const auto& arco: archi) {
        if ((nomi[arco])[0]=='V') {
            archi_generatori.push_back(arco);
        }
    }
    //riempo vettore v:
    for (int i=0; i<num_maglie; i++) { //per ogni maglia, cioè scorro le righe del vettore v
        vector<int> maglia = tutte_maglie[i];
        int n = maglia.size();
        for (int j=0; j<num_generatori; j++) { //per ogni generatore memorizzato in archi_generatore
            undirected_edge<int> arco_gen = archi_generatori[j];
            int nodo_pos = nodo_positivo_netlist[arco_gen];
            for (int k=1; k<n; k++) { //per ogni arco della maglia in questione
                int nodo_da = maglia[k-1];
                int nodo_a = maglia[k];
                undirected_edge<int> arco_maglia(nodo_da, nodo_a);
                if (arco_maglia == arco_gen) { // se quel generatore appartiene a quell'arco
                    if (nodo_pos == nodo_a) {
                        v(i) += pesi[arco_gen];
                    }
                    else {
                        v(i) -= pesi[arco_gen];
                    }
                }
            }
        }
    }
    
    /*
    //stampo vettore v per vedere gli errori
    cout << "Vettore v:" << endl;
    for (int i=0; i<num_maglie; i++) {
        cout << v(i) << endl;
    }
    */


    //la matrice A è data da A=B'*R*B e uso il gradiente coniugato per risolvere il sistema 
    Eigen::MatrixXd A = B.transpose()*R*B; 

    const double tol = 1.0e-15; //tolleranza per il controllo della matrice
    const unsigned int it_max = 10000; //numero massimo di iterazioni 
    unsigned int it = 0; //contatore iniziale 
    const double res_tol = 1.0e-12; //tolleranza del residuo 
    
    //risolviamo il sistema e troviamo un vettore i di correnti
    Eigen::VectorXd i = gradiente_coniugato<double>(A, v, it, it_max, tol, res_tol);

    //ora le tensioni V
    Eigen::VectorXd V = R*B*i;
    Eigen::VectorXd I_reali = B*i;
    
    //stampa dei risultati
    int j=0;
    for (const auto& arco: archi_resistori) {
        cout << nomi[arco] << ": V = " << V[j] << " volts , I_reali = " << I_reali[j] << " amps." << endl;
        j++;
    }

    return 0;
}