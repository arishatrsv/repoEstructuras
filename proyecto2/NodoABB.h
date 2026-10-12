#ifndef NODOABB_H
#define NODOABB_H

#include "Pais.h"

class NodoABB
{
public:
Pais dato;
NodoABB* Hizq;
NodoABB* Hder;

NodoABB(Pais pais);

};

#endif