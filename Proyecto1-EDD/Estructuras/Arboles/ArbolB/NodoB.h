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

        // Alocar memoria para claves, libros e hijos
        // Alocar memoria para claves, libros e hijos
        claves = new int[2 * grado - 1];
        libros = new Libro *[2 * grado - 1];
        hijos = new NodoB *[2 * grado];

        // Inicializar arrays
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

    // Buscar una clave en este nodo
    int buscarClave(int clave);

    // Insertar una clave y libro cuando el nodo no está lleno
    void insertarNoLleno(int clave, Libro *libro);

    // Dividir un hijo lleno
    void dividirHijo(int indice, NodoB *hijo);

    // Recorrido del nodo para mostrar todas las claves
    void recorrer();

    // Buscar una clave específica en el subárbol
    Libro *buscar(int clave);

    // Buscar todos los libros en un rango de años
    void buscarRango(int anioInicio, int anioFin, ListaEnlazada *resultados);

    // Mostrar estructura del nodo
    void mostrarEstructura(const string &prefijo, bool esUltimo, int nivel);
};


#endif //PROYECTO1_EDD_NODOB_H
