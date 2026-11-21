//Tarea Grafos - Estructura de Datos
//Hilary Aguilar y Arina Tarasova

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <string>
using namespace std;

#define MAX 100

class Arista {
public:
    int destino;
    int peso;
    Arista* sig;
    Arista(int d, int p) {
        destino = d;
        peso = p;
        sig = NULL;
    }
};

class Grafo {
public:
    int n;
    string codigo[MAX];
    string nombre[MAX];
    Arista* lista[MAX];

    Grafo() {
        n = 0;
        for (int i = 0; i < MAX; i++) lista[i] = NULL;
    }

    void limpiar() {
        for (int i = 0; i < n; i++) {
            Arista* a = lista[i];
            while (a != NULL) {
                Arista* borrar = a;
                a = a->sig;
                delete borrar;
            }
            lista[i] = NULL;
        }
        n = 0;
    }

    int buscar(const char* cod) {
        for (int i = 0; i < n; i++)
            if (codigo[i] == cod) return i;
        return -1;
    }

    int existeArista(int o, int d) {
        for (Arista* a = lista[o]; a != NULL; a = a->sig)
            if (a->destino == d) return 1;
        return 0;
    }

    void agregarArista(int o, int d, int peso) {
        Arista* nueva = new Arista(d, peso);
        if (lista[o] == NULL) {
            lista[o] = nueva;
        }
        else {
            Arista* a = lista[o];
            while (a->sig != NULL) a = a->sig;
            a->sig = nueva;
        }
    }

    //Ciudades
    void leerCiudades(const char* archCiudades)
    {
        ifstream archivo(archCiudades);
        if (!archivo)
        {
            cout << "Error al abrir " << archCiudades << endl;
            return;
        }
        string linea;
        while (getline(archivo, linea))
        {
            if (linea.size() == 0) continue; //salta lineas en blanco
            int pos = linea.find(';'); //obtiene la posicion del ';'
            string cod = linea.substr(0, pos); //extrae el texto antes del ';'
            string nom = linea.substr(pos + 1); //extrae el texto despues del ';'
            if (buscar(cod.c_str()) == -1) //evita repetidos
            {
                codigo[n] = cod;
                nombre[n] = nom;
                n++;
            }
        }
        archivo.close();
        cout << "Ciudades cargadas correctamente" << endl;
    }

    //Carreteras
    void leerCarreteras(const char* archCarreteras)
    {
        ifstream archivo(archCarreteras);
        if (!archivo)
        {
            cout << "Error al abrir " << archCarreteras << endl;
            return;
        }
        string linea;
        while (getline(archivo, linea))
        {
            int pos1 = linea.find(';'); //posicion del primer ';'
            int pos2 = linea.find(';', pos1 + 1); //posicion del segundo ';'
            string origen = linea.substr(0, pos1);
            string destino;
            int peso = 0;
            if (pos2 == (int)string::npos) //no trae distancia
            {
                destino = linea.substr(pos1 + 1);
            }
            else
            {
                destino = linea.substr(pos1 + 1, pos2 - pos1 - 1);
                peso = atoi(linea.substr(pos2 + 1).c_str());
            }
            int o = buscar(origen.c_str());
            int d = buscar(destino.c_str());
            if (o != -1 && d != -1) //los codigos deben existir
            {
                if (!existeArista(o, d)) agregarArista(o, d, peso);
                if (!existeArista(d, o)) agregarArista(d, o, peso);
            }
        }
        archivo.close();
        cout << "Carreteras cargadas correctamente" << endl;
    }

    void leerArchivos(const char* archCiudades, const char* archCarreteras) {
        limpiar();
        leerCiudades(archCiudades);
        leerCarreteras(archCarreteras);
        cout << archCiudades << " y " << archCarreteras << " leidos correctamente " << endl;
    }
};

class NodoLista {
public:
    int dato;
    NodoLista* sig;
    NodoLista(int d) {
        dato = d;
        sig = NULL;
    }
};

class Cola {
public:
    NodoLista* frente;
    NodoLista* fin;
    Cola() {
        frente = NULL;
        fin = NULL;
    }
    int vacia() { return frente == NULL; }
    void insertar(int d) {
        NodoLista* nuevo = new NodoLista(d);
        if (frente == NULL) frente = nuevo;
        else fin->sig = nuevo;
        fin = nuevo;
    }
    int sacar() {
        NodoLista* borrar = frente;
        int d = borrar->dato;
        frente = frente->sig;
        if (frente == NULL) fin = NULL;
        delete borrar;
        return d;
    }
    void escribir(ofstream& f, Grafo& g) {
        f << "Cola: ";
        for (NodoLista* p = frente; p != NULL; p = p->sig)
            f << g.codigo[p->dato] << " ";
        f << endl;
    }
};

//Cola y Pila (listas enlazadas)
class Pila {
public:
    NodoLista* tope;
    Pila() { tope = NULL; }
    int vacia() { return tope == NULL; }
    void push(int d) {
        NodoLista* nuevo = new NodoLista(d);
        nuevo->sig = tope;
        tope = nuevo;
    }
    int pop() {
        NodoLista* borrar = tope;
        int d = borrar->dato;
        tope = tope->sig;
        delete borrar;
        return d;
    }
    void escribir(ofstream& f, Grafo& g) {
        //se escribe de la base hacia el tope
        int datos[MAX];
        int cant = 0;
        for (NodoLista* p = tope; p != NULL; p = p->sig) datos[cant++] = p->dato;
        f << "Pila (base -> tope): ";
        for (int i = cant - 1; i >= 0; i--) f << g.codigo[datos[i]] << " ";
        f << endl;
    }
};

Grafo g1;  //Ciudades1 - Carreteras1
Grafo g2;  //Ciudades2 - Carreteras2

//Prim
void prim(Grafo& g) {
    char cod[20];
    cout << "Punto de partida: ";
    cin >> cod;
    int ini = g.buscar(cod);
    if (ini == -1) {
        cout << "Codigo no valido o archivos no leidos" << endl;
        return;
    }

    int enW[MAX];
    int W[MAX];
    int cant = 0;
    int costo = 0;
    for (int i = 0; i < g.n; i++) enW[i] = 0;

    ofstream f("AEM_Prim.txt");
    f << "Algoritmo de Prim - Punto de partida: " << g.codigo[ini] << endl;
    f << "Aristas del AEM:" << endl;

    enW[ini] = 1;
    W[cant++] = ini;

    while (cant < g.n) {
        int mejorO = -1, mejorD = -1, mejorP = 0;
        for (int i = 0; i < g.n; i++) {
            if (enW[i]) {
                for (Arista* a = g.lista[i]; a != NULL; a = a->sig) {
                    if (!enW[a->destino] && (mejorO == -1 || a->peso < mejorP)) {
                        mejorO = i;
                        mejorD = a->destino;
                        mejorP = a->peso;
                    }
                }
            }
        }
        if (mejorD == -1) { //grafo no conexo
            f << "El grafo no es conexo, no se puede completar el AEM" << endl;
            break;
        }
        enW[mejorD] = 1;
        W[cant++] = mejorD;
        costo += mejorP;
        f << g.codigo[mejorO] << " - " << g.codigo[mejorD] << " (" << mejorP << ")" << endl;
    }

    f << "W = { ";
    for (int i = 0; i < cant; i++) f << g.codigo[W[i]] << " ";
    f << "}" << endl;
    f << "Costo = " << costo << endl;
    f.close();
    cout << "Prim: AEM y costo (" << costo << ") guardados en AEM_Prim.txt" << endl;
}

//Kruskal
void kruskal(Grafo& g) {
    if (g.n == 0) {
        cout << "Primero debe leer los archivos" << endl;
        return;
    }
    int aO[MAX * MAX], aD[MAX * MAX], aP[MAX * MAX];
    int cantA = 0;

    // se toma cada arista una sola vez
    for (int i = 0; i < g.n; i++)
        for (Arista* a = g.lista[i]; a != NULL; a = a->sig)
            if (i < a->destino) {
                aO[cantA] = i;
                aD[cantA] = a->destino;
                aP[cantA] = a->peso;
                cantA++;
            }

    // se ordenan las aristas de menor a mayor
    for (int i = 0; i < cantA - 1; i++)
        for (int j = 0; j < cantA - 1 - i; j++)
            if (aP[j] > aP[j + 1]) {
                int t;
                t = aO[j]; aO[j] = aO[j + 1]; aO[j + 1] = t;
                t = aD[j]; aD[j] = aD[j + 1]; aD[j + 1] = t;
                t = aP[j]; aP[j] = aP[j + 1]; aP[j + 1] = t;
            }

    int comp[MAX];
    int usada[MAX * MAX]; // 1 si la arista queda en el AEM
    for (int i = 0; i < g.n; i++) comp[i] = i;

    int costo = 0;
    ofstream f("AEM_Kruskal.txt");
    f << "Algoritmo de Kruskal" << endl;
    f << "Aristas ordenadas:" << endl;
    for (int i = 0; i < cantA; i++) {
        f << g.codigo[aO[i]] << g.codigo[aD[i]] << " " << aP[i];
        if (comp[aO[i]] == comp[aD[i]]) {
            f << "  ciclo" << endl;
            usada[i] = 0;
        }
        else {
            int viejo = comp[aD[i]];
            int nuevo = comp[aO[i]];
            for (int k = 0; k < g.n; k++)
                if (comp[k] == viejo) comp[k] = nuevo;
            costo += aP[i];
            usada[i] = 1;
            f << endl;
        }
    }
    f << "Aristas del AEM:" << endl;
    for (int i = 0; i < cantA; i++)
        if (usada[i])
            f << g.codigo[aO[i]] << " - " << g.codigo[aD[i]] << " (" << aP[i] << ")" << endl;
    f << "Costo = " << costo << endl;
    f.close();
    cout << "Kruskal: AEM y costo (" << costo << ") guardados en AEM_Kruskal.txt" << endl;
}

//Dijkstra
void dijkstra(Grafo& g) {
    char cod[20];
    cout << "Punto de partida: ";
    cin >> cod;
    int ini = g.buscar(cod);
    cout << "Punto de llegada: ";
    cin >> cod;
    int fin = g.buscar(cod);
    if (ini == -1 || fin == -1) {
        cout << "Codigo no valido o archivos no leidos" << endl;
        return;
    }

    int resuelto[MAX];
    int orden[MAX];          // nodos resueltos en orden
    int cantRes = 0;
    int dist[MAX];           // distancia total desde el inicio
    int pred[MAX];
    for (int i = 0; i < g.n; i++) {
        resuelto[i] = 0;
        dist[i] = 0;
        pred[i] = -1;
    }

    resuelto[ini] = 1;
    orden[cantRes++] = ini;

    ofstream f("Dijkstra.txt");
    f << "Algoritmo de Dijkstra: " << g.codigo[ini] << " -> " << g.codigo[fin] << endl;
    f << "Nodo resuelto | Nodos no resueltos | Distancia minima | Distancia total | Ultima conexion" << endl;

    while (!resuelto[fin]) {
        int mejorO = -1, mejorD = -1, mejorTotal = 0, mejorPeso = 0;

        for (int k = 0; k < cantRes; k++)
            f << g.codigo[orden[k]] << " ";
        f << "| ";

        for (int k = 0; k < cantRes; k++) {
            int u = orden[k];
            for (Arista* a = g.lista[u]; a != NULL; a = a->sig) {
                if (!resuelto[a->destino]) {
                    int total = dist[u] + a->peso;
                    f << g.codigo[a->destino] << "(" << total << ") ";
                    if (mejorO == -1 || total < mejorTotal) {
                        mejorO = u;
                        mejorD = a->destino;
                        mejorTotal = total;
                        mejorPeso = a->peso;
                    }
                }
            }
        }

        if (mejorD == -1) { //no hay ruta
            f << endl << "No hay ruta de " << g.codigo[ini] << " a " << g.codigo[fin] << endl;
            f.close();
            cout << "Dijkstra: no hay ruta entre esas ciudades" << endl;
            return;
        }
        resuelto[mejorD] = 1;
        orden[cantRes++] = mejorD;
        dist[mejorD] = mejorTotal;
        pred[mejorD] = mejorO;
        f << "| " << mejorPeso << " | " << mejorTotal << " | "
            << g.codigo[mejorO] << "-" << g.codigo[mejorD] << endl;
    }

    int ruta[MAX];
    int cant = 0;
    int v = fin;
    while (v != -1) {
        ruta[cant++] = v;
        v = pred[v];
    }
    f << "Ruta " << g.codigo[ini] << "-" << g.codigo[fin] << ": ";
    for (int i = 0; i < cant; i++) {
        f << g.codigo[ruta[i]];
        if (i < cant - 1) f << " - ";
    }
    f << endl;
    f << "Ordenada = ";
    for (int i = cant - 1; i >= 0; i--) {
        f << g.codigo[ruta[i]];
        if (i > 0) f << " - ";
    }
    f << endl;
    f << "Costo = " << dist[fin] << endl;
    cout << "Dijkstra: ruta menor (costo " << dist[fin] << ") guardada en Dijkstra.txt" << endl;
    f.close();
}

//Puntos de articulación
int num[MAX];
int bajo[MAX];
int padre[MAX];
int preorden[MAX];
int cantPre;
int contador;
int retO[MAX * MAX];
int retD[MAX * MAX];
int cantRet;

void profundidadArt(Grafo& g, int v) {
    contador++;
    num[v] = contador;
    bajo[v] = contador;
    preorden[cantPre++] = v;

    for (Arista* a = g.lista[v]; a != NULL; a = a->sig) {
        int w = a->destino;
        if (num[w] == 0) {
            padre[w] = v;
            profundidadArt(g, w);
            if (bajo[w] < bajo[v]) bajo[v] = bajo[w];
        }
        else if (w != padre[v] && num[w] < num[v]) {
            // arista de retroceso
            retO[cantRet] = v;
            retD[cantRet] = w;
            cantRet++;
            if (num[w] < bajo[v]) bajo[v] = num[w];
        }
    }
}

void puntosArticulacion(Grafo& g) {
    char cod[20];
    cout << "Punto de partida: ";
    cin >> cod;
    int ini = g.buscar(cod);
    if (ini == -1) {
        cout << "Codigo no valido o archivos no leidos" << endl;
        return;
    }

    for (int i = 0; i < g.n; i++) {
        num[i] = 0;
        bajo[i] = 0;
        padre[i] = -1;
    }
    cantPre = 0;
    contador = 0;
    cantRet = 0;

    profundidadArt(g, ini);

    ofstream f("PuntosArticulacion.txt");
    f << "Puntos de Articulacion - Punto de partida: " << g.codigo[ini] << endl;

    f << "Recorrido en preorden: ";
    for (int i = 0; i < cantPre; i++) {
        f << g.codigo[preorden[i]];
        if (i < cantPre - 1) f << " - ";
    }
    f << endl;

    f << "Aristas de retroceso:" << endl;
    for (int i = 0; i < cantRet; i++)
        f << g.codigo[retO[i]] << " -> " << g.codigo[retD[i]] << endl;

    f << "Vertice: Num, Bajo" << endl;
    for (int i = 0; i < cantPre; i++) {
        int v = preorden[i];
        f << g.codigo[v] << ": " << num[v] << ", " << bajo[v] << endl;
    }

    f << "Analisis:" << endl;
    int puntos[MAX];
    int cantPuntos = 0;
    for (int i = 0; i < cantPre; i++) {
        int v = preorden[i];
        int hijos = 0;
        int esPunto = 0;

        if (v == ini) {
            for (Arista* a = g.lista[v]; a != NULL; a = a->sig)
                if (padre[a->destino] == v) hijos++;
            if (hijos >= 2) {
                f << g.codigo[v] << ": raiz con " << hijos << " hijos, Es punto" << endl;
                esPunto = 1;
            }
            else {
                f << g.codigo[v] << ": raiz, no tiene dos o mas hijos, No es punto" << endl;
            }
        }
        else {
            for (Arista* a = g.lista[v]; a != NULL; a = a->sig) {
                int w = a->destino;
                if (padre[w] == v) {
                    hijos++;
                    f << g.codigo[v] << ": hijo " << g.codigo[w] << ", bajo(" << g.codigo[w] << ")="
                        << bajo[w] << " >= num(" << g.codigo[v] << ")=" << num[v] << " ? ";
                    if (bajo[w] >= num[v]) {
                        f << "Si, Es punto" << endl;
                        esPunto = 1;
                    }
                    else {
                        f << "No" << endl;
                    }
                }
            }
            if (hijos == 0)
                f << g.codigo[v] << ": No tiene hijo, No es punto" << endl;
            else if (!esPunto)
                f << g.codigo[v] << ": No es punto" << endl;
        }
        if (esPunto) puntos[cantPuntos++] = v;
    }

    f << "Puntos de Articulacion: ";
    for (int i = 0; i < cantPuntos; i++) f << g.codigo[puntos[i]] << " ";
    f << endl;
    f.close();
    cout << "Puntos de articulacion guardados en PuntosArticulacion.txt" << endl;
}

//Anchura
void anchura(Grafo& g) {
    char cod[20];
    cout << "Punto de partida: ";
    cin >> cod;
    int ini = g.buscar(cod);
    if (ini == -1) {
        cout << "Codigo no valido o archivos no leidos" << endl;
        return;
    }

    int visitado[MAX];
    int ingreso[MAX], salida[MAX];
    int cantIng = 0, cantSal = 0;
    for (int i = 0; i < g.n; i++) visitado[i] = 0;

    Cola c;
    ofstream f("Anchura.txt");
    f << "Recorrido en Anchura - Punto de partida: " << g.codigo[ini] << endl;

    visitado[ini] = 1;
    c.insertar(ini);
    ingreso[cantIng++] = ini;
    f << "Ingresa " << g.codigo[ini] << " - ";
    c.escribir(f, g);

    while (!c.vacia()) {
        int u = c.sacar();
        salida[cantSal++] = u;
        f << "Sale " << g.codigo[u] << " - ";
        c.escribir(f, g);
        for (Arista* a = g.lista[u]; a != NULL; a = a->sig) {
            int w = a->destino;
            if (!visitado[w]) {
                visitado[w] = 1;
                c.insertar(w);
                ingreso[cantIng++] = w;
                f << "Ingresa " << g.codigo[w] << " - ";
                c.escribir(f, g);
            }
        }
    }

    f << "Orden de ingreso: ";
    for (int i = 0; i < cantIng; i++) f << g.codigo[ingreso[i]] << " ";
    f << endl;
    f << "Orden de salida: ";
    for (int i = 0; i < cantSal; i++) f << g.codigo[salida[i]] << " ";
    f << endl;
    f.close();
    cout << "Anchura guardada en Anchura.txt" << endl;
}

//Profundidad
void profundidad(Grafo& g) {
    char cod[20];
    cout << "Punto de partida: ";
    cin >> cod;
    int ini = g.buscar(cod);
    if (ini == -1) {
        cout << "Codigo no valido o archivos no leidos" << endl;
        return;
    }

    int visitado[MAX];
    Arista* actual[MAX];      // proximo vecino por revisar de cada vertice
    int ingreso[MAX], salida[MAX];
    int cantIng = 0, cantSal = 0;
    for (int i = 0; i < g.n; i++) {
        visitado[i] = 0;
        actual[i] = g.lista[i];
    }

    Pila p;
    ofstream f("Profundidad.txt");
    f << "Recorrido en Profundidad - Punto de partida: " << g.codigo[ini] << endl;

    visitado[ini] = 1;
    p.push(ini);
    ingreso[cantIng++] = ini;
    f << "Ingresa " << g.codigo[ini] << " - ";
    p.escribir(f, g);

    while (!p.vacia()) {
        int u = p.tope->dato;
        while (actual[u] != NULL && visitado[actual[u]->destino]) actual[u] = actual[u]->sig;

        if (actual[u] != NULL) {
            int w = actual[u]->destino;
            visitado[w] = 1;
            p.push(w);
            ingreso[cantIng++] = w;
            f << "Ingresa " << g.codigo[w] << " - ";
            p.escribir(f, g);
        }
        else {
            p.pop();
            salida[cantSal++] = u;
            f << "Sale " << g.codigo[u] << " - ";
            p.escribir(f, g);
        }
    }

    f << "Orden de ingreso: ";
    for (int i = 0; i < cantIng; i++) f << g.codigo[ingreso[i]] << " ";
    f << endl;
    f << "Orden de salida: ";
    for (int i = 0; i < cantSal; i++) f << g.codigo[salida[i]] << " ";
    f << endl;
    f.close();
    cout << "Profundidad guardada en Profundidad.txt" << endl;
}

//Menu
int main() {
    int opcion = -1;
    while (opcion != 0) {
        cout << endl;
        cout << "------ MENU ------" << endl;
        cout << "1. Leer Archivos" << endl;
        cout << "2. Prim" << endl;
        cout << "3. Kruskal" << endl;
        cout << "4. Dijkstra" << endl;
        cout << "5. Puntos de Articulacion" << endl;
        cout << "6. Anchura" << endl;
        cout << "7. Profundidad" << endl;
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            g1.leerArchivos("Ciudades1.csv", "Carreteras1.csv");
            g2.leerArchivos("Ciudades2.csv", "Carreteras2.csv");
        }
        else if (opcion == 2) {
            prim(g1);
        }
        else if (opcion == 3) {
            kruskal(g1);
        }
        else if (opcion == 4) {
            dijkstra(g1);
        }
        else if (opcion == 5) {
            puntosArticulacion(g2);
        }
        else if (opcion == 6) {
            anchura(g1);
        }
        else if (opcion == 7) {
            profundidad(g1);
        }
    }
    return 0;
}