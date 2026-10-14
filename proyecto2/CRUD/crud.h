#ifndef CRUD_H
#define CRUD_H

#include "arboles/ABBusqueda.h"
#include "arboles/arbolRN.h"

// Arboles
extern ABBusqueda arbolPaises;
extern ABBusqueda arbolCiudades;
extern ArbolRN arbolTratamientos;

// Paises
void insertarPais();
void buscarPais();

//Ciudades
void insertarCiudad();
void buscarCiudad();

//tratamientos
void insertarTratamiento();
void buscarTratamiento();

#endif