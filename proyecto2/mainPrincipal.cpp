//Elaborado por : Hilary Aguilar y Arina Tarasova
//Proyecto Programado #2 - Estructuras de Datos

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //permite separar los campos de cada linea
#include "hpdf.h"

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
void cargarPaises()
{
    ifstream archivo("Paises.csv");
    if (!archivo)
    {
        cout << "Error al abrir Paises.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        int pos = linea.find(';'); //obtiene la posiciÃ³n del ';'
        int codigo = stoi(linea.substr(0, pos)); //extrae el texto antes del ';', lo convierte a entero
        string nombre = linea.substr(pos + 1); //extrae el texto despues del ';'
        if (!listaPaises.existe(codigo)) //evita repetidos
        {
            listaPaises.insertar(codigo, nombre);
        }
    }
    archivo.close();
    cout << "Paises cargados correctamente" << endl;
}

void cargarCiudades()
{
    ifstream archivo("Ciudades.csv");
    if (!archivo)
    {
        cout << "Error al abrir Ciudades.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int codPais;
        int codCiudad;
        string nombre;
        getline(datos, campo, ';');
        codPais = stoi(campo);
        getline(datos, campo, ';');
        codCiudad = stoi(campo);
        getline(datos, nombre);

        if (listaPaises.existe(codPais) && !listaCiudades.existe(codPais, codCiudad)) //valida pais y ciudad
        {
            listaCiudades.insertar(codPais, codCiudad, nombre);
        }
    }
    archivo.close();
    cout << "Ciudades cargadas correctamente" << endl;
}

void cargarEspecialidades()
{
    ifstream archivo("Especialidades.csv");
    if (!archivo)
    {
        cout << "Error al abrir Especialidades.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        string nombre;
        string descripcion;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, nombre, ';');
        getline(datos, descripcion);
        if (!listaEspecialidades.existe(id)) //evita especialidades repetidas
        {
            listaEspecialidades.insertar(id, nombre, descripcion);
        }
    }
    archivo.close();
    cout << "Especialidades cargadas correctamente" << endl;
}

void cargarPacientes()
{
    ifstream archivo("Pacientes.csv");
    if (!archivo)
    {
        cout << "Error al abrir Pacientes.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        string nombre;
        string fecha;
        string telefono;
        int codPais;
        int codCiudad;
        string correo;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, nombre, ';');
        getline(datos, fecha, ';');
        getline(datos, telefono, ';');
        getline(datos, campo, ';');
        codPais = stoi(campo);
        getline(datos, campo, ';');
        codCiudad = stoi(campo);
        getline(datos, correo);
        if (listaCiudades.existe(codPais, codCiudad) &&
            !tablaPacientes.existe(id) &&
            fechaValida(fecha))
        {
            tablaPacientes.insertar(id, nombre, fecha, telefono, codPais, codCiudad, correo);
        }
    }
    archivo.close();
    cout << "Pacientes cargados correctamente" << endl;
}

void cargarMedicos()
{
    ifstream archivo("Medicos.csv");
    if (!archivo)
    {
        cout << "Error al abrir Medicos.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        string nombre;
        string telefono;
        string correo;
        int especialidad;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, nombre, ';');
        getline(datos, telefono, ';');
        getline(datos, correo, ';');
        getline(datos, campo);
        especialidad = stoi(campo);
        if (listaEspecialidades.existe(especialidad) && !tablaMedicos.existe(id)) //valida especialidad y medico
        {
            tablaMedicos.insertar(id, nombre, telefono, correo, especialidad);
        }
    }
    archivo.close();
    cout << "Medicos cargados correctamente" << endl;
}

void cargarHabitaciones()
{
    ifstream archivo("Habitaciones.csv");
    if (!archivo)
    {
        cout << "Error al abrir Habitaciones.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        int numero;
        int piso;
        int tipo;
        int estado;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, campo, ';');
        numero = stoi(campo);
        getline(datos, campo, ';');
        piso = stoi(campo);
        getline(datos, campo, ';');
        tipo = stoi(campo);
        getline(datos, campo);
        estado = stoi(campo);
        if (!listaHabitaciones.existe(id)) //evita habitaciones repetidas
        {
            listaHabitaciones.insertar(id, numero, piso, tipo, estado);
        }
    }
    archivo.close();
    cout << "Habitaciones cargadas correctamente" << endl;
}

void cargarCitas()
{
    ifstream archivo("Citas.csv");
    if (!archivo)
    {
        cout << "Error al abrir Citas.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        int paciente;
        int medico;
        int especialidad;
        string fecha;
        string hora;
        string motivo;
        int estado;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, campo, ';');
        paciente = stoi(campo);
        getline(datos, campo, ';');
        medico = stoi(campo);
        getline(datos, campo, ';');
        especialidad = stoi(campo);
        getline(datos, fecha, ';');
        getline(datos, hora, ';');
        getline(datos, motivo, ';');
        getline(datos, campo);
        estado = stoi(campo);
        if (tablaPacientes.existe(paciente) && tablaMedicos.existe(medico) && !listaCitas.existe(id) && listaEspecialidades.existe(especialidad)) //valida paciente, medico y cita
        {
            listaCitas.insertar(id, paciente, medico, especialidad, fecha, hora, motivo, estado);
        }
    }
    archivo.close();
    cout << "Citas cargadas correctamente" << endl;
}

void cargarHospitalizaciones()
{
    ifstream archivo("Hospitalizaciones.csv");
    if (!archivo)
    {
        cout << "Error al abrir Hospitalizaciones.csv" << endl;
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        stringstream datos(linea);
        string campo;
        int id;
        int paciente;
        int habitacion;
        int medico;
        string ingreso;
        string salida;
        string motivo;
        getline(datos, campo, ';');
        id = stoi(campo);
        getline(datos, campo, ';');
        paciente = stoi(campo);
        getline(datos, campo, ';');
        habitacion = stoi(campo);
        getline(datos, campo, ';');
        medico = stoi(campo);
        getline(datos, ingreso, ';');
        getline(datos, salida, ';');
        getline(datos, motivo);
        if (tablaPacientes.existe(paciente) &&
            listaHabitaciones.existe(habitacion) &&
            tablaMedicos.existe(medico) &&
            !listaHospitalizaciones.existe(id) &&
            fechaValida(ingreso) &&
            fechaValida(salida) &&
            salida >= ingreso)
        {
            listaHospitalizaciones.insertar(id, paciente, habitacion, medico, ingreso, salida, motivo);
        }
    }
    archivo.close();
    cout << "Hospitalizaciones cargadas correctamente" << endl;
}

void cargarArchivos()
{
    cargarPaises();
    cargarCiudades();
    cargarEspecialidades();
    cargarPacientes();
    cargarMedicos();
    cargarHabitaciones();
    cargarCitas();
    cargarHospitalizaciones();
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
        case 3:
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
            break;
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
        case 3:
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
            break;
        case 0:
            cout << "Regresando..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuModificaciones()
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
}

void menuReportes()
{
    int opcion;
    do
    {
        cout << "\n===== REPORTES =====" << endl;
        cout << "1. Paises" << endl;
        cout << "2. Ciudades de un pais" << endl;
        cout << "3. Especialidades" << endl;
        cout << "4. Habitaciones disponibles" << endl;
        cout << "5. Habitaciones ocupadas" << endl;
        cout << "6. Hospitalizaciones" << endl;
        cout << "7. Hospitalizaciones de un medico" << endl;
        cout << "8. Medicos" << endl;
        cout << "9. Medicos de una especialidad" << endl;
        cout << "10. Citas por fecha" << endl;
        cout << "11. Citas por especialidad" << endl;
        cout << "12. Citas de un medico" << endl;
        cout << "0. Regresar" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            reportePaises();
            break;
        case 2:
            reporteCiudades();
            break;
        case 3:
            reporteEspecialidades();
            break;
        case 4:
            reporteHabitacionesDisponibles();
            break;
        case 5:
            reporteHabitacionesOcupadas();
            break;
        case 6:
            reporteHospitalizaciones();
            break;
        case 7:
            reporteHospitalizacionesPorMedico();
            break;
        case 8:
            reporteMedicos();
            break;
        case 9:
            reporteMedicosPorEspecialidad();
            break;
        case 10:
            reporteCitasPorFecha();
            break;
        case 11:
            reporteCitasPorEspecialidad();
            break;
        case 12:
            reporteCitasPorMedico();
            break;
        case 0:
            break;
        default:
            cout << "Opcion no valida." << endl;
        }
    } while (opcion != 0);
}

void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n===== MANTENIMIENTO DE LA BASE DE DATOS =====" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busquedas" << endl;
        cout << "3. Eliminaciones" << endl;
        cout << "4. Modificaciones" << endl;
        cout << "5. Reportes" << endl;
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
        case 3:
            menuModificaciones();
            break;
        case 4:
            menuReportes();
            break;
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
        cout << "\n========== MENU PRINCIPAL ==========" << endl;
        std::cout << "LibHaru funciona correctamente." << std::endl;
        cout << "1. Leer Archivos" << endl;
        cout << "2. Mantenimiento de la Base de Datos" << endl;
        cout << "0. Salir" << endl;
        cout << "Digite una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cargarArchivos();
            break;
        case 2:
            menuMantenimiento();
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