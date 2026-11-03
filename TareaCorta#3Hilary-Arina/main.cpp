#include <iostream>
#include "ABBusqueda.h"
#include "Cache.h"
#include "Archivos.h"

using namespace std;

//lee un numero entero, si el usuario escribe otra cosa, vuelve a pedirlo
int leerEntero() 
{
    int numero;
    cin >> numero;
    while (cin.fail() && !cin.eof()) 
	{
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Dato invalido, digite un numero: ";
        cin >> numero;
    }
    return numero;
}

void mostrarArbol(ABBusqueda &arbol) 
{
    cout << endl << "ARBOL preorden, cedula(indice): " << endl;
    arbol.PreordenR();
}

void mostrarCache(Cache &cache) 
{
    cout << endl << "CACHE:" << endl;
    cache.mostrar();
}

void mostrarTodo(ABBusqueda &arbol, Cache &cache) 
{
    mostrarArbol(arbol);
    mostrarCache(cache);
}

//lee Clientes.txt sin repetidos, crea Indices.txt y construye el arbol
void ingresar(ABBusqueda &arbol, Cache &cache) 
{
    depurarClientes();
    crearIndices();
    construirArbol(arbol);
    cache.vaciar();
    cout << "Clientes depurados, indices creados y arbol construido" << endl;
}

void buscarCliente(ABBusqueda &arbol, Cache &cache) 
{
    int cedula, indice;
    cout << "Cedula a buscar: ";
    cedula = leerEntero();
    indice = arbol.BuscarIndice(cedula);
    if (indice == 0) 
	{
        cout << "No existe" << endl;
    } 
	else 
	{
        if (cache.contiene(indice)) 
		{
            cout << "Encontrado en la cache" << endl;
        } 
		else 
		{
            cout << "No esta en la cache, se carga desde Clientes.txt" << endl;
            cargarCacheBusqueda(cache, indice);
        }
        cache.mostrarCliente(indice);
    }
    mostrarTodo(arbol, cache);
}

void insertarCliente(ABBusqueda &arbol, Cache &cache) 
{
    int cedula, indice;
    string nombre;
    cout << "Cedula: ";
    cedula = leerEntero();
    if (arbol.Buscarvalor(cedula)) 
	{
        cout << "La cedula ya existe, no se inserta" << endl;
    } 
	else 
	{
        cout << "Nombre (una sola palabra): ";
        cin >> nombre;
        indice = agregarCliente(cedula, nombre);
        agregarIndice(indice, cedula);
        arbol.InsertaNodo(cedula, indice);
        cargarCacheInsercion(cache);
        cout << "Cliente insertado en la posicion " << indice << endl;
    }
    mostrarTodo(arbol, cache);
}

void eliminarCliente(ABBusqueda &arbol, Cache &cache) 
{
    int cedula, indice;
    cout << "Cedula a eliminar: ";
    cedula = leerEntero();
    indice = arbol.BuscarIndice(cedula);
    if (indice == 0) 
	{
        cout << "El cliente no existe" << endl;
    } 
	else 
	{
        arbol.EliminarNodo(cedula);
        marcarBorrado(indice);
        cache.eliminarIndice(indice);
        cout << "Cliente eliminado " << endl;
    }
    mostrarTodo(arbol, cache);
}

void purgarClientes(ABBusqueda &arbol, Cache &cache) 
{
    if (purgar()) 
	{
        cout << "Archivo purgado. Los indices cambiaron: ejecute 7. Reindexar para que indices y arbol coincidan con Clientes.txt" << endl;
        cache.vaciar(); //los indices guardados en la cache ya no son validos << "Archivo purgado, se ejecutó reindexar, indices y arbol ya no coinciden con Clientes.txt" << endl;
    } 
	else 
	{
        cout << "No hay registros borrados, no se jace nada" << endl;
    }
    mostrarTodo(arbol, cache);
}

void reindexar(ABBusqueda &arbol, Cache &cache) 
{
    crearIndices();
    construirArbol(arbol);
    cache.vaciar();
    cout << "Indices recreados y arbol reconstruido" << endl;
    mostrarTodo(arbol, cache);
}

int main() 
{
    ABBusqueda arbol;
    Cache cache;
    int opcion;
    ingresar(arbol, cache);
    do 
	{
        cout << endl;
        cout << "MENU" << endl;
        cout << "0. Ingresar (limpia clientes, crea indices y arbol)" << endl;
        cout << "1. Ver arbol en preorden" << endl;
        cout << "2. Ver cache" << endl;
        cout << "3. Buscar" << endl;
        cout << "4. Insertar" << endl;
        cout << "5. Eliminar" << endl;
        cout << "6. Purgar" << endl;
        cout << "7. Reindexar" << endl;
        cout << "8. Salir" << endl;
        cout << "Opcion: ";
        opcion = leerEntero();
        if (cin.eof()) 
		{
            opcion = 8;
        }
        if (opcion == 0) 
		{
            ingresar(arbol, cache);
            mostrarTodo(arbol, cache);
        } 
		else if (opcion == 1) 
		{
            mostrarArbol(arbol);
        } 
		else if (opcion == 2) 
		{
            mostrarCache(cache);
        } 
		else if (opcion == 3) 
		{
            buscarCliente(arbol, cache);
        } 
		else if (opcion == 4) 
		{
            insertarCliente(arbol, cache);
        } 
		else if (opcion == 5) 
		{
            eliminarCliente(arbol, cache);
        } 
		else if (opcion == 6) 
		{
            purgarClientes(arbol, cache);
        } 
		else if (opcion == 7) 
		{
            reindexar(arbol, cache);
        }
    } 
	while (opcion != 8);
    return 0;
}
