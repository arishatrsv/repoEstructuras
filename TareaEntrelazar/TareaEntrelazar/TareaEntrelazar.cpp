#include <iostream>  //Librería: entrada y salida de datos
using namespace std;  //imprimir en pantalla

class nodo { // Constructores - Define que es un nodo
public:
	nodo(int pvalor) { //valor que tendrá el nodo
		valor = pvalor;
		siguiente = NULL; //no apunta a ningún nodo
	}
	nodo(int pvalor, nodo* sigNodo) { //el valor y el nodo que debe apuntar
		valor = pvalor;
		siguiente = sigNodo; //apunta al nodo indicado
	}
private:
	int valor;
	nodo* siguiente; //guarda dirección del nodo
	friend class lista; //permite que la clase lista acceda a lo privado
};

typedef nodo* pnodo;	//Alias para puntero a nodo/ con alias se escribe  nodo*pn

class lista {
public:
	lista() { //construye la lista
		primero = NULL;
	} //inicia la lista en vacia
	void InsertarInicio(int valor); //No retorna nada
	void InsertarFinal(int valor);
	bool ListaVacia() { return primero == NULL; } //retorna True o False-- revisa si la lista está vacia
	void Mostrar();
	int LargoLista(); //retorna valor númerico
	void ContruirLista(int num);
	void ProcesarNumero(int num1, int num2);
	void Promedio(int num);
	bool Buscar(int num, int buscar);
	void SumaLista(int num1, int num2);
	void SumaElevado(int num);
	void Entrelazar(lista& L2);

private:
	pnodo primero;
};

void lista::InsertarInicio(int valor) { // crea un nuevo nodo al inicio 
	if (ListaVacia()) {
		primero = new nodo(valor); //crea el primer nodo de la lista
	}
	else {
		primero = new nodo(valor, primero); //conecta el nuevo nodo, con el nodo anterior
	}
}

void lista::InsertarFinal(int valor) {
	if (ListaVacia())
		primero = new nodo(valor);
	else {
		pnodo nodoActual = primero;
		while (nodoActual->siguiente != NULL)
			nodoActual = nodoActual->siguiente;
		nodoActual->siguiente = new nodo(valor);
	}
}

void lista::Mostrar() { //imprimir las listas
	pnodo nodoActual; //puntero que recorre la lista
	if (primero == NULL)
		cout << "No hay elementos para mostrar";
	else {
		nodoActual = primero; //Comienza a recorrer desde el primer nodo
		while (nodoActual) {  //Continua mientras exista un nodo
			cout << nodoActual->valor << "->";
			nodoActual = nodoActual->siguiente; //Avanza al siguiente nodo
		}
		cout << "NULL" << endl; //indica que es el final
	}
}

int lista::LargoLista() {
	int cont = 0;
	pnodo nodoActual = primero; //inicia desde el primer nodo
	if (ListaVacia()) { //si la lista está vacia
		return cont;
	}
	else {
		while (nodoActual != NULL) {
			nodoActual = nodoActual->siguiente; //avanza al siguiente nodo
			cont++;
		}
		return cont; //cantidad total de nodos
	}
}

void lista::ContruirLista(int num) { //convierte los dígitos en nodos de una lista
	while (num != 0) {  //Repite mientras hay dígitos
		int digito = num % 10;  //Saca el ultimo dígito
		InsertarInicio(digito);  //Lo agrega al inicio
		num = num / 10;  //elimina el último dígito
	}
}

void lista::ProcesarNumero(int num1, int num2) {
	lista lista1; //crea las listas
	lista lista2;
	if (lista1.LargoLista() != lista2.LargoLista()) {
		cout << "Los números no tienen el mismo largo" << endl;
		return;
	}
	lista1.ContruirLista(num1); //llama al método y contruye la lista
	lista2.ContruirLista(num2);
	cout << "Lista1 -> "; //imprime
	lista1.Mostrar();  //muestra la lista
	cout << "Lista2 -> ";
	lista2.Mostrar();

	int suma = 0;
	int mult = 1;
	pnodo nodoActual = lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	while (nodoActual != NULL) { //recorre hasta que no haya nodos
		if (nodoActual->valor % 2 == 0) { //verifica si es par
			suma = suma + nodoActual->valor * nodoActual->valor; //eleva el digito al cuadrado y lo agrega a la suma
		}
		else { //es impar
			mult = mult * nodoActual->valor * nodoActual->valor * nodoActual->valor; //Eleva el dígito al cubo y lo multiplica
		}
		nodoActual = nodoActual->siguiente; //avanza al siguiente nodo
	}
	nodoActual = lista2.primero; //Reinicia el puntero para hacer lista 2
	while (nodoActual != NULL) {
		if (nodoActual->valor % 2 == 0) {   //si es par
			mult = mult * nodoActual->valor * nodoActual->valor; //Eleva el dígito al cuadrado y lo multiplica
		}
		else { //si es impar
			suma = suma + nodoActual->valor * nodoActual->valor * nodoActual->valor; //Eleva al cubo y lo suma
		}
		nodoActual = nodoActual->siguiente;
	}
	cout << "Suma= " << suma << endl;
	cout << "Mult= " << mult << endl;
}

void lista::Promedio(int num) {
	if (num == 0) {
		cout << "La suma es 0";
	}
	else {
		while (num != 0) {
			int copia = num % 10; //hace una copia y saca el último dígito
			InsertarInicio(copia); //inserta al inicio de la lista
			num = num / 10; //elimina el último dígito del número
		}
		int suma = 0;
		pnodo nodoActual = primero; //inicia el recorrido desde el primer nodo de la lista
		while (nodoActual != NULL) {
			suma = suma + nodoActual->valor; //Suma todos los nodos
			nodoActual = nodoActual->siguiente; //Pasa al siguiente nodo
		}
		int largo = LargoLista(); //Saca el largo de la lista
		cout << "Lista -> ";
		Mostrar();
		cout << "Promedio= " << suma / largo << endl; //divide la suma por el largo de la lista
	}
}

bool lista::Buscar(int num, int buscar) {
	while (num != 0) {
		int digito = num % 10; //saca el último dígito
		InsertarInicio(digito); //inserta al inicio de la lista
		num = num / 10; //elimina el último dígito del número
	}
	cout << "Lista -> ";
	Mostrar();

	pnodo nodoActual = primero; //inicia el recorrido desde el primer nodo de la lista
	while (nodoActual != NULL) {
		if (nodoActual->valor == buscar) { //Si el valor atual del nodo es igual al número buscado
			cout << "True" << endl;
			return true;
		}
		nodoActual = nodoActual->siguiente; //Si no coincide pasa al siguiente
	}
	cout << "False" << endl;
	return false;
}

void lista::SumaLista(int num1, int num2) {
	lista lista1; //crea las listas
	lista lista2;
	lista resultado;

	lista1.ContruirLista(num1); //llama al método y contruye la lista
	lista2.ContruirLista(num2);

	if (lista1.LargoLista() != lista2.LargoLista()) {
		cout << "Las listas no tienen el mismo largo" << endl;
		return;
	}
	cout << "Lista1 -> "; //imprime
	lista1.Mostrar();  //muestra la lista
	cout << "Lista2 -> ";
	lista2.Mostrar();

	pnodo nodoLista1 = lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	pnodo nodoLista2 = lista2.primero;
	while (nodoLista1 != NULL) { //recorre hasta que no haya nodos
		int suma = nodoLista1->valor + nodoLista2->valor; //Suma el nodo con el nodo de la otra lista
		resultado.InsertarFinal(suma);
		nodoLista1 = nodoLista1->siguiente;
		nodoLista2 = nodoLista2->siguiente;
	}
	cout << "Resultado -> ";
	resultado.Mostrar();
}

void lista::SumaElevado(int num) {
	lista lista1; //crea las listas
	lista1.ContruirLista(num); //llama al método y contruye la lista
	cout << "Lista -> "; //imprime
	lista1.Mostrar();  //muestra la lista

	int suma = 0;
	pnodo nodoActual = lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	while (nodoActual != NULL) { //recorre hasta que no haya nodos
		if (nodoActual->valor % 2 == 0) { //verifica si es par
			suma = suma + nodoActual->valor * nodoActual->valor; //eleva el digito al cuadrado y lo agrega a la suma
		}
		nodoActual = nodoActual->siguiente; //avanza al siguiente nodo
	}
	cout << "SumaParesElevados= " << suma << endl;
}

void lista::Entrelazar(lista& L2)
{
	int largo = LargoLista();
	if (largo != L2.LargoLista()) {
		cout << "Las listas no tienen el mismo largo" << endl;
		return;
	}

	int pos = 1; // posicion actual dentro de L1 (solo posiciones impares)
	while (pos <= largo) { //que no se pase de la longitud de la lista
		// ---- Buscar el nodo de L1 que esta en la posicion "pos" ----
		pnodo nodoImparL1 = primero;
		int cont = 1;
		while (cont < pos) {
			nodoImparL1 = nodoImparL1->siguiente;
			cont = cont + 1;
		}

		// Posicion destino en L2 = pos + 2, dando la vuelta si se pasa de largo
		int posDestino = pos + 2;
		if (posDestino > largo) {
			posDestino = posDestino - largo;
		}

		// ---- Buscar el nodo de L2 que esta en la posicion "posDestino" ----
		pnodo nodoDestinoL2 = L2.primero;
		cont = 1;
		while (cont < posDestino) {
			nodoDestinoL2 = nodoDestinoL2->siguiente;
			cont = cont + 1;
		}

		// Guardamos el nodo que L1 va a dejar huerfano (antes de romper el enlace)
		pnodo huerfano = nodoImparL1->siguiente;

		// El nodo impar de L1 ahora apunta al nodo robado de L2
		nodoImparL1->siguiente = nodoDestinoL2;

		if (posDestino == 1) {
			// Dio la vuelta: no hay nodo anterior en L2, se pega el
			// huerfano al final de L2 (buscamos el ultimo nodo)
			pnodo ultimoL2 = L2.primero;
			while (ultimoL2->siguiente != NULL) {
				ultimoL2 = ultimoL2->siguiente;
			}
			ultimoL2->siguiente = huerfano;
		}
		else {
			// ---- Buscar el nodo de L2 en la posicion (posDestino - 1) ----
			// (el que originalmente apuntaba al nodo robado)
			pnodo nodoAnteriorL2 = L2.primero;
			cont = 1;
			while (cont < posDestino - 1) {
				nodoAnteriorL2 = nodoAnteriorL2->siguiente;
				cont = cont + 1;
			}
			nodoAnteriorL2->siguiente = huerfano;
		}

		pos = pos + 2; // pasamos a la siguiente posicion impar
	}
}

int main() {
	lista proceso; //Objeto de la clase lista
	cout << "Ejercicio#1" << endl;
	proceso.ProcesarNumero(6234, 5890); //llama al método para ejecutar

	lista proceso2;
	cout << endl << "Ejercicio#2" << endl;
	proceso2.Promedio(638901);

	lista proceso3;
	cout << endl << "Ejercicio#3" << endl;
	proceso3.Buscar(23345, 6);

	lista proceso4;
	cout << endl << "Ejercicio#4" << endl;
	proceso4.SumaLista(234, 645);

	lista proceso5;
	cout << endl << "Ejercicio#5" << endl;
	proceso5.SumaElevado(23345);

	cout << "EJERCICIO ENTRELAZAR" << endl;

	// Construimos L1 = 5-6-3-12-23-56 insertando al inicio en orden inverso
	lista L1;
	L1.InsertarInicio(56);
	L1.InsertarInicio(23);
	L1.InsertarInicio(12);
	L1.InsertarInicio(3);
	L1.InsertarInicio(6);
	L1.InsertarInicio(5);

	// Construimos L2 = 8-9-2-13-32-5 insertando al inicio en orden inverso
	lista L2;
	L2.InsertarInicio(5);
	L2.InsertarInicio(32);
	L2.InsertarInicio(13);
	L2.InsertarInicio(2);
	L2.InsertarInicio(9);
	L2.InsertarInicio(8);

	cout << "Antes de entrelazar:" << endl;
	cout << "L1 -> "; L1.Mostrar();
	cout << "L2 -> "; L2.Mostrar();

	L1.Entrelazar(L2);

	cout << endl << "Despues de entrelazar:" << endl;
	cout << "L1 -> "; L1.Mostrar();
	cout << "L2 -> "; L2.Mostrar();
	return 0;
}