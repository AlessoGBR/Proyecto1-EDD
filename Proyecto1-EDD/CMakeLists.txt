cmake_minimum_required(VERSION 4.0)
project(Proyecto1_EDD)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto1_EDD main.cpp
        Estructuras/ListaEnlazada/ListaEnlazada.cpp
        Estructuras/ListaEnlazada/ListaEnlazada.h
        Objetos/Libro.cpp
        Objetos/Libro.h
        Utilidades/Biblioteca.cpp
        Utilidades/Biblioteca.h
        Estructuras/Arboles/ArbolAVL/ArbolAVL.cpp
        Estructuras/Arboles/ArbolAVL/ArbolAVL.h
        Utilidades/CargadorDatos.cpp
        Utilidades/CargadorDatos.h
        Estructuras/Arboles/ArbolAVL/NodoAVL.cpp
        Estructuras/Arboles/ArbolAVL/NodoAVL.h
        Estructuras/ListaEnlazada/NodoLista.cpp
        Estructuras/ListaEnlazada/NodoLista.h
        Estructuras/Arboles/ArbolB/NodoB.cpp
        Estructuras/Arboles/ArbolB/NodoB.h
        Estructuras/Arboles/ArbolB/ArbolB.cpp
        Estructuras/Arboles/ArbolB/ArbolB.h
        Estructuras/Arboles/ArbolB+/NodoBPlus.cpp
        Estructuras/Arboles/ArbolB+/NodoBPlus.h
        Estructuras/Arboles/ArbolB+/ArbolBPlus.cpp
        Estructuras/Arboles/ArbolB+/ArbolBPlus.h
        Utilidades/ManejoBiblioteca.cpp
        Utilidades/ManejoBiblioteca.h
        Utilidades/GeneradorGraficas.cpp
        Utilidades/GeneradorGraficas.h
)
