//
// Created by alesso on 26/09/25.
//

#ifndef PROYECTO1_EDD_ARBOLAVL_H
#define PROYECTO1_EDD_ARBOLAVL_H

#include "../../../Objetos/Libro.h"
#include "../../ListaEnlazada/ListaEnlazada.h"
#include "NodoAVL.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

class ArbolAVL {
private:
    NodoAVL *raiz;
    int tamaño;

    int obtenerAlturaNodo(NodoAVL *nodo);

    int obtenerBalance(NodoAVL *nodo);

    void actualizarAltura(NodoAVL *nodo);

    // ROTACION DERECHA
    NodoAVL *rotarDerecha(NodoAVL *y);

    //ROTACION IZQUIERDA
    NodoAVL *rotarIzquierda(NodoAVL *x);

    // FUNCION RECURSIVA PARA INSERTAR
    NodoAVL *insertarRec(NodoAVL *nodo, Libro *libro);

    NodoAVL *obtenerMinimo(NodoAVL *nodo);

    NodoAVL *eliminarRec(NodoAVL *raiz, const string &titulo);

    NodoAVL *buscarRec(NodoAVL *nodo, const string &titulo);

    void inOrderRec(NodoAVL *nodo, ListaEnlazada *lista);

    void mostrarArbolRec(NodoAVL *nodo, const string &prefijo, bool esUltimo);

    void limpiarRec(NodoAVL *nodo);

    void convertirAArrayRec(NodoAVL *nodo, Libro **array, int &index);

public:
    ArbolAVL() : raiz(nullptr), tamaño(0) {
    }

    ~ArbolAVL() {
        limpiar();
    }

    void insertar(Libro *libro);

    Libro *buscarPorTitulo(const string &titulo);

    bool eliminar(const string &titulo);

    ListaEnlazada *obtenerLibrosOrdenados();

    bool estaVacio() const;

    int obtenerTamaño();

    int obtenerAltura();

    void mostrarArbol();

    void mostrarLibrosOrdenados();

    void limpiar();

    Libro **convertirAArrayOrdenado();

    Libro *busquedaBinariaEnArray(Libro **array, int tamaño, const string &titulo);

    void mostrarEstadisticas();
};

#endif //PROYECTO1_EDD_ARBOLAVL_H
