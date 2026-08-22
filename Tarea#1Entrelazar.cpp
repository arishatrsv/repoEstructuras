#include <iostream>  //Librería: entrada y salida de datos
using namespace std;  //imprimir en pantalla

class nodo { // Constructores - Define que es un nodo
	public:
		nodo(int pvalor){ //valor que tendrá el nodo
			valor= pvalor;
			siguiente= NULL; //no apunta a ningún nodo
		}
		nodo(int pvalor,nodo*sigNodo){ //el valor y el nodo que debe apuntar
			valor= pvalor;
			siguiente= sigNodo; //apunta al nodo indicado
		}
	private:
		int valor;
		nodo*siguiente; //guarda dirección del nodo
		friend class lista; //permite que la clase lista acceda a lo privado
};

typedef nodo*pnodo;	//Alias para puntero a nodo/ con alias se escribe  nodo*pn

class lista {
	public:
		lista(){ //construye la lista
			primero=NULL;} //inicia la lista en vacia
		void InsertarInicio(int valor); //No retorna nada
		void InsertarFinal(int valor);
		bool ListaVacia() { return primero == NULL; } //retorna True o False-- revisa si la lista está vacia
		void Mostrar();
		int LargoLista(); //retorna valor númerico
		void ContruirLista(int num);
		void ProcesarNumero(int num1,int num2);
		void Promedio(int num);
		bool Buscar(int num, int buscar);
		void SumaLista(int num1, int num2);
		void SumaElevado(int num);
		
	private:
		pnodo primero;
};

void lista::InsertarInicio(int valor){ // crea un nuevo nodo al inicio 
	if(ListaVacia()){
		primero= new nodo(valor); //crea el primer nodo de la lista
	}
	else{
		primero= new nodo(valor, primero); //conecta el nuevo nodo, con el nodo anterior
	}
}

void lista::InsertarFinal(int valor){
   if (ListaVacia())
     primero = new nodo(valor);
   else{
	    pnodo nodoActual = primero;
        while ( nodoActual->siguiente != NULL)
          nodoActual= nodoActual->siguiente;
        nodoActual->siguiente=new nodo(valor);
    }    
}

void lista::Mostrar(){ //imprimir las listas
	pnodo nodoActual; //puntero que recorre la lista
	if(primero==NULL)	
		cout<<"No hay elementos para mostrar";
	else{
		nodoActual=primero; //Comienza a recorrer desde el primer nodo
		while(nodoActual){  //Continua mientras exista un nodo
			cout<<nodoActual->valor<< "->";
			nodoActual= nodoActual-> siguiente; //Avanza al siguiente nodo
		}
		cout<<"NULL"<<endl; //indica que es el final
	}
}

int lista::LargoLista(){
    int cont=0;
    pnodo nodoActual= primero; //inicia desde el primer nodo
    if(ListaVacia()){ //si la lista está vacia
        return cont;
    }else{
        while(nodoActual!=NULL){ 
        nodoActual=nodoActual->siguiente; //avanza al siguiente nodo
        cont++;
    }
    return cont; //cantidad total de nodos
    }
}

void lista::ContruirLista(int num){ //convierte los dígitos en nodos de una lista
	while(num!=0){  //Repite mientras hay dígitos
		int digito= num % 10;  //Saca el ultimo dígito
		InsertarInicio(digito);  //Lo agrega al inicio
		num= num/10;  //elimina el último dígito
	}
}

void lista::ProcesarNumero(int num1,int num2){ 
	lista lista1; //crea las listas
	lista lista2;
	if(lista1.LargoLista() != lista2.LargoLista()){
        cout << "Los números no tienen el mismo largo" << endl;
        return;
    }
	lista1.ContruirLista(num1); //llama al método y contruye la lista
	lista2.ContruirLista(num2);
	cout<<"Lista1 -> "; //imprime
	lista1.Mostrar();  //muestra la lista
	cout<<"Lista2 -> ";
	lista2.Mostrar();
	
	int suma=0;
	int mult=1;
	pnodo nodoActual= lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	while(nodoActual!=NULL){ //recorre hasta que no haya nodos
		if(nodoActual->valor%2==0 ){ //verifica si es par
			suma= suma+nodoActual->valor*nodoActual->valor; //eleva el digito al cuadrado y lo agrega a la suma
		}
		else{ //es impar
			mult=mult*nodoActual->valor*nodoActual->valor*nodoActual->valor; //Eleva el dígito al cubo y lo multiplica
		}
		nodoActual= nodoActual->siguiente; //avanza al siguiente nodo
	}
	nodoActual= lista2.primero; //Reinicia el puntero para hacer lista 2
	while(nodoActual!=NULL){
		if(nodoActual->valor%2==0 ){   //si es par
			mult=mult*nodoActual->valor*nodoActual->valor; //Eleva el dígito al cuadrado y lo multiplica
		}
		else{ //si es impar
            suma = suma+ nodoActual->valor* nodoActual->valor* nodoActual->valor; //Eleva al cubo y lo suma
		}
		nodoActual= nodoActual->siguiente;
	}
	cout<<"Suma= "<< suma << endl;
	cout<<"Mult= "<< mult<< endl;
}

void lista::Promedio(int num){
	if (num==0){
		cout<<"La suma es 0";
		}
	else{
		while(num!=0){
			int copia= num%10; //hace una copia y saca el último dígito
			InsertarInicio(copia); //inserta al inicio de la lista
			num=num/10; //elimina el último dígito del número
		}
		int suma=0;
		pnodo nodoActual= primero; //inicia el recorrido desde el primer nodo de la lista
		while(nodoActual!=NULL){
			suma=suma+nodoActual->valor; //Suma todos los nodos
			nodoActual=nodoActual->siguiente; //Pasa al siguiente nodo
		}
		int largo= LargoLista(); //Saca el largo de la lista
		cout<<"Lista -> ";
		Mostrar();
		cout<<"Promedio= "<<suma/largo<<endl; //divide la suma por el largo de la lista
	}
}

bool lista::Buscar(int num, int buscar){
	while(num!=0){
		int digito= num%10; //saca el último dígito
		InsertarInicio(digito); //inserta al inicio de la lista
		num=num/10; //elimina el último dígito del número
	}
	cout<< "Lista -> ";
	Mostrar();
	
	pnodo nodoActual= primero; //inicia el recorrido desde el primer nodo de la lista
	while(nodoActual!=NULL){
		if(nodoActual->valor==buscar){ //Si el valor atual del nodo es igual al número buscado
			cout<<"True"<<endl;
			return true;
		}
		nodoActual=nodoActual->siguiente; //Si no coincide pasa al siguiente
	}
	cout<<"False"<<endl;
	return false;
}

void lista::SumaLista(int num1,int num2){
	lista lista1; //crea las listas
	lista lista2;
	lista resultado;
	
	lista1.ContruirLista(num1); //llama al método y contruye la lista
	lista2.ContruirLista(num2);
	
	if(lista1.LargoLista() != lista2.LargoLista()){
        cout << "Las listas no tienen el mismo largo" << endl;
        return;
    }
	cout<<"Lista1 -> "; //imprime
	lista1.Mostrar();  //muestra la lista
	cout<<"Lista2 -> ";
	lista2.Mostrar();
	
	pnodo nodoLista1= lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	pnodo nodoLista2= lista2.primero;
	while(nodoLista1!=NULL){ //recorre hasta que no haya nodos
		int suma= nodoLista1->valor + nodoLista2->valor; //Suma el nodo con el nodo de la otra lista
		resultado.InsertarFinal(suma);
		nodoLista1= nodoLista1->siguiente;
		nodoLista2= nodoLista2->siguiente;
	}
	cout<<"Resultado -> ";
	resultado.Mostrar();
}

void lista::SumaElevado(int num){
	lista lista1; //crea las listas
	lista1.ContruirLista(num); //llama al método y contruye la lista
	cout<<"Lista -> "; //imprime
	lista1.Mostrar();  //muestra la lista
	
	int suma=0;
	pnodo nodoActual= lista1.primero; //inicia el recorrido desde el primer nodo de la lista
	while(nodoActual!=NULL){ //recorre hasta que no haya nodos
		if(nodoActual->valor%2==0 ){ //verifica si es par
			suma= suma+nodoActual->valor*nodoActual->valor; //eleva el digito al cuadrado y lo agrega a la suma
		}
		nodoActual= nodoActual->siguiente; //avanza al siguiente nodo
	}
	cout<<"SumaParesElevados= "<< suma << endl;
}

int main(){
	lista proceso; //Objeto de la clase lista
	cout<< "Ejercicio#1"<< endl;
	proceso.ProcesarNumero(6234,5890); //llama al método para ejecutar
	
	lista proceso2;
	cout<<endl<<"Ejercicio#2"<<endl;
	proceso2.Promedio(638901);
	
	lista proceso3;
	cout<<endl<<"Ejercicio#3"<<endl;
	proceso3.Buscar(23345,6);
	
	lista proceso4;
	cout<<endl<<"Ejercicio#4"<<endl;
	proceso4.SumaLista(234,645);
	
	lista proceso5;
	cout<<endl<<"Ejercicio#5"<<endl;
	proceso5.SumaElevado(23345 );
	
	return 0;
}


