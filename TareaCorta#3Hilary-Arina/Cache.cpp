#include <iostream>
#include "Cache.h"

using namespace std;

NodoCache::NodoCache(int ind, int ced, string nom)
{
    indice = ind;
    cedula = ced;
    nombre = nom;
    sig = NULL;
}

Cache::Cache()
{
    primero = NULL;
    total = 0;
}

Cache::~Cache()
{
    vaciar();
}

bool Cache::estaVacia()
{
    return primero == NULL;
}

int Cache::cuantos()
{
    return total;
}

void Cache::agregarFinal(int indice, int cedula, string nombre)
{
    NodoCache *nuevo = new NodoCache(indice, cedula, nombre);
    if (primero == NULL)
    {
        primero = nuevo;
    }
    else
    {
        NodoCache *aux = primero;
        while (aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
    total = total + 1;
}

void Cache::eliminarPrimero()
{
    if (primero == NULL)
        return;
    NodoCache *temp = primero;
    primero = primero->sig;
    delete temp;
    total = total - 1;
}

void Cache::vaciar()
{
    while (primero != NULL)
    {
        eliminarPrimero();
    }
}

bool Cache::contiene(int indice)
{
    NodoCache *aux = primero;
    while (aux != NULL)
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
    while (aux != NULL)
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
    NodoCache *ant = NULL;
    NodoCache *aux = primero;
    while (aux != NULL && aux->indice != indice)
    {
        ant = aux;
        aux = aux->sig;
    }

    if (aux == NULL)
        return; // no esta en la cache: no hace nada
    if (ant == NULL)
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
        if (aux != NULL)
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
