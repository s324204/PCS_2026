#pragma once
#include <iostream>
#include <concepts> // header per std::integral
#include <numeric>

/* L’obiettivo di questa esercitazione `e l’implementazione di una classe rational che implementi i
numeri razionali (ovvero quelli appartenenti all’insieme Q). Lo scheletro iniziale di tale classe
potrebbe essere il seguente: */
using namespace std;

template<typename I> requires std::integral<I> // “∀I” “tale che I è un intero”
class rational { 
    //class come le structs (= cioè definisco un nuovo tipo di variabile, i rational) ma inaccessibili
    I num_;  // _ per distinguere membri della classe dai parametri delle funzioni
    I den_;

public:
    /* costruttore di default */
    rational()
        : num_(I{0}), den_(I{1})
    {}                            

    /* costruttore user-defined */
    rational(const I& num, const I& den)
        : num_(num), den_(den)
    {   if (den_ == 0) {
            if (num_ == 0) {
                cout << "Nan" << endl;
            }
            else if (num_>0) {
                cout << "+Inf" << endl;
            }
            else {
                cout << "-Inf" << endl;
            }
        }
    }                                     
    
    /* metodi che restituiscono numeratore e denominatore*/
    I num() const { return num_; }
    I den() const { return den_; }

/* PRODOTTO */
    /* implemento *= fra frazioni */
    rational& operator*=(const rational& frazione) {
        if ((den_ == 0 && num_ == 0) || (frazione.den_ == 0 && frazione.num_ == 0)) {
            num_ = 0; den_ = 0;
            return *this;
        }

        else if ((num_ == 0 && frazione.den_ == 0) || (den_ == 0 && frazione.num_ == 0)) {
            num_ = 0; den_ = 0;
            return *this;
        }

        else if (den_ == 0 || frazione.den_ == 0) {
            if ((num_ > 0 && frazione.num_ > 0) || (num_ < 0 && frazione.num_ < 0)) {
                num_ = 1; // +Inf
            }
            else {
                num_ = -1; // -Inf
            }
            den_ = 0;
            return *this;
        }
        // se sono ben def  finiti:
        else {
            num_ *= frazione.num_;
            den_ *= frazione.den_;
            return *this;
        }
    }

    /* implemento prodotto fra frazioni */
    rational operator*(const rational& frazione) const {
        rational ris = *this;
        ris *= frazione;
        return ris;
    }

/* SOMMA */    
    /* implemento incremento fra frazioni */
    rational& operator+=(const rational& frazione) { //frazione sarà un numero del tipo rational(num,den)
        if ((den_ == 0 && num_ == 0) || (frazione.den_ == 0 && frazione.num_ == 0)) {
            num_ = 0; den_ = 0;
            return *this;
        }
        else if (den_ == 0 || frazione.den_ == 0) {
            if (den_ == 0 && frazione.den_ == 0) {
                if (num_ != frazione.num_) {
                    num_ = 0; den_ = 0; // Inf + (-Inf) = NaN
                }
            }
            else if (den_ != 0) {
                num_ = frazione.num_;
                den_ = 0; // Inf + numero finito = Inf
            }
            return *this;
        }
        
        else { // numeri ben def  --> a/b + c/d = (ad + bc)/bd 
            num_ = num_*frazione.den_ + den_*frazione.num_; // modifica direttamente num_
            den_ *= frazione.den_; // e den_
            return *this; // riferimento all'oggetto (num_ e den_ ?)
        }
    }
    
    /* implemento somma fra frazioni */
    rational operator+(const rational& frazione) const {
        rational ris = *this; // ris = risultato
        ris += frazione;
        return ris;
    }

/* SOTTRAZIONE --> a/b - c/d = (ad - bc)/bd */
    rational& operator-=(const rational& frazione) { //frazione sarà un numero del tipo rational(num,den)
        /* num_ *= frazione.den_;
        num_ -= den_*frazione.num_;
        //num_ = num_*frazione.den_ - den_*frazione.num_;
        den_ *= frazione.den_;
        -OPPURE: */
        rational neg_frazione(-frazione.num(),frazione.den());
        *this += neg_frazione;
        return *this;
    }
    rational operator-(const rational& frazione) const {
        rational ris = *this; // ris = risultato
        ris -= frazione;
        return ris;
    }
        
/* DIVISIONE */
    rational& operator/=(const rational& frazione) { //frazione sarà un numero del tipo rational(num,den)
        /* num_ /= frazione.num_; // modifica direttamente num_
        den_ /= frazione.den_; // e den_
        OPPURE */
        rational reciproco(frazione.den(), frazione.num());
        *this *= reciproco;
        return *this;
    }
    rational operator/(const rational& frazione) const {
        rational ris = *this;
        ris /= frazione;
        return ris;
    }

}

std::ostream&
operator<<(ostream& output, const rational<I>& numero)
{
    output << "(" << numero.num() << "," << numero.den() << ")";
    return output;
}

/* Si implementi quanto segue:
• Un costruttore di default che inizializzi opportunamente num_ e den_;
• Un costruttore user-defined che inizializzi num e den con i valori specificati dall’utente. 
  Se viene specificato il valore zero per den il programma NON deve uscire con errore ma deve gestire opportun. 
  questo caso e continuare a funzionare. Si prenda per esempio spunto da Inf e NaN dei numeri floating point 
  e si documenti opportunamente le proprie scelte: per esempio, num!=0 mentre den=0 potrebbe rappresentare Inf, 
  mentre num=den=0 potrebbe implementare il NaN. 
  Di conseguenza, per esempio, un qualsiasi rational sommato ad Inf deve dare Inf, mentre un qualsiasi rational 
  sommato a NaN deve dare NaN;
• I metodi num() e den() per ottenere rispettivamente numeratore e denominatore;
• L’operatore << per la stampa di un oggetto della classe rational;
• Le operazioni +=, +, -=, -, *=, *, /=, /
`
E' inoltre richiesto che la rappresentazione interna delle frazioni (quindi num_ e den_) sia sempre
correttamente semplificata. Per esempio, il programma qui sotto non dovr`a stampare 3/6 ma 1/2.
int main(void)
{
    rational<int> r(3,6);
    std::cout << r << "\n";
    return 0;
}
*/