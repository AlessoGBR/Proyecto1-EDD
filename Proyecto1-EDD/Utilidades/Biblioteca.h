//
// Created by alesso on 26/09/25.
//

#ifndef PROYECTO1_EDD_BIBLIOTECA_H
#define PROYECTO1_EDD_BIBLIOTECA_H

#include "../Objetos/Libro.h"
#include "../Estructuras/ListaEnlazada/ListaEnlazada.h"
#include "../Estructuras/Arboles/ArbolAVL/ArbolAVL.h"
#include "CargadorDatos.h"

class Biblioteca {
private:
    ListaEnlazada *listaBusquedaSecuencial;
    ArbolAVL *arbolTitulos;
    ArbolB *arbolFechas;
    ArbolBPlus *arbolGeneros;

    ListaEnlazada *todosLosLibros;

    CargadorDatos *cargador;

public:
    Biblioteca();

    ~Biblioteca();

    int cargarCatalogo(const string &rutaArchivo);

    bool agregarLibro(const string &titulo, const string &isbn, const string &genero,
                      int anio, const string &autor);

    bool eliminarLibro(const string& isbn);

    Libro *buscarPorTitulo(const string &titulo);

    Libro *buscarPorTituloSecuencial(const string &titulo);

    Libro *buscarPorISBN(const string &isbn);

    ListaEnlazada *buscarPorGenero(const string &genero);

    ListaEnlazada *buscarPorRangoFechas(int anioInicio, int anioFin);

    void listarPorTitulo();

    void compararBusquedaPorTitulo(const string &titulo);

    void compararBusquedaPorISBN(const string &isbn);

    void mostrarEstadisticas();

    void mostrarEstadisticasPorGenero();

    int obtenerTotalLibros() const;

    void generarGraficas();
};

#endif //PROYECTO1_EDD_BIBLIOTECA_H
