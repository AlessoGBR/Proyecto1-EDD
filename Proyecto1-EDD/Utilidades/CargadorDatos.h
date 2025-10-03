//
// Created by alesso on 27/09/25.
//

#ifndef PROYECTO1_EDD_CARGARDATOS_H
#define PROYECTO1_EDD_CARGARDATOS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../Objetos/Libro.h"
#include "../Estructuras/Arboles/ArbolAVL/ArbolAVL.h"
#include "../Estructuras/Arboles/ArbolB/ArbolB.h"
#include "../Estructuras/Arboles/ArbolB+/ArbolBPlus.h"
using namespace std;

class CargadorDatos {
private:
    string limpiarEspacios(const string &str);

    string limpiarComillas(const string &str);

    bool parsearLineaCSV(const string &linea, string &titulo, string &isbn,
                         string &genero, int &anio, string &autor);

    bool validarISBN(const string &isbn, ListaEnlazada *listaExistente);

    bool validarAnio(int anio);

public:
    CargadorDatos();

    ~CargadorDatos();

    ListaEnlazada *cargarDesdeCSV(const string &rutaArchivo);

    bool validarFormatoCSV(const string &rutaArchivo);
};


#endif //PROYECTO1_EDD_CARGARDATOS_H
