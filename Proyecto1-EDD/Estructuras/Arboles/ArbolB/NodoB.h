//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_NODOB_H
#define PROYECTO1_EDD_NODOB_H

#include "../../ListaEnlazada/ListaEnlazada.h"
#include "../../../Objetos/Libro.h"
#include <string>

class NodoB {
public:
    int *claves;
    Libro **libros;
    NodoB **hijos;
    int numClaves;
    bool esHoja;
    int grado;

    NodoB(int gradoMinimo, bool hoja) {
        grado = gradoMinimo;
        esHoja = hoja;
        numClaves = 0;

        claves = new int[2 * grado - 1];
        libros = new Libro *[2 * grado - 1];
        hijos = new NodoB *[2 * grado];

        for (int i = 0; i < 2 * grado - 1; i++) {
            claves[i] = 0;
            libros[i] = nullptr;
        }
        for (int i = 0; i < 2 * grado; i++) {
            hijos[i] = nullptr;
        }
    }

    ~NodoB() {
        delete[] claves;
        delete[] libros;
        delete[] hijos;
    }

    int buscarClave(int clave);

    void insertarNoLleno(int clave, Libro *libro);

    void dividirHijo(int indice, NodoB *hijo);

    void recorrer();

    Libro *buscar(int clave);

    void buscarRango(int anioInicio, int anioFin, ListaEnlazada *resultados);

};


#endif //PROYECTO1_EDD_NODOB_H
