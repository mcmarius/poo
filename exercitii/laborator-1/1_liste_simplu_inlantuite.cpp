#include <iostream>
#include <sstream>

#include "lista_simpla.h"

void verifica_lista_simpla() {
    lista_simpla l1, l2;

    std::cout << "l1: ";
    l1.afisare();
    std::cout << "l2: ";
    l2.afisare();
    l1.adauga(1);
    l2.adauga(2);
    std::cout << "l1: ";
    l1.afisare();
    std::cout << "l2: ";
    l2.afisare();
    {
        lista_simpla l3{l1};
        std::cout << "l1: ";
        l1.afisare();
        std::cout << "l3: ";
        l3.afisare();
        l3.adauga(3, false);
        std::cout << "l1: ";
        l1.afisare();
        std::cout << "l3: ";
        l3.afisare();
    }
    std::cout << "l1: ";
    l1.afisare();
    {
        lista_simpla l4;
        l4.adauga(4);
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
        l2 = l4;
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
        l4.adauga(5, false);
        std::cout << "l2: ";
        l2.afisare();
        std::cout << "l4: ";
        l4.afisare();
    }    
    std::cout << "l2: ";
    l2.afisare();
}

int main() {
    verifica_lista_simpla();
    lista_simpla lista;
    lista.afisare();
    lista.adauga(1);
    lista.afisare();
    lista.adauga(3);
    lista.afisare();
    lista.adauga(2, false);
    lista.afisare();
    lista.adauga(2);
    lista.adauga_val_poz(10, 2); // indexare de la 1
    lista.afisare();
    // std::cout << lista;
    lista.elimina_poz(2);
    lista.afisare();
    // std::cout << lista;
    lista.elimina_val(2);
    lista.afisare();
    // std::cout << lista;
    lista.modifica_val_poz(1, 14);
    lista.afisare();
    // std::cout << lista;

    std::ostringstream output;
    output << "start: ";
    output << lista;
    output << "gata\n";
    std::cout << output.str();
    return 0;
}
