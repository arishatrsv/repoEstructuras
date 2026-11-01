#include <iostream>
#include "ABBusqueda.h"

using namespace std;

// Constructor
ABBusqueda::ABBusqueda()
{
    raiz = nullptr;
}

// Destructor
ABBusqueda::~ABBusqueda()
{
    destruirArbol(raiz);
}

// Metodos publicos
void ABBusqueda::InsertaNodo(int valor, int indice)
{
    if (raiz == NULL)
    {
        raiz = new Nodo(valor, indice);
    }
    else
    {
        raiz = InsertaBinario(raiz, valor, indice);
    }
}

bool ABBusqueda::Buscarvalor(int valor)
{
    return Buscarvalor(raiz, valor);
}

int ABBusqueda::BuscarIndice(int valor)
{
    return BuscarIndice(raiz, valor);
}

void ABBusqueda::InordenR()
{
    InordenR(raiz);
    cout << endl;
}

void ABBusqueda::PreordenR()
{
    if (raiz == nullptr)
    {
        cout << "Arbol vacio";
    }
    else
    {
        PreordenR(raiz);
    }
    cout << endl;
}

void ABBusqueda::PostordenR()
{
    PostordenR(raiz);
    cout << endl;
}

void ABBusqueda::EliminarNodo(int valor)
{
    raiz = EliminarNodo(raiz, valor);
}

void ABBusqueda::Vaciar()
{
    destruirArbol(raiz);
    raiz = nullptr;
}

// Metodos privados
pnodo ABBusqueda::InsertaBinario(pnodo raiz, int valor, int indice)
{
    if (raiz == nullptr)
    {
        return new Nodo(valor, indice);
    }
    if (valor < raiz->valor)
    {
        raiz->Hizq = InsertaBinario(raiz->Hizq, valor, indice);
    }
    else if (valor > raiz->valor)
    {
        raiz->Hder = InsertaBinario(raiz->Hder, valor, indice);
    }

    return raiz;
}

bool ABBusqueda::Buscarvalor(pnodo raiz, int valor)
{
    if (raiz == nullptr)
        return false;
    if (valor == raiz->valor)
        return true;
    if (valor < raiz->valor)
        return Buscarvalor(raiz->Hizq, valor);
    else
        return Buscarvalor(raiz->Hder, valor);
}

int ABBusqueda::BuscarIndice(pnodo raiz, int valor)
{
    if (raiz == nullptr)
        return 0;
    if (valor == raiz->valor)
        return raiz->indice;
    if (valor < raiz->valor)
        return BuscarIndice(raiz->Hizq, valor);
    else
        return BuscarIndice(raiz->Hder, valor);
}

void ABBusqueda::InordenR(pnodo raiz)
{
    if (raiz == nullptr)
        return;
    InordenR(raiz->Hizq);
    cout << raiz->valor << " - ";
    InordenR(raiz->Hder);
}

void ABBusqueda::PreordenR(pnodo raiz)
{
    if (raiz == nullptr)
        return;
    cout << raiz->valor << "(" << raiz->indice << ") - ";
    PreordenR(raiz->Hizq);
    PreordenR(raiz->Hder);
}

void ABBusqueda::PostordenR(pnodo raiz)
{
    if (raiz == nullptr)
        return;
    PostordenR(raiz->Hizq);
    PostordenR(raiz->Hder);
    cout << raiz->valor << " - ";
}

void ABBusqueda::destruirArbol(pnodo raiz)
{
    if (raiz == nullptr)
        return;
    destruirArbol(raiz->Hizq);
    destruirArbol(raiz->Hder);
    delete raiz;
}

pnodo ABBusqueda::encontrarMinimo(pnodo raiz)
{
    while (raiz->Hizq != nullptr)
    {
        raiz = raiz->Hizq;
    }
    return raiz;
}

pnodo ABBusqueda::EliminarNodo(pnodo raiz, int valor)
{
    if (raiz == nullptr)
    {
        cout << "Valor no encontrado: " << valor << endl;
        return nullptr;
    }
    if (valor < raiz->valor)
    {
        raiz->Hizq = EliminarNodo(raiz->Hizq, valor);
    }
    else if (valor > raiz->valor)
    {
        raiz->Hder = EliminarNodo(raiz->Hder, valor);
    }
    else
    {
        // Nodo encontrado
        if (raiz->Hizq == nullptr && raiz->Hder == nullptr)
        {
            delete raiz;
            return nullptr;
        }
        else if (raiz->Hizq == nullptr)
        {
            pnodo temp = raiz->Hder;
            delete raiz;
            return temp;
        }
        else if (raiz->Hder == nullptr)
        {
            pnodo temp = raiz->Hizq;
            delete raiz;
            return temp;
        }
        else
        {
            pnodo sucesor = encontrarMinimo(raiz->Hder);
            raiz->valor = sucesor->valor;
            raiz->indice = sucesor->indice;
            raiz->Hder = EliminarNodo(raiz->Hder, sucesor->valor);
        }
    }

    return raiz;
}
