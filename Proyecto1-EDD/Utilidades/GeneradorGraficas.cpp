//
// Created by alesso on 2/10/25.
//

#include "GeneradorGraficas.h"

NodoB* GeneradorGraficas::obtenerRaizB(ArbolB* arbol) {
    if (arbol == nullptr) return nullptr;
    return arbol->obtenerRaiz();
}
NodoAVL *GeneradorGraficas::obtenerRaizAVL(ArbolAVL *arbol) {
    if (arbol == nullptr) return nullptr;
    return arbol->obtenerRaiz();
}

NodoBPlus *GeneradorGraficas::obtenerRaizBPlus(ArbolBPlus *arbol) {
    if (arbol == nullptr) return nullptr;
    return arbol->obtenerRaiz();
}
