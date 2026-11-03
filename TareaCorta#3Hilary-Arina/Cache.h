#ifndef CACHE_H
#define CACHE_H

#include <string>

using namespace std;

const int TAM_CACHE = 20;

// Nodo de la lista enlazada de la cache
class NodoCache 
{
public:
    int indice;
    int cedula;
    string nombre;
    NodoCache* sig;
    NodoCache(int ind, int ced, string nom);
};

class Cache 
{
private:
    NodoCache* primero;
    int total;
public:
    Cache();
    ~Cache();
    bool estaVacia();
    int cuantos();
    void agregarFinal(int indice, int cedula, string nombre);
    void eliminarPrimero();
    bool contiene(int indice);
    void mostrarCliente(int indice);
    void eliminarIndice(int indice); // quita el registro y corre los demas
    void vaciar();
    void mostrar();
};

#endif
