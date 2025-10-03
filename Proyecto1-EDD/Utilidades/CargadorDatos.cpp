#include "CargadorDatos.h"

string CargadorDatos::limpiarEspacios(const string &str) {
    size_t inicio = str.find_first_not_of(" \t\r\n");
    if (inicio == string::npos) return "";

    size_t fin = str.find_last_not_of(" \t\r\n");
    return str.substr(inicio, fin - inicio + 1);
}

string CargadorDatos::limpiarComillas(const string &str) {
    string resultado = limpiarEspacios(str);

    if (resultado.length() >= 2) {
        if (resultado[0] == '"' && resultado[resultado.length() - 1] == '"') {
            resultado = resultado.substr(1, resultado.length() - 2);
        }
    }

    return resultado;
}

bool CargadorDatos::parsearLineaCSV(const string &linea, string &titulo, string &isbn,
                                    string &genero, int &anio, string &autor) {
    if (linea.empty() || linea[0] == '#') return false;

    string campoActual = "";
    bool dentroComillas = false;
    int campoNumero = 0;

    for (size_t i = 0; i < linea.length(); i++) {
        char c = linea[i];

        if (c == '"') {
            dentroComillas = !dentroComillas;
            campoActual += c;
        } else if (c == ',' && !dentroComillas) {
            // Fin de campo
            string valorLimpio = limpiarComillas(campoActual);

            switch (campoNumero) {
                case 0: titulo = valorLimpio;
                    break;
                case 1: isbn = valorLimpio;
                    break;
                case 2: genero = valorLimpio;
                    break;
                case 3:
                    try {
                        anio = stoi(valorLimpio);
                    } catch (...) {
                        return false;
                    }
                    break;
                case 4: autor = valorLimpio;
                    break;
            }

            campoActual = "";
            campoNumero++;
        } else {
            campoActual += c;
        }
    }

    if (campoNumero == 4) {
        autor = limpiarComillas(campoActual);
    }

    return campoNumero == 4 && !titulo.empty() && !isbn.empty();
}

bool CargadorDatos::validarISBN(const string &isbn, ListaEnlazada *listaExistente) {
    if (isbn.empty()) return false;

    Libro *existente = listaExistente->buscarPorISBN(isbn);
    return existente == nullptr;
}

bool CargadorDatos::validarAnio(int anio) {
    return anio >= -3000 && anio <= 2100;
}

CargadorDatos::CargadorDatos() {
}

CargadorDatos::~CargadorDatos() {
}

ListaEnlazada *CargadorDatos::cargarDesdeCSV(const string &rutaArchivo) {
    string rutaCompleta = rutaArchivo;

    if (rutaCompleta.length() < 4 ||
        rutaCompleta.substr(rutaCompleta.length() - 4) != ".csv") {
        rutaCompleta += ".csv";
    }

    ifstream archivo(rutaCompleta.c_str());

    if (!archivo.is_open()) {
        cout << "ERROR: NO SE PUDO ABRIR EL ARCHIVO: " << rutaCompleta << "\n";
        return nullptr;
    }
    cout << "--------------------------------------------------\n";
    cout << "CARGANDO CATALOGO DESDE CSV:\n";
    cout << "ARCHIVO: " << rutaCompleta << "\n";

    ListaEnlazada *librosCargados = new ListaEnlazada();

    string linea;
    int lineaNumero = 0;
    int librosInsertados = 0;
    int lineasIgnoradas = 0;
    int isbnsDuplicados = 0;

    if (getline(archivo, linea)) {
        lineaNumero++;
    }

    while (getline(archivo, linea)) {
        lineaNumero++;

        if (limpiarEspacios(linea).empty()) {
            continue;
        }

        string titulo, isbn, genero, autor;
        int anio;

        if (!parsearLineaCSV(linea, titulo, isbn, genero, anio, autor)) {
            cout << "LINEA " << lineaNumero << ": FORMATO INVALIDO - IGNORADA\n";
            lineasIgnoradas++;
            continue;
        }

        if (!validarISBN(isbn, librosCargados)) {
            cout << "LINEA " << lineaNumero << ": ISBN DUPLICADO (" << isbn << ") - IGNORADA\n";
            isbnsDuplicados++;
            continue;
        }

        if (!validarAnio(anio)) {
            cout << "LINEA " << lineaNumero << ": AÑO INVALIDO (" << anio << ") - IGNORADA\n";
            lineasIgnoradas++;
            continue;
        }

        Libro *nuevoLibro = new Libro(titulo, isbn, genero, anio, autor);
        librosCargados->insertar(nuevoLibro);

        librosInsertados++;

    }

    archivo.close();
    cout << "--------------------------------------------------\n";
    cout << "RESUMEN DE CARGA:\n";
    cout << "TOTAL DE LINEAS PROCESADAS: " << lineaNumero - 1 << "\n";
    cout << "LIBROS CARGADOS CORRECTAMENTE: " << librosInsertados << "\n";
    cout << "LINEAS CON FORMATO INVALIDO: " << lineasIgnoradas << "\n";
    cout << "ISBNS DUPLICADOS RECHAZADOS: " << isbnsDuplicados << "\n";

    return librosCargados;
}

bool CargadorDatos::validarFormatoCSV(const string &rutaArchivo) {
    string rutaCompleta = rutaArchivo;

    if (rutaCompleta.length() < 4 ||
        rutaCompleta.substr(rutaCompleta.length() - 4) != ".csv") {
        rutaCompleta += ".csv";
    }

    ifstream archivo(rutaCompleta.c_str());

    if (!archivo.is_open()) {
        return false;
    }

    string linea;
    bool tieneEncabezado = false;

    if (getline(archivo, linea)) {
        if (linea.find("Titulo") != string::npos ||
            linea.find("ISBN") != string::npos) {
            tieneEncabezado = true;
        }
    }

    archivo.close();
    return tieneEncabezado;
}
