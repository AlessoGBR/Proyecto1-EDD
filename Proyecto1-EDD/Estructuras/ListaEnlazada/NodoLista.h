//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_NODOLISTA_H
#define PROYECTO1_EDD_NODOLISTA_H
#include "../../Objetos/Libro.h"

class NodoLista {
public:
    Libro *libro;
    NodoLista *siguiente;

    NodoLista(Libro *lib) : libro(lib), siguiente(nullptr) {
    }

    ~NodoLista() {
    }
};


#endif //PROYECTO1_EDD_NODOLISTA_H
