#ifndef NODO_H
#define NODO_H

class Nodo 
{
public:
    int valor; //cedula es la llave del arbol
    int indice; //posicion del registro dentro de Clientes.txt
    Nodo* Hizq;
    Nodo* Hder;

    Nodo(int val, int ind);
    
friend class ABBusqueda;
};

#endif
