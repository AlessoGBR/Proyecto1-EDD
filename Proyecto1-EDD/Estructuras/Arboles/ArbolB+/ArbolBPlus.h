//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_ARBOLBPLUS_H
#define PROYECTO1_EDD_ARBOLBPLUS_H
#include <string>
#include "NodoBPlus.h"

class ArbolBPlus {
private:
    NodoBPlus *raiz;
    int grado;
    int tamaño;
    NodoBPlus *primeraHoja;

    void limpiarRec(NodoBPlus *nodo);

public:
    ArbolBPlus(int gradoMinimo = 3) {
        raiz = nullptr;
        grado = gradoMinimo;
        tamaño = 0;
        primeraHoja = nullptr;
    }

    ~ArbolBPlus() {
        limpiar();
    }

    void insertar(Libro *libro);

    ListaEnlazada *buscarPorGenero(const string &genero);

    ListaEnlazada *obtenerGeneros();

    bool estaVacio() const;

    int obtenerTamaño() const;

    int obtenerGrado() const;

    void mostrarLibrosPorGenero();

    void mostrarEstructura();

    void mostrarEstadisticas();

    void mostrarEstadisticasPorGenero();

    void limpiar();

    void recorridoSecuencial();
};


#endif //PROYECTO1_EDD_ARBOLBPLUS_H
