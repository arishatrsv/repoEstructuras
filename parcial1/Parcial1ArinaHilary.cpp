// 1er Parcial - Estructuras de Datos
// Parte 1
//  Estudiantes: Arina Tarasova y Hilary Aguilar

#include <iostream>
#include <cstdlib> // abs
#include <cmath>   // abs para double
using namespace std;

class nodo
{ // constructores
public:
    nodo(int v)
    {
        valor = v;
        siguiente = NULL;
    }
    nodo(int v, nodo *signodo)
    {
        valor = v;
        siguiente = signodo;
    }

private:
    int valor = 0;
    nodo *siguiente;
    friend class lista;
};

typedef nodo *pnodo; //alias
class lista
{
public:
    lista() { primero = NULL; }
    ~lista(); //destructor

    void InsertarInicio(int v); //no retornan nada
    void InsertarFinal(int v);
    void InsertarPos(int v, int pos);
    bool ListaVacia() { return primero == NULL; } //retorna True o False
    void Imprimir();
    void Borrar(int v);
    void Mostrar();
    void Siguiente();
    void BorrarFinal();
    void BorrarInicio();
    void borrarPosicion(int pos);
    void Sumanum(int num);
    int largoLista(); //retorna un valor numerico

    void UNO(double x1, double x2);
    void DOS(double x);
    void TRES();
    void CUATRO(double x1, double x2, double x3);

private:
    pnodo primero;
};

lista::~lista() //~ para destruir lista
{
    pnodo aux;
    while (primero)
    {
        aux = primero;
        primero = primero->siguiente;
        delete aux;
    }
    primero = NULL;
}

int lista::largoLista()
{
    int cont = 0;
    pnodo aux = primero;
    if (ListaVacia())
    {
        return cont;
    }
    else
    {
        while (aux != NULL)
        {
            aux = aux->siguiente;
            cont++;
        }
        return cont;
    }
}

void lista::InsertarInicio(int v)
{
    if (ListaVacia())
    {
        primero = new nodo(v);
    }
    else
    {
        primero = new nodo(v, primero);
    }
}

void lista::InsertarFinal(int v)
{
    if (ListaVacia())
        primero = new nodo(v);
    else
    {
        pnodo aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodo(v);
    }
}

void lista::InsertarPos(int v, int pos)
{
    if (ListaVacia())
        primero = new nodo(v);
    else
    {
        if (pos <= 1)
        {
            InsertarInicio(v);
        }
        else
        {
            nodo *aux = primero;
            int i = 2;
            while ((i != pos) && (aux->siguiente != NULL))
            {
                i++;
                aux = aux->siguiente;
            }
            pnodo nuevo = new nodo(v);
            nuevo->siguiente = aux->siguiente;
            aux->siguiente = nuevo;
        }
    }
}

void lista::BorrarFinal()
{
    if (ListaVacia())
    {
        cout << "No hay elementos en la lista" << endl;
    }
    else
    {
        if (primero->siguiente == NULL)
        {
            pnodo temp = primero;
            primero = NULL;
            delete temp;
        }
        else
        {
            pnodo aux = primero;
            while (aux->siguiente->siguiente != NULL)
            {
                aux = aux->siguiente;
            }
            pnodo temp = aux->siguiente;
            aux->siguiente = NULL;
            delete temp;
        }
    }
}

void lista::BorrarInicio()
{
    if (ListaVacia())
    {
        cout << "No hay elementos en la lista" << endl;
    }
    else
    {
        if (primero->siguiente == NULL)
        {
            pnodo temp = primero;
            primero = NULL;
            delete temp;
        }
        else
        {
            pnodo aux = primero;
            primero = primero->siguiente;
            delete aux;
        }
    }
}

void lista::borrarPosicion(int pos)
{
    if (ListaVacia())
    {
        cout << "Lista vacia" << endl;
    }
    else
    {
        if ((pos > largoLista()) || (pos < 1))
        {
            cout << "Error en posicion" << endl;
        }
        else
        {
            if (pos == 1)
            {
                pnodo temp = primero;
                primero = primero->siguiente;
                delete temp; 
            }
            else
            {
                int cont = 2;
                pnodo aux = primero;
                while (cont < pos)
                {
                    aux = aux->siguiente;
                    cont++;
                }
                pnodo temp = aux->siguiente;
                aux->siguiente = aux->siguiente->siguiente;
                delete temp;
            }
        }
    }
}

void lista::Mostrar()
{
    nodo *aux;
    if (primero == NULL)
        cout << "No hay elementos aqui";
    else
    {
        aux = primero;
        while (aux != NULL)
        {
            cout << aux->valor << "->";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

void lista::Sumanum(int num)
{
    if (num == 0)
        cout << "Suma igual a 0";
    else
    {
        while (num != 0)
        {
            int temp = num % 10;
            InsertarInicio(temp);
            num = num / 10;
        }
        int suma = 0;
        pnodo aux = primero;
        while (aux != NULL)
        {
            suma = suma + aux->valor;
            aux = aux->siguiente;
        }
        cout << suma << endl;
    }
}

//  Ejercicio 1 - UNO
//  Punteros usados: 1 (aux)
void lista::UNO(double x1, double x2)
{
    // validaciones: abs, entero, maximo 15 digitos y mismo largo
    double a1 = abs(x1); // valor absoluto de cada numero
    double a2 = abs(x2);
    if (a1 > 999999999999999.0 || a2 > 999999999999999.0 || // es or
        a1 != (long long)a1 || a2 != (long long)a2)
    {
        cout << "Error: los numeros deben ser enteros (maximo 15 digitos)" << endl;
        return;
    }
    long long num1 = (long long)a1; // paso a entero grande
    long long num2 = (long long)a2;

    int len1 = 0, len2 = 0;
    long long numero = num1;
    do // para el 0
    {
        len1++;
        numero = numero / 10;
    } while (numero != 0);
    numero = num2;
    do
    {
        len2++;
        numero = numero / 10;
    } while (numero != 0);
    if (len1 != len2)
    {
        cout << "Los numeros deben tener el mismo largo" << endl;
        return;
    }

    // La lista de salida empieza vacia (por si el objeto ya se habia usado).
    while (!ListaVacia())
        BorrarInicio();
    lista L1, L2;
    numero = num1;
    do
    {
        L1.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);
    numero = num2;
    do
    {
        L2.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);

    //imprimir numeros originales y listas iniciales
    cout << "Numero 1 original: " << num1 << endl;
    cout << "Numero 2 original: " << num2 << endl;
    cout << "Lista 1 inicial: ";
    L1.Mostrar();
    cout << "Lista 2 inicial: ";
    L2.Mostrar();

    pnodo aux; //el unico puntero auxiliar
    int paso, pos, k, d;
    for (paso = 0; paso < 2 * len1; paso++)
    {
        if (paso < len1)
            pos = paso + 1; // ida
        else
            pos = 2 * len1 - paso; // vuelta

        // se llega al digito. aux empieza en la lista que toca y avanza pos-1
        if (paso % 2 == 0)
            aux = L1.primero;
        else
            aux = L2.primero;
        for (k = 1; k < pos; k++)
            aux = aux->siguiente;
        d = aux->valor; //digito leido

        if (paso % 2 == 0)
            InsertarFinal(101);
        else
            InsertarFinal(-202);
        InsertarFinal(d + 1);// S
        InsertarFinal(d);// E
        InsertarFinal((d + 1) + d - (d - 1));// S+E-A (se guarda calculado)
        InsertarFinal(d - 1);// A
        if (paso % 2 == 0)
            InsertarFinal(-101);
        else
            InsertarFinal(202);
    }
    cout << "Lista nueva: ";
    Mostrar();
}

//  Ejercicio 2 - DOS
//  Punteros usados: 1 (aux)
void lista::DOS(double x)
{
    //validaciones: abs, entero, maximo 15 digitos, largo multiplo de 5
    double ax = abs(x);
    if (ax > 999999999999999.0 || ax != (long long)ax)
    {
        cout << "Error: el numero debe ser entero (maximo 15 digitos)" << endl;
        return;
    }
    long long num = (long long)ax; //paso a entero

    int len = 0; //largo del numero
    long long numero = num;
    do
    {
        len++;
        numero = numero / 10;
    } while (numero != 0);
    if (len % 5 != 0)
    {
        cout << "El largo " << len << " no es multiplo de 5" << endl;
        return;
    }

    // La lista de salida empieza vacia.
    while (!ListaVacia())
        BorrarInicio();
    lista Datos;
    numero = num;
    do
    {
        Datos.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);

    cout << "Numero original: " << num << endl;

    pnodo aux;//puntero auxiliar
    int bloques = len / 5;//cantidad de listas de 5 digitos
    int b, j, k, v, centro, pot; //b-bloque,j-posicion dentro del bloque

    //pasada 1 - imprimir las listas iniciales
    aux = Datos.primero;
    for (b = 1; b <= bloques; b++)
    {
        cout << "L" << b << " inicial: ";
        for (j = 0; j < 5; j++)
        {
            cout << aux->valor << "->";
            aux = aux->siguiente;
        }
        cout << endl;
    }

    //pasada 2 - modificar cada bloque y guardarlo en this
    aux = Datos.primero;
    for (b = 1; b <= bloques; b++)
    {
        centro = aux->siguiente->siguiente->valor;
        for (j = 1; j <= 5; j++)
        {
            v = aux->valor;
            if (b % 2 == 1) //lista que suma y multiplica
            {
                if (j == 3)
                    InsertarFinal(centro * centro);
                else
                    InsertarFinal(v + centro);
            }
            else //lista que resta y eleva
            {
                if (j == 3)
                {
                    pot = 1; //centro^centro con un ciclo
                    for (k = 0; k < centro; k++)
                        pot = pot * centro;
                    InsertarFinal(pot); //si centro = 0, queda 1
                }
                else
                    InsertarFinal(v - centro);
            }
            aux = aux->siguiente; //siguiente digito del bloque
        }
    }

    //pasada 3 - imprimir las listas finales (salida = this)
    aux = primero;
    for (b = 1; b <= bloques; b++)
    {
        cout << "L" << b << " nueva: ";
        for (j = 0; j < 5; j++)
        {
            cout << aux->valor << "->";
            aux = aux->siguiente;
        }
        cout << endl;
    }
}

//  Ejercicio 3 - TRES
//  Punteros usados: 1 (aux)
void lista::TRES()
{
    //Validacion - la lista debe ser de largo impar
    //m = largo de la lista( si es 0 (vacia) o par no sirve)l
    int m = largoLista();
    if (m % 2 == 0)
    {
        cout << "La lista debe tener un tamano impar" << endl;
        return;
    }
    cout << "Lista original: ";
    Mostrar();
    cout << "Tamano = " << m << " -> se realizan " << m << " pasadas" << endl;
    lista ListaNueva; //lista de salida
    pnodo aux;        //puntero auxiliar
    int pasada, pos, k, a, b, c;
    for (pasada = 0; pasada < m; pasada++)
    {
        // a-elemento de la posicion de la pasada.
        pos = pasada;
        aux = primero;
        for (k = 0; k < pos; k++)
            aux = aux->siguiente;
        a = aux->valor;

        // b-salto de suma - 2 posiciones adelante (es circular)
        pos = (pasada + 2) % m;
        aux = primero;
        for (k = 0; k < pos; k++)
            aux = aux->siguiente;
        b = aux->valor;

        // c-salto de resta - 4 posiciones adelante (tmb circular)
        pos = (pasada + 4) % m;
        aux = primero;
        for (k = 0; k < pos; k++)
            aux = aux->siguiente;
        c = aux->valor;

        // sublista de la pasada(patron, valor calculado, patron)
        if (pasada % 2 == 0)
            ListaNueva.InsertarFinal(101);
        else
            ListaNueva.InsertarFinal(-202);
        ListaNueva.InsertarFinal(a + b - c);
        if (pasada % 2 == 0)
            ListaNueva.InsertarFinal(-101);
        else
            ListaNueva.InsertarFinal(202);
    }

    cout << "Lista salida: ";
    ListaNueva.Mostrar();
}

//  Ejercicio 4 - CUATRO
//  Punteros usados: 1 (aux)
void lista::CUATRO(double x1, double x2, double x3)
{
    double a1 = abs(x1);
    double a2 = abs(x2);
    double a3 = abs(x3);
    if (a1 > 999999999999999.0 || a2 > 999999999999999.0 || a3 > 999999999999999.0 ||
        a1 != (long long)a1 || a2 != (long long)a2 || a3 != (long long)a3)
    {
        cout << "Los numeros deben ser enteros (maximo 15 digitos)" << endl;
        return;
    }
    long long n1 = (long long)a1; //paso a entero
    long long n2 = (long long)a2;
    long long n3 = (long long)a3;

    int len1 = 0, len2 = 0, len3 = 0;
    long long numero = n1;
    do
    {
        len1++;
        numero = numero / 10;
    } while (numero != 0);
    numero = n2;
    do
    {
        len2++;
        numero = numero / 10;
    } while (numero != 0);
    numero = n3;
    do
    {
        len3++;
        numero = numero / 10;
    } while (numero != 0);
    if (len1 != len2 || len2 != len3)
    {
        cout << "LOs tres numeros deben tener el mismo largo" << endl;
        return;
    }
    if (len1 % 2 == 0 || len1 < 3)
    {
        cout << "El largo debe ser impar y de al menos 3 digitos" << endl;
        return;
    }

    //La lista de salida empieza vacia.
    while (!ListaVacia())
        BorrarInicio();

    lista L1, L2, L3;//lista de digitos por numero,los numeros no se tocan
    numero = n1;
    do
    {
        L1.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);
    numero = n2;
    do
    {
        L2.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);
    numero = n3;
    do
    {
        L3.InsertarInicio((int)(numero % 10));
        numero = numero / 10;
    } while (numero != 0);

    cout << "Numero 1 original: " << n1 << endl;
    cout << "Numero 2 original: " << n2 << endl;
    cout << "Numero 3 original: " << n3 << endl;

    pnodo aux;
    int n = len1; //largo comun impar
    int i, j, s, k, pos, a, b, centro, c1, c2, c3;

    //centros, el centro esta en la posicion (n+1)/2 de cada numeri
    aux = L1.primero;
    for (k = 1; k < (n + 1) / 2; k++)
        aux = aux->siguiente;
    c1 = aux->valor;
    aux = L2.primero;
    for (k = 1; k < (n + 1) / 2; k++)
        aux = aux->siguiente;
    c2 = aux->valor;
    aux = L3.primero;
    for (k = 1; k < (n + 1) / 2; k++)
        aux = aux->siguiente;
    c3 = aux->valor;

    //construir ListaNueva
    for (i = 1; i <= n / 2; i++)
    {
        j = n + 1 - i;
        for (s = 0; s < 4; s++)
        {
            //a-de que lista se lee y en que posicion
            if (s == 0)
                aux = L3.primero;
            else if (s == 1)
                aux = L1.primero;
            else
                aux = L2.primero;
            if (s == 3)
                pos = j;
            else
                pos = i;
            for (k = 1; k < pos; k++)
                aux = aux->siguiente;
            a = aux->valor;

            //b- en s=0 y s=1 es el otro extremo del par (posicion j)
            //en s=2 y s=3 es el centro del numero 2
            if (s == 0 || s == 1)
            {
                if (s == 0)
                    aux = L3.primero;
                else
                    aux = L1.primero;
                for (k = 1; k < j; k++)
                    aux = aux->siguiente;
                b = aux->valor;
            }
            else
                b = c2;

            //el centro de la sublista alterna entre c1 y c3
            if (s % 2 == 0)
                centro = c1;
            else
                centro = c3;

            InsertarFinal(101);
            InsertarFinal(centro);
            InsertarFinal(a);
            InsertarFinal(b);
            InsertarFinal(10); //patron final 010, un int no guarda el 0 inicial
        }
    }

    //salida es igual que mostrar, pero el patron 10 se ve como 010
    cout << "Lista salida: ";
    aux = primero;
    while (aux != NULL)
    {
        if (aux->valor == 10)
            cout << "010-> ";
        else
            cout << aux->valor << "->";
        aux = aux->siguiente;
    }
    cout << endl;
}

int main()
{
    int op, m, i, v;
    double x1, x2, x3;
    do
    {
        cout << endl;
        cout << "1 PARCIAL - PARTE 1" << endl;
        cout << "1. UNO (dos numeros del mismo largo)" << endl;
        cout << "2. DOS (numero con largo multiplo de 5)" << endl;
        cout << "3. TRES (lista de largo impar)" << endl;
        cout << "4. CUATRO (tres numeros de largo impar)" << endl;
        cout << "5. Ejemplos de la profe" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 1:
        {
            cout << "Numero 1: ";
            cin >> x1;
            cout << "Numero 2: ";
            cin >> x2;
            lista Salida;
            Salida.UNO(x1, x2);
            break;
        }
        case 2:
        {
            cout << "Numero: ";
            cin >> x1;
            lista Salida;
            Salida.DOS(x1);
            break;
        }
        case 3:
        {
            cout << "Cantidad de elementos de la lista: ";
            cin >> m;
            lista Original;
            for (i = 1; i <= m; i++)
            {
                cout << "Elemento " << i << ": ";
                cin >> v;
                Original.InsertarFinal(v);
            }
            Original.TRES();
            break;
        }
        case 4:
        {
            cout << "Numero 1: ";
            cin >> x1;
            cout << "Numero 2: ";
            cin >> x2;
            cout << "Numero 3: ";
            cin >> x3;
            lista Salida;
            Salida.CUATRO(x1, x2, x3);
            break;
        }
        case 5:
        {
            lista S1, S2, S3, S5, S6, Orig;
            cout << "UNO: 612345 y 107895" << endl;
            S1.UNO(612345, 107895);
            cout << endl << "UNO: 5 y 6" << endl;
            S2.UNO(5, 6);
            cout << endl << "DOS: 4567895987" << endl;
            S3.DOS(4567895987.0);
            cout << endl << "TRES: 6 1 5 8 9" << endl;
            Orig.InsertarFinal(6);
            Orig.InsertarFinal(1);
            Orig.InsertarFinal(5);
            Orig.InsertarFinal(8);
            Orig.InsertarFinal(9);
            Orig.TRES();
            cout << endl << "CUATRO: 31235, 89012 y 43576" << endl;
            S5.CUATRO(31235, 89012, 43576);
            cout << endl << "CUATRO: 3123590, 8901285 y 4357623" << endl;
            S6.CUATRO(3123590, 8901285, 4357623);
            break;
        }
        case 0:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion no valida" << endl;
        }
    } while (op != 0);
    return 0;
}