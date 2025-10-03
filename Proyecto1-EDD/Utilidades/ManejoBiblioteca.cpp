//
// Created by alesso on 29/09/25.
//

#include "ManejoBiblioteca.h"
#include "GeneradorGraficas.h"

ManejoBiblioteca::ManejoBiblioteca() {
}

void ManejoBiblioteca::inicio() {
    string opcion;
    bool continuar = true;
    Biblioteca *biblioteca = new Biblioteca();
    mostrarMenu(biblioteca);
    while (continuar) {
        menu();

        getline(cin, opcion);
        if (opcion == "1") {
            cout << "--------------------------------------------------\n";
            cout << "AGREGAR LIBRO MANUALMENTE:\n";
            string titulo, isbn, genero, autor, anioStr;
            int anio;

            cout << "TITULO: ";
            getline(cin, titulo);
            cout << "ISBN: ";
            getline(cin, isbn);
            cout << "GENERO: ";
            getline(cin, genero);
            cout << "AÑO: ";
            getline(cin, anioStr);
            anio = stoi(anioStr);
            cout << "AUTOR: ";
            getline(cin, autor);

            biblioteca->agregarLibro(titulo, isbn, genero, anio, autor);
        } else if (opcion == "2") {
            cout << "--------------------------------------------------\n";
            cout << "ELIMINAR LIBRO: \n";
            cout << "INGRESE ISBN DEL LIBRO A ELIMINAR: ";
            string isbn;
            getline(cin, isbn);
            biblioteca->eliminarLibro(isbn);
        } else if (opcion == "3") {
            cout << "--------------------------------------------------\n";
            cout << "BUSCAR LIBRO POR TITULO:\n";
            cout << "INGRESE EL TITULO: ";
            string titulo;
            getline(cin, titulo);

            auto inicio = high_resolution_clock::now();
            Libro *encontrado = biblioteca->buscarPorTitulo(titulo);
            auto fin = high_resolution_clock::now();

            if (encontrado != nullptr) {
                cout << "--------------------------------------------------\n";
                cout << "LIBRO ENCONTRADO:\n";
                encontrado->mostrarInfo();
                auto duracion = duration_cast<microseconds>(fin - inicio);
                cout << "TIEMPO DE BUSQUEDA: " << duracion.count() << " MICROSEGUNDOS\n";
            } else {
                cout << "--------------------------------------------------\n";
                cout << "LIBRO NO ENCONTRADO\n";
            }
        } else if (opcion == "4") {
            cout << "--------------------------------------------------\n";
            cout << "BUSCAR LIBRO POR ISBN:\n";
            cout << "INGRESE EL ISBN: ";
            string isbn;
            getline(cin, isbn);

            auto inicio = high_resolution_clock::now();
            Libro *encontrado = biblioteca->buscarPorISBN(isbn);
            auto fin = high_resolution_clock::now();

            if (encontrado != nullptr) {
                cout << "--------------------------------------------------\n";
                cout << "LIBRO ENCONTRADO:\n";
                encontrado->mostrarInfo();
                auto duracion = duration_cast<microseconds>(fin - inicio);
                cout << "TIEMPO DE BUSQUEDA: " << duracion.count() << " MICROSEGUNDOS\n";
            } else {
                cout << "--------------------------------------------------\n";
                cout << "LIBRO NO ENCONTRADO\n";
            }
        } else if (opcion == "5") {
            cout << "--------------------------------------------------\n";
            cout << "BUSCAR LIBROS POR GENERO:\n";
            cout << "INGRESE EL GENERO: ";
            string genero;
            getline(cin, genero);

            auto inicio = high_resolution_clock::now();
            ListaEnlazada *resultados = biblioteca->buscarPorGenero(genero);
            auto fin = high_resolution_clock::now();
            cout << "--------------------------------------------------\n";
            cout << "SE ENCONTRARON " << resultados->obtenerTamaño() << " LIBROS\n";
            if (resultados->obtenerTamaño() > 0) {
                auto duracion = duration_cast<microseconds>(fin - inicio);
                cout << "TIEMPO DE BUSQUEDA: " << duracion.count() << " MICROSEGUNDOS\n";
                resultados->mostrarLibros();
            }
            delete resultados;
        } else if (opcion == "6") {
            cout << "--------------------------------------------------\n";
            cout << "BUSCAR LIBROS POR RANGO DE FECHAS:\n";
            cout << "INGRESE AÑO INICIAL: ";
            string anioInicioStr;
            getline(cin, anioInicioStr);
            int anioInicio = stoi(anioInicioStr);

            cout << "INGRESE AÑO FINAL: ";
            string anioFinStr;
            getline(cin, anioFinStr);
            int anioFin = stoi(anioFinStr);

            auto inicio = high_resolution_clock::now();
            ListaEnlazada *resultados = biblioteca->buscarPorRangoFechas(anioInicio, anioFin);
            auto fin = high_resolution_clock::now();
            cout << "--------------------------------------------------\n";
            cout << "SE ENCONTRARON " << resultados->obtenerTamaño() << " LIBROS\n";
            if (resultados->obtenerTamaño() > 0) {
                auto duracion = duration_cast<microseconds>(fin - inicio);
                cout << "TIEMPO DE BUSQUEDA: " << duracion.count() << " MICROSEGUNDOS\n";
                resultados->mostrarLibros();
            }
            delete resultados;
        } else if (opcion == "7") {
            cout << "--------------------------------------------------\n";
            cout << "LISTADO DE LIBROS:\n";
            biblioteca->listarPorTitulo();
        } else if (opcion == "8") {
            cout << "--------------------------------------------------\n";
            cout << "COMPARACION DE BUSQUEDA POR TITULO:\n";
            cout << "INGRESE EL TITULO A BUSCAR: ";
            string titulo;
            getline(cin, titulo);

            biblioteca->compararBusquedaPorTitulo(titulo);
        } else if (opcion == "9") {
            cout << "--------------------------------------------------\n";
            cout << "COMPARACION DE BUSQUEDA POR ISBN:\n";
            cout << "INGRESE EL ISBN A BUSCAR: ";
            string isbn;
            getline(cin, isbn);

            biblioteca->compararBusquedaPorISBN(isbn);
        } else if (opcion == "10") {
            biblioteca->mostrarEstadisticas();
        } else if (opcion == "11") {
            cout << "--------------------------------------------------\n";
            cout << "ESTADISTICAS POR GENERO:\n";
            biblioteca->mostrarEstadisticasPorGenero();
        } else if (opcion == "12") {
            cout << "--------------------------------------------------\n";
            cout << "GENERAR GRAFICAS\n";
            biblioteca->generarGraficas();
        } else if (opcion == "0") {
            cout << "--------------------------------------------------\n";
            cout << "GRACIAS POR USAR LA BIBLIOTECA MAGICA\n";
            cout << "CERRANDO SISTEMA...\n";
            continuar = false;
        } else {
            cout << "OPCION INVALIDA. INTENTE NUEVAMENTE.\n";
        }

        if (continuar) {
            cout << "PRESIONE ENTER PARA CONTINUAR...";
            cin.get();
        }
    }

    delete biblioteca;
}

void ManejoBiblioteca::mostrarMenu(Biblioteca *biblioteca) {
    cout << "DESEAS CARGAR UN ARCHIVO .CSV CON LOS DATOS DE LIBROS? \n";
    cout << "1. INGRESAR ARCHIVO\n";
    cout << "2. SIN CARGA DE ARCHIVO\n";
    string opcion;
    getline(cin, opcion);
    if (opcion == "1") {
        cout << "--------------------------------------------------\n";
        cout << "INGRESE EL PATH DEL ARCHIVO (SIN EXTENSION .CSV)\n";
        string rutaArchivo;
        getline(cin, rutaArchivo);

        int librosInsertados = biblioteca->cargarCatalogo(rutaArchivo);
        if (librosInsertados > 0) {
            biblioteca->mostrarEstadisticas();
        }
    }
}

void ManejoBiblioteca::menu() {
    cout << "--------------------------------------------------\n";
    cout << "MENU PRINCIPAL: \n";
    cout << "1.  AGREGAR LIBRO MANUALMENTE\n";
    cout << "2.  ELIMINAR LIBRO\n";
    cout << "3.  BUSCAR LIBRO POR TITULO (AVL)\n";
    cout << "4.  BUSCAR LIBRO POR ISBN\n";
    cout << "5.  BUSCAR LIBROS POR GENERO (B+)\n";
    cout << "6.  BUSCAR LIBROS POR RANGO DE FECHAS (B)\n";
    cout << "7.  LISTAR TODOS LOS LIBROS ORDENADOS POR TITULO\n";
    cout << "8.  COMPARAR BUSQUEDA SECUENCIAL VS BINARIA (TITULO)\n";
    cout << "9.  COMPARAR BUSQUEDA SECUENCIAL VS BINARIA (ISBN)\n";
    cout << "10. MOSTRAR ESTADISTICAS GENERALES\n";
    cout << "11. MOSTRAR ESTADISTICAS POR GENERO\n";
    cout << "12. GENERAR GRAFICAS\n";
    cout << "0.  SALIR\n";
    cout << "--------------------------------------------------\n";
    cout << "SELECCIONE UNA OPCION: ";
}
