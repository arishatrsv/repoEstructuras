// Creado por: Hilary Aguilar y Arina Tarasova
// Tarea Corta #2 - Estructuras de Datos

#include <iostream>  // entrada y salida de datos
#include <fstream>   // manejo y lectura de archivos de texto
#include <string>    // manejo de cadenas de texto
#include <windows.h> // para dibujar el arbol en la consola

using namespace std;

#define TAM 5 // Tamano estatico para la Bicola

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

class nodo;
class lista;

// Alias que simplifica la escritura de punteros a objetos de tipo nodo.
// Equivale a: pnodo es un sinónimo de nodo*.
typedef nodo* pnodo;

// Indica si el carácter representa un dígito decimal.
bool EsDigito(char c) {
    return (c >= '0' && c <= '9');
}

// Detecta espacios, tabulaciones y saltos de línea leídos del archivo.
bool EsEspacio(char c) { // Comprueba manualmente espacios en blanco o saltos de linea
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

// Determina si el carácter pertenece a los operadores o paréntesis de la expresión.
bool EsOperador(char c) { // Valida si un caracter corresponde a un operador matematico
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
} // || es el operador lógico OR; devuelve true cuando se cumple al menos una condición.

// Cada nodo almacena una parte de la expresión y enlaza con el siguiente nodo.
class nodo {
public:
    // Crea un nodo con su valor y deja el enlace en NULL.
    nodo(string pvalor) {
        valor = pvalor;
        siguiente = NULL; // El nodo no tiene sucesor.
    }

    // Crea un nodo y conecta directamente con otro nodo indicado.
    nodo(string pvalor, nodo* sigNodo) {
        valor = pvalor;
        siguiente = sigNodo; // Apunta al nodo recibido como argumento.
    }

    // Devuelve el contenido almacenado en el nodo.
    string ObtenerValor() {
        return valor;
    }

    // Devuelve el puntero al nodo siguiente, o NULL si no existe.
    pnodo ObtenerSiguiente() {
        return siguiente;
    }

private:
    string valor;     // Token de la expresión: número, operador o paréntesis.
    nodo* siguiente;  // Dirección del siguiente nodo de la lista.

    // Permite que lista y Bicola accedan a los miembros privados del nodo.
    friend class lista;
    friend class Bicola;
};

// Lista enlazada simple que guarda los tokens de una expresión.
class lista {
public:
    // Crea una lista vacía inicializando el primer nodo en NULL.
    lista() {
        primero = NULL;
    }

    // Indica si la lista no contiene ningún nodo.
    bool ListaVacia() { return primero == NULL; }

    // Inserta un valor al inicio o al final de la lista.
    void InsertarInicio(string valor);
    void InsertarFinal(string valor);

    // Muestra todos los valores de la lista desde el primero.
    void Mostrar();

    // Devuelve el puntero al primer nodo de la lista.
    pnodo ObtenerPrimero() { return primero; }

private:
    pnodo primero; // Primer elemento de la lista; NULL cuando está vacía.
};

// Inserta un nuevo nodo como primer elemento.
void lista::InsertarInicio(string valor) {
    if (ListaVacia()) {
        primero = new nodo(valor); // La lista queda con un único nodo.
    }
    else {
        // El nuevo nodo apunta al anterior primero y se convierte en el primero.
        primero = new nodo(valor, primero);
    }
}

// Inserta un valor al final recorriendo la lista hasta el último nodo.
void lista::InsertarFinal(string valor) {
    if (ListaVacia())
        primero = new nodo(valor);
    else {
        pnodo nodoActual = primero; // Comienza en el primer elemento.
        while (nodoActual->siguiente != NULL) // Avanza hasta el último nodo.
            nodoActual = nodoActual->siguiente;
        nodoActual->siguiente = new nodo(valor); // Enlaza el nuevo nodo al final.
    }
}

// Imprime todos los valores de la lista en orden de enlace.
void lista::Mostrar() {
    pnodo nodoActual; // Puntero auxiliar usado para recorrer los nodos.
    if (primero == NULL)
        cout << "No hay elementos para mostrar" << endl;
    else {
        nodoActual = primero; // Comienza desde el primer nodo.
        while (nodoActual) { // Continúa mientras exista un nodo válido.
            cout << nodoActual->valor << " ";
            nodoActual = nodoActual->siguiente; // Avanza al siguiente nodo.
        }
        cout << endl;
    }
}

// Bicola circular de tamaño fijo que almacena punteros a listas de expresión.
class Bicola {
private:
    pnodo datos[TAM]; // Posiciones disponibles para almacenar nodos de inicio de lista.
    int frente;       // Índice del elemento que se elimina por el frente.
    int fondo;        // Índice del elemento que se elimina por el final.
    int cantidad;     // Número de elementos almacenados actualmente.

public:
    // Inicializa una bicola vacía y las posiciones del arreglo en NULL.
    Bicola() {
        frente = 0;
        fondo = -1; // Indica que no hay elementos en la bicola.
        cantidad = 0;
        for (int i = 0; i < TAM; i++) { // Recorre todas las posiciones del arreglo.
            datos[i] = NULL; // Cada posición comienza vacía.
        }
    }

    // Comprueba si la bicola contiene cero elementos.
    bool estaVacia() {
        return cantidad == 0;
    }

    // Comprueba si el número de elementos alcanza el tamaño máximo.
    bool estaLlena() {
        return cantidad == TAM;
    }

    // Inserta un elemento por el frente, desplazando el índice circularmente.
    void insertarFrente(pnodo valor) {
        if (estaLlena()) {
            cout << "Bicola llena. No se puede insertar al frente.\n";
            return; // No modifica la bicola cuando está llena.
        }
        if (estaVacia()) { // La primera inserción ocupa la posición inicial.
            frente = 0;
            fondo = 0;
        }
        else {
            // Mueve el frente hacia atrás empleando aritmética modular.
            frente = (frente - 1 + TAM) % TAM;
        }
        datos[frente] = valor; // Guarda el nodo en la nueva posición del frente.
        cantidad++;
    }

    // Inserta un elemento por el final, desplazando el índice circularmente.
    void insertarFinal(pnodo valor) {
        if (estaLlena()) {
            cout << "Bicola llena. No se puede insertar al final.\n";
            return;
        }
        if (estaVacia()) { // La primera inserción ocupa la posición inicial.
            frente = 0;
            fondo = 0;
        }
        else {
            // Mueve el fondo hacia adelante manteniendo el orden circular.
            fondo = (fondo + 1) % TAM;
        }
        datos[fondo] = valor; // Guarda el nodo en la nueva posición del fondo.
        cantidad++;
    }

    // Elimina y devuelve el nodo almacenado en el frente de la bicola.
    pnodo eliminarFrente() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo lista = datos[frente]; // Guarda temporalmente el nodo eliminado.
        datos[frente] = NULL; // Libera la posición para futuras inserciones.
        cantidad--; // Disminuye la cantidad de elementos almacenados.
        if (cantidad == 0) { // Si se removió el último elemento, se reinician índices.
            frente = 0;
            fondo = -1; // La bicola queda vacía.
        }
        else {
            // El frente avanza una posición circularmente.
            frente = (frente + 1) % TAM;
        }
        return lista; // Retorna el nodo eliminado para que pueda procesarse.
    }

    // Elimina y devuelve el nodo almacenado en el final de la bicola.
    pnodo eliminarFinal() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo valor = datos[fondo]; // Guarda temporalmente el nodo eliminado.
        datos[fondo] = NULL;
        cantidad--;
        if (cantidad == 0) { // Si se removió el último elemento, se reinician índices.
            frente = 0;
            fondo = -1; // La bicola queda vacía.
        }
        else {
            // El fondo retrocede en el arreglo circular.
            fondo = (fondo - 1 + TAM) % TAM;
        }
        return valor; // Retorna el nodo eliminado.
    }

    // Devuelve el nodo ubicado en una posición del arreglo, si es válida.
    pnodo obtenerPosicion(int pos) {
        if (pos >= 0 && pos < TAM) { // Verifica que el índice esté dentro del rango.
            return datos[pos]; // Retorna el nodo de esa posición.
        }
        return NULL;
    }

    // Muestra cada lista almacenada, recorriendo el arreglo desde el frente.
    void mostrar() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return;
        }
        else {
            cout << "Contenido de la bicola:\n";
            int i = frente; // Comienza desde la posición del frente.
            for (int pos = 0; pos < cantidad; pos++) { // Recorre solo los elementos existentes.
                cout << "Posicion [" << i << "]: ";
                pnodo actual = datos[i]; // Obtiene la lista almacenada en esa posición.
                while (actual != NULL) { // Recorre todos los nodos de la lista.
                    cout << actual->valor << " "; // Muestra el valor del nodo actual.
                    actual = actual->siguiente;
                }
                cout << endl;
                i = (i + 1) % TAM; // Avanza circularmente a la siguiente posición.
            }
        }
    }
};

// Declaración adelantada del nodo que forma el árbol de expresión.
class NodoArbol;
// Alias para apuntar con comodidad a un nodo del árbol.
typedef NodoArbol* pNodoArbol;

// Representa un número u operador de la expresión dentro del árbol.
class NodoArbol {
private:
    string valor;        // Texto almacenado: número, operador o paréntesis.
    string resultado;    // Resultado parcial calculado para este operador.
    pNodoArbol izquierdo; // Subárbol izquierdo.
    pNodoArbol derecho;  // Subárbol derecho.

public:
    // Crea un nodo con el valor indicado y sin hijos.
    NodoArbol(string pValor) {
        valor = pValor;
        resultado = "";
        izquierdo = NULL;
        derecho = NULL;
    }

    // Devuelve el contenido del nodo.
    string ObtenerValor() {
        return valor;
    }

    // Devuelve el resultado calculado para este operador.
    string ObtenerResultado() {
        return resultado;
    }

    // Permite que Arbol modifique los datos privados del nodo.
    friend class Arbol;
};

// Cada elemento de una pila contiene un puntero a un nodo del árbol.
class NodoPilaArbol;
typedef NodoPilaArbol* pNodoPilaArbol;
class PilaRecorrido;

class NodoPilaArbol {
private:
    pNodoArbol nodoArbol;   // Nodo del árbol que se almacena en la pila.
    pNodoPilaArbol siguiente; // Siguiente elemento de la pila enlazada.

public:
    // Crea un elemento de pila con el nodo recibido.
    NodoPilaArbol(pNodoArbol pNodo) {
        nodoArbol = pNodo;
        siguiente = NULL;
    }

    // Permite que las pilas accedan directamente a sus miembros privados.
    friend class PilaOperadores;
    friend class PilaOperandos;
    friend class PilaRecorrido;
};

// Pila de operadores usada durante la construcción del árbol.
class PilaOperadores {
private:
    pNodoPilaArbol tope; // Último operador agregado; la pila se comporta como una lista enlazada.

public:
    // Inicializa la pila como vacía.
    PilaOperadores() { tope = NULL; }

    // Determina si no hay operadores almacenados.
    bool estaVacia() {
        return tope == NULL;
    }

    // Inserta un operador en la parte inferior de la pila.
    void Push(pNodoArbol nodo);

    // Elimina y devuelve el último operador insertado.
    pNodoArbol Pop();

    // Consulta el último operador sin eliminarlo.
    pNodoArbol VerTope();
};

// Agrega un operador al final de la pila, de modo que el último agregado quede acceso no por el puntero tope, sino por el recorrido hasta el último nodo.
void PilaOperadores::Push(pNodoArbol nodo) {
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

// Elimina el último elemento de la pila y devuelve el nodo del árbol que contenía.
pNodoArbol PilaOperadores::Pop() {
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

// Consulta el último operador almacenado sin eliminarlo.
pNodoArbol PilaOperadores::VerTope() {
    if (estaVacia()) {
        return NULL;
    }
    pNodoPilaArbol actual = tope;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    return actual->nodoArbol;
}

// Pila de operandos usada para almacenar los subárboles ya identificados.
class PilaOperandos {
private:
    pNodoPilaArbol tope; // Último operando agregado.

public:
    // Inicializa la pila como vacía.
    PilaOperandos() {
        tope = NULL;
    }

    // Determina si no hay operandos almacenados.
    bool estaVacia() {
        return tope == NULL;
    }

    // Inserta un operando en la parte inferior de la pila.
    void Push(pNodoArbol nodo);

    // Elimina y devuelve el último operando insertado.
    pNodoArbol Pop();

    // Consulta el último operando sin eliminarlo.
    pNodoArbol VerTope();
};

// Agrega un operando al final de la pila, utilizando el mismo esquema enlazado.
void PilaOperandos::Push(pNodoArbol nodo) {
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

// Elimina el último operando y devuelve el subárbol asociado.
pNodoArbol PilaOperandos::Pop() {
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

// Consulta el último operando sin eliminarlo.
pNodoArbol PilaOperandos::VerTope() {
    if (estaVacia()) {
        return NULL;
    }
    pNodoPilaArbol actual = tope;
    while (actual->siguiente != NULL) {
        actual = actual->siguiente;
    }
    return actual->nodoArbol;
}

// Pila de recorrido que permite aplicar algoritmos iterativos de recorrido.
class PilaRecorrido {
private:
    pNodoPilaArbol tope; // Nodo más recientemente agregado.

public:
    // Inicializa la pila vacía.
    PilaRecorrido() {
        tope = NULL;
    }

    // Comprueba si la pila no contiene nodos.
    bool estaVacia() {
        return tope == NULL;
    }

    // Inserta, elimina y consulta un nodo del árbol.
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

// Árbol binario que representa la expresión matemática.
class Arbol {
private:
    pNodoArbol raiz; // Nodo raíz del árbol, NULL cuando no existe expresión.

public:
    // Crea un árbol vacío.
    Arbol() {
        raiz = NULL;
    }

    // Devuelve la raíz actual del árbol.
    pNodoArbol ObtenerRaiz() {
        return raiz;
    }

    // Establece una raíz determinada para el árbol.
    void AsignarRaiz(pNodoArbol pRaiz) {
        raiz = pRaiz;
    }

    // Crea y devuelve un nuevo nodo con el valor indicado.
    pNodoArbol CrearNodo(string valor) {
        return new NodoArbol(valor);
    }

    // Asigna un nodo como hijo izquierdo de otro nodo.
    void AsignarIzquierdo(pNodoArbol nodo, pNodoArbol izquierdo) {
        if (nodo != NULL) {
            nodo->izquierdo = izquierdo;
        }
    }

    // Asigna un nodo como hijo derecho de otro nodo.
    void AsignarDerecho(pNodoArbol nodo, pNodoArbol derecho) {
        if (nodo != NULL) {
            nodo->derecho = derecho;
        }
    }

    // Comprueba y convierte números entre texto y valores numéricos.
    bool EsOperador(string valor);
    double ConvertirNumero(string numero);

    // Define la precedencia de cada operador al evaluar una expresión.
    int PrioridadDentro(string operador);
    int PrioridadFuera(string operador);

    // Combina dos operandos usando el operador de la cima de la pila.
    void AplicarOperador(PilaOperadores& operadores, PilaOperandos& operandos);

    // Muestra el árbol usando recorridos iterativos.
    void MostrarInordenIterativo();
    void MostrarPreorden();
    void MostrarPreordenRecursivo(pNodoArbol nodo);
    void MostrarPostordenIterativo();

    // Evalúa el árbol mediante una llamada recursiva sobre sus hijos.
    double EvaluarRecursivo(pNodoArbol nodo, PilaOperandos& operandos, ofstream& archivoEvaluacion);
    double Evaluar(ofstream& archivoEvaluacion);

    // Calcula la altura del árbol y prepara su representación gráfica.
    int Altura(pNodoArbol nodo);
    void ImprimirNivel(pNodoArbol nodo, int posicion, int fila, int separacion);
    void GraficarArbol();
    void MostrarArbol();
};

// Determina si una cadena representa uno de los operadores permitidos.
bool Arbol::EsOperador(string valor) {
    return valor == "+" ||
        valor == "-" ||
        valor == "*" ||
        valor == "/" ||
        valor == "^";
}

// Convierte una secuencia de dígitos en un número decimal.
double Arbol::ConvertirNumero(string numero) {
    double resultado = 0;
    for (int i = 0; i < numero.length(); i++) {
        resultado = resultado * 10 + (numero[i] - '0');
    }
    return resultado;
}

// Define la prioridad de un operador cuando está dentro de la pila.
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

// Define la prioridad de un operador cuando recién llega desde la expresión.
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

// Construye un subárbol con el operador superior y sus dos operandos.
void Arbol::AplicarOperador(PilaOperadores& operadores, PilaOperandos& operandos) {
    if (operadores.estaVacia() || operandos.estaVacia()) {
        return;
    }
    pNodoArbol derecho = operandos.Pop();
    if (operandos.estaVacia()) {
        operandos.Push(derecho);
        return;
    }
    pNodoArbol izquierdo = operandos.Pop();
    pNodoArbol operador = operadores.Pop();
    if (derecho == NULL || izquierdo == NULL || operador == NULL) {
        return;
    }
    operador->izquierdo = izquierdo;
    operador->derecho = derecho;
    operandos.Push(operador);
}

// Recorre el árbol en orden: izquierda, raíz y derecha, usando una pila.
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

// Muestra el valor de cada nodo antes de sus hijos de forma recursiva.
void Arbol::MostrarPreordenRecursivo(pNodoArbol nodo) {
    if (nodo == NULL) {
        return;
    }
    cout << nodo->valor << " ";
    MostrarPreordenRecursivo(nodo->izquierdo);
    MostrarPreordenRecursivo(nodo->derecho);
}

// Inicia la impresión del árbol en preorden desde la raíz.
void Arbol::MostrarPreorden() {
    MostrarPreordenRecursivo(raiz);
    cout << endl;
}

// Recorre el árbol en postorden mediante dos pilas: registra primero y muestra después.
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

// Evalúa de forma recursiva el subárbol y guarda el cálculo del operador.
double Arbol::EvaluarRecursivo(pNodoArbol nodo,
    PilaOperandos& operandos, ofstream& archivoEvaluacion) {
    if (nodo == NULL) {
        return 0;
    }
    // Si el nodo contiene un número, se convierte y se guarda como operando.
    if (!EsOperador(nodo->valor)) {
        operandos.Push(nodo);
        return ConvertirNumero(nodo->valor);
    }

    // Se evalúan primero los subárboles izquierdo y derecho.
    double izquierdo = EvaluarRecursivo(nodo->izquierdo, operandos, archivoEvaluacion);
    double derecho = EvaluarRecursivo(nodo->derecho, operandos, archivoEvaluacion);

    // Se registran los valores que salen de la pila durante la evaluación.
    pNodoArbol nodoDerecho = operandos.Pop();
    if (nodoDerecho != NULL) {
        if (nodoDerecho->resultado != "") {
            archivoEvaluacion
                << "Desapila: "
                << nodoDerecho->resultado
                << endl;
        }
        else {
            archivoEvaluacion
                << "Desapila: "
                << nodoDerecho->valor
                << endl;
        }
    }

    pNodoArbol nodoIzquierdo = operandos.Pop();
    if (nodoIzquierdo != NULL) {
        if (nodoIzquierdo->resultado != "") {
            archivoEvaluacion
                << "Desapila: "
                << nodoIzquierdo->resultado
                << endl;
        }
        else {
            archivoEvaluacion
                << "Desapila: "
                << nodoIzquierdo->valor
                << endl;
        }
    }

    // Aplica la operación correspondiente a la raíz del subárbol.
    double resultado = 0;
    if (nodo->valor == "+") {
        resultado = izquierdo + derecho;
    }
    else if (nodo->valor == "-") {
        resultado = izquierdo - derecho;
    }
    else if (nodo->valor == "*") {
        resultado = izquierdo * derecho;
    }
    else if (nodo->valor == "/") {
        if (derecho == 0) {
            cout << "Error: division entre cero" << endl;
            resultado = 0;
        }
        else {
            resultado = izquierdo / derecho;
        }
    }
    else if (nodo->valor == "^") {
        resultado = 1;
        for (int i = 0; i < derecho; i++) {
            resultado = resultado * izquierdo;
        }
    }

    // El resultado se guarda en el nodo operator y se convierte nuevamente en operando.
    nodo->resultado = to_string(resultado);
    operandos.Push(nodo);
    return resultado;
}

// Inicializa una pila de operandos y evalúa la raíz del árbol.
double Arbol::Evaluar(ofstream& archivoEvaluacion) {
    PilaOperandos operandos;
    return EvaluarRecursivo(
        raiz, operandos, archivoEvaluacion);
}

// Calcula la altura de un subárbol mediante llamadas recursivas a sus hijos.
int Arbol::Altura(pNodoArbol nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int alturaIzquierda = Altura(nodo->izquierdo);
    int alturaDerecha = Altura(nodo->derecho);
    if (alturaIzquierda > alturaDerecha) {
        return alturaIzquierda + 1;
    }
    return alturaDerecha + 1;
}

// Coloca el valor de un nodo en la posición indicada y dibuja las conexiones.
void Arbol::ImprimirNivel(pNodoArbol nodo, int posicion, int fila, int separacion) {
    if (nodo == NULL) {
        return;
    }
    gotoxy(posicion, fila);
    cout << nodo->valor;

    // Conecta el valor con el hijo izquierdo mediante una diagonal.
    if (nodo->izquierdo != NULL) {
        gotoxy(posicion - separacion / 2, fila + 1);
        cout << "/";
    }

    // Conecta el valor con el hijo derecho mediante una diagonal.
    if (nodo->derecho != NULL) {
        gotoxy(posicion + separacion / 2, fila + 1);
        cout << "\\";
    }

    // El recorrido recursivo dibuja cada nivel del árbol.
    ImprimirNivel(nodo->izquierdo, posicion - separacion, fila + 2, separacion / 2);
    ImprimirNivel(nodo->derecho, posicion + separacion, fila + 2, separacion / 2);
}

// Calcula la separación necesaria y mueve el cursor para dibujar el árbol.
void Arbol::GraficarArbol() {
    if (raiz == NULL) {
        return;
    }
    int altura = Altura(raiz);
    int separacion = 1;
    for (int i = 1; i < altura; i++) {
        separacion = separacion * 2;
    }
    int posicionInicial = separacion * 2;

    // Reserva espacio en la consola antes de dibujar el árbol.
    for (int i = 0; i < altura * 2; i++) {
        cout << endl;
    }
    CONSOLE_SCREEN_BUFFER_INFO informacion;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &informacion);
    int filaInicial = informacion.dwCursorPosition.Y - altura * 2;
    ImprimirNivel(raiz, posicionInicial, filaInicial, separacion);

    // Mueve el cursor debajo del árbol para conservar la presentación.
    gotoxy(0, filaInicial + altura * 2);
}

// Presenta el árbol usando su representación gráfica en consola.
void Arbol::MostrarArbol() {
    GraficarArbol();
}

void ProcesarExpresion(pnodo expresion, Arbol& arbol, ofstream& archivoComparaciones) {
    PilaOperadores operadores;
    PilaOperandos operandos;
    pnodo actual = expresion;

    while (actual != NULL) {
        string valor = actual->ObtenerValor();
        // Si es un numero, se coloca en la pila de operandos
        if (EsDigito(valor[0])) {
            pNodoArbol nuevo = arbol.CrearNodo(valor);
            operandos.Push(nuevo);
        }
        // Si es un parentesis de apertura
    else if (valor == "(") {
        pNodoArbol nuevo = arbol.CrearNodo(valor);
        archivoComparaciones
            << "Lee ("
            << endl;
        archivoComparaciones
            << "Push ("
            << endl;
        operadores.Push(nuevo);
    }
            // Si es un parentesis de cierre
    else if (valor == ")") {
        archivoComparaciones
            << "Lee )"
            << endl;
        while (!operadores.estaVacia() &&
            operadores.VerTope()->ObtenerValor() != "(") {
            archivoComparaciones
                << "Pop "
                << operadores.VerTope()->ObtenerValor()
                << " por )"
                << endl;
            arbol.AplicarOperador(
                operadores,
                operandos);
        }
        if (!operadores.estaVacia() &&
            operadores.VerTope()->ObtenerValor() == "(") {
            operadores.Pop();
            archivoComparaciones
                << "Pop ("
                << endl;
        }
    }
        // Si es un operador
        else if (arbol.EsOperador(valor)) {
            pNodoArbol nuevo = arbol.CrearNodo(valor);
            archivoComparaciones
                << "Lee "
                << valor
                << endl;

            // Si la pila de operadores esta vacia
            if (operadores.estaVacia()) {
                archivoComparaciones
                    << "Pila vacia -> Push "
                    << valor
                    << endl;
            }
            else {
                // Compara el operador actual con los operadores de la pila
                while (!operadores.estaVacia() &&
                    operadores.VerTope()->ObtenerValor() != "(") {
                    string operadorPila =
                        operadores.VerTope()->ObtenerValor();
                    int prioridadPila =
                        arbol.PrioridadDentro(operadorPila);
                    int prioridadActual =
                        arbol.PrioridadFuera(valor);
                    archivoComparaciones
                        << "Comparar "
                        << valor
                        << " con "
                        << operadorPila
                        << endl;
                    // El operador actual tiene mayor prioridad
                    if (prioridadActual > prioridadPila) {
                        archivoComparaciones
                            << "    "
                            << prioridadActual
                            << " > "
                            << prioridadPila
                            << " -> Push "
                            << valor
                            << endl;
                        break;
                    }

                    // El operador de la pila tiene mayor prioridad
                    else if (prioridadActual < prioridadPila) {
                        archivoComparaciones
                            << "    "
                            << prioridadActual
                            << " < "
                            << prioridadPila
                            << " -> Pop "
                            << operadorPila
                            << endl;
                        arbol.AplicarOperador(
                            operadores,
                            operandos);
                    }

                    // Tienen la misma prioridad
                    else {
                        archivoComparaciones
                            << "    "
                            << prioridadActual
                            << " = "
                            << prioridadPila
                            << " -> Pop "
                            << operadorPila
                            << endl;
                        arbol.AplicarOperador(
                            operadores,
                            operandos);
                    }
                }
            }
            // Se coloca el operador actual en la pila
            operadores.Push(nuevo);
        }
        actual = actual->ObtenerSiguiente();
    }
    // Aplicar los operadores que quedaron en la pila
    while (!operadores.estaVacia()) {
        arbol.AplicarOperador(
            operadores,
            operandos);
    }
    // La raiz es el ultimo que queda en la pila de operandos
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
			if (numero != "") { // Si hay un numero acumulado, se agrega a la lista antes de agregar el operador
                listaExpresion->InsertarFinal(numero);
                numero = "";
            }
            string simbolo(1, caracter);
            listaExpresion->InsertarFinal(simbolo);
        }
    }
    if (numero != "") { //Agrega el ultimo numero del archivo
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
    //Lee los cinco archivos
    for (int i = 0; i < 5; i++) {
        pnodo expresion = LeerArchivo(nombresArchivos[i]);
        if (expresion != NULL) {
            archivos.insertarFinal(expresion); //Aquí es donde cambia si se inserta al frente o al final
        }
    }
    //Mostrar la cola antes de procesar
    cout << endl;
    cout << "Archivos cargados en la bicola:"
        << endl;
    archivos.mostrar();

	//Procesa cada archivo de la bicola
    for (int i = 0; i < TAM; i++) {
		pnodo expresion = archivos.eliminarFrente(); //Aquí se cambia si se elimina del frente o del final
        if (expresion == NULL) {
            continue;
        }
        Arbol arbol;
        //Comparaciones
        archivoComparaciones
            << "--------------------------------" << endl;
        archivoComparaciones << "Archivo: " << nombresArchivos[i] << endl;
        archivoComparaciones
            << "--------------------------------" << endl;

        // Construir el árbol
        ProcesarExpresion(
            expresion,
            arbol,
            archivoComparaciones);

        //Evaluar
        archivoEvaluacion
            << "--------------------------------" << endl
            << "Archivo: "
            << nombresArchivos[i]
            << endl
            << "--------------------------------" << endl;
        double resultado = arbol.Evaluar(archivoEvaluacion);
        archivoEvaluacion << endl;

        //Mostrar resultados
        cout << endl;
        cout << "Archivo: "<< nombresArchivos[i]<< endl;
        cout << "Expresion original: ";
        MostrarExpresionOriginal(expresion);
        cout << "Recorrido inorder iterativo: ";
        arbol.MostrarInordenIterativo();
        cout << "Recorrido preorden recursivo: ";
        arbol.MostrarPreorden();
        cout << "Recorrido postorden iterativo: ";
        arbol.MostrarPostordenIterativo();
        cout << "Resultado: " << resultado << endl;
        cout << "Arbol:" << endl;
        arbol.MostrarArbol();
        cout << endl;
    }
    archivoComparaciones.close();
    archivoEvaluacion.close();
    cout << endl;
    cout << "Proceso terminado" << endl;
    archivos.mostrar();
    return 0;
}