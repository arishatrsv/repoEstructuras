// Creado por: Hilary Aguilar y Arina Tarasova
// Tarea Corta #1 - Estructuras de Datos

#include <iostream>  // entrada y salida de datos
#include <fstream>   // manejo y lectura de archivos de texto
#include <string>    // manejo de cadenas de texto

using namespace std; 

#define TAM 5 // Tamano estatico para la Bicola

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
    friend class Bicola; // permite que acceda a los miembros privados
	friend class Pila; // permite que acceda a los miembros privados
	friend lista* InfijoAPostfijo(pnodo inicioInfijo); // permite que acceda a los miembros privados
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

class Bicola {
private:
    pnodo datos[TAM]; // Guarda las referencias a las listas creadas por archivo
    int frente;
    int fondo;
    int cantidad;

public:
    Bicola() {
        frente = 0;
        fondo = -1;
        cantidad = 0;
        for (int i = 0; i < TAM; i++) {
            datos[i] = NULL;
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
            return;
        }
        else {
            frente = (frente - 1 + TAM) % TAM;
            datos[frente] = valor;
            cantidad++;
        }
    }

    void insertarFinal(pnodo valor) {
        if (estaLlena()) {
            cout << "Bicola llena. No se puede insertar al final.\n";
            return;
        }
        else {
            fondo = (fondo + 1) % TAM;
            datos[fondo] = valor;
            cantidad++;
        }
    }

    pnodo eliminarFrente() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo temp = datos[frente];
        frente = (frente + 1) % TAM;
        cantidad--;
        return temp;
    }

    pnodo eliminarFinal() {
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo temp = datos[fondo];
        fondo = (fondo - 1 + TAM) % TAM;
        cantidad--;
        return temp;
    }

    pnodo obtenerPosicion(int pos) {
        if (pos >= 0 && pos < TAM) {
            return datos[pos];
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
            int i = frente;
            for (int pos = 0; pos < cantidad; pos++) {
                cout << "Posicion [" << i << "]: ";
                pnodo actual = datos[i];
                while (actual != NULL) {
                    cout << actual->valor << " ";
                    actual = actual->siguiente;
                }
                cout << endl;
                i = (i + 1) % TAM;
            }
        }
    }
};

class Pila {
private:
    pnodo tope;

public:
    Pila() { tope = NULL; } // Constructor: la pila inicia vacia, sin nodos

    bool EstaVacia() {
        return tope == NULL; //Revisa si la pila está vacía
    }

    void Apilar(string valor){// Agrega un nuevo elemento al tope de la pila
        tope = new nodo(valor, tope); //El nuevo nodo apunta al tope actual y pasa a ser el nuevo tope
    }

	String Desapilar() { // Saca y retorna el elemento que esta en el tope
		if (EstaVacia()) {
			cout << "Pila vacia.\n";
			return "";
		}
		pnodo temp = tope; // Guarda el nodo actual del tope
		string valor = temp->valor; // Obtiene el valor del nodo antes de borrar el nodo
		tope = temp->siguiente; // El tope pasa a ser el siguiente nodo
		delete temp; // Libera la memoria del nodo eliminado
		return valor; 
	}

	String VerTope() { // Retorna el valor del tope sin eliminarlo
		if (EstaVacia()) return "";
		return tope->valor;
	}
};

bool EsDigito(char c) {
    return (c >= '0' && c <= '9');
}

bool EsEspacio(char c) { // Comprueba manualmente espacios en blanco o saltos de linea
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

bool EsOperador(char c) { // Valida si un caracter corresponde a un operador matematico
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')');
} // || es or, retorna true o false. 

int PrioridadDentroPila(string operador) { // Asigna prioridad a los operadores dentro de la pila);
    if (operador == "^") return 3;  //Exponente
    if (operador == "*" || operador == "/") return 2;//Multiplicación y división
    if (operador == "+" || operador == "-") return 1; //Suma y resta
    if (operador == "(")  return 0;// parentesis abierto, prioridad minima dentro
    return -1; // no deberia ocurrir con un operador valido
}

int PrioridadFueraPila(string operador) { // Prioridad de un operador leido desde la expresion (entrando)
    if (operador == "^") return 4;              // el exponente entrante siempre gana sobre el que esta en la pila
    if (operador == "*" || operador == "/") return 2;
    if (operador == "+" || operador == "-") return 1;
    if (operador == "(") return 5;              // parentesis abierto entrante siempre se apila
    return -1;
}

bool RevisarOperadorValor(string valor){// Revisa si el valor del nodo es un operador o parentesis
    return (valor == "+" || valor == "-" || valor == "*" ||
		    valor == "/" || valor == "^" || valor == "(" || valor == ")");
}

bool RevisarNumeroValor(string valor) {// Revisa si el valor del nodo es un numero, viendo su primer caracter
    if (valor == "") {
        return false;
    }
	return EsDigito(valor[0]);
}

pnodo LeerArchivo(string rutaArchivo) { // Lee un archivo de texto y convierte su contenido en una lista enlazada simple
    ifstream archivo(rutaArchivo.c_str()); // abre el archivo para lectura. c_str concierte string en un arreglo de caracteres
    if (!archivo.is_open()) { // is_open revisa si se abrio correctamente
        cout << "Error al abrir el archivo: " << rutaArchivo << endl;
        return NULL; //si no se pudo abrir
    }

    lista* listaExpresion = new lista(); // Se crea dinamicamente en memoria para no perder los datos
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

        if (EsEspacio(c)) { // Si es un espacio, se ignora y avanza, isspace sale de la libreria cctype
            i++;
            continue;
        }

        if (EsDigito(c)) { // Si encuentra un digito, agrupa los continuos para formar el numero, isdigit tmb esta en cctype
            string numero = "";
            while (i < n && EsDigito(expresionCompleta[i])) { 
                numero += expresionCompleta[i]; //agrega el digito al numero
                i++;
            }
            listaExpresion->InsertarFinal(numero); // Agrega el numero completo a la lista
        }else if (EsOperador(c)) { // Si es un operador, lo agrega a la lista
            string op(1, c);//convierte el caracter en string
            listaExpresion->InsertarFinal(op); // agrega el operador a la lista
            i++;
        }else {
            i++;
        }
    }
    return listaExpresion->ObtenerPrimero(); // Retorna el puntero al inicio de la lista
}

lista* InfijoAPostfijo(pnodo inicioInfijo){ // Convierte la lista infija en una nueva lista postfija
    lista* postfijo = new lista(); // lista nueva donde se va guardando el resultado
    Pila pilaOperadores; //pila para guardar operadores temporalmente
    pnodo actual = inicioInfijo; //puntero que recorre la lista

    while(actual != NULL){ //Recorre la lista infija nodo por nodo
        string valor = actual->valor; //Obtiene el contenido del nodo actual

        if (RevisarNumeroValor(valor)) { //Si es un numero, se agrega directamente a la lista postfija
            postfijo->InsertarFinal(valor);
        }
        else if (valor == "(") {
			pilaOperadores.Apilar(valor); //Si abre parentesis, se apila sin comparar
        }
        else if (valor == ")") { //Si cierra parentesis, se desapila todo hasta el "("
            while (!pilaOperadores.EstaVacia() && pilaOperadores.VerTope() != "(") {
                postfijo->InsertarFinal(pilaOperadores.Desapilar()); // Se quitan operadores hasta encontrar el parentesis abierto))
            }
            if (!pilaOperadores.EstaVacia()) {
				pilaOperadores.Desapilar(); //Se descarta el "(" que quedo en el tope
			}   
        }
        else if (EsOperadorToken(valor)) { // si es un operador (+, -, *, /, ^)
            // mientras el tope tenga prioridad (dentro) mayor o igual a la
            // prioridad (fuera) del que esta entrando, se saca al resultado
            while (!pilaOperadores.EstaVacia() &&
                pilaOperadores.VerTope() != "(" &&
                PrioridadDentroPila(pilaOperadores.VerTope()) >= PrioridadFueraPila(valor)) {
                postfijo->InsertarFinal(pilaOperadores.Desapilar());
            }
            pilaOperadores.Apilar(valor); // finalmente se apila el operador entrante
        }
		actual = actual->siguiente; // Avanza al siguiente nodo de la lista infija
    }
    while (!pilaOperadores.EstaVacia()) { //Al terminar, se vacia el resto de la pila
		postfijo->InsertarFinal(pilaOperadores.Desapilar()); 
    }
    return postfijo; //Retorna la lista en postfijo
}