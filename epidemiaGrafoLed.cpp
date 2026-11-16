///Autores: Alvarado Méndez Oscar Eduardo (AM22043) 
/// Orellana Velasquez Daniela Estefany (OV22002) 
/// Hernandez Cardenas Joel Eduardo (HC23044)
 ///Fecha: Lunes 2 de noviembre del 2026 
///Hora: 9:00 pm 
/// Descripción: Implementación práctica relacionada con el estudio del uso de grafos
/// en modelos basados en agentes aplicados a la epidemiología. Cada persona se
/// representa como un nodo y sus contactos como conexiones. El programa utiliza
/// listas doblemente enlazadas para representar la red y simula los estados
/// susceptible, infectado y recuperado (modelo SIR).
/// No se utilizan contenedores STL como vector, list o map; sí se emplean
/// componentes de la biblioteca estándar de C++, como string, fstream e iostream.

/// ------------- Librerias utilizadas -------------
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

///Autores: Alvarado Méndez Oscar Eduardo (AM22043) 
/// Orellana Velasquez Daniela Estefany (OV22002) 
/// Hernandez Cardenas Joel Eduardo (HC23044)
 ///Fecha: Lunes 2 de noviembre del 2026 
///Hora: 9:00 pm 
/// Descripción: Implementación práctica relacionada con el estudio del uso de grafos
/// en modelos basados en agentes aplicados a la epidemiología. Cada persona se
/// representa como un nodo y sus contactos como conexiones. El programa utiliza
/// listas doblemente enlazadas para representar la red y simula los estados
/// susceptible, infectado y recuperado (modelo SIR).
/// No se utilizan contenedores STL como vector, list o map; sí se emplean
/// componentes de la biblioteca estándar de C++, como string, fstream e iostream.

/// ------------- Librerias utilizadas -------------
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;

/// ---------- Nodo de la lista doblemente enlazada (un contacto) ----------
struct Nodo {
    string id;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(const string& _id)
        : id(_id), siguiente(nullptr), anterior(nullptr) {}
};

/// ---------- Lista enlazada doble: contactos de una persona ----------
class ListaLED {
private:
    Nodo* cabeza;
    Nodo* cola;
    int tamano;

public:
    ListaLED() : cabeza(nullptr), cola(nullptr), tamano(0) {}

    /// Destructor: libera la memoria de los nodos
    ~ListaLED() { liberarMemoria(); }

    void liberarMemoria() {
        Nodo* actual = cabeza;
        while (actual) {
            Nodo* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
        cabeza = cola = nullptr;
        tamano = 0;
    }

    int cantidad() const { return tamano; }

    Nodo* obtenerCabeza() const { return cabeza; }

    /// Verifica si un ID ya existe en la lista
    bool existeID(const string& id) const {
        Nodo* actual = cabeza;
        while (actual) {
            if (actual->id == id) return true;
            actual = actual->siguiente;
        }
        return false;
    }

    /// Inserta al final usando el puntero cola
    bool insertarContacto(const string& id) {
        if (existeID(id)) return false;

        Nodo* nuevo = new Nodo(id);
        if (!cabeza) cabeza = cola = nuevo;
        else {
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        tamano++;
        return true;
    }

    /// Elimina un contacto por su ID
    bool eliminarContacto(const string& id) {
        Nodo* actual = cabeza;
        while (actual && actual->id != id) actual = actual->siguiente;

        if (!actual) return false;

        if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
        else cabeza = actual->siguiente;

        if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
        else cola = actual->anterior;

        delete actual;
        tamano--;
        return true;
    }

    /// Muestra los contactos de cabeza a cola
    void mostrarContactos() const {
        if (!cabeza) {
            cout << "(sin contactos)";
            return;
        }
        Nodo* actual = cabeza;
        while (actual) {
            cout << actual->id;
            if (actual->siguiente) cout << ", ";
            actual = actual->siguiente;
        }
    }

    /// Muestra los contactos de cola a cabeza
    void mostrarContactosInverso() const {
        if (!cola) {
            cout << "(sin contactos)";
            return;
        }
        Nodo* actual = cola;
        while (actual) {
            cout << actual->id;
            if (actual->anterior) cout << ", ";
            actual = actual->anterior;
        }
    }
};

/// ---------- Persona (vertice de la red) ----------
struct Persona {
    string id;
    string nombre;
    char estado;            // 'S', 'I' o 'R'
    bool marcaInfectar;     // marcas para actualizar los estados al final del dia
    bool marcaRecuperar;
    ListaLED contactos;
    Persona* siguiente;
    Persona* anterior;

    Persona(const string& _id, const string& _nombre, char _estado = 'S')
        : id(_id), nombre(_nombre), estado(_estado),
          marcaInfectar(false), marcaRecuperar(false),
          siguiente(nullptr), anterior(nullptr) {}
};

/// ---------- Red de contactos (lista doble de personas) ----------
class RedContactos {
private:
    Persona* cabeza;
    Persona* cola;
    int total;

    // Devuelve true con una probabilidad p (entre 0 y 1)
    bool hayProbabilidad(double p) const {
        return ((double)rand() / RAND_MAX) < p;
    }

    string textoEstado(char e) const {
        if (e == 'S') return "Susceptible";
        if (e == 'I') return "Infectado";
        return "Recuperado";
    }

public:
    RedContactos() : cabeza(nullptr), cola(nullptr), total(0) {}

    /// Destructor: libera cada persona y su lista de contactos
    ~RedContactos() { liberarMemoria(); }

    void liberarMemoria() {
        Persona* actual = cabeza;
        while (actual) {
            Persona* sig = actual->siguiente;
            delete actual;
            actual = sig;
        }
        cabeza = cola = nullptr;
        total = 0;
    }

    int cantidad() const { return total; }

    Persona* obtenerPersona(const string& id) const {
        Persona* actual = cabeza;
        while (actual) {
            if (actual->id == id) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    /// Registra una persona nueva al final de la red
    bool agregarPersona(const string& id, const string& nombre, char estado = 'S') {
        if (obtenerPersona(id)) return false;

        Persona* nueva = new Persona(id, nombre, estado);
        if (!cabeza) cabeza = cola = nueva;
        else {
            cola->siguiente = nueva;
            nueva->anterior = cola;
            cola = nueva;
        }
        total++;
        return true;
    }
//dany abajo
