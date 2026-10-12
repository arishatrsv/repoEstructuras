#ifndef ARBOLPAISES_H
#define ARBOLPAISES_H

#include "NodoABB.h"

class ArbolPaises
{
private:
NodoABB* raiz;

NodoABB* insertar(NodoABB* actual, Pais pais);
bool buscar(NodoABB* actual, int codigo);
void mostrar(NodoABB* actual);
void destruir(NodoABB* actual);

public:
ArbolPaises();
~ArbolPaises();

bool insertar(Pais pais);
bool buscar(int codigo);
void mostrar();

};

#endif