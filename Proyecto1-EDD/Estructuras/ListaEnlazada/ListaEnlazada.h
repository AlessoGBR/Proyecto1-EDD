//
// Created by alesso on 23/09/25.
//

#ifndef PROYECTO1_EDD_LISTAENLAZADA_H
#define PROYECTO1_EDD_LISTAENLAZADA_H

#include "../../Objetos/Libro.h"
#include "NodoLista.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

class ListaEnlazada {
private:
    NodoLista *cabeza;
    int tamaño;

public:
    ListaEnlazada() : cabeza(nullptr), tamaño(0) {
    }

    ~ListaEnlazada() {
        limpiar();
    }

    void insertar(Libro *libro);

    void insertarAlInicio(Libro *libro);

    Libro *buscarPorTitulo(const string &titulo);

    Libro *buscarPorISBN(const string &isbn);

    ListaEnlazada *buscarPorGenero(const string &genero);

    ListaEnlazada *buscarPorRangoFechas(int anioInicio, int anioFin);

    bool eliminar(const string &isbn);

    bool estaVacia() const;

    int obtenerTamaño() const;

    void mostrarLibros() const;

    void limpiar();

    NodoLista *obtenerCabeza();

    Libro **convertirAArray() const;
};

#endif //PROYECTO1_EDD_LISTAENLAZADA_H
