//
// Created by alesso on 28/09/25.
//

#include "NodoBPlus.h"

int NodoBPlus::buscarPosicion(const string &clave) {
    int i = 0;
    while (i < numClaves && clave > claves[i]) {
        i++;
    }
    return i;
}

void NodoBPlus::insertarEnHoja(const string &genero, Libro *libro) {
    int pos = buscarPosicion(genero);

    if (pos < numClaves && claves[pos] == genero) {
        listas[pos]->insertar(libro);
        return;
    }

    for (int i = numClaves; i > pos; i--) {
        claves[i] = claves[i - 1];
        listas[i] = listas[i - 1];
    }

    claves[pos] = genero;
    listas[pos] = new ListaEnlazada();
    listas[pos]->insertar(libro);
    numClaves++;
}

void NodoBPlus::insertarNoLleno(const string &genero, Libro *libro) {
    if (esHoja) {
        insertarEnHoja(genero, libro);
    } else {
        int i = buscarPosicion(genero);

        if (hijos[i]->numClaves == 2 * grado - 1) {
            dividirHijo(i, hijos[i]);

            if (genero > claves[i]) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(genero, libro);
    }
}

void NodoBPlus::dividirHijo(int indice, NodoBPlus *hijo) {
    NodoBPlus *nuevoNodo = new NodoBPlus(hijo->grado, hijo->esHoja);
    nuevoNodo->numClaves = grado - 1;

    for (int j = 0; j < grado - 1; j++) {
        nuevoNodo->claves[j] = hijo->claves[j + grado];

        if (hijo->esHoja) {
            nuevoNodo->listas[j] = hijo->listas[j + grado];
            hijo->listas[j + grado] = nullptr;
        }
    }

    if (!hijo->esHoja) {
        for (int j = 0; j < grado; j++) {
            nuevoNodo->hijos[j] = hijo->hijos[j + grado];
        }
    } else {
        nuevoNodo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevoNodo;
    }

    hijo->numClaves = grado - 1;

    for (int j = numClaves; j >= indice + 1; j--) {
        hijos[j + 1] = hijos[j];
    }
    hijos[indice + 1] = nuevoNodo;

    for (int j = numClaves - 1; j >= indice; j--) {
        claves[j + 1] = claves[j];
    }

    string clavePromovida = hijo->esHoja ? hijo->claves[grado - 1] : hijo->claves[grado - 1];
    claves[indice] = clavePromovida;
    numClaves++;
}

ListaEnlazada *NodoBPlus::buscarGenero(const string &genero) {
    if (esHoja) {
        int pos = buscarPosicion(genero);
        if (pos < numClaves && claves[pos] == genero) {
            return listas[pos];
        }
        return nullptr;
    } else {
        int pos = buscarPosicion(genero);
        return hijos[pos]->buscarGenero(genero);
    }
}

NodoBPlus *NodoBPlus::obtenerPrimeraHoja() {
    if (esHoja) {
        return this;
    } else {
        return hijos[0]->obtenerPrimeraHoja();
    }
}

void NodoBPlus::recorrerHojas() {
    if (esHoja) {
        for (int i = 0; i < numClaves; i++) {
            cout << "GENERO: " << claves[i] << " (" << listas[i]->obtenerTamaño() << " LIBROS)\n";
            listas[i]->mostrarLibros();
        }
    }
}
