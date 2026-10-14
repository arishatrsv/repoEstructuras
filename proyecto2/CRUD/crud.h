#ifndef CRUD_H
#define CRUD_H

#include "arboles/ABBusqueda.h"

// Arboles
extern ABBusqueda arbolPaises;
extern ABBusqueda arbolCiudades;

// Paises
void insertarPais();
void buscarPais();

//Ciudades
void insertarCiudad();
void buscarCiudad();
#endif