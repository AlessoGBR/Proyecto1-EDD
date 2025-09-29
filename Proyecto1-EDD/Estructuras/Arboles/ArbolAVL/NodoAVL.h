//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_NODOAVL_H
#define PROYECTO1_EDD_NODOAVL_H
#include "../../../Objetos/Libro.h"

class NodoAVL {
public:
    Libro *libro;
    NodoAVL *izquierdo;
    NodoAVL *derecho;
    int altura;

    NodoAVL(Libro *lib) : libro(lib), izquierdo(nullptr), derecho(nullptr), altura(1) {
    }

    ~NodoAVL() {

    }
};


#endif //PROYECTO1_EDD_NODOAVL_H