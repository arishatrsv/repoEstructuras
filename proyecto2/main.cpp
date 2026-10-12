#include <iostream>

using namespace std;

int main()
{
    int opcion;
    do
    {
        cout << "\n===== SISTEMA DE GESTION HOSPITALARIA =====" << endl;
        cout << "1. Leer archivos y construir los arboles" << endl;
        cout << "2. Mantenimiento de la base de datos" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
            case 1:
                cout << "\nFalta" << endl;
                break;
            case 2:
                cout << "\nMantenimiento de la base de datos" << endl;
                cout << "Falta" << endl;
                break;
            case 0:
                cout << "\nSaliendo del sistema..." << endl;
                break;
            default:
                cout << "\nOpcion invalida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);
    return 0;
}