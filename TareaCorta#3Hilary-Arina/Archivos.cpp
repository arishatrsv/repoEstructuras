#include <iostream>
#include <cstdio>
#include "Archivos.h"

using namespace std;

bool leerRegistro(ifstream &archivo, int &cedula, string &nombre, int &borrado) 
{
    char c;
    string basura;
    if (!(archivo >> cedula)) 
	{
        if (archivo.eof()) return false;
        archivo.clear();
        getline(archivo, basura); // salta el encabezado
        if (!(archivo >> cedula)) return false;
    }
    archivo.get(c);// el ';' despues de la cedula
    nombre = "";
    borrado = 0;
    archivo.get(c);
    while (c != '\n' && c != '\r' && c != ';' && !archivo.eof()) 
	{
        nombre = nombre + c;
        archivo.get(c);
    }
    if (c == ';') 
	{
        archivo >> borrado;
        getline(archivo, basura);// resto de la linea
    }
    return true;
}

void escribirRegistro(ofstream &salida, int cedula, string nombre, int borrado) 
{
    salida << cedula << ";" << nombre;
    if (borrado == 1) 
	{
        salida << ";1";
    }
    salida << endl;
}

int contarRegistros() 
{
    ifstream clientes("Clientes.txt");
    int cedula, borrado;
    int cuantos = 0;
    string nombre;

    while (leerRegistro(clientes, cedula, nombre, borrado)) 
	{
        cuantos = cuantos + 1;
    }
    clientes.close();
    return cuantos;
}

//copia a Temporal.txt solo las cedulas no repetidas.
//para saber si una cedula ya salio se usa un ABB auxiliar
void depurarClientes() 
{
    ifstream original("Clientes.txt");

    if (original.fail()) 
	{
        cout << "No se pudo abrir Clientes.txt" << endl;
        return;
    }

    ofstream nuevo("Temporal.txt");
    ABBusqueda vistos;
    int cedula, borrado;
    string nombre;

    nuevo << "cedula;nombre" << endl;

    while (leerRegistro(original, cedula, nombre, borrado)) 
	{
        if (borrado == 1) 
		{
            escribirRegistro(nuevo, cedula, nombre, borrado);
        } 
		else 
		{
            if (vistos.Buscarvalor(cedula) == false) 
			{
                vistos.InsertaNodo(cedula, 0);
                escribirRegistro(nuevo, cedula, nombre, borrado);
            }
        }
    }
    original.close();
    nuevo.close();
    remove("Clientes.txt");
    rename("Temporal.txt", "Clientes.txt");
}
void crearIndices() 
{
    ifstream clientes("Clientes.txt");
    ofstream indices("Indices.txt");
    int cedula, borrado;
    int pos = 0;
    string nombre;
    while (leerRegistro(clientes, cedula, nombre, borrado)) 
	{
        pos = pos + 1;
        if (borrado == 0) 
		{
            indices << pos << ";" << cedula << endl;
        }
    }
    clientes.close();
    indices.close();
}

void construirArbol(ABBusqueda &arbol) 
{
    ifstream indices("Indices.txt");
    int indice, cedula;
    char c;
    arbol.Vaciar();
    while (indices >> indice) 
	{
        indices.get(c);//el ';', pertenece a la clase ifstream
        indices >> cedula;
        arbol.InsertaNodo(cedula, indice);
    }
    indices.close();
}

int agregarCliente(int cedula, string nombre) 
{
    int nuevo = contarRegistros() + 1;
    ofstream clientes("Clientes.txt", ios::app);
    escribirRegistro(clientes, cedula, nombre, 0);
    clientes.close();
    return nuevo;
}

void agregarIndice(int indice, int cedula) 
{
    ofstream indices("Indices.txt", ios::app);
    indices << indice << ";" << cedula << endl;
    indices.close();
}

//se copia todo a Temporal.txt y al registro "indice" se le pone el 1
void marcarBorrado(int indice) 
{
    ifstream original("Clientes.txt");
    ofstream nuevo("Temporal.txt");
    int cedula, borrado;
    int pos = 0;
    string nombre;
    nuevo << "cedula;nombre" << endl;
    while (leerRegistro(original, cedula, nombre, borrado)) 
	{
        pos = pos + 1;
        if (pos == indice) 
		{
            borrado = 1;
        }
        escribirRegistro(nuevo, cedula, nombre, borrado);
    }
    original.close();
    nuevo.close();
    remove("Clientes.txt");
    rename("Temporal.txt", "Clientes.txt");
}

//pasa a Temporal.txt solo los registros que no tienen el 1
bool purgar() 
{
    ifstream original("Clientes.txt");
    int cedula, borrado;
    string nombre;
    bool hay = false;
    while (leerRegistro(original, cedula, nombre, borrado)) 
	{
        if (borrado == 1) 
		{
            hay = true;
        }
    }
    original.close();
    if (hay == false) return false; //no hay 1, no hace nada
    ifstream origen("Clientes.txt");
    ofstream nuevo("Temporal.txt");
    nuevo << "cedula;nombre" << endl;
    while (leerRegistro(origen, cedula, nombre, borrado)) 
	{
        if (borrado == 0) 
		{
            escribirRegistro(nuevo, cedula, nombre, borrado);
        }
    }
    origen.close();
    nuevo.close();
    remove("Clientes.txt");
    rename("Temporal.txt", "Clientes.txt");
    return true;
}

//se detiene si la cache llega a 20
void llenarCache(Cache &cache, int desde, int hasta) 
{
    ifstream clientes("Clientes.txt");
    int cedula, borrado;
    int pos = 0;
    string nombre;
    while (pos < hasta && cache.cuantos() < TAM_CACHE && leerRegistro(clientes, cedula, nombre, borrado)) 
	{
        pos = pos + 1;
        if (pos >= desde && borrado == 0) 
		{
            cache.agregarFinal(pos, cedula, nombre);
        }
    }
    clientes.close();
}

void cargarCacheBusqueda(Cache &cache, int indice) 
{
    int total = contarRegistros();
    cache.vaciar();
    llenarCache(cache, indice, total);
    if (cache.cuantos() < TAM_CACHE) 
	{
        llenarCache(cache, 1, indice - 1); //si llega al final del archivo sigue circular desde la posicion 1
    }
}

void cargarCacheInsercion(Cache &cache) 
{
    ifstream clientes("Clientes.txt");
    int cedula, borrado;
    int pos = 0;
    string nombre;
    cache.vaciar();
    while (leerRegistro(clientes, cedula, nombre, borrado)) 
	{
        pos = pos + 1;
        if (borrado == 0) 
		{
            cache.agregarFinal(pos, cedula, nombre);
            if (cache.cuantos() > TAM_CACHE) 
			{
                cache.eliminarPrimero();
            }
        }
    }
    clientes.close();
}
