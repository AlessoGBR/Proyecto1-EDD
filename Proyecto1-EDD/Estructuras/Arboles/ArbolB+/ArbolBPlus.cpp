//
// Created by alesso on 28/09/25.
//

#include "ArbolBPlus.h"

ArbolBPlus::ArbolBPlus(int gradoMinimo) {
    raiz = nullptr;
    grado = gradoMinimo;
    tamaño = 0;
    primeraHoja = nullptr;
}

ArbolBPlus::~ArbolBPlus() {
    limpiar();
}

void ArbolBPlus::limpiarRec(NodoBPlus *nodo) {
    if (nodo != nullptr) {
        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                limpiarRec(nodo->hijos[i]);
            }
        }
        delete nodo;
    }
}

void ArbolBPlus::insertar(Libro *libro) {
    if (libro == nullptr) return;

    string genero = libro->getGenero();

    if (raiz == nullptr) {
        raiz = new NodoBPlus(grado, true);
        raiz->insertarEnHoja(genero, libro);
        primeraHoja = raiz;
        tamaño++;
        return;
    }

    if (raiz->numClaves == 2 * grado - 1) {
        NodoBPlus *nuevaRaiz = new NodoBPlus(grado, false);
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->dividirHijo(0, raiz);

        int i = 0;
        if (genero > nuevaRaiz->claves[0]) {
            i++;
        }
        nuevaRaiz->hijos[i]->insertarNoLleno(genero, libro);

        raiz = nuevaRaiz;
        primeraHoja = raiz->obtenerPrimeraHoja();
    } else {
        raiz->insertarNoLleno(genero, libro);
    }

    tamaño++;
}

ListaEnlazada *ArbolBPlus::buscarPorGenero(const string &genero) {
    if (raiz == nullptr) {
        return new ListaEnlazada();
    }

    ListaEnlazada *resultado = raiz->buscarGenero(genero);
    if (resultado == nullptr) {
        return new ListaEnlazada();
    }

    ListaEnlazada *copia = new ListaEnlazada();
    NodoLista *actual = resultado->obtenerCabeza();
    while (actual != nullptr) {
        copia->insertar(actual->libro);
        actual = actual->siguiente;
    }

    return copia;
}

ListaEnlazada *ArbolBPlus::obtenerGeneros() {
    ListaEnlazada *generos = new ListaEnlazada();
    if (primeraHoja != nullptr) {
        NodoBPlus *actual = primeraHoja;
        while (actual != nullptr) {
            for (int i = 0; i < actual->numClaves; i++) {
                // Crear un "libro" temporal solo con el género
                Libro *generoLibro = new Libro("", "", actual->claves[i], 0, "");
                generos->insertar(generoLibro);
            }
            actual = actual->siguiente;
        }
    }
    return generos;
}

bool ArbolBPlus::estaVacio() const {
    return raiz == nullptr;
}

int ArbolBPlus::obtenerTamaño() const {
    return tamaño;
}

int ArbolBPlus::obtenerGrado() const {
    return grado;
}

void ArbolBPlus::mostrarLibrosPorGenero() {
    if (primeraHoja == nullptr) {
        cout << "--------------------------------------------------\n";
        cout << "NO HAY LIBROS EN EL ARBOL.\n";
        return;
    }
    cout << "--------------------------------------------------\n";
    cout << "LIBROS ORGANIZADOS POR GENERO:\n";
    NodoBPlus *actual = primeraHoja;
    while (actual != nullptr) {
        actual->recorrerHojas();
        actual = actual->siguiente;
    }
    cout << "--------------------------------------------------\n";
}

void ArbolBPlus::mostrarEstadisticas() {
    cout << "--------------------------------------------------\n";
    cout << "ESTADISTICAS DEL ARBOL B+:\n";
    cout << "NUMERO TOTAL DE LIBROS: " << tamaño << "\n";
    cout << "GRADO MINIMO: " << grado << "\n";
    cout << "¿ESTA VACIO?: " << (estaVacio() ? "SI" : "NO") << "\n";
    cout << "--------------------------------------------------\n";
}

void ArbolBPlus::limpiar() {
    limpiarRec(raiz);
    raiz = nullptr;
    primeraHoja = nullptr;
    tamaño = 0;
}

void ArbolBPlus::mostrarEstadisticasPorGenero() {
    if (primeraHoja == nullptr) {
        cout << "--------------------------------------------------\n";
        cout << "NO HAY GENEROS DISPONIBLES.\n";
        return;
    }
    cout << "--------------------------------------------------\n";
    cout << "ESTADISTICAS POR GENERO:\n";
    NodoBPlus *actual = primeraHoja;
    int totalGeneros = 0;

    while (actual != nullptr) {
        for (int i = 0; i < actual->numClaves; i++) {
            cout << "GENERO: " << actual->claves[i]
                    << " - CANTIDAD: " << actual->listas[i]->obtenerTamaño() << " LIBROS\n";
            totalGeneros++;
        }
        actual = actual->siguiente;
    }

    cout << "TOTAL DE GENEROS DIFERENTES: " << totalGeneros << "\n";
    cout << "--------------------------------------------------\n";
}

void ArbolBPlus::recorridoSecuencial() {
    cout << "--------------------------------------------------\n";
    cout << "RECORRIDO SECUENCIAL DE GENEROS:\n";
    if (primeraHoja == nullptr) {
        cout << "ARBOL VACIO\n";
        return;
    }

    NodoBPlus *actual = primeraHoja;
    int contador = 1;

    while (actual != nullptr) {
        for (int i = 0; i < actual->numClaves; i++) {
            cout << contador << ". " << actual->claves[i]
                    << " (" << actual->listas[i]->obtenerTamaño() << " LIBROS)\n";
            contador++;
        }
        actual = actual->siguiente;
    }
    cout << "--------------------------------------------------\n";
}
