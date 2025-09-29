//
// Created by alesso on 23/09/25.
//

#ifndef PROYECTO1_EDD_LIBRO_H
#define PROYECTO1_EDD_LIBRO_H
#include <string>
#include <iostream>
using namespace std;

class Libro {
public:
    string titulo;
    string isbn;
    string genero;
    int anio;
    string autor;

    Libro(string t, string i, string g, int a, string au)
        : titulo(t), isbn(i), genero(g), anio(a), autor(au) {
    }

    string getTitulo() const { return titulo; }
    string getIsbn() const { return isbn; }
    string getGenero() const { return genero; }
    int getAño() const { return anio; }
    string getAutor() const { return autor; }

    void setTitulo(const string &titulo) { this->titulo = titulo; }
    void setIsbn(const string &isbn) { this->isbn = isbn; }
    void setGenero(const string &genero) { this->genero = genero; }
    void setAño(int anio) { this->anio = anio; }
    void setAutor(const string &autor) { this->autor = autor; }

    void mostrarInfo() const {
        cout << "TITULO: " << titulo << "\n";
        cout << "ISBN: " << isbn << "\n";
        cout << "GENERO: " << genero << "\n";
        cout << "ANIO: " << anio << "\n";
        cout << "AUTOR: " << autor << "\n";
    }
};

#endif //PROYECTO1_EDD_LIBRO_H
