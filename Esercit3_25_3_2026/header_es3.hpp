#pragma once
#include <iostream>
#include <concepts> // header per std::integral
#include <numeric>

// main 

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