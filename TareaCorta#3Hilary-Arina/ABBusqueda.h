#ifndef ABBUSQUEDA_H
#define ABBUSQUEDA_H

#include "Nodo.h"

typedef Nodo* pnodo;

class ABBusqueda {
private:
    pnodo raiz;

    //metodos auxiliares privados
    pnodo InsertaBinario(pnodo raiz, int valor, int indice);
    bool Buscarvalor(pnodo raiz, int valor);
    int BuscarIndice(pnodo raiz, int valor);
    void InordenR(pnodo raiz);
    void PreordenR(pnodo raiz);
    void PostordenR(pnodo raiz);
    void destruirArbol(pnodo raiz);
    pnodo EliminarNodo(pnodo raiz, int valor);
    pnodo encontrarMinimo(pnodo raiz);

public:
    ABBusqueda();
    ~ABBusqueda();

    void InsertaNodo(int valor, int indice);
    bool Buscarvalor(int valor);
    int BuscarIndice(int valor);// devuelve el indice, o 0 si la cedula no esta

    void InordenR();
    void PreordenR();
    void PostordenR();

    void EliminarNodo(int valor);
    void Vaciar();
};

#endif
