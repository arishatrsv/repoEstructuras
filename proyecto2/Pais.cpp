#include "Pais.h"

Pais::Pais()
{
codigo = 0;
nombre = "";
}

Pais::Pais(int codigo, string nombre)
{
this->codigo = codigo;
this->nombre = nombre;
}