#include <iostream>
#include "Cache.h"

using namespace std;

NodoCache::NodoCache(int ind, int ced, string nom)
{
    indice = ind;
    cedula = ced;
    nombre = nom;
    sig = nullptr;
}

Cache::Cache()
{
    primero = nullptr;
    total = 0;
}

Cache::~Cache()
{
    vaciar();
}

bool Cache::estaVacia()
{
    return primero == nullptr;
}

int Cache::cuantos()
{
    return total;
}

void Cache::agregarFinal(int indice, int cedula, string nombre)
{
    NodoCache *nuevo = new NodoCache(indice, cedula, nombre);
    if (primero == nullptr)
    {
        primero = nuevo;
    }
    else
    {
        NodoCache *aux = primero;
        while (aux->sig != nullptr)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    total = total + 1;
}

void Cache::eliminarPrimero()
{
    if (primero == nullptr)
        return;
    NodoCache *temp = primero;
    primero = primero->sig;
    delete temp;
    total = total - 1;
}

void Cache::vaciar()
{
    while (primero != nullptr)
    {
        eliminarPrimero();
    }
}

bool Cache::contiene(int indice)
{
    NodoCache *aux = primero;
    while (aux != nullptr)
    {
        if (aux->indice == indice)
            return true;
        aux = aux->sig;
    }
    return false;
}

void Cache::mostrarCliente(int indice)
{
    NodoCache *aux = primero;
    while (aux != nullptr)
    {
        if (aux->indice == indice)
        {
            cout << "Indice: " << aux->indice << "  Cedula: " << aux->cedula
                << "  Nombre: " << aux->nombre << endl;
            return;
        }
        aux = aux->sig;
    }
}

void Cache::eliminarIndice(int indice)
{
    NodoCache *ant = nullptr;
    NodoCache *aux = primero;
    while (aux != nullptr && aux->indice != indice)
    {
        ant = aux;
        aux = aux->sig;
    }

    if (aux == nullptr)
        return; // no esta en la cache: no hace nada
    if (ant == nullptr)
    {
        primero = aux->sig;
    }
    else
    {
        ant->sig = aux->sig;
    }
    delete aux;
    total = total - 1;
}

void Cache::mostrar()
{
    if (total == 0)
    {
        cout << "Cache vacia" << endl;
        return;
    }
    cout << "Pos\tIndice\tCedula\tNombre" << endl; //\t paa columnas, tab
    NodoCache *aux = primero;
    int pos = 1;
    while (pos <= TAM_CACHE)
    {
        cout << pos << "\t";
        if (aux != nullptr)
        {
            cout << aux->indice << "\t" << aux->cedula << "\t" << aux->nombre << endl;
            aux = aux->sig;
        }
        else
        {
            cout << "-\t-\t(libre)" << endl;
        }
        pos = pos + 1;
    }
}
