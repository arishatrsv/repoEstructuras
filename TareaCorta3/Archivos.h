#ifndef ARCHIVOS_H
#define ARCHIVOS_H

#include <fstream>
#include <string>
#include "ABBusqueda.h"
#include "Cache.h"

using namespace std;

//lee un registro "cedula;nombre" o "cedula;nombre;1". 1 = borrado logico
bool leerRegistro(ifstream &archivo, int &cedula, string &nombre, int &borrado);
void escribirRegistro(ofstream &salida, int cedula, string nombre, int borrado);
int contarRegistros();
void depurarClientes();//quita cedulas repetidas
void crearIndices();//crea Indices.txt
void construirArbol(ABBusqueda &arbol);//arbol a partir de Indices.txt
int agregarCliente(int cedula, string nombre); //devuelve el indice nuevo
void agregarIndice(int indice, int cedula);
void marcarBorrado(int indice); //pone el 1 al final del registro
bool purgar(); //false si no habia borrados
void llenarCache(Cache &cache, int desde, int hasta);
void cargarCacheBusqueda(Cache &cache, int indice);
void cargarCacheInsercion(Cache &cache);

#endif
