//
// Created by alesso on 26/09/25.
//

#include "../ArbolAVL/ArbolAVL.h"

ArbolAVL::ArbolAVL() : raiz(nullptr), tamaño(0) {
}

ArbolAVL::~ArbolAVL() {
    limpiar();
}

int ArbolAVL::obtenerAlturaNodo(NodoAVL *nodo) {
    if (nodo == nullptr) return 0;
    return nodo->altura;
}

int ArbolAVL::obtenerBalance(NodoAVL *nodo) {
    if (nodo == nullptr) return 0;
    return obtenerAlturaNodo(nodo->izquierdo) - obtenerAlturaNodo(nodo->derecho);
}

void ArbolAVL::actualizarAltura(NodoAVL *nodo) {
    if (nodo != nullptr) {
        nodo->altura = 1 + max(obtenerAlturaNodo(nodo->izquierdo), obtenerAlturaNodo(nodo->derecho));
    }
}

// ROTACION DERECHA
NodoAVL *ArbolAVL::rotarDerecha(NodoAVL *y) {
    NodoAVL *x = y->izquierdo;
    NodoAVL *T2 = x->derecho;

    x->derecho = y;
    y->izquierdo = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

//ROTACION IZQUIERDA
NodoAVL *ArbolAVL::rotarIzquierda(NodoAVL *x) {
    NodoAVL *y = x->derecho;
    NodoAVL *T2 = y->izquierdo;

    y->izquierdo = x;
    x->derecho = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}

// FUNCION RECURSIVA PARA INSERTAR
NodoAVL *ArbolAVL::insertarRec(NodoAVL *nodo, Libro *libro) {
    if (nodo == nullptr) {
        tamaño++;
        return new NodoAVL(libro);
    }

    if (libro->getTitulo() < nodo->libro->getTitulo()) {
        nodo->izquierdo = insertarRec(nodo->izquierdo, libro);
    } else if (libro->getTitulo() > nodo->libro->getTitulo()) {
        nodo->derecho = insertarRec(nodo->derecho, libro);
    } else {
        return nodo;
    }

    actualizarAltura(nodo);

    int balance = obtenerBalance(nodo);


    // CASO IZQUIERDA IZQUIERDA
    if (balance > 1 && libro->getTitulo() < nodo->izquierdo->libro->getTitulo()) {
        return rotarDerecha(nodo);
    }

    // CASO DERECHA DERECHA
    if (balance < -1 && libro->getTitulo() > nodo->derecho->libro->getTitulo()) {
        return rotarIzquierda(nodo);
    }

    // CASO IZQUIERDA DERECHA
    if (balance > 1 && libro->getTitulo() > nodo->izquierdo->libro->getTitulo()) {
        nodo->izquierdo = rotarIzquierda(nodo->izquierdo);
        return rotarDerecha(nodo);
    }

    // CASO DERECHA IZQUIERDA
    if (balance < -1 && libro->getTitulo() < nodo->derecho->libro->getTitulo()) {
        nodo->derecho = rotarDerecha(nodo->derecho);
        return rotarIzquierda(nodo);
    }

    return nodo;
}

NodoAVL *ArbolAVL::obtenerMinimo(NodoAVL *nodo) {
    NodoAVL *actual = nodo;
    while (actual->izquierdo != nullptr) {
        actual = actual->izquierdo;
    }
    return actual;
}

NodoAVL *ArbolAVL::eliminarRec(NodoAVL *raiz, const string &titulo) {
    if (raiz == nullptr) return raiz;

    if (titulo < raiz->libro->getTitulo()) {
        raiz->izquierdo = eliminarRec(raiz->izquierdo, titulo);
    } else if (titulo > raiz->libro->getTitulo()) {
        raiz->derecho = eliminarRec(raiz->derecho, titulo);
    } else {
        if ((raiz->izquierdo == nullptr) || (raiz->derecho == nullptr)) {
            NodoAVL *temp = raiz->izquierdo ? raiz->izquierdo : raiz->derecho;

            if (temp == nullptr) {
                temp = raiz;
                raiz = nullptr;
            } else {
                *raiz = *temp;
            }
            delete temp;
            tamaño--;
        } else {
            NodoAVL *temp = obtenerMinimo(raiz->derecho);

            raiz->libro = temp->libro;

            raiz->derecho = eliminarRec(raiz->derecho, temp->libro->getTitulo());
        }
    }

    if (raiz == nullptr) return raiz;

    actualizarAltura(raiz);

    int balance = obtenerBalance(raiz);

    // CASO IZQUIERDA IZQUIERDA
    if (balance > 1 && obtenerBalance(raiz->izquierdo) >= 0) {
        return rotarDerecha(raiz);
    }

    // CASO IZQUIERDA DERECHA
    if (balance > 1 && obtenerBalance(raiz->izquierdo) < 0) {
        raiz->izquierdo = rotarIzquierda(raiz->izquierdo);
        return rotarDerecha(raiz);
    }

    // CASO DERECHA DERECHA
    if (balance < -1 && obtenerBalance(raiz->derecho) <= 0) {
        return rotarIzquierda(raiz);
    }

    // CASO DERECHA IZQUIERDA
    if (balance < -1 && obtenerBalance(raiz->derecho) > 0) {
        raiz->derecho = rotarDerecha(raiz->derecho);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

NodoAVL *ArbolAVL::buscarRec(NodoAVL *nodo, const string &titulo) {
    if (nodo == nullptr || nodo->libro->getTitulo() == titulo) {
        return nodo;
    }

    if (titulo < nodo->libro->getTitulo()) {
        return buscarRec(nodo->izquierdo, titulo);
    }

    return buscarRec(nodo->derecho, titulo);
}

void ArbolAVL::inOrderRec(NodoAVL *nodo, ListaEnlazada *lista) {
    if (nodo != nullptr) {
        inOrderRec(nodo->izquierdo, lista);
        lista->insertar(nodo->libro);
        inOrderRec(nodo->derecho, lista);
    }
}

void ArbolAVL::limpiarRec(NodoAVL *nodo) {
    if (nodo != nullptr) {
        limpiarRec(nodo->izquierdo);
        limpiarRec(nodo->derecho);
        delete nodo;
    }
}

void ArbolAVL::convertirAArrayRec(NodoAVL *nodo, Libro **array, int &index) {
    if (nodo != nullptr) {
        convertirAArrayRec(nodo->izquierdo, array, index);
        array[index++] = nodo->libro;
        convertirAArrayRec(nodo->derecho, array, index);
    }
}

void ArbolAVL::insertar(Libro *libro) {
    if (libro != nullptr) {
        raiz = insertarRec(raiz, libro);
    }
}

Libro *ArbolAVL::buscarPorTitulo(const string &titulo) {
    NodoAVL *nodo = buscarRec(raiz, titulo);
    return (nodo != nullptr) ? nodo->libro : nullptr;
}

bool ArbolAVL::eliminar(const string &titulo) {
    int tamaño_inicial = tamaño;
    raiz = eliminarRec(raiz, titulo);
    return tamaño < tamaño_inicial;
}

ListaEnlazada *ArbolAVL::obtenerLibrosOrdenados() {
    ListaEnlazada *lista = new ListaEnlazada();
    inOrderRec(raiz, lista);
    return lista;
}

bool ArbolAVL::estaVacio() const {
    return raiz == nullptr;
}

int ArbolAVL::obtenerTamaño() {
    return tamaño;
}

int ArbolAVL::obtenerAltura() {
    return obtenerAlturaNodo(raiz);
}

void ArbolAVL::mostrarLibrosOrdenados() {
    ListaEnlazada *librosOrdenados = obtenerLibrosOrdenados();
    cout << "--------------------------------------------------\n";
    cout << "LIBROS ORDENADOS ALFABETICAMENTE:\n";
    librosOrdenados->mostrarLibros();
    delete librosOrdenados;
}

void ArbolAVL::limpiar() {
    limpiarRec(raiz);
    raiz = nullptr;
    tamaño = 0;
}

Libro **ArbolAVL::convertirAArrayOrdenado() {
    if (tamaño == 0) return nullptr;

    Libro **array = new Libro *[tamaño];
    int index = 0;
    convertirAArrayRec(raiz, array, index);
    return array;
}

Libro *ArbolAVL::busquedaBinariaEnArray(Libro **array, int tamaño, const string &titulo) {
    int izquierda = 0;
    int derecha = tamaño - 1;

    while (izquierda <= derecha) {
        int medio = izquierda + (derecha - izquierda) / 2;

        if (array[medio]->getTitulo() == titulo) {
            return array[medio];
        }

        if (array[medio]->getTitulo() < titulo) {
            izquierda = medio + 1;
        } else {
            derecha = medio - 1;
        }
    }

    return nullptr;
}

void ArbolAVL::mostrarEstadisticas() {
    cout << "--------------------------------------------------\n";
    cout << "ESTADISTICAS DEL ARBOL AVL:\n";
    cout << "NUMERO TOTAL DE LIBROS: " << tamaño << "\n";
    cout << "ALTURA DEL ARBOL: " << obtenerAltura() << "\n";
    cout << "¿ESTA VACIO?: " << (estaVacio() ? "SI" : "NO") << "\n";
    cout << "--------------------------------------------------\n";
}
