// Creado por: Hilary Aguilar y Arina Tarasova
// Tarea Corta #1 - Estructuras de Datos

#include <iostream>  // entrada y salida de datos
#include <fstream>   // manejo y lectura de archivos de texto
#include <string>    // manejo de cadenas de texto
#include <cctype>    // funciones para validar caracteres (isdigit, isspace)

using namespace std; 

class nodo { 
public:
    nodo(string pvalor) { // Constructor con un valor, puntero a nulo
        valor = pvalor;
        siguiente = NULL; // no apunta a ningun nodo
    }
    nodo(string pvalor, nodo* sigNodo) { // Constructor con valor y puntero al siguiente
        valor = pvalor;
        siguiente = sigNodo; // apunta al nodo indicado
    }
private:
    string valor;     // almacena la expresion, operador o numero
    nodo* siguiente;  // guarda direccion del siguiente nodo
    friend class lista; // permite que la clase lista acceda a los miembros privados
    friend class bicola; // permite que acceda a los miembros privados
};

typedef nodo* pnodo; // Alias para puntero a nodo (pnodo = nodo*)

class lista {
public:
    lista() { // Construye la lista vacia
        primero = NULL;
    }
    bool ListaVacia() { return primero == NULL; } // Revisa si la lista esta vacia
    void InsertarInicio(string valor); 
    void InsertarFinal(string valor);
    void Mostrar();
    pnodo ObtenerPrimero() { return primero; } // Retorna la referencia al primer nodo

private:
    pnodo primero; // Puntero al primer elemento de la lista
};

void lista::InsertarInicio(string valor) { // Crea un nuevo nodo al inicio 
    if (ListaVacia()) {
        primero = new nodo(valor); // crea el primer nodo de la lista
    }
    else {
        primero = new nodo(valor, primero); // conecta el nuevo nodo con el nodo anterior
    }
}

void lista::InsertarFinal(string valor) { // Agrega un elemento al final de la lista
    if (ListaVacia())
        primero = new nodo(valor);
    else {
        pnodo nodoActual = primero;
        while (nodoActual->siguiente != NULL) // Avanza hasta el ultimo nodo
            nodoActual = nodoActual->siguiente;
        nodoActual->siguiente = new nodo(valor); // Conecta el nuevo nodo al final
    }
}

void lista::Mostrar() { // Imprime los elementos de la lista en orden
    pnodo nodoActual; // Puntero que recorre la lista
    if (primero == NULL)
        cout << "No hay elementos para mostrar" << endl;
    else {
        nodoActual = primero; // Comienza a recorrer desde el primer nodo
        while (nodoActual) {  // Continua mientras exista un nodo
            cout << nodoActual->valor << " ";
            nodoActual = nodoActual->siguiente; // Avanza al siguiente nodo
        }
        cout << endl;
    }
}

class bicola {
private:
    pnodo arreglo[5]; // Arreglo estatico de 5 posiciones que guarda referencias a listas
    int cantidad;     // Cantidad de elementos almacenados

public:
    bicola() {
        cantidad = 0;
        for (int i = 0; i < 5; i++) {
            arreglo[i] = NULL; // Inicializa cada posicion del arreglo en NULL
        }
    }

    void AsignarPosicion(int pos, pnodo primerNodo) { // Asigna la cabeza de la lista a la casilla
        if (pos >= 0 && pos < 5) { //&& es and
            arreglo[pos] = primerNodo;
            cantidad++;
        }
    }

    pnodo ObtenerPosicion(int pos) { // Devuelve el primer nodo almacenado en la posicion solicitada
        if (pos >= 0 && pos < 5) {
            return arreglo[pos];
        }
        return NULL;
    }
};

bool EsOperador(char c) { // Valida si un caracter corresponde a un operador matematico
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
} // || es or, retorna true o false. 

pnodo LeerArchivoAContenidoLista(string rutaArchivo) { // Lee un archivo de texto y convierte su contenido en una lista enlazada simple
    ifstream archivo(rutaArchivo.c_str()); // abre el archivo para lectura. c_str concierte string en un arreglo de caracteres
    if (!archivo.is_open()) { // is_open revisa si se abrio correctamente
        cout << "Error al abrir el archivo: " << rutaArchivo << endl;
        return NULL; //si no se pudo abrir
    }

    lista listaExpresion; // lista donde se guardara la expresion original
    string linea; // para almacenat cada linea leida del archivo
    string expresionCompleta = ""; // para almacenar la expresion completa

    while (getline(archivo, linea)) { //Lee el archivo linea por linea
        expresionCompleta += linea;
    }
    archivo.close();

    int i = 0; //para recorrer la cadena completa
    int n = expresionCompleta.length(); //longuitut de la cadena

    while (i < n) { // Recorre la cadena separando numeros de varios digitos u operadores
        char c = expresionCompleta[i]; //obtiene el caracter actual

        if (isspace(c)) { // Si es un espacio, se ignora y avanza, isspace sale de la libreria cctype
            i++;
            continue;
        }

        if (isdigit(c)) { // Si encuentra un digito, agrupa los continuos para formar el numero, isdigit tmb esta en cctype
            string numero = "";
            while (i < n && isdigit(expresionCompleta[i])) { 
                numero += expresionCompleta[i]; //agrega el digito al numero
                i++;
            }
            listaExpresion.InsertarFinal(numero); // Agrega el numero completo a la lista
        } 
        else if (EsOperador(c)) { // Si es un operador, lo agrega a la lista
            string op(1, c);//convierte el caracter en string
            listaExpresion.InsertarFinal(op); // agrega el operador a la lista
            i++;
        } 
        else {
            i++;
        }
    }

    return listaExpresion.ObtenerPrimero(); // Retorna el puntero al inicio de la lista
}