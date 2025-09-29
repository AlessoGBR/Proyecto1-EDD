//
// Created by alesso on 28/09/25.
//

#include "NodoB.h"

int NodoB::buscarClave(int clave) {
    int i = 0;
    while (i < numClaves && clave > claves[i]) {
        i++;
    }
    return i;
}

void NodoB::insertarNoLleno(int clave, Libro *libro) {
    int i = numClaves - 1;

    if (esHoja) {
        while (i >= 0 && claves[i] > clave) {
            claves[i + 1] = claves[i];
            libros[i + 1] = libros[i];
            i--;
        }

        claves[i + 1] = clave;
        libros[i + 1] = libro;
        numClaves++;
    } else {
        while (i >= 0 && claves[i] > clave) {
            i--;
        }
        i++;

        if (hijos[i]->numClaves == 2 * grado - 1) {
            dividirHijo(i, hijos[i]);

            if (claves[i] < clave) {
                i++;
            }
        }
        hijos[i]->insertarNoLleno(clave, libro);
    }
}

void NodoB::dividirHijo(int indice, NodoB *hijo) {
    NodoB *nuevoNodo = new NodoB(hijo->grado, hijo->esHoja);
    nuevoNodo->numClaves = grado - 1;

    for (int j = 0; j < grado - 1; j++) {
        nuevoNodo->claves[j] = hijo->claves[j + grado];
        nuevoNodo->libros[j] = hijo->libros[j + grado];
    }

    if (!hijo->esHoja) {
        for (int j = 0; j < grado; j++) {
            nuevoNodo->hijos[j] = hijo->hijos[j + grado];
        }
    }

    hijo->numClaves = grado - 1;

    for (int j = numClaves; j >= indice + 1; j--) {
        hijos[j + 1] = hijos[j];
    }

    hijos[indice + 1] = nuevoNodo;

    for (int j = numClaves - 1; j >= indice; j--) {
        claves[j + 1] = claves[j];
        libros[j + 1] = libros[j];
    }

    claves[indice] = hijo->claves[grado - 1];
    libros[indice] = hijo->libros[grado - 1];

    numClaves++;
}

void NodoB::recorrer() {
    int i;
    for (i = 0; i < numClaves; i++) {
        if (!esHoja) {
            hijos[i]->recorrer();
        }
        cout << "ANIO: " << claves[i] << " - " << libros[i]->getTitulo() << "\n";
    }

    if (!esHoja) {
        hijos[i]->recorrer();
    }
}

Libro *NodoB::buscar(int clave) {
    int i = 0;
    while (i < numClaves && clave > claves[i]) {
        i++;
    }

    if (i < numClaves && claves[i] == clave) {
        return libros[i];
    }

    if (esHoja) {
        return nullptr;
    }

    return hijos[i]->buscar(clave);
}

void NodoB::buscarRango(int anioInicio, int anioFin, ListaEnlazada *resultados) {
    int i = 0;

    while (i < numClaves) {
        if (!esHoja) {
            hijos[i]->buscarRango(anioInicio, anioFin, resultados);
        }

        if (claves[i] >= anioInicio && claves[i] <= anioFin) {
            resultados->insertar(libros[i]);
        }

        i++;
    }

    if (!esHoja) {
        hijos[i]->buscarRango(anioInicio, anioFin, resultados);
    }
}

void NodoB::mostrarEstructura(const string &prefijo, bool esUltimo, int nivel) {
    cout << prefijo;
    cout << (esUltimo ? "└── " : "├── ");
    cout << "NIVEL " << nivel << " [";

    for (int i = 0; i < numClaves; i++) {
        cout << claves[i];
        if (i < numClaves - 1) cout << ", ";
    }
    cout << "] " << (esHoja ? "(HOJA)" : "(INTERNO)") << "\n";

    if (!esHoja) {
        string nuevoPrefijo = prefijo + (esUltimo ? "    " : "│   ");
        for (int i = 0; i < numClaves + 1; i++) {
            if (hijos[i] != nullptr) {
                hijos[i]->mostrarEstructura(nuevoPrefijo, i == numClaves, nivel + 1);
            }
        }
    }
}
