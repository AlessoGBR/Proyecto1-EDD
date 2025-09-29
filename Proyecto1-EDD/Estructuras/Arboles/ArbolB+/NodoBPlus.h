//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_NODOBPLUS_H
#define PROYECTO1_EDD_NODOBPLUS_H
#include <iostream>
#include <string>
#include "../../ListaEnlazada/ListaEnlazada.h"
#include "../../../Objetos/Libro.h"

class NodoBPlus {
public:
    string *claves;
    ListaEnlazada **listas;
    NodoBPlus **hijos;
    NodoBPlus *siguiente;
    int numClaves;
    bool esHoja;
    int grado;

    NodoBPlus(int gradoMinimo, bool hoja) {
        grado = gradoMinimo;
        esHoja = hoja;
        numClaves = 0;
        siguiente = nullptr;

        claves = new string[2 * grado - 1];

        if (esHoja) {
            listas = new ListaEnlazada *[2 * grado - 1];
            hijos = nullptr;

            for (int i = 0; i < 2 * grado - 1; i++) {
                claves[i] = "";
                listas[i] = nullptr;
            }
        } else {
            listas = nullptr;
            hijos = new NodoBPlus *[2 * grado];

            for (int i = 0; i < 2 * grado - 1; i++) {
                claves[i] = "";
            }
            for (int i = 0; i < 2 * grado; i++) {
                hijos[i] = nullptr;
            }
        }
    }

    ~NodoBPlus() {
        delete[] claves;

        if (esHoja && listas != nullptr) {
            for (int i = 0; i < numClaves; i++) {
                delete listas[i];
            }
            delete[] listas;
        }

        if (!esHoja && hijos != nullptr) {
            delete[] hijos;
        }
    }

    int buscarPosicion(const string &clave);

    void insertarEnHoja(const string &genero, Libro *libro);

    void insertarNoLleno(const string &genero, Libro *libro);

    void dividirHijo(int indice, NodoBPlus *hijo);

    ListaEnlazada *buscarGenero(const string &genero);

    NodoBPlus *obtenerPrimeraHoja();

    void mostrarEstructura(const string &prefijo, bool esUltimo, int nivel);

    void recorrerHojas();
};


#endif //PROYECTO1_EDD_NODOBPLUS_H
