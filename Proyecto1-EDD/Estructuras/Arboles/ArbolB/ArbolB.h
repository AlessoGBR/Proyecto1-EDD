//
// Created by alesso on 28/09/25.
//

#ifndef PROYECTO1_EDD_ARBOLB_H
#define PROYECTO1_EDD_ARBOLB_H

#include "NodoB.h"

class ArbolB {
private:
    NodoB *raiz;
    int grado;
    int tamaño;

    void limpiarRec(NodoB *nodo);

public:
    ArbolB(int gradoMinimo = 3);

    ~ArbolB();

    void insertar(Libro *libro);

    Libro *buscarPorAño(int anio);

    ListaEnlazada *buscarPorRangoFechas(int anioInicio, int anioFin);

    bool estaVacio() const;

    int obtenerTamaño() const;

    int obtenerGrado() const;

    void mostrarLibrosOrdenados();

    void mostrarEstadisticas();

    void limpiar();

    ListaEnlazada *obtenerAñosUnicos();

    NodoB *obtenerRaiz();

private:
    void obtenerAñosRec(NodoB *nodo, ListaEnlazada *años);
};


#endif //PROYECTO1_EDD_ARBOLB_H
