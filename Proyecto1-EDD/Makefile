CXX = g++
CXXFLAGS = -std=c++20 -g

SRC = main.cpp \
    Estructuras/ListaEnlazada/ListaEnlazada.cpp \
    Objetos/Libro.cpp \
    Utilidades/Biblioteca.cpp \
    Estructuras/Arboles/ArbolAVL/ArbolAVL.cpp \
    Utilidades/CargadorDatos.cpp \
    Estructuras/Arboles/ArbolAVL/NodoAVL.cpp \
    Estructuras/ListaEnlazada/NodoLista.cpp \
    Estructuras/Arboles/ArbolB/NodoB.cpp \
    Estructuras/Arboles/ArbolB/ArbolB.cpp \
    Estructuras/Arboles/ArbolB+/NodoBPlus.cpp \
    Estructuras/Arboles/ArbolB+/ArbolBPlus.cpp \
    Utilidades/ManejoBiblioteca.cpp \
    Utilidades/GeneradorGraficas.cpp

OBJ = $(SRC:.cpp=.o)

# DETECTA EL SISTEMA OPERATIVO
ifeq ($(OS),Windows_NT)
    TARGET = Proyecto1_EDD.exe
else
    TARGET = Proyecto1_EDD
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) Proyecto1_EDD Proyecto1_EDD.exe


