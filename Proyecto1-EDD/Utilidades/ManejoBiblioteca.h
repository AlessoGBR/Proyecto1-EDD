//
// Created by alesso on 29/09/25.
//

#ifndef PROYECTO1_EDD_MANEJOBIBLIOTECA_H
#define PROYECTO1_EDD_MANEJOBIBLIOTECA_H
#include "Biblioteca.h"


class ManejoBiblioteca {
public:
    Biblioteca *biblioteca;

    void mostrarMenu(Biblioteca *biblioteca);

    void inicio();

    void menu();


    ManejoBiblioteca();
};


#endif //PROYECTO1_EDD_MANEJOBIBLIOTECA_H
