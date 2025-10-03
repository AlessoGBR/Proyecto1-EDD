//
// Created by alesso on 26/09/25.
//

#include "Biblioteca.h"

#include "GeneradorGraficas.h"

Biblioteca::Biblioteca() {
    listaBusquedaSecuencial = new ListaEnlazada();
    arbolTitulos = new ArbolAVL();
    arbolFechas = new ArbolB(3);
    arbolGeneros = new ArbolBPlus(3);
    todosLosLibros = new ListaEnlazada();
    cargador = new CargadorDatos();
}

Biblioteca::~Biblioteca() {
    delete listaBusquedaSecuencial;
    delete arbolTitulos;
    delete arbolFechas;
    delete arbolGeneros;
    delete cargador;

    NodoLista *actual = todosLosLibros->obtenerCabeza();
    while (actual != nullptr) {
        delete actual->libro;
        actual = actual->siguiente;
    }
    delete todosLosLibros;
}

int Biblioteca::cargarCatalogo(const string &rutaArchivo) {
    ListaEnlazada *librosCargados = cargador->cargarDesdeCSV(rutaArchivo);

    if (librosCargados == nullptr) {
        return -1;
    }

    int librosInsertados = 0;
    NodoLista *actual = librosCargados->obtenerCabeza();

    while (actual != nullptr) {
        Libro *libro = actual->libro;

        listaBusquedaSecuencial->insertar(libro);
        arbolTitulos->insertar(libro);
        arbolFechas->insertar(libro);
        arbolGeneros->insertar(libro);
        todosLosLibros->insertar(libro);

        librosInsertados++;
        actual = actual->siguiente;
    }

    delete librosCargados;


    return librosInsertados;
}

bool Biblioteca::agregarLibro(const string &titulo, const string &isbn, const string &genero,
                              int anio, const string &autor) {
    if (listaBusquedaSecuencial->buscarPorISBN(isbn) != nullptr) {
        cout << "ERROR: EL ISBN YA EXISTE EN EL CATALOGO\n";
        return false;
    }

    if (anio < -3000 || anio > 2100) {
        cout << "ERROR: AÑO INVALIDO\n";
        return false;
    }

    Libro *nuevoLibro = new Libro(titulo, isbn, genero, anio, autor);

    listaBusquedaSecuencial->insertar(nuevoLibro);
    arbolTitulos->insertar(nuevoLibro);
    arbolFechas->insertar(nuevoLibro);
    arbolGeneros->insertar(nuevoLibro);
    todosLosLibros->insertar(nuevoLibro);
    cout << "--------------------------------------------------\n";
    cout << "LIBRO AGREGADO EXITOSAMENTE A TODAS LAS ESTRUCTURAS\n";
    return true;
}

bool Biblioteca::eliminarLibro(const string &isbn) {
    Libro *libro = listaBusquedaSecuencial->buscarPorISBN(isbn);

    if (libro == nullptr) {
        cout << "ERROR: LIBRO NO ENCONTRADO\n";
        return false;
    }

    string titulo = libro->getTitulo();

    bool resultado = true;
    resultado &= listaBusquedaSecuencial->eliminar(isbn);
    resultado &= arbolTitulos->eliminar(titulo);
    // Nota: ArbolB y ArbolB+ requieren implementación de eliminación

    if (resultado) {
        cout << "LIBRO ELIMINADO EXITOSAMENTE\n";
    } else {
        cout << "ADVERTENCIA: EL LIBRO PUDO NO SER ELIMINADO DE TODAS LAS ESTRUCTURAS\n";
    }

    return resultado;
}

Libro *Biblioteca::buscarPorTitulo(const string &titulo) {
    return arbolTitulos->buscarPorTitulo(titulo);
}

Libro *Biblioteca::buscarPorTituloSecuencial(const string &titulo) {
    return listaBusquedaSecuencial->buscarPorTitulo(titulo);
}

Libro *Biblioteca::buscarPorISBN(const string &isbn) {
    return listaBusquedaSecuencial->buscarPorISBN(isbn);
}

ListaEnlazada *Biblioteca::buscarPorGenero(const string &genero) {
    return arbolGeneros->buscarPorGenero(genero);
}

ListaEnlazada *Biblioteca::buscarPorRangoFechas(int anioInicio, int anioFin) {
    return arbolFechas->buscarPorRangoFechas(anioInicio, anioFin);
}

void Biblioteca::listarPorTitulo() {
    cout << "--------------------------------------------------\n";
    cout << "LIBROS ORDENADOS POR TITULO (ARBOL AVL)\n";
    arbolTitulos->mostrarLibrosOrdenados();
}

void Biblioteca::compararBusquedaPorTitulo(const string &titulo) {
    cout << "--------------------------------------------------\n";
    cout << "COMPARACION: BUSQUEDA POR TITULO\n";

    auto inicio = high_resolution_clock::now();
    Libro *resultadoSecuencial = buscarPorTituloSecuencial(titulo);
    auto fin = high_resolution_clock::now();
    auto duracionSecuencial = duration_cast<microseconds>(fin - inicio);

    cout << "BUSQUEDA SECUENCIAL (LISTA ENLAZADA):\n";
    if (resultadoSecuencial != nullptr) {
        cout << "  LIBRO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionSecuencial.count() << " MICROSEGUNDOS\n";
    } else {
        cout << "  LIBRO NO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionSecuencial.count() << " MICROSEGUNDOS\n";
    }

    inicio = high_resolution_clock::now();
    Libro *resultadoBinaria = buscarPorTitulo(titulo);
    fin = high_resolution_clock::now();
    auto duracionBinaria = duration_cast<microseconds>(fin - inicio);
    cout << "--------------------------------------------------\n";
    cout << "BUSQUEDA BINARIA (ARBOL AVL):\n";
    if (resultadoBinaria != nullptr) {
        cout << "  LIBRO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionBinaria.count() << " MICROSEGUNDOS\n";
    } else {
        cout << "  LIBRO NO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionBinaria.count() << " MICROSEGUNDOS\n";
    }
    cout << "--------------------------------------------------\n";
    cout << "RESULTADO:\n";
    if (duracionSecuencial.count() > 0 && duracionBinaria.count() > 0) {
        cout << "  LA BUSQUEDA BINARIA FUE MAS RAPIDA\n";
    } else {
        cout << "  LA BUSQUEDA SECUENCIAL FUE MAS RAPIDA\n";
    }
    cout << "--------------------------------------------------\n";
}

void Biblioteca::compararBusquedaPorISBN(const string &isbn) {
    cout << "--------------------------------------------------\n";
    cout << "COMPARACION: BUSQUEDA POR ISBN\n";

    // BUSQUEDA SECUENCIAL
    auto inicio = high_resolution_clock::now();
    Libro *resultadoSecuencial = listaBusquedaSecuencial->buscarPorISBN(isbn);
    auto fin = high_resolution_clock::now();
    auto duracionSecuencial = duration_cast<microseconds>(fin - inicio);
    cout << "--------------------------------------------------\n";
    cout << "BUSQUEDA SECUENCIAL (LISTA ENLAZADA):\n";
    if (resultadoSecuencial != nullptr) {
        cout << "  LIBRO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionSecuencial.count() << " MICROSEGUNDOS\n";
    } else {
        cout << "  LIBRO NO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionSecuencial.count() << " MICROSEGUNDOS\n";
    }

    inicio = high_resolution_clock::now();
    Libro **arrayOrdenado = arbolTitulos->convertirAArrayOrdenado();
    int tamaño = arbolTitulos->obtenerTamaño();

    Libro *resultadoBinaria = nullptr;
    for (int i = 0; i < tamaño; i++) {
        if (arrayOrdenado[i]->getIsbn() == isbn) {
            resultadoBinaria = arrayOrdenado[i];
            break;
        }
    }
    fin = high_resolution_clock::now();
    auto duracionBinaria = duration_cast<microseconds>(fin - inicio);
    cout << "--------------------------------------------------\n";
    cout << "BUSQUEDA BINARIA (ARBOL AVL):\n";
    if (resultadoBinaria != nullptr) {
        cout << "  LIBRO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionBinaria.count() << " MICROSEGUNDOS\n";
    } else {
        cout << "  LIBRO NO ENCONTRADO\n";
        cout << "  TIEMPO: " << duracionBinaria.count() << " MICROSEGUNDOS\n";
    }
    cout << "--------------------------------------------------\n";
    cout << "RESULTADO:\n";
    if (duracionSecuencial.count() > 0 && duracionBinaria.count() > 0 && duracionSecuencial.count() > duracionBinaria.
        count()) {
        cout << "  LA BUSQUEDA BINARIA FUE MAS RAPIDA\n";
    } else {
        cout << "  LA BUSQUEDA SECUENCIAL FUE MAS RAPIDA\n";
    }

    delete[] arrayOrdenado;

    cout << "--------------------------------------------------\n";
}

void Biblioteca::mostrarEstadisticas() {
    cout << "--------------------------------------------------\n";
    cout << "ESTADISTICAS GENERALES:\n";
    cout << "TOTAL DE LIBROS EN EL CATALOGO: " << todosLosLibros->obtenerTamaño() << "\n";
    cout << "--------------------------------------------------\n";
    cout << "ESTADO DE LAS ESTRUCTURAS:\n";
    cout << "- LISTA ENLAZADA: "
            << listaBusquedaSecuencial->obtenerTamaño() << " LIBROS\n";
    cout << "- ARBOL AVL: "
            << arbolTitulos->obtenerTamaño() << " LIBROS\n";
    cout << "- ARBOL B: "
            << arbolFechas->obtenerTamaño() << " LIBROS\n";
    cout << "- ARBOL B+: "
            << arbolGeneros->obtenerTamaño() << " LIBROS\n";
}

void Biblioteca::mostrarEstadisticasPorGenero() {
    arbolGeneros->mostrarEstadisticasPorGenero();
}

int Biblioteca::obtenerTotalLibros() const {
    return todosLosLibros->obtenerTamaño();
}

void Biblioteca::generarGraficas() {
    cout << "SELECCIONE LA ESTRUCTURA A GENERAR GRAFICA:\n";
    cout << "1. ARBOL AVL.\n";
    cout << "2. ARBOL B.\n";
    cout << "3. ARBOL B+\n";
    cout << "--------------------------------------------------\n";
    cout << "SELECCIONE UNA OPCION: ";
    string opcion;
    getline(cin, opcion);
    GeneradorGraficas *gen = new GeneradorGraficas();
    if (opcion == "1") {
        gen->generarGraficaAVL(arbolTitulos);
    } else if (opcion == "2") {
        gen->generarGraficaArbolB(arbolFechas);
    } else if (opcion == "3") {
        gen->generarGraficaArbolBPlus(arbolGeneros);
    } else {
        cout << "OPCION INVALIDA.\n";
    }
}
