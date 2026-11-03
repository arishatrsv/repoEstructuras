#include <cstddef>
#include "Nodo.h"

Nodo::Nodo(int val, int ind) 
{
    valor = val;
    indice = ind;
    Hizq = NULL;
    Hder = NULL;
}

