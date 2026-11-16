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

