//
// Created by alesso on 2/10/25.
//

#ifndef PROYECTO1_EDD_GENERADORGRAFICAS_H
#define PROYECTO1_EDD_GENERADORGRAFICAS_H
#include "../Estructuras/Arboles/ArbolAVL/ArbolAVL.h"
#include "../Estructuras/Arboles/ArbolB/ArbolB.h"
#include "../Estructuras/Arboles/ArbolB+/ArbolBPlus.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

class GeneradorGraficas {
private:
    int contadorNodos;

    string generarID() {
        stringstream ss;
        ss << "nodo" << contadorNodos++;
        return ss.str();
    }

    string escaparTexto(const string &texto) {
        string resultado = "";
        for (size_t i = 0; i < texto.length(); i++) {
            char c = texto[i];
            if (c == '"') {
                resultado += "\\\"";
            } else if (c == '\n') {
                resultado += "\\n";
            } else if (c == '\\') {
                resultado += "\\\\";
            } else {
                resultado += c;
            }
        }
        return resultado;
    }

    string generarDOTAVL(NodoAVL *nodo, ofstream &archivo) {
        if (nodo == nullptr) return "";

        string idActual = generarID();
        string titulo = escaparTexto(nodo->libro->getTitulo());

        archivo << "    " << idActual << " [label=\"" << titulo
                << "\\nh=" << nodo->altura << "\", shape=circle, style=filled, fillcolor=lightblue];\n";

        if (nodo->izquierdo != nullptr) {
            string idIzq = generarDOTAVL(nodo->izquierdo, archivo);
            archivo << "    " << idActual << " -> " << idIzq << " [label=\"I\"];\n";
        }

        if (nodo->derecho != nullptr) {
            string idDer = generarDOTAVL(nodo->derecho, archivo);
            archivo << "    " << idActual << " -> " << idDer << " [label=\"D\"];\n";
        }

        return idActual;
    }

    string generarDOTArbolB(NodoB *nodo, ofstream &archivo) {
        if (nodo == nullptr) return "";

        string idActual = generarID();

        string etiqueta = "";
        for (int i = 0; i < nodo->numClaves; i++) {
            etiqueta += to_string(nodo->claves[i]);
            if (i < nodo->numClaves - 1) {
                etiqueta += " | ";
            }
        }

        string color = nodo->esHoja ? "lightgreen" : "lightyellow";
        archivo << "    " << idActual << " [label=\"" << etiqueta
                << "\", shape=record, style=filled, fillcolor=" << color << "];\n";

        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                if (nodo->hijos[i] != nullptr) {
                    string idHijo = generarDOTArbolB(nodo->hijos[i], archivo);
                    archivo << "    " << idActual << " -> " << idHijo << ";\n";
                }
            }
        }

        return idActual;
    }

    string generarDOTArbolBPlus(NodoBPlus *nodo, ofstream &archivo, bool &primeraHoja, string &ultimaHojaID) {
        if (nodo == nullptr) return "";

        string idActual = generarID();

        string etiqueta = "";
        for (int i = 0; i < nodo->numClaves; i++) {
            etiqueta += escaparTexto(nodo->claves[i]);
            if (nodo->esHoja) {
                etiqueta += "(" + to_string(nodo->listas[i]->obtenerTamaño()) + ")";
            }
            if (i < nodo->numClaves - 1) {
                etiqueta += " | ";
            }
        }

        string color = nodo->esHoja ? "lightcoral" : "lightyellow";
        archivo << "    " << idActual << " [label=\"" << etiqueta
                << "\", shape=record, style=filled, fillcolor=" << color << "];\n";

        if (nodo->esHoja) {
            if (primeraHoja) {
                primeraHoja = false;
            } else if (ultimaHojaID != "") {
                archivo << "    " << ultimaHojaID << " -> " << idActual
                        << " [style=dashed, color=red, constraint=false];\n";
            }
            ultimaHojaID = idActual;
        }

        if (!nodo->esHoja) {
            for (int i = 0; i <= nodo->numClaves; i++) {
                if (nodo->hijos[i] != nullptr) {
                    string idHijo = generarDOTArbolBPlus(nodo->hijos[i], archivo, primeraHoja, ultimaHojaID);
                    archivo << "    " << idActual << " -> " << idHijo << ";\n";
                }
            }
        }

        return idActual;
    }

    bool ejecutarComando(const string &comando) {
        int resultado = system(comando.c_str());
        return resultado == 0;
    }

public:
    GeneradorGraficas() : contadorNodos(0) {
    }

    bool generarGraficaAVL(ArbolAVL *arbol, const string &nombreArchivo = "arbol_avl") {
        if (arbol == nullptr || arbol->estaVacio()) {
            cout << "ERROR: ARBOL AVL VACIO O NULO\n";
            return false;
        }

        contadorNodos = 0;
        string archivoDOT = nombreArchivo + ".dot";
        string archivoPNG = nombreArchivo + ".png";

        ofstream archivo(archivoDOT.c_str());
        if (!archivo.is_open()) {
            cout << "ERROR: NO SE PUDO CREAR EL ARCHIVO DOT\n";
            return false;
        }

        archivo << "digraph ArbolAVL {\n";
        archivo << "    node [fontname=\"Arial\"];\n";
        archivo << "    graph [rankdir=TB];\n";
        archivo << "    label=\"ARBOL AVL - BUSQUEDA POR TITULO\";\n";
        archivo << "    labelloc=\"t\";\n";
        archivo << "    fontsize=20;\n\n";

        NodoAVL *raiz = obtenerRaizAVL(arbol);
        if (raiz != nullptr) {
            generarDOTAVL(raiz, archivo);
        }

        archivo << "}\n";
        archivo.close();

        cout << "ARCHIVO DOT GENERADO: " << archivoDOT << "\n";

        string comando = "dot -Tpng " + archivoDOT + " -o " + archivoPNG;
        cout << "EJECUTANDO: " << comando << "\n";

        if (ejecutarComando(comando)) {
            cout << "IMAGEN GENERADA EXITOSAMENTE: " << archivoPNG << "\n";
            return true;
        } else {
            cout << "ADVERTENCIA: NO SE PUDO GENERAR LA IMAGEN PNG\n";
            cout << "ASEGURESE DE TENER GRAPHVIZ INSTALADO\n";
            cout << "EL ARCHIVO DOT FUE CREADO CORRECTAMENTE\n";
            return false;
        }
    }

    bool generarGraficaArbolB(ArbolB *arbol, const string &nombreArchivo = "arbol_b") {
        if (arbol == nullptr || arbol->estaVacio()) {
            cout << "ERROR: ARBOL B VACIO O NULO\n";
            return false;
        }

        contadorNodos = 0;
        string archivoDOT = nombreArchivo + ".dot";
        string archivoPNG = nombreArchivo + ".png";

        ofstream archivo(archivoDOT.c_str());
        if (!archivo.is_open()) {
            cout << "ERROR: NO SE PUDO CREAR EL ARCHIVO DOT\n";
            return false;
        }

        archivo << "digraph ArbolB {\n";
        archivo << "    node [fontname=\"Arial\"];\n";
        archivo << "    graph [rankdir=TB];\n";
        archivo << "    label=\"ARBOL B - BUSQUEDA POR RANGO DE FECHAS\";\n";
        archivo << "    labelloc=\"t\";\n";
        archivo << "    fontsize=20;\n\n";

        NodoB *raiz = obtenerRaizB(arbol);
        if (raiz != nullptr) {
            generarDOTArbolB(raiz, archivo);
        }

        archivo << "}\n";
        archivo.close();

        cout << "ARCHIVO DOT GENERADO: " << archivoDOT << "\n";

        string comando = "dot -Tpng " + archivoDOT + " -o " + archivoPNG;
        cout << "EJECUTANDO: " << comando << "\n";

        if (ejecutarComando(comando)) {
            cout << "IMAGEN GENERADA EXITOSAMENTE: " << archivoPNG << "\n";
            return true;
        } else {
            cout << "ADVERTENCIA: NO SE PUDO GENERAR LA IMAGEN PNG\n";
            cout << "ASEGURESE DE TENER GRAPHVIZ INSTALADO\n";
            cout << "EL ARCHIVO DOT FUE CREADO CORRECTAMENTE\n";
            return false;
        }
    }

    bool generarGraficaArbolBPlus(ArbolBPlus *arbol, const string &nombreArchivo = "arbol_b_plus") {
        if (arbol == nullptr || arbol->estaVacio()) {
            cout << "ERROR: ARBOL B+ VACIO O NULO\n";
            return false;
        }

        contadorNodos = 0;
        string archivoDOT = nombreArchivo + ".dot";
        string archivoPNG = nombreArchivo + ".png";

        ofstream archivo(archivoDOT.c_str());
        if (!archivo.is_open()) {
            cout << "ERROR: NO SE PUDO CREAR EL ARCHIVO DOT\n";
            return false;
        }

        archivo << "digraph ArbolBPlus {\n";
        archivo << "    node [fontname=\"Arial\"];\n";
        archivo << "    graph [rankdir=TB];\n";
        archivo << "    label=\"ARBOL B+ - BUSQUEDA POR GENERO\";\n";
        archivo << "    labelloc=\"t\";\n";
        archivo << "    fontsize=20;\n\n";

        NodoBPlus *raiz = obtenerRaizBPlus(arbol);
        if (raiz != nullptr) {
            bool primeraHoja = true;
            string ultimaHojaID = "";
            generarDOTArbolBPlus(raiz, archivo, primeraHoja, ultimaHojaID);
        }

        archivo << "}\n";
        archivo.close();

        cout << "ARCHIVO DOT GENERADO: " << archivoDOT << "\n";

        string comando = "dot -Tpng " + archivoDOT + " -o " + archivoPNG;
        cout << "EJECUTANDO: " << comando << "\n";

        if (ejecutarComando(comando)) {
            cout << "IMAGEN GENERADA EXITOSAMENTE: " << archivoPNG << "\n";
            return true;
        } else {
            cout << "ADVERTENCIA: NO SE PUDO GENERAR LA IMAGEN PNG\n";
            cout << "ASEGURESE DE TENER GRAPHVIZ INSTALADO\n";
            cout << "EL ARCHIVO DOT FUE CREADO CORRECTAMENTE\n";
            return false;
        }
    }

    NodoAVL *obtenerRaizAVL(ArbolAVL *arbol);

    NodoB *obtenerRaizB(ArbolB *arbol);

    NodoBPlus *obtenerRaizBPlus(ArbolBPlus *arbol);
};


#endif //PROYECTO1_EDD_GENERADORGRAFICAS_H
