//
// Created by alesso on 23/09/25.
//


#include "ListaEnlazada.h"

void ListaEnlazada::insertar(Libro *libro) {
    if (libro == nullptr) return;

    NodoLista *nuevoNodo = new NodoLista(libro);

    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
    } else {
        NodoLista *actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
    tamaño++;
}

void ListaEnlazada::insertarAlInicio(Libro *libro) {
    if (libro == nullptr) return;

    NodoLista *nuevoNodo = new NodoLista(libro);
    nuevoNodo->siguiente = cabeza;
    cabeza = nuevoNodo;
    tamaño++;
}

Libro *ListaEnlazada::buscarPorTitulo(const string &titulo) {
    NodoLista *actual = cabeza;
    while (actual != nullptr) {
        if (actual->libro->getTitulo() == titulo) {
            return actual->libro;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

Libro *ListaEnlazada::buscarPorISBN(const string &isbn) {
    NodoLista *actual = cabeza;
    while (actual != nullptr) {
        if (actual->libro->getIsbn() == isbn) {
            return actual->libro;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

ListaEnlazada *ListaEnlazada::buscarPorGenero(const string &genero) {
    ListaEnlazada *resultados = new ListaEnlazada();
    NodoLista *actual = cabeza;

    while (actual != nullptr) {
        if (actual->libro->getGenero() == genero) {
            resultados->insertar(actual->libro);
        }
        actual = actual->siguiente;
    }

    return resultados;
}

ListaEnlazada *ListaEnlazada::buscarPorRangoFechas(int anioInicio, int anioFin) {
    ListaEnlazada *resultados = new ListaEnlazada();
    NodoLista *actual = cabeza;

    while (actual != nullptr) {
        int anioLibro = actual->libro->getAño();
        if (anioLibro >= anioInicio && anioLibro <= anioFin) {
            resultados->insertar(actual->libro);
        }
        actual = actual->siguiente;
    }

    return resultados;
}

bool ListaEnlazada::eliminar(const string &isbn) {
    if (cabeza == nullptr) return false;

    if (cabeza->libro->getIsbn() == isbn) {
        NodoLista *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        tamaño--;
        return true;
    }

    NodoLista *actual = cabeza;
    while (actual->siguiente != nullptr) {
        if (actual->siguiente->libro->getIsbn() == isbn) {
            NodoLista *temp = actual->siguiente;
            actual->siguiente = actual->siguiente->siguiente;
            delete temp;
            tamaño--;
            return true;
        }
        actual = actual->siguiente;
    }

    return false;
}

bool ListaEnlazada::estaVacia() const {
    return cabeza == nullptr;
}

int ListaEnlazada::obtenerTamaño() const {
    return tamaño;
}

void ListaEnlazada::mostrarLibros() const {
    if (cabeza == nullptr) {
        cout << "NO HAY LIBROS EN LA LISTA.\n";
        return;
    }

    NodoLista *actual = cabeza;
    int contador = 1;

    cout << "\n=== LISTA DE LIBROS ===\n";
    while (actual != nullptr) {
        cout << contador << ". ";
        cout << "TITULO: " << actual->libro->getTitulo() << " | ";
        cout << "ISBN: " << actual->libro->getIsbn() << " | ";
        cout << "GENERO: " << actual->libro->getGenero() << " | ";
        cout << "ANIO: " << actual->libro->getAño() << " | ";
        cout << "AUTOR: " << actual->libro->getAutor() << "\n";

        actual = actual->siguiente;
        contador++;
    }
    cout << "========================\n";
}

void ListaEnlazada::limpiar() {
    while (cabeza != nullptr) {
        NodoLista *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
    tamaño = 0;
}

NodoLista *ListaEnlazada::obtenerCabeza() {
    return cabeza;
}

Libro **ListaEnlazada::convertirAArray() const {
    if (tamaño == 0) return nullptr;

    Libro **array = new Libro *[tamaño];
    NodoLista *actual = cabeza;
    int index = 0;

    while (actual != nullptr && index < tamaño) {
        array[index] = actual->libro;
        actual = actual->siguiente;
        index++;
    }

    return array;
}
