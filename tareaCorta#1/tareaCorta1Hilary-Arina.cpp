// Creado por: Hilary Aguilar y Arina Tarasova
// Tarea Corta #1 - Estructuras de Datos

#include <iostream>  // entrada y salida de datos
#include <fstream>   // manejo y lectura de archivos de texto
#include <string>    // manejo de cadenas de texto

using namespace std; 

#define TAM 5 // Tamano estatico para la Bicola

class nodo;
class lista;
typedef nodo* pnodo; // Alias para puntero a nodo (pnodo = nodo*)

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
    friend void MostrarLista(pnodo inicio);
    friend double EvaluarPostfijo(pnodo inicioPostfijo);
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
        if (cantidad == 0) { // Verifica si es la primera insercion
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
        if (cantidad == 0) { // Verifica si es la primera insercion
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
        pnodo temp = datos[frente]; // Guarda temporalmente el nodo del frente
        cantidad--; // Disminuye la cantidad de elementos
        if (cantidad == 0) { // Verifica si se elimino el ultimo elemento
        frente = 0; // Reinicia el frente
        fondo = -1; // Reinicia el fondo indicando que esta vacia
        }
        else {
            frente = (frente + 1) % TAM; // Mueve el frente una posicion hacia adelante de forma circular
        }
        return temp;// Retorna el nodo que fue eliminado
    }

    pnodo eliminarFinal() { // Elimina y retorna el nodo que esta en el final
        if (estaVacia()) {
            cout << "Bicola vacia.\n";
            return NULL;
        }
        pnodo temp = datos[fondo]; // Guarda temporalmente el nodo del final
        cantidad--;
        if (cantidad == 0) { // Verifica si se elimino el ultimo elemento
        frente = 0; // Reinicia el frente
        fondo = -1; // Reinicia el fondo indicando que esta vacia
        }
        else {
            fondo = (fondo - 1 + TAM) % TAM; // Mueve el fondo una posicion hacia atras de forma circular
        }
        return temp; // Retorna el nodo que fue eliminado
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

class Pila { // Clase que representa una pila dinamica
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

    string Desapilar() { // Saca y retorna el elemento que esta en el tope
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

    string VerTope() { // Retorna el valor del tope sin eliminarlo
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
        else if (RevisarOperadorValor(valor)) { // si es un operador (+, -, *, /, ^)
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
    while (!pilaOperadores.EstaVacia()) { //Al terminar, se vacia operadores restantes
		postfijo->InsertarFinal(pilaOperadores.Desapilar()); 
    }
    return postfijo; //Retorna la lista en postfijo
}

double StringADouble(string texto) { // Convierte el numero de la expresion a double
    double resultado = 0;       // aqui se va acumulando el numero
    double signo = 1;           // 1 si es positivo, -1 si es negativo
    int indice = 0;             // posicion actual dentro del texto
    int longitud = texto.length(); // cantidad total de caracteres del texto

    if (longitud > 0 && texto[0] == '-') { // revisa si el numero tiene negativo
        signo = -1;
        indice = 1; // se salta el signo, para no leerlo como digito
    }

    while (indice < longitud && EsDigito(texto[indice])) { // arma la parte entera del numero
        resultado = resultado * 10 + (texto[indice] - '0');  // desplaza lo acumulado y suma el nuevo digito
        indice++;
    }

    if (indice < longitud && texto[indice] == '.') { //Si despues de la parte entera hay un punto, hay decimales
        indice++; //se salta el punto decimal
        double factorDecimal = 0.1; // factor para la parte decimal
        while (indice < longitud && EsDigito(texto[indice])) { // arma la parte decimal del numero
            resultado += (texto[indice] - '0') * factorDecimal; // suma el digito multiplicado por su factor decimal
            factorDecimal *= 0.1; // disminuye el factor para el siguiente digito
            indice++;
        }
    }
    return resultado * signo; // retorna el numero final con su signo correspondiente
}

string DoubleAString(double numero) {// Convierte un double (resultado de una operacion) a string
    string resultado = ""; // aqui se va armando el texto final
    if (numero < 0) { //Si el numero es negativo, se guarda el signo aparte
        resultado += "-"; 
		numero = -numero; // se hace positivo para procesarlo
    }
    int parteEntera = (int)numero; //Parte antes del punto decimal
    double parteDecimal = numero - parteEntera; //Parte despues del punto decimal

	string parteEnteraStr = ""; //Aqui se va armando la parte entera 
    if (parteEntera == 0) {
        parteEnteraStr = "0";// caso: si la parte entera es 0
    }
	else {
        int valorRestante = parteEntera; // copia que se va reduciendo mientras se sacan digitos
        while (valorRestante > 0) {
            char digitoActual = '0' + (valorRestante % 10); //Ultimo digito del numero restante
            parteEnteraStr = digitoActual + parteEnteraStr; //Se agrega al inicio del texto
            valorRestante /= 10; // se quita el ultimo digito ya procesado
		}
	}
	resultado += parteEnteraStr; //Se agrega la parte entera al resultado final

    if (parteDecimal > 0.0000001) { //Si la parte decimal es significativa
        resultado += ".";
        for (int contador = 0; contador < 6; contador++) {
			parteDecimal *= 10; //Se desplaza un digito a la izquierda
			int digitoActual = (int)parteDecimal; //Se obtiene el digito actual
			resultado += ('0' + digitoActual); //Se agrega al resultado final
			parteDecimal -= digitoActual; //Se quita el digito ya procesado

			if (parteDecimal < 0.0000001) { //Si la parte decimal ya no tiene digitos significativos, se detiene
				break;
			}
        }
    }
	return resultado; //Retorna el numero convertido a string
}

double AplicarOperador(double num1, double num2, string operador) { //Aplica la operacion correspondiente a los dos numeros
	double resultado = 0; //almacena el resultado de la operacion
    if (operador == "+") {
        return num1 + num2;
    }
    else if (operador == "-") {
        return num1 - num2;
    }
    else if (operador == "*") {
        return num1 * num2;
    }
	else if (operador == "/") {
		if (num2 == 0) {
			cout << "No se puede divir por cero." << endl;
			return 0; // Retorna 0 en caso de division por cero
		}
		return num1 / num2;
	}
	else if (operador == "^") {
		resultado = 1;
		for (int i = 0; i < (int)num2; i++) {
			resultado *= num1; // Eleva el numero a la potencia indicada
		}
	}
    return resultado;
}

double EvaluarPostfijo(pnodo inicioPostfijo) { //Evalua una expresion en postfijo y retorna el resultado
    Pila pilaNumeros;  //pila para guardar numeros temporalmente(como texto)
    pnodo actual = inicioPostfijo; // puntero para recorrer la lista postfija

    while (actual != NULL) { //recorre toda la expresion postfija, nodo por nodo
        string valor = actual->valor; //obtiene el contenido del nodo actual

        if (RevisarNumeroValor(valor)) { //Si es numero, se apila directamente como texto
            pilaNumeros.Apilar(valor);
        }
        else if (RevisarOperadorValor(valor)) { //Si es un operador, se opera con los dos numeros del tope
            string strNum2 = pilaNumeros.Desapilar(); // primer tope sacado = num2
            string strNum1 = pilaNumeros.Desapilar(); //segundo tope sacado = num 1

            double num1 = StringADouble(strNum1); //convierte el texto a numero real
            double num2 = StringADouble(strNum2); //convierte el texto a numero real
            double resultado = AplicarOperador(num1, num2, valor); //Aplica la operacion correspondiente

            pilaNumeros.Apilar(DoubleAString(resultado)); //Se apila el resultado como texto
        }
        actual = actual->siguiente; //Avanza al siguiente nodo
    }
	string resultadoFinal = pilaNumeros.Desapilar(); //El resultado final queda en el tope de la pila
	return StringADouble(resultadoFinal); //Se convierte el resultado final a numero real y se retorna
}

void MostrarLista(pnodo inicio)
{
    while (inicio != NULL)
    {
        cout << inicio->valor << " ";
        inicio = inicio->siguiente;
    }
    cout << endl;
}

int main()
{
    Bicola bicola;

    bicola.insertarFrente(LeerArchivo("ArchivosPrueba/Arch1.txt"));
    bicola.insertarFinal(LeerArchivo("ArchivosPrueba/Arch2.txt"));
    bicola.insertarFrente(LeerArchivo("ArchivosPrueba/Arch3.txt"));
    bicola.insertarFinal(LeerArchivo("ArchivosPrueba/Arch4.txt"));
    bicola.insertarFrente(LeerArchivo("ArchivosPrueba/Arch5.txt"));

    bicola.mostrar();

    cout << "\nProcesando archivos...\n\n";

    while (!bicola.estaVacia())
    {
        pnodo expresionOriginal = bicola.eliminarFrente();

        cout << "Expresion Original: ";
        MostrarLista(expresionOriginal);

        lista* postfijo = InfijoAPostfijo(expresionOriginal);

        cout << "Expresion Postfijo: ";
        postfijo->Mostrar();

        double resultado =
            EvaluarPostfijo(postfijo->ObtenerPrimero());

        cout << "Resultado: "
            << resultado << endl;

        cout << "----------------------\n";
    }

    return 0;
}