#include <iostream>
#include <string>
#include "crud.h"

using namespace std;

// Arbol de ciudades (clave compuesta: codPais + codCiudad).
ABBusqueda arbolCiudades(TipoClave::Ciudad);

void insertarCiudad(){
    int codPais;
    int codCiudad;
    string nombre;

    cout << "Codigo del pais: ";
    if (!leerEntero(codPais)){
        cout << "Codigo invalido." << endl;
        return;
    }

    if (!arbolPaises.Buscarvalor(codPais)) // validacion: el pais debe existir
    {
        cout << "El pais no existe." << endl;
        return;
    }

    cout << "Codigo de la ciudad: ";
    if (!leerEntero(codCiudad)){
        cout << "Codigo invalido." << endl;
        return;
    }

    if (arbolCiudades.Buscarvalor(codPais, codCiudad)) // validacion: ciudad no repetida
    {
        cout << "La ciudad ya existe en ese pais." << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, nombre);
    if (nombre.empty()){
        cout << "El nombre no puede estar vacio." << endl;
        return;
    }
    arbolCiudades.InsertaNodo(codPais, codCiudad, nombre);
    cout << "Ciudad insertada correctamente." << endl;
}

void buscarCiudad(){
    int codPais;
    int codCiudad;

    cout << "Digite el codigo del pais: ";
    if (!leerCodigo(codPais)){
        cout << "Codigo invalido." << endl;
        return;
    }

    if (!arbolPaises.Buscarvalor(codPais)) // validacion: el pais debe existir
    {
        cout << "El pais no existe." << endl;
        return;
    }
    cout << "Digite el codigo de la ciudad: ";
    if (!leerCodigo(codCiudad)){
        cout << "Codigo invalido." << endl;
        return;
    }

    if (arbolCiudades.Buscarvalor(codPais, codCiudad)){
        cout << "Ciudad encontrada: ";
        arbolCiudades.mostrarPorClave(codPais, codCiudad);
    }
    else{
        cout << "La ciudad no existe." << endl;
    }
}