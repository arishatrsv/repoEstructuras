// Creado por: Hilary Aguilar y Arina Tarasova
// Tarea Corta #2 - Estructuras de Datos

#include <iostream>  // entrada y salida de datos
#include <fstream>   // manejo y lectura de archivos de texto
#include <string>    // manejo de cadenas de texto

using namespace std;

#define TAM 5 // Tamano estatico para la Bicola

class nodo;
class lista;
typedef nodo* pnodo; // Alias para puntero a nodo (pnodo = nodo*)

bool EsDigito(char c) {
    return (c >= '0' && c <= '9');
}

bool EsEspacio(char c) { // Comprueba manualmente espacios en blanco o saltos de linea
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool EsOperador(char c) { // Valida si un caracter corresponde a un operador matematico
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
} // || es or, retorna true o false. 

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
    string ObtenerValor() {
    return valor;
}
    pnodo ObtenerSiguiente() {
    return siguiente;
}

private:
    string valor;     // almacena la expresion, operador o numero
    nodo* siguiente;  // guarda direccion del siguiente nodo
    friend class lista; // permite que la clase lista acceda a los miembros privados
    friend class Bicola; // permite que acceda a los miembros privados
};

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

class Bicola {
private:
    pnodo datos[TAM]; // Guarda las referencias a las listas creadas por archivo
    int frente;
    int fondo;
    int cantidad;

public:
    Bicola() { // Constructor de la bicola
        frente = 0;
        fondo = -1; // Inicializa el fondo en -1 porque la bicola esta vacia
        cantidad = 0; // Inicializa la cantidad de elementos en 0
        for (int i = 0; i < TAM; i++) { // Recorre todas las posiciones del arreglo
            datos[i] = NULL; // Inicializa cada posicion del arreglo como vacia
        }
    }

    bool estaVacia() {
        return cantidad == 0;
    }

    bool estaLlena() {
        return cantidad == TAM;
    }

    void insertarFrente(pnodo valor) {
        if (estaLlena()) {
            cout << "Bicola llena. No se puede insertar al frente.\n";
            return; // Sale del metodo sin insertar
        }
        if (estaVacia()) { // Verifica si es la primera insercion
            frente = 0;
            fondo = 0;
        }
        else {
            frente = (frente - 1 + TAM) % TAM; // Mueve el frente una posicion hacia atras de forma circular
        }
        datos[frente] = valor; // Guarda el nodo en la posicion del frente
        cantidad++;
    }

    void insertarFinal(pnodo valor) {
        if (estaLlena()) {
            cout << "Bicola llena. No se puede insertar al final.\n";
            return;
        }
        if (estaVacia()) { // Verifica si es la primera insercion
            frente = 0;
            fondo = 0;
        }
        else {
            fondo = (fondo + 1) % TAM; // Mueve el fondo una posicion hacia adelante de forma circular
        }
        datos[fondo] = valor; // Guarda el nodo en la posicion del fondo
        cantidad++;
    }

    pnodo eliminarFrente() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo valor = datos[frente]; // Guarda temporalmente el nodo del frente
        cantidad--; // Disminuye la cantidad de elementos
        if (cantidad == 0) { // Verifica si se elimino el ultimo elemento
            frente = 0; // Reinicia el frente
            fondo = -1; // Reinicia el fondo indicando que esta vacia
        }
        else {
            frente = (frente + 1) % TAM; // Mueve el frente una posicion hacia adelante de forma circular
        }
        return valor;// Retorna el nodo que fue eliminado
    }

    pnodo eliminarFinal() { // Elimina y retorna el nodo que esta en el final
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo valor = datos[fondo]; // Guarda temporalmente el nodo del final
        cantidad--;
        if (cantidad == 0) { // Verifica si se elimino el ultimo elemento
            frente = 0; // Reinicia el frente
            fondo = -1; // Reinicia el fondo indicando que esta vacia
        }
        else {
            fondo = (fondo - 1 + TAM) % TAM; // Mueve el fondo una posicion hacia atras de forma circular
        }
        return valor; // Retorna el nodo que fue eliminado
    }

    pnodo obtenerPosicion(int pos) { // Obtiene el nodo almacenado en una posicion especifica
        if (pos >= 0 && pos < TAM) { // Verifica que la posicion este dentro del arreglo
            return datos[pos]; // Retorna el nodo de esa posicion
        }
        return NULL;
    }

    void mostrar() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return;
        }
        else {
            cout << "Contenido de la bicola:\n";
            int i = frente; // Inicia el recorrido desde el frente
            for (int pos = 0; pos < cantidad; pos++) { // Recorre todos los elementos de la bicola
                cout << "Posicion [" << i << "]: ";
                pnodo actual = datos[i]; // Obtiene el primer nodo de la lista almacenada
                while (actual != NULL) { // Recorre todos los nodos de la lista
                    cout << actual->valor << " "; // Muestra el valor del nodo actual
                    actual = actual->siguiente;
                }
                cout << endl;
                i = (i + 1) % TAM; // Avanza a la siguiente posicion de forma circular
            }
        }
    }
};

class NodoArbol;
typedef NodoArbol* pNodoArbol;

class NodoArbol{
private:
    string valor;
    pNodoArbol izquierdo;
    pNodoArbol derecho;

public:
    NodoArbol(string pValor){
        valor = pValor;
        izquierdo = NULL;
        derecho = NULL;
    }
    string ObtenerValor() {
    return valor;
}
    friend class Arbol;
};

class NodoPilaArbol;
typedef NodoPilaArbol* pNodoPilaArbol;
class PilaRecorrido;

class NodoPilaArbol{
private: 
	pNodoArbol nodoArbol;
	pNodoPilaArbol siguiente;
public:
	NodoPilaArbol(pNodoArbol pNodo) {
		nodoArbol = pNodo;
		siguiente = NULL;
	}
	friend class PilaOperadores;
    friend class PilaOperandos;
    friend class PilaRecorrido;
};

class PilaOperadores {
private: 
    pNodoPilaArbol tope;
public:
    PilaOperadores() { tope = NULL; }
	bool estaVacia() { 
        return tope == NULL; }
    void Push(pNodoArbol nodo); //apilar
    pNodoArbol Pop(); //desapilar
    pNodoArbol VerTope();
};

void PilaOperadores::Push(pNodoArbol nodo) { //Push= Agrega un nuevo elemento al tope de la pila
    pNodoPilaArbol nuevo = new NodoPilaArbol(nodo);
    if (estaVacia()) {
        tope = nuevo;
    }
    else {
            pNodoPilaArbol actual = tope;
            while (actual->siguiente != NULL) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

pNodoArbol PilaOperadores::Pop() { //Pop= Saca y retorna el elemento que esta en el tope
    if (estaVacia()){
        return NULL;
    }

    if (tope->siguiente == NULL){
        pNodoArbol nodo = tope->nodoArbol;
        delete tope;
        tope = NULL;
        return nodo;
    }
    pNodoPilaArbol anterior = tope;
    while (anterior->siguiente->siguiente != NULL) {
        anterior = anterior->siguiente;
    }
    pNodoPilaArbol temp = anterior->siguiente;
    pNodoArbol nodo = temp->nodoArbol;
    anterior->siguiente = NULL;
    delete temp;
    return nodo;
}

pNodoArbol PilaOperadores::VerTope(){
    if (estaVacia()){
        return NULL;
    }
    return tope->nodoArbol;
}

class PilaOperandos {
private:
    pNodoPilaArbol tope;

public:
    PilaOperandos(){
        tope = NULL;
    }
    bool estaVacia() {
        return tope == NULL;
    }
    void Push(pNodoArbol nodo); //apilar
    pNodoArbol Pop(); //desapilar
    pNodoArbol VerTope();   
};

void PilaOperandos::Push(pNodoArbol nodo) { //Push= Agrega un nuevo elemento al tope de la pila
    pNodoPilaArbol nuevo = new NodoPilaArbol(nodo);
    if (estaVacia()) {
        tope = nuevo;
    }
    else {
        pNodoPilaArbol actual = tope;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

pNodoArbol PilaOperandos::Pop() { //Pop= Saca y retorna el elemento que esta en el tope
    if (estaVacia()) {
        return NULL;
    }
    if (tope->siguiente == NULL) {
        pNodoArbol nodo = tope->nodoArbol;
        delete tope;
        tope = NULL;
        return nodo;
    }
    pNodoPilaArbol anterior = tope;
    while (anterior->siguiente->siguiente != NULL) {
        anterior = anterior->siguiente;
    }
    pNodoPilaArbol temp = anterior->siguiente;
    pNodoArbol nodo = temp->nodoArbol;
    anterior->siguiente = NULL;
    delete temp;
    return nodo;
}

pNodoArbol PilaOperandos::VerTope() {
    if (estaVacia()) {
        return NULL;
    }
    return tope->nodoArbol;
}

class PilaRecorrido {
private:
    pNodoPilaArbol tope;

public:
    PilaRecorrido() {
        tope = NULL;
    }

    bool estaVacia() {
        return tope == NULL;
    }

    void Push(pNodoArbol nodo);
    pNodoArbol Pop();
    pNodoArbol VerTope();
};

void PilaRecorrido::Push(pNodoArbol nodo) {
    pNodoPilaArbol nuevo = new NodoPilaArbol(nodo);

    if (estaVacia()) {
        tope = nuevo;
    }
    else {
        nuevo->siguiente = tope;
        tope = nuevo;
    }
}

pNodoArbol PilaRecorrido::Pop() {
    if (estaVacia()) {
        return NULL;
    }
    pNodoPilaArbol temp = tope;
    pNodoArbol nodo = temp->nodoArbol;
    tope = tope->siguiente;
    delete temp;
    return nodo;
}
pNodoArbol PilaRecorrido::VerTope() {
    if (estaVacia()) {
        return NULL;
    }

    return tope->nodoArbol;
}

class Arbol {
private:
    pNodoArbol raiz;
public:
    Arbol() {
		raiz = NULL;
    }
	pNodoArbol ObtenerRaiz() {
		return raiz;
	}
	void AsignarRaiz(pNodoArbol pRaiz) {
		raiz = pRaiz;
	}
    pNodoArbol CrearNodo(string valor) {
        return new NodoArbol(valor);
    }
    bool EsOperador(string valor);
    int PrioridadDentro(string operador);
    int PrioridadFuera(string operador);
    void AplicarOperador(PilaOperadores& operadores,PilaOperandos& operandos);
    void MostrarInordenIterativo();
    void MostrarPreorden();
    void MostrarPreordenRecursivo(pNodoArbol nodo);
    void MostrarPostordenIterativo();
    double EvaluarRecursivo(pNodoArbol nodo);
    double Evaluar();
    void GraficarArbol(pNodoArbol nodo, int espacio);
    void MostrarArbol();
};

bool Arbol::EsOperador(string valor) {
    return valor == "+" ||
        valor == "-" ||
        valor == "*" ||
        valor == "/" ||
        valor == "^";
}

int Arbol::PrioridadDentro(string operador) {
    if (operador == "^") {
        return 3;
    }
    if (operador == "*" || operador == "/") {
        return 2;
    }
    if (operador == "+" || operador == "-") {
        return 1;
    }
    if (operador == "(") {
        return 0;
    }
    return 0;
}

int Arbol::PrioridadFuera(string operador) {
    if (operador == "^") {
        return 4;
    }
    if (operador == "*" || operador == "/") {
        return 2;
    }
    if (operador == "+" || operador == "-") {
        return 1;
    }
    if (operador == "(") {
        return 5;
    }
    return 0;
}

void Arbol::AplicarOperador(PilaOperadores& operadores, PilaOperandos& operandos) {
    pNodoArbol derecho = operandos.Pop();
    pNodoArbol izquierdo = operandos.Pop();
    pNodoArbol operador = operadores.Pop();
    if (derecho == NULL || izquierdo == NULL || operador == NULL) {
        return;
    }
    operador->izquierdo = izquierdo;
    operador->derecho = derecho;
    operandos.Push(operador);
}

void Arbol::MostrarInordenIterativo() {
    PilaRecorrido pila;
    pNodoArbol actual = raiz;
    while (actual != NULL || !pila.estaVacia()) {
        while (actual != NULL) {
            pila.Push(actual);
            actual = actual->izquierdo;
        }
        actual = pila.Pop();
        cout << actual->valor << " ";
        actual = actual->derecho;
    }
    cout << endl;
}

void Arbol::MostrarPreordenRecursivo(pNodoArbol nodo) {
    if (nodo == NULL) {
        return;
    }
    cout << nodo->valor << " ";
    MostrarPreordenRecursivo(nodo->izquierdo);
    MostrarPreordenRecursivo(nodo->derecho);
}

void Arbol::MostrarPreorden() {
    MostrarPreordenRecursivo(raiz);
    cout << endl;
}

void Arbol::MostrarPostordenIterativo() {
    if (raiz == NULL) {
        return;
    }
    PilaRecorrido pila1;
    PilaRecorrido pila2;
    pila1.Push(raiz);
    while (!pila1.estaVacia()) {
        pNodoArbol actual = pila1.Pop();
        pila2.Push(actual);
        if (actual->izquierdo != NULL) {
            pila1.Push(actual->izquierdo);
        }
        if (actual->derecho != NULL) {
            pila1.Push(actual->derecho);
        }
    }
    while (!pila2.estaVacia()) {
        cout << pila2.Pop()->valor << " ";
    }
    cout << endl;
}

double Arbol::EvaluarRecursivo(pNodoArbol nodo) {
    if (nodo == NULL) {
        return 0;
    }
    if (!EsOperador(nodo->valor)) {
        return atof(nodo->valor.c_str());
    }
    double izquierdo = EvaluarRecursivo(nodo->izquierdo);
    double derecho = EvaluarRecursivo(nodo->derecho);
    if (nodo->valor == "+") {
        return izquierdo + derecho;
    }
    if (nodo->valor == "-") {
        return izquierdo - derecho;
    }
    if (nodo->valor == "*") {
        return izquierdo * derecho;
    }
    if (nodo->valor == "/") {
        if (derecho == 0) {
            cout << "Error: division entre cero" << endl;
            return 0;
        }
        return izquierdo / derecho;
    }
    if (nodo->valor == "^") {
        double resultado = 1;
        for (int i = 0; i < derecho; i++) {
            resultado = resultado * izquierdo;
        }
        return resultado;
    }
    return 0;
}

double Arbol::Evaluar() {
    return EvaluarRecursivo(raiz);
}

void Arbol::GraficarArbol(pNodoArbol nodo, int espacio) {
    if (nodo == NULL) {
        return;
    }
    espacio += 5;
    GraficarArbol(nodo->derecho, espacio);
    cout << endl;
    for (int i = 5; i < espacio; i++) {
        cout << " ";
    }
    cout << nodo->valor << endl;
    GraficarArbol(nodo->izquierdo, espacio);
}

void Arbol::MostrarArbol() {
    GraficarArbol(raiz, 0);
}

void ProcesarExpresion(pnodo expresion, Arbol& arbol, ofstream& archivoComparaciones) {
    PilaOperadores operadores;
    PilaOperandos operandos;
    pnodo actual = expresion;
    while (actual != NULL) {
        string valor = actual->ObtenerValor();
        // Si es un numero, se coloca en la pila de operandos
        if (!arbol.EsOperador(valor) && valor != "(" && valor != ")") {
            pNodoArbol nuevo = arbol.CrearNodo(valor);
            operandos.Push(nuevo);
        }
        // Si es un parentesis de apertura
        else if (valor == "(") {
            pNodoArbol nuevo = arbol.CrearNodo(valor);
            operadores.Push(nuevo);
        }
        // Si es un parentesis de cierre
        else if (valor == ")") {
            while (!operadores.estaVacia() &&
                    operadores.VerTope()->ObtenerValor() != "(") {
                archivoComparaciones << "Comparacion: "
                                        << operadores.VerTope()->ObtenerValor()
                                        << " con )" << endl;
                arbol.AplicarOperador(operadores, operandos);
            }
            if (!operadores.estaVacia() &&
                operadores.VerTope()->ObtenerValor() == "(") {
                operadores.Pop();
            }
        }
        // Si es un operador
        else {
            pNodoArbol nuevo = arbol.CrearNodo(valor);
            while (!operadores.estaVacia() &&
                    operadores.VerTope()->ObtenerValor() != "(" &&
                    arbol.PrioridadDentro(operadores.VerTope()->ObtenerValor())
                    >= arbol.PrioridadFuera(valor)) {
                    archivoComparaciones
                        << "Comparar "
                        << valor
                        << " con "
                        << operadores.VerTope()->ObtenerValor()
                        << endl;
                    archivoComparaciones
                        << "Se desapila "
                        << operadores.VerTope()->ObtenerValor()
                        << endl;
                    arbol.AplicarOperador(operadores, operandos);
            }
            operadores.Push(nuevo);
        }
        actual = actual->ObtenerSiguiente();
    }
    // Aplicar los operadores que quedaron en la pila
    while (!operadores.estaVacia()) {
        arbol.AplicarOperador(operadores, operandos);
    }
    if (!operandos.estaVacia()) {
        arbol.AsignarRaiz(operandos.Pop());
    }
}

pnodo LeerArchivo(string rutaArchivo) { // Lee un archivo de texto y convierte su contenido en una lista enlazada simple
    ifstream archivo(rutaArchivo.c_str()); // abre el archivo para lectura. c_str concierte string en un arreglo de caracteres
    if (!archivo.is_open()) { // is_open revisa si se abrio correctamente
        cout << "Error al abrir el archivo: " << rutaArchivo << endl;
        return NULL; //si no se pudo abrir
    }
    lista* listaExpresion = new lista(); // Se crea dinamicamente en memoria para no perder los datos
	char caracter; // para almacenar cada caracter leido del archivo
    string numero = "";

    while (archivo.get(caracter)) {
        if (EsEspacio(caracter)) {
            continue;
        }
        if (EsDigito(caracter)) {
            numero = numero + caracter; // construye el numero completo
        }
        else if (EsOperador(caracter)) {
            if (numero != "") {
                listaExpresion->InsertarFinal(numero);
                numero = "";
            }
            string simbolo(1, caracter);
            listaExpresion->InsertarFinal(simbolo);
        }
    }
    if (numero != "") {
        listaExpresion->InsertarFinal(numero);
    }
    archivo.close();
    return listaExpresion->ObtenerPrimero(); // Retorna el puntero al inicio de la lista
}

void MostrarExpresionOriginal(pnodo expresion) {
    pnodo actual = expresion;
    while (actual != NULL) {
        cout << actual->ObtenerValor();
        actual = actual->ObtenerSiguiente();
    }
    cout << endl;
}

int main() {
    Bicola archivos;
    string nombresArchivos[5] = {
        "Arch1.txt",
        "Arch2.txt",
        "Arch3.txt",
        "Arch4.txt",
        "Arch5.txt"
    };
    ofstream archivoComparaciones("Comparaciones.txt");
    if (!archivoComparaciones.is_open()) {
        cout << "No se pudo crear el archivo de comparaciones." << endl;
        return 1;
    }
    ofstream archivoEvaluacion("Evaluacion.txt");
    if (!archivoEvaluacion.is_open()) {
        cout << "No se pudo crear el archivo de evaluacion." << endl;
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        pnodo expresion = LeerArchivo(nombresArchivos[i]);
        if (expresion != NULL) {
            archivos.insertarFinal(expresion);
            Arbol arbol;
            archivoComparaciones << "Archivo: "
                                    << nombresArchivos[i] << endl;
            ProcesarExpresion(
                expresion,
                arbol,
                archivoComparaciones
            );
            archivoEvaluacion
                << nombresArchivos[i]
                << " = "
                << arbol.Evaluar()
                << endl;
            cout << endl;
            cout << "Expresion original: ";
            MostrarExpresionOriginal(expresion);
            cout << "Recorrido inorder iterativo: ";
            arbol.MostrarInordenIterativo();
            cout << "Recorrido preorden recursivo: ";
            arbol.MostrarPreorden();
            cout << "Recorrido postorden iterativo: ";
            arbol.MostrarPostordenIterativo();
            cout << "Resultado: "<< arbol.Evaluar()<< endl;
            cout << "Arbol:" << endl;
            arbol.MostrarArbol();
        }
    }
    archivoComparaciones.close();
    archivoEvaluacion.close();
    cout << endl;
    cout << "Archivos cargados en la bicola:" << endl;
    archivos.mostrar();
    return 0;
}