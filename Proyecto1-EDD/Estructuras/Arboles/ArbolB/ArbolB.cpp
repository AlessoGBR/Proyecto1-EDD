//
// Created by alesso on 28/09/25.
//

#include "ArbolB.h"

ArbolB::ArbolB(int gradoMinimo) {
    raiz = nullptr;
    grado = gradoMinimo;
    tamaño = 0;
}

ArbolB::~ArbolB() {
    limpiar();
}

void ArbolB::limpiarRec(NodoB *nodo) {
    if (nodo != nullptr) {
        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                limpiarRec(nodo->hijos[i]);
            }
        }
        delete nodo;
    }
}

void ArbolB::insertar(Libro *libro) {
    if (libro == nullptr) return;

    int anio = libro->getAño();

    if (raiz == nullptr) {
        raiz = new NodoB(grado, true);
        raiz->claves[0] = anio;
        raiz->libros[0] = libro;
        raiz->numClaves = 1;
        tamaño++;
        return;
    }

    if (raiz->numClaves == 2 * grado - 1) {
        NodoB *nuevaRaiz = new NodoB(grado, false);
        nuevaRaiz->hijos[0] = raiz;
        nuevaRaiz->dividirHijo(0, raiz);

        int i = 0;
        if (nuevaRaiz->claves[0] < anio) {
            i++;
        }
        nuevaRaiz->hijos[i]->insertarNoLleno(anio, libro);

        raiz = nuevaRaiz;
    } else {
        raiz->insertarNoLleno(anio, libro);
    }

    tamaño++;
}

Libro *ArbolB::buscarPorAño(int anio) {
    return (raiz == nullptr) ? nullptr : raiz->buscar(anio);
}

ListaEnlazada *ArbolB::buscarPorRangoFechas(int anioInicio, int anioFin) {
    ListaEnlazada *resultados = new ListaEnlazada();

    if (raiz != nullptr && anioInicio <= anioFin) {
        raiz->buscarRango(anioInicio, anioFin, resultados);
    }

    return resultados;
}

bool ArbolB::estaVacio() const {
    return raiz == nullptr;
}

int ArbolB::obtenerTamaño() const {
    return tamaño;
}

int ArbolB::obtenerGrado() const {
    return grado;
}

void ArbolB::mostrarLibrosOrdenados() {
    if (raiz == nullptr) {
        cout << "--------------------------------------------------\n";
        cout << "NO HAY LIBROS EN EL ARBOL.\n";
        return;
    }

    cout << "--------------------------------------------------\n";
    cout << "LIBROS ORDENADOS POR AÑO:\n";
    raiz->recorrer();
    cout << "--------------------------------------------------\n";
}

void ArbolB::mostrarEstadisticas() {
    cout << "--------------------------------------------------\n";
    cout << "ESTADÍSTICAS DEL ÁRBOL B:\n";
    cout << "NUMERO TOTAL DE LIBROS: " << tamaño << "\n";
    cout << "GRADOM INIMO: " << grado << "\n";
    cout << "¿ESTA VACIO?: " << (estaVacio() ? "SI" : "NO") << "\n";
    cout << "--------------------------------------------------\n";
}

void ArbolB::limpiar() {
    limpiarRec(raiz);
    raiz = nullptr;
    tamaño = 0;
}

ListaEnlazada *ArbolB::obtenerAñosUnicos() {
    ListaEnlazada *años = new ListaEnlazada();
    if (raiz != nullptr) {
        obtenerAñosRec(raiz, años);
    }
    return años;
}

void ArbolB::obtenerAñosRec(NodoB *nodo, ListaEnlazada *años) {
    if (nodo != nullptr) {
        int i;
        for (i = 0; i < nodo->numClaves; i++) {
            if (!nodo->esHoja) {
                obtenerAñosRec(nodo->hijos[i], años);
            }
            Libro *añoLibro = new Libro("", "", "", nodo->claves[i], "");
            años->insertar(añoLibro);
        }

        if (!nodo->esHoja) {
            obtenerAñosRec(nodo->hijos[i], años);
        }
    }
}

NodoB *ArbolB::obtenerRaiz() {
    return raiz;
}
