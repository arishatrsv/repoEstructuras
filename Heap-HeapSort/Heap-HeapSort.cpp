// Creado por: Hilary Aguilar y Arina Tarasova

// Inserta una nueva llave en el heap
Siguiente = i;
Padre = Siguiente / 2;
Llave[Siguiente] = NuevaLlave;

while (Siguiente != 1 && Llave[Padre] <= Llave[Siguiente]){
    Auxiliar = Llave[Padre];
    Llave[Padre] = Llave[Siguiente];
    Llave[Siguiente] = Auxiliar;
    // Avanza sobre el árbol
    Siguiente = Padre;
    Padre = Siguiente / 2;
}

// HeapSort
for (Ultima = LargoDelArreglo; Ultima >= 2; Ultima--){
    // Mueve la llave raíz al último lugar
    LlaveAnterior = Llave[Ultima];
    Llave[Ultima] = Llave[1];
    // Ajusta el árbol al tamaño menos 1
    Padre = 1;
    // Busca al mayor de los hijos de la raíz
    if (Ultima - 1 >= 3 && Llave[3] > Llave[2]){
        Hijo = 3;
    }
    else{
        Hijo = 2;
    }
    // Mueve las llaves hacia arriba hasta encontrar
    // el lugar para LlaveAnterior
    while (Hijo <= Ultima - 1 && Llave[Hijo] > LlaveAnterior){
        Llave[Padre] = Llave[Hijo];

        Padre = Hijo;
        Hijo = Padre * 2;
        // Encuentra al mayor de los hijos del padre
        if (Hijo + 1 <= Ultima - 1 &&
            Llave[Hijo + 1] > Llave[Hijo])
        {
            Hijo = Hijo + 1;
        }
    }
    // Coloca la llave anterior en su posición
    Llave[Padre] = LlaveAnterior;
}