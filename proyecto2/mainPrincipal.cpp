//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #2 - Estructuras de Datos

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "crud.h"

using namespace std;


bool fechaValida(string fecha)
{
    if (fecha.length() != 10)
    {
        return false;
    }
    if (fecha[4] != '-' || fecha[7] != '-')
    {
        return false;
    }
    for (int i = 0; i < 10; i++)
    {
        if (i != 4 && i != 7 && (fecha[i] < '0' || fecha[i] > '9'))
        {
            return false;
        }
    }
    return true;
}

bool horaValida(string hora)
{
    if (hora.length() != 5)
    {
        return false;
    }
    if (hora[2] != ':')
    {
        return false;
    }
    for (int i = 0; i < 5; i++)
    {
        if (i != 2 && (hora[i] < '0' || hora[i] > '9'))
        {
            return false;
        }
    }
    int horas = stoi(hora.substr(0, 2));
    int minutos = stoi(hora.substr(3, 2));
    if (horas < 0 || horas > 23 || minutos < 0 || minutos > 59)
    {
        return false;
    }
    return true;
}

//------ARCHIVOS---------
void cargarPaises(){
    ifstream archivo("Paises.csv");
    if (!archivo){
        cout << "Error al abrir Paises.csv" << endl;
        return;
    }
    string linea;
    string codigo, nombre;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, codigo, ';');
        getline(datos, nombre);
        int codPais = stoi(codigo);
        if (!arbolPaises.Buscarvalor(codPais)){
            arbolPaises.InsertaNodo(codPais, 0, nombre);
        }
    }
    archivo.close();
    cout << "Paises cargados correctamente." << endl;
}

void cargarCiudades(){
    ifstream archivo("Ciudades.csv");
    if (!archivo){
        cout << "Error al abrir Ciudades.csv" << endl;
        return;
    }
    string linea;
    string codPais, codCiudad, nombre;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)){
        stringstream datos(linea);
        getline(datos, codPais, ';');
        codPais = stoi(codPais);
        getline(datos, codCiudad, ';');
        codCiudad = stoi(codCiudad);
        getline(datos, nombre);

        // Verifica que el pais exista y que la ciudad no este repetida.
        if (arbolPaises.Buscarvalor(codPais) &&!arbolCiudades.Buscarvalor(codPais, codCiudad))
        {
            arbolCiudades.InsertaNodo(codPais, codCiudad, nombre);
        }
    }
    archivo.close();
    cout << "Ciudades cargadas correctamente" << endl;
}


void cargarTratamientos(){
    ifstream archivo("Tratamiento.csv");
    if (!archivo) {
        cout << "Error al abrir Tratamiento.csv" << endl;
        return;
    }

    string linea;
    string idTratamiento, nombre, descripcion, textoCosto;
    getline(archivo, linea); // Saltar encabezado
    while (getline(archivo, linea)) {
        stringstream datos(linea);
        getline(datos, idTratamiento, ';');
        getline(datos, nombre, ';');
        getline(datos, descripcion, ';');
        getline(datos, textoCosto);

        int id = stoi(idTratamiento);
        double costo = stod(textoCosto);
        if (!arbolTratamientos.Buscar(id)) {
            arbolTratamientos.Insertar(id, nombre, descripcion, costo);
        }
    }
    archivo.close();
    cout << "Tratamientos cargados correctamente." << endl;
}


void cargarArchivos()
{
    cargarPaises();
    cargarCiudades();
    /*cargarEspecialidades();
    cargarPacientes();
    cargarMedicos();
    cargarHabitaciones();
    cargarCitas();
    cargarHospitalizaciones();*/
	cargarTratamientos();
}

//---------MENÚ-------
void menuInserciones() {
    int opcion;
    do {
        cout << "\n===== INSERCIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            insertarPais();
            break;
        case 2:
            insertarCiudad();
            break;
        /*case 3:
            insertarPaciente();
            break;
        case 4:
            insertarMedico();
            break;
        case 5:
            insertarEspecialidad();
            break;
        case 6:
            insertarCita();
            break;
        case 7:
            insertarHabitacion();
            break;
        case 8:
            insertarHospitalizacion();
            break;*/
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuBusquedas() {
    int opcion;
    do {
        cout << "\n===== BUSQUEDAS =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            buscarPais();
            break;
        case 2:
            buscarCiudad();
            break;
        /*case 3:
            buscarPaciente();
            break;
        case 4:
            buscarMedico();
            break;
        case 5:
            buscarEspecialidad();
            break;
        case 6:
            buscarCita();
            break;
        case 7:
            buscarHabitacion();
            break;
        case 8:
            buscarHospitalizacionMenu();
            break;*/
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

/*void menuModificaciones()
{
    int opcion;
    do {
        cout << "\n===== MODIFICACIONES =====" << endl;
        cout << "1. Pais" << endl;
        cout << "2. Ciudad" << endl;
        cout << "3. Paciente" << endl;
        cout << "4. Medico" << endl;
        cout << "5. Especialidad" << endl;
        cout << "6. Cita" << endl;
        cout << "7. Habitacion" << endl;
        cout << "8. Hospitalizacion" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            modificarPais();
            break;
        case 2:
            modificarCiudad();
            break;
        case 3:
            modificarPaciente();
            break;
        case 4:
            modificarMedico();
            break;
        case 5:
            modificarEspecialidad();
            break;
        case 6:
            modificarCita();
            break;
        case 7:
            modificarHabitacion();
            break;
        case 8:
            modificarHospitalizacion();
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}*/

void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n===== MANTENIMIENTO DE LA BASE DE DATOS =====" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busquedas" << endl;
        cout << "3. Modificaciones" << endl;
        cout << "4. Reportes" << endl;
        cout << "0. Regresar" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            menuInserciones();
            break;
        case 2:
            menuBusquedas();
            break;
        /*case 3:
            menuModificaciones();
            break;
        case 4:
            menuReportes();
            break;*/
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

int main() {
    int opcion;
    do {
        cout << "\n===== SISTEMA DE GESTION HOSPITALARIA =====" << endl;
        cout << "1. Leer archivos y construir los arboles" << endl;
        cout << "2. Mantenimiento de la base de datos" << endl;
        cout << "3. Mostrar paises ordenados" << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cargarArchivos();
            break;
        case 2:
            menuMantenimiento();
            break;
        case 3:
            arbolPaises.InordenR();
            break;
        case 0:
            cout << "Programa finalizado." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
    return 0;
}