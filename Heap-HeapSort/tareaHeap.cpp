//Creado por: Hilary Aguilar y Arina Tarasova

#include <iostream>

using namespace std;

//imprime el contenido del arreglo
void imprimirArreglo(int Llave[], int LargoDelArreglo){
    cout << "[ ";
    for(int k = 1; k <= LargoDelArreglo; k++){
        cout << Llave[k];
        if(k < LargoDelArreglo){
            cout << ", ";
        }
    }
    cout << " ]" << endl;
}

//funcion para la creacion del heap
void crearHeap(int ArregloInicial[], int Llave[], int LargoDelArreglo){
    int i;
    int NuevaLlave;
    int Padre;
    int Siguiente;
    int Auxiliar;

    cout << endl;
    cout << "CREACION DEL HEAP" << endl;

    for(i = 1; i <= LargoDelArreglo; i++){
        NuevaLlave = ArregloInicial[i];
        Siguiente = i; //inserta una nueva llave en el heap
        Padre = Siguiente / 2;
        Llave[Siguiente] = NuevaLlave;

        while(Siguiente != 1 && Llave[Padre] <= Llave[Siguiente]){ 
            cout << "Intercambio: Llave[" << Padre << "](" << Llave[Padre]
                << ") <= Llave[" << Siguiente << "](" << Llave[Siguiente] << ")" << endl;
            Auxiliar = Llave[Padre];
            Llave[Padre] = Llave[Siguiente];
            Llave[Siguiente] = Auxiliar;
            Siguiente = Padre; //avanza sobre el arbol
            Padre = Siguiente / 2;
        }
        cout << "Paso " << i << ": ";
        imprimirArreglo(Llave, LargoDelArreglo);
    }
    cout << endl;
    cout << "HEAP GENERADO: ";
    imprimirArreglo(Llave, LargoDelArreglo);
}

//funcion para ejecutar heapsort
void ejecutarHeapSort(int Llave[], int LargoDelArreglo){
    int Ultima;
    int LlaveAnterior;
    int Hijo;
    int Padre;

    cout << endl;
    cout << "--- HEAPSORT ---" << endl;

    for(Ultima = LargoDelArreglo; Ultima >= 2; Ultima--){
        LlaveAnterior = Llave[Ultima];//mueve la llave raiz al ultimo lugar
        cout << "Mueve raiz (" << Llave[1]
            << ") a posicion " << Ultima << endl;
        Llave[Ultima] = Llave[1];
        Padre = 1; //ajusta el arbol al tamaño menos 1

        if(Ultima - 1 >= 3 && Llave[3] > Llave[2]){ //busca al mayor de los hijos de la raiz
            Hijo = 3;
        }
        else{
            Hijo = 2;
        }

        // mueve las llaves hacia arriba hasta encontrar el lugar para llaveanterior
        while(Hijo <= Ultima - 1 && Llave[Hijo] > LlaveAnterior){
            cout << "Mueve hijo en posicion "
                << Hijo << " (" << Llave[Hijo]
                << ") a padre en posicion "
                << Padre << endl;
            Llave[Padre] = Llave[Hijo];
            Padre = Hijo;
            Hijo = Padre * 2;
            if(Hijo + 1 <= Ultima - 1 && //encuentra al mayor de los hijos del padre
                Llave[Hijo + 1] > Llave[Hijo]){
                Hijo = Hijo + 1;
            }
        }

        Llave[Padre] = LlaveAnterior; //coloca la llave anterior en su posicion
        cout << "Coloca " << LlaveAnterior
            << " en posicion " << Padre << endl;
        cout << "Estado actual: ";
        imprimirArreglo(Llave, LargoDelArreglo);
        cout << "Pasada "
            << (LargoDelArreglo - Ultima + 1)
            << ": ";
        imprimirArreglo(Llave, LargoDelArreglo);
    }

    cout << endl;
    cout << "ORDENAMIENTO FINAL: ";
    imprimirArreglo(Llave, LargoDelArreglo);
}

int main(){
    // posicion 0 sin uso para trabajar igual que el algoritmo visto en clase
    int ArregloInicial[11] = {0, 45, 12, 400, 89, 1000, 2, 5, 1, 700, 5000};
    int LargoDelArreglo = 10;
    int Llave[11] = {0};
    cout << "LISTA INICIAL: ";
    imprimirArreglo(ArregloInicial, LargoDelArreglo);
    crearHeap(ArregloInicial, Llave, LargoDelArreglo);
    ejecutarHeapSort(Llave, LargoDelArreglo);
    return 0;
}