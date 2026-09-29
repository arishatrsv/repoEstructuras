#include <iostream>
using namespace std;

const int Tam_Tabla = 13;

// --------------------- Clase Nodo ---------------------
class Nodo {
public:
    
    Nodo(int nuevovalor) {
        valor = nuevovalor;
        siguiente = NULL;
    }

    Nodo(int nuevovalor,Nodo* signodo) {
        valor=nuevovalor;
		siguiente = signodo;
    }
  private:
    int valor;                                 
    Nodo* siguiente;
        
   friend class listaSimple;
};
    
        
typedef Nodo *pnodo; //Alias


// ------------------ Clase Lista Simpñe ------------------


//void no retorna nada
//bool retorna False o True
//int retorna entero
class listaSimple 
{
   
   private:
    pnodo primero;
   
public:
   
    listaSimple() { primero =  NULL; }//constructor
    bool ListaVacia() { return primero == NULL; } 
    
                             
    void InsertarInicio(int nuevovalor) 
	{
    if (ListaVacia())
    {
   
     primero = new Nodo(nuevovalor);//6
     
    }
   else
   {
        pnodo nuevo = new Nodo(nuevovalor);
        nuevo->siguiente=(primero);
        primero = nuevo;
    }
  }
    
   void InsertarFinal(int nuevovalor)//76
   {
   if (ListaVacia())
     primero = new Nodo(nuevovalor);
   else
      { 
      //primera forma
	    pnodo aux = primero;
		while ( aux->siguiente != NULL) 
		  aux= aux->siguiente;  
		aux->siguiente=new Nodo(nuevovalor);
       
       //segunda forma 
      /* pnodo aux = primero;
        while ( aux->siguiente != NULL)
         aux= aux->siguiente;
        pnodo nuevo=new nodo(v);
        aux->siguiente=nuevo;*/
      }    
}

    bool Buscar(int valbuscado) {//44 18
        pnodo aux = primero;
        while (aux != nullptr) {
            if (aux->valor == valbuscado)
                //44==44si 44=18x 18=18si
                cout<<aux->valor<<endl;//44 18
                return true;
            aux = aux->siguiente;
        }
        return false;
    }                
    
    
     bool Eliminar(int valbuscado) {
        pnodo aux = primero;
        pnodo ant = nullptr;

        while (aux != nullptr) {
            if (aux->valor == valbuscado) {
                if (ant == nullptr) {
                    // Eliminar primero
                    primero = aux->siguiente;
                } else {
                    ant->siguiente=aux->siguiente;
                }
                delete aux;
                return true;
            }
            ant = aux;
            aux = aux->siguiente;
        }

        return false;  // No se encontró
    }
    
    void Mostrar() { //5->44->18->31
        pnodo aux = primero;
        while (aux != nullptr) {
            cout << aux->valor << " -> ";//41 44->18->31->null
            aux = aux->siguiente;
        }
        cout << "NULL";
    }

    ~listaSimple() {
        pnodo aux = primero;
        while (aux != nullptr) {
            pnodo temp = aux;
            aux = aux->siguiente;
            delete temp;
        }
    }
    
   
   
   friend class TablaHashing;
};

// ------------------ Clase Tabla de Hashing ------------------
class TablaHashing {
private:
    listaSimple* tabla[Tam_Tabla];

    int FuncionHash(int valor) { //18%13=5 44%13=5
        return valor % Tam_Tabla;
    }

public:
    TablaHashing() {
        for (int i = 0; i < Tam_Tabla; i++) {
            tabla[i] = new listaSimple();
        }
    }

    void Insertar(int valor) {//18  44 //Funcion de Hashing
        int pos = FuncionHash(valor);//5 5
        tabla[pos]->InsertarFinal(valor);//18 44   Clase ListaSimple
        cout << "Insertado " << valor << " en la posicion " << pos << endl;
    }

     bool Buscar(int valor) {//44
        int pos = FuncionHash(valor);//44%13=5
        return tabla[pos]->Buscar(valor);
    }

    bool Eliminar (int valor) {
        int pos = FuncionHash(valor);
        return tabla[pos]->Eliminar(valor);
    }
    void Mostrar() {
        cout << "\nTabla Hash con Encadenamiento:\n";
        for (int i = 0; i < Tam_Tabla; i++) {//i=0si 1si 2si 3 4 5 6 7 8 9 10 11 12
            cout << "[" << i << "]: ";
            tabla[i]->Mostrar();
            cout << endl;
        }
    }

    ~TablaHashing() {
        for (int i = 0; i < Tam_Tabla; i++) {
            delete tabla[i];
        }
    }
};

// ------------------ Programa Principal ------------------
/*int main() {
	ListaSimple L1;
	L1.Insertar(23);
	L1.Insertar(44);
	L1.Insertar(89);
	
	L1.mostrar();
	cout<<L1.buscar(44)<<endl;
	
	
	
    TablaHashing tabla;

    tabla.Insertar(18);
    tabla.Insertar(41);
    tabla.Insertar(22);
    tabla.Insertar(44);
    tabla.Insertar(59);
    tabla.Insertar(32);
    tabla.Insertar(31);
    tabla.Insertar(73);

    tabla.Mostrar();
    tabla.Eliminar(44);
    tabla.Mostrar();

    /*int id;
    cout << "\nBuscar identificacion: ";
    cin >> id;*/

   /*if (tabla.buscar (id))
        cout << "Identificacion " << id << " encontrada." << endl;
    else
        cout << "Identificacion " << id << " no encontrada." << endl;*/
    
   // return 0;
//}

