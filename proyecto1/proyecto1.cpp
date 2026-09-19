// Creado por: Arina Tarasova y Hilary Aguilar
// Proyecto Programado #1 - Estructuras de Datos

#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //permite separar los campos de cada linea

using namespace std;

class NodoPais //lista simple
{
public:
    int codPais;
    string nombre;
    NodoPais* siguiente;

    NodoPais(int codigo, string nombrePais)
    {
        codPais = codigo;
        nombre = nombrePais;
        siguiente = NULL;
    }
};

class NodoCiudad //lista circular
{
public:
    int codPais;
    int codCiudad;
    string nombre;
    NodoCiudad* siguiente;

    NodoCiudad(int codigoPais, int codigoCiudad, string nombreCiudad)
    {
        codPais = codigoPais;
        codCiudad = codigoCiudad;
        nombre = nombreCiudad;
        siguiente = NULL;
    }
};

class NodoPaciente //hashing
{
public:
    int idPaciente;
    string nombre;
    string fechaNacimiento;
    string telefono;
    int codPais;
    int codCiudad;
    string correo;
    NodoPaciente* siguiente;

    NodoPaciente(int id, string nombrePaciente, string fecha, string tel, int pais, int ciudad, string email)
    {
        idPaciente = id;
        nombre = nombrePaciente;
        fechaNacimiento = fecha;
        telefono = tel;
        codPais = pais;
        codCiudad = ciudad;
        correo = email;
        siguiente = NULL;
    }
};

class NodoMedico //hashing
{
public:
    int idMedico;
    string nombre;
    string telefono;
    string correo;
    int idEspecialidad;
    NodoMedico* siguiente;

    NodoMedico(int id, string nombreMedico, string tel, string email, int especialidad)
    {
        idMedico = id;
        nombre = nombreMedico;
        telefono = tel;
        correo = email;
        idEspecialidad = especialidad;
        siguiente = NULL;
    }
};

class NodoEspecialidad //lista doble circular
{
public:
    int idEspecialidad;
    string nombre;
    string descripcion;
    NodoEspecialidad* anterior;
    NodoEspecialidad* siguiente;

    NodoEspecialidad(int id, string nombreEspecialidad, string desc)
    {
        idEspecialidad = id;
        nombre = nombreEspecialidad;
        descripcion = desc;
        anterior = NULL;
        siguiente = NULL;
    }
};

class NodoCita //lista doble
{
public:
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;
    int estado;
    NodoCita* anterior;
    NodoCita* siguiente;

    NodoCita(int id, int paciente, int medico, int especialidad, string fechaCita, string horaCita, string motivoCita, int estadoCita)
    {
        idCita = id;
        idPaciente = paciente;
        idMedico = medico;
        idEspecialidad = especialidad;
        fecha = fechaCita;
        hora = horaCita;
        motivo = motivoCita;
        estado = estadoCita;
        anterior = NULL;
        siguiente = NULL;
    }
};

class NodoHabitacion //lista doble circular
{
public:
    int idHabitacion;
    int numero;
    int piso;
    int tipo;
    int estado;
    NodoHabitacion* anterior;
    NodoHabitacion* siguiente;

    NodoHabitacion(int id, int numeroHabitacion, int pisoHabitacion, int tipoHabitacion, int estadoHabitacion)
    {
        idHabitacion = id;
        numero = numeroHabitacion;
        piso = pisoHabitacion;
        tipo = tipoHabitacion;
        estado = estadoHabitacion;
        anterior = NULL;
        siguiente = NULL;
    }
};

class NodoHospitalizacion //lista doble
{
public:
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    int idMedico;
    string fechaIngreso;
    string fechaSalida;
    string motivo;
    NodoHospitalizacion* anterior;
    NodoHospitalizacion* siguiente;

    NodoHospitalizacion(int id, int paciente, int habitacion, int medico, string ingreso, string salida, string motivoHosp)
    {
        idHospitalizacion = id;
        idPaciente = paciente;
        idHabitacion = habitacion;
        idMedico = medico;
        fechaIngreso = ingreso;
        fechaSalida = salida;
        motivo = motivoHosp;
        anterior = NULL;
        siguiente = NULL;
    }
};

class ListaPais //lista simple de paises
{
private:
    NodoPais* primero;
public:
    ListaPais()
    {
        primero = NULL;
    }
    void insertar(int codPais, string nombre)
    {
        NodoPais* nuevo = new NodoPais(codPais, nombre);

        if (primero == NULL)
        {
            primero = nuevo;
        }
        else
        {
            NodoPais* actual = primero;
            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }
    NodoPais* buscar(int codPais)
    {
        NodoPais* actual = primero;
        while (actual != NULL)
            {
                if (actual->codPais == codPais)
                {
                    return actual; // pais encontrado
                }
                actual = actual->siguiente;
            }   
        return NULL; // pais no encontrado
    }

    bool existe(int codPais)
    {
        return buscar(codPais) != NULL; // verifica si existe el pais
    }

    void mostrar(NodoPais* pais){
        if (pais != NULL){
            cout << "Codigo del pais: " << pais->codPais << endl;
            cout << "Nombre: " << pais->nombre << endl;
        }
    }
};

class ListaCiudad // lista circulas de cuidades
{
private:
    NodoCiudad* primero;
public:
    ListaCiudad()
    {
        primero = NULL;
    }
    void insertar(int codPais, int codCiudad, string nombre)
    {
        NodoCiudad* nuevo = new NodoCiudad(codPais, codCiudad, nombre);
        if (primero == NULL)
        {
            primero = nuevo;
            nuevo->siguiente = primero;
        }
        else
        {
            NodoCiudad* actual = primero;
            while (actual->siguiente != primero)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
            nuevo->siguiente = primero;
        }
    }
    NodoCiudad* buscar(int codPais, int codCiudad)
    {
        if (primero == NULL)
        {
            return NULL; // lista vacia
        }
        NodoCiudad* actual = primero;
        do
        {
            if (actual->codPais == codPais && actual->codCiudad == codCiudad)
            {
                return actual; // ciudad encontrada
            }
            actual = actual->siguiente;
        } while (actual != primero);
        return NULL; // ciudad no encontrada
    }
    bool existe(int codPais, int codCiudad)
    {
        return buscar(codPais, codCiudad) != NULL; // verifica si existe la ciudad
    }
    void mostrar(NodoCiudad* ciudad){
        if (ciudad != NULL){
            cout << "Codigo del pais: " << ciudad->codPais << endl;
            cout << "Codigo de la ciudad: " << ciudad->codCiudad << endl;
            cout << "Nombre: " << ciudad->nombre << endl;
        }
    }
    
};

#define TAM_HASH 10 //hashing de pacientes
class TablaPacientes
{
private:
    NodoPaciente* tabla[TAM_HASH];
    int funcionHash(int idPaciente)
    {
        return idPaciente % TAM_HASH;
    }
public:
    TablaPacientes()
    {
        for (int i = 0; i < TAM_HASH; i++)
        {
            tabla[i] = NULL;
        }
    }
    void insertar(int id, string nombre, string fecha, string telefono, int codPais, int codCiudad, string correo)
    {
        int posicion = funcionHash(id);
        NodoPaciente* nuevo = new NodoPaciente(id, nombre, fecha, telefono, codPais, codCiudad, correo);
        if (tabla[posicion] == NULL)
        {
            tabla[posicion] = nuevo;
        }
        else
        {
            NodoPaciente* actual = tabla[posicion];

            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    NodoPaciente* buscar(int idPaciente){
        int posicion = funcionHash(idPaciente);
        NodoPaciente* actual = tabla[posicion];
        while (actual != NULL){
            if (actual->idPaciente == idPaciente)
            {
                return actual; // paciente encontrado
            }
            actual = actual->siguiente;
        }
        return NULL; // paciente no encontrado
    }
    bool existe(int idPaciente)
    {
        return buscar(idPaciente) != NULL;
    }

    void mostrar(NodoPaciente* paciente) {
        if (paciente != NULL) {
            cout << "Id del paciente: " << paciente->idPaciente << endl;
            cout << "Nombre: " << paciente->nombre << endl;
            cout << "Fecha de nacimiento: " << paciente->fechaNacimiento << endl;
            cout << "Telefono: " << paciente->telefono << endl;
            cout << "Codigo de pais: " << paciente->codPais << endl;
            cout << "Codigo de ciudad: " << paciente->codCiudad << endl;
            cout << "Correo: " << paciente->correo << endl;
        }
    }

};

class TablaMedicos //hashing de medicos
{
private:
    NodoMedico* tabla[TAM_HASH];
    int funcionHash(int idMedico)
    {
        return idMedico % TAM_HASH;
    }
public:
    TablaMedicos()
    {
        for (int i = 0; i < TAM_HASH; i++)
        {
            tabla[i] = NULL;
        }
    }
    void insertar(int id, string nombre, string telefono, string correo, int especialidad)
    {
        int posicion = funcionHash(id);
        NodoMedico* nuevo = new NodoMedico(id, nombre, telefono, correo, especialidad);
        if (tabla[posicion] == NULL)
        {
            tabla[posicion] = nuevo;
        }
        else{
            NodoMedico* actual = tabla[posicion];
            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
        }
    }

    NodoMedico* buscar(int idMedico) {
        int posicion = funcionHash(idMedico);
        NodoMedico* actual = tabla[posicion]; //posicion en la tabla
        while (actual != NULL) {
            if (actual->idMedico == idMedico) {
                return actual; //medico encontrado
            }
            actual = actual->siguiente;
        }
        return NULL; //medico no encontrado
    }
    bool existe(int idMedico){
        return buscar(idMedico) != NULL;
    }

    void mostrar(NodoMedico* medico) {
        if (medico != NULL) {
            cout << "Id del medico: " << medico->idMedico << endl;
            cout << "Nombre: " << medico->nombre << endl;
            cout << "Telefono: " << medico->telefono << endl;
            cout << "Correo: " << medico->correo << endl;
            cout << "Id de especialidad: " << medico->idEspecialidad << endl;
        }
    }
};

class ListaEspecialidad //lista doble circular de especialidades
{
private:
    NodoEspecialidad* primero;
public:
    ListaEspecialidad()
    {
        primero = NULL;
    }
    void insertar(int id, string nombre, string descripcion)
    {
        NodoEspecialidad* nuevo = new NodoEspecialidad(id, nombre, descripcion);
        if (primero == NULL)
        {
            primero = nuevo;
            nuevo->siguiente = primero;
            nuevo->anterior = primero;
        }
        else
        {
            NodoEspecialidad* ultimo = primero->anterior;
            nuevo->siguiente = primero;
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            primero->anterior = nuevo;
        }
    }
    NodoEspecialidad* buscar(int idEspecialidad)
    {
        if (primero == NULL)
        {
            return NULL; // lista vacia
        }
        NodoEspecialidad* actual = primero;
        do{
            if (actual->idEspecialidad == idEspecialidad){
                return actual; // especialidad encontrada
            }
            actual = actual->siguiente;
        } while (actual != primero);
        return NULL; // especialidad no encontrada
    }
    bool existe(int idEspecialidad){
        return buscar(idEspecialidad) != NULL;
    }
    void mostrar(NodoEspecialidad* especialidad) {
        if (especialidad != NULL) {
            cout << "Id de especialidad: " << especialidad->idEspecialidad << endl;
            cout << "Nombre: " << especialidad->nombre << endl;
            cout << "Descripcion: " << especialidad->descripcion << endl;
        }
    }
};

class ListaCita //lista doble de citas
{
private:
    NodoCita* primero;
    NodoCita* ultimo;
public:
    ListaCita()
    {
        primero = NULL;
        ultimo = NULL;
    }
    void insertar(int id, int paciente, int medico, int especialidad, string fecha, string hora, string motivo, int estado)
    {
        NodoCita* nuevo = new NodoCita(id, paciente, medico, especialidad, fecha, hora, motivo, estado);

        if (primero == NULL)
        {
            primero = nuevo;
            ultimo = nuevo;
        }
        else
        {
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            ultimo = nuevo;
        }
    }
    NodoCita* buscar(int idCita) {
        NodoCita* actual = primero;
        while (actual != NULL) {
            if (actual->idCita == idCita) {
                return actual; //cita encontrada
            }
            actual = actual->siguiente;
        }
        return NULL; //cita no encontrada
    }
    bool existe(int idCita) {
        return buscar(idCita) != NULL;
    }
    void mostrar(NodoCita* cita) {
        if (cita != NULL) {
            cout << "Id de la cita: " << cita->idCita << endl;
            cout << "Id del paciente: " << cita->idPaciente << endl;
            cout << "Id del medico: " << cita->idMedico << endl;
            cout << "Id de especialidad: " << cita->idEspecialidad << endl;
            cout << "Fecha: " << cita->fecha << endl;
            cout << "Hora: " << cita->hora << endl;
            cout << "Motivo: " << cita->motivo << endl;
            cout << "Estado: " << cita->estado << endl;
        }
    }
};

class ListaHabitacion // lista doble circular de habitaciones
{
private:
    NodoHabitacion* primero;
public:
    ListaHabitacion()
    {
        primero = NULL;
    }
    void insertar(int id, int numero, int piso, int tipo, int estado)
    {
        NodoHabitacion* nuevo = new NodoHabitacion(id, numero, piso, tipo, estado);
        if (primero == NULL)
        {
            primero = nuevo;
            nuevo->siguiente = primero;
            nuevo->anterior = primero;
        }
        else
        {
            NodoHabitacion* ultimo = primero->anterior;
            nuevo->siguiente = primero;
            nuevo->anterior = ultimo;
            ultimo->siguiente = nuevo;
            primero->anterior = nuevo;
        }
    }
    NodoHabitacion* buscar(int idHabitacion) {
        if (primero == NULL) {
            return NULL; //lista vacia
        }
        NodoHabitacion* actual = primero;

        do {
            if (actual->idHabitacion == idHabitacion) {
                return actual; //habitacion encontrada
            }
            actual = actual->siguiente;
        } while (actual != primero);
        return NULL; //habitacion no encontrada
    }
    bool existe(int idHabitacion) {
        return buscar(idHabitacion) != NULL;
    }

    void mostrar(NodoHabitacion* habitacion) {
        if (habitacion != NULL) {
            cout << "Id de habitacion: " << habitacion->idHabitacion << endl;
            cout << "Numero: " << habitacion->numero << endl;
            cout << "Piso: " << habitacion->piso << endl;
            cout << "Tipo: " << habitacion->tipo << endl;
            cout << "Estado: " << habitacion->estado << endl;
        }
    }
};

class ListaHospitalizacion //lista doble de hospitalizaciones
{
private:
    NodoHospitalizacion* primero;
    NodoHospitalizacion* ultimo;
public:
    ListaHospitalizacion()
    {
        primero = NULL;
        ultimo = NULL;
    }
    void insertar(int id, int paciente, int habitacion, int medico, string ingreso, string salida, string motivo)
    {
        NodoHospitalizacion* nuevo = new NodoHospitalizacion(id, paciente, habitacion, medico, ingreso, salida, motivo);
        if (primero == NULL)
        {
            primero = nuevo;
            ultimo = nuevo;
        }
        else
        {
            ultimo->siguiente = nuevo;
            nuevo->anterior = ultimo;
            ultimo = nuevo;
        }
    }
    NodoHospitalizacion* buscar(int idHospitalizacion)
    {
        NodoHospitalizacion* actual = primero;
        while (actual != NULL) {
            if (actual->idHospitalizacion == idHospitalizacion) {
                return actual; // hospitalizacion encontrada
            }
            actual = actual->siguiente;
        }
        return NULL; // hospitalizacion no encontrada
    }
    bool existe(int idHospitalizacion){
        return buscar(idHospitalizacion) != NULL;
    }

    void mostrar(NodoHospitalizacion* hospitalizacion) {
        if (hospitalizacion != NULL) {
            cout << "Id de hospitalizacion: " << hospitalizacion->idHospitalizacion << endl;
            cout << "Id del paciente: " << hospitalizacion->idPaciente << endl;
            cout << "Id de habitacion: " << hospitalizacion->idHabitacion << endl;
            cout << "Id del medico: " << hospitalizacion->idMedico << endl;
            cout << "Fecha de ingreso: " << hospitalizacion->fechaIngreso << endl;
            cout << "Fecha de salida: " << hospitalizacion->fechaSalida << endl;
            cout << "Motivo: " << hospitalizacion->motivo << endl;
        }
    }
};
//objetos globales
ListaPais listaPaises;
ListaCiudad listaCiudades;
TablaPacientes tablaPacientes;
TablaMedicos tablaMedicos;
ListaEspecialidad listaEspecialidades;
ListaCita listaCitas;
ListaHabitacion listaHabitaciones;
ListaHospitalizacion listaHospitalizaciones;

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

void cargarPaises()
    {
        ifstream archivo("Paises.txt");
        if (!archivo)
        {
            cout << "Error al abrir Paises.txt" << endl;
            return;
        }
        string linea;
        while (getline(archivo, linea))
        {
            int pos = linea.find(';'); //obtiene la posición del ';'
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
    ifstream archivo("Ciudades.txt");
    if (!archivo)
    {
        cout << "Error al abrir Ciudades.txt" << endl;
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
    ifstream archivo("Especialidades.txt");
    if (!archivo)
    {
        cout << "Error al abrir Especialidades.txt" << endl;
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
    ifstream archivo("Pacientes.txt");
    if (!archivo)
    {
        cout << "Error al abrir Pacientes.txt" << endl;
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
    ifstream archivo("Medicos.txt");
    if (!archivo)
    {
        cout << "Error al abrir Medicos.txt" << endl;
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
    ifstream archivo("Habitaciones.txt");
    if (!archivo)
    {
        cout << "Error al abrir Habitaciones.txt" << endl;
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
    ifstream archivo("Citas.txt");
    if (!archivo)
    {
        cout << "Error al abrir Citas.txt" << endl;
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
    ifstream archivo("Hospitalizaciones.txt");
    if (!archivo)
    {
        cout << "Error al abrir Hospitalizaciones.txt" << endl;
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

//----------Parte Insertar--------
void insertarPais()
{
    int codigo;
    string nombre;
    cout << "Codigo del pais: ";
    cin >> codigo; //pedimos datos
    cin.ignore(); //ignora el enter pendiente
    cout << "Nombre: ";
    getline(cin, nombre); //
    if (listaPaises.existe(codigo)) //revisamos que no este repetido
    {
        cout << "El pais ya existe" << endl;
    }
    else
    {
        listaPaises.insertar(codigo, nombre);
        cout << "Pais insertado correctamente" << endl;
    }
}

void insertarCiudad()
{
    int codPais;
    int codCiudad;
    string nombre;
    cout << "Codigo del pais: ";
    cin >> codPais;
    if (!listaPaises.existe(codPais))
    {
        cout << "El pais no existe" << endl;
        return;
    }
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    if (listaCiudades.existe(codPais, codCiudad))
    {
        cout << "La ciudad ya existe" << endl;
    }
    else
    {
        listaCiudades.insertar(codPais, codCiudad, nombre);
        cout << "Ciudad insertada correctamente" << endl;
    }
}

void insertarEspecialidad()
{
    int id;
    string nombre;
    string descripcion;
    cout << "Id de especialidad: ";
    cin >> id;
    cin.ignore();
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    if (listaEspecialidades.existe(id))
    {
        cout << "La especialidad ya existe" << endl;
    }
    else
    {
        listaEspecialidades.insertar(id, nombre, descripcion);
        cout << "Especialidad insertada correctamente" << endl;
    }
}

void insertarPaciente()
{
    int id;
    string nombre;
    string fecha;
    string telefono;
    int codPais;
    int codCiudad;
    string correo;
    cout << "Id del paciente: ";
    cin >> id;
    cin.ignore();
    if (tablaPacientes.existe(id))
    {
        cout << "El paciente ya existe" << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Fecha de nacimiento: ";
    getline(cin, fecha);
    if (!fechaValida(fecha))
    {
        cout << "La fecha no tiene un formato valido." << endl;
        return;
    }
    cout << "Telefono: ";
    getline(cin, telefono);
    cout << "Codigo del pais: ";
    cin >> codPais;
    if (!listaPaises.existe(codPais))
    {
        cout << "El pais no existe" << endl;
        return;
    }
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    cin.ignore();
    if (!listaCiudades.existe(codPais, codCiudad))
    {
        cout << "La ciudad no existe" << endl;
        return;
    }
    cout << "Correo: ";
    getline(cin, correo);

    tablaPacientes.insertar(id, nombre, fecha, telefono, codPais, codCiudad, correo);
    cout << "Paciente insertado correctamente" << endl;
}

void insertarMedico()
{
    int id;
    string nombre;
    string telefono;
    string correo;
    int especialidad;
    cout << "Id del medico: ";
    cin >> id;
    cin.ignore();
    if (tablaMedicos.existe(id))
    {
        cout << "El medico ya existe" << endl;
        return;
    }
    cout << "Nombre: ";
    getline(cin, nombre);
    cout << "Telefono: ";
    getline(cin, telefono);
    cout << "Correo: ";
    getline(cin, correo);
    cout << "Id de especialidad: ";
    cin >> especialidad;
    if (!listaEspecialidades.existe(especialidad))
    {
        cout << "La especialidad no existe" << endl;
        return;
    }
    tablaMedicos.insertar(id, nombre, telefono, correo, especialidad);
    cout << "Medico insertado correctamente" << endl;
}

void insertarCita(){
    int idCita;
    int idPaciente;
    int idMedico;
    int idEspecialidad;
    string fecha;
    string hora;
    string motivo;
    int estado;

    cout << "Digite el Id de la cita: ";
    cin >> idCita;
    if (listaCitas.existe(idCita)){ // Valida que el Id de la cita no este repetido
        cout << "La cita ya existe." << endl;
        return;
    }

    cout << "Digite el Id del paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente)){ // Validar que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }

    cout << "Digite el Id del medico: ";
    cin >> idMedico;
    if (!tablaMedicos.existe(idMedico)){ // Validar que el medico exista
        cout << "El medico no existe." << endl;
        return;
    }
    cout << "Digite el Id de la especialidad: ";
    cin >> idEspecialidad;
    if (!listaEspecialidades.existe(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cin.ignore();
    cout << "Digite la fecha: ";
    getline(cin, fecha);
    if (!fechaValida(fecha))
    {
        cout << "La fecha no tiene un formato valido." << endl;
        return;
    }
    cout << "Digite la hora: ";
    getline(cin, hora);
    if (!horaValida(hora))
    {
        cout << "La hora no es valida." << endl;
        return;
    }
    cout << "Digite el motivo: ";
    getline(cin, motivo);
    cout << "Digite el estado: ";
    cin>>estado;

    listaCitas.insertar(idCita,idPaciente,idMedico,idEspecialidad,fecha,hora,motivo,estado);//Se crea el nodo
    cout << "Cita insertada correctamente." << endl;
}

void insertarHabitacion() {
    int idHabitacion;
    int numero;
    int piso;
    int tipo;
    int estado;

    cout << "Digite el Id de la habitacion: ";
    cin >> idHabitacion;

    if (listaHabitaciones.existe(idHabitacion)) { // valida que idhabitacion no este repetido
        cout << "La habitacion ya existe." << endl;
        return;
    }
    cout << "Digite el numero de la habitacion: ";
    cin >> numero;
    cout << "Digite el piso: ";
    cin >> piso;
    cin.ignore();
    cout << "Digite el tipo de habitacion: ";
    cin>>tipo;
    cout << "Digite el estado de la habitacion: ";
    cin>>estado;

    listaHabitaciones.insertar(idHabitacion, numero, piso, tipo, estado);
    cout << "Habitación insertada correctamente" << endl;
}

void insertarHospitalizacion() {
    int idHospitalizacion;
    int idPaciente;
    int idHabitacion;
    int idMedico;
    string fechaIngreso;
    string fechaSalida;
    string motivo;

    cout << "Digite el Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    if (listaHospitalizaciones.existe(idHospitalizacion)) { // Validar que el Id de la hospitalizacion no este repetido
        cout << "La hospitalizacion ya existe." << endl;
        return;
    }

    cout << "Id del Paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente)) { // Validar que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }

    cout << "Digite el Id de la habitacion: ";
    cin >> idHabitacion;
    if (!listaHabitaciones.existe(idHabitacion)) { // Validar que la habitacion exista
        cout << "La habitacion no existe." << endl;
        return;

    }

    cout<< "Digite el Id del medico: ";
    cin >> idMedico;
    if (!tablaMedicos.existe(idMedico))
    {
        cout << "El medico no existe." << endl;
        return;
    }
    cin.ignore();
    cout<< "Digite la fecha de ingreso: ";
    getline(cin, fechaIngreso);
    if (!fechaValida(fechaIngreso))
    {
        cout << "La fecha de ingreso no tiene un formato valido." << endl;
        return;
    }
    cout << "Digite la fecha de salida: ";
    getline(cin, fechaSalida);
    if (!fechaValida(fechaSalida))
    {
        cout << "La fecha de salida no tiene un formato valido." << endl;
        return;
    }
    if (fechaSalida < fechaIngreso)
    {
        cout << "La fecha de salida no puede ser anterior a la fecha de ingreso." << endl;
        return;
    }
    cout << "Digite el motivo: ";
    getline(cin, motivo);

    listaHospitalizaciones.insertar(idHospitalizacion, idPaciente, idHabitacion, idMedico, fechaIngreso, fechaSalida, motivo);
    cout << "Hospitalización insertada correctamente." << endl;

}

//------------Parte Búsqueda----------------
void buscarPais() {
    int codPais;
    cout << "Digite el código del pais: ";
    cin >> codPais;

    NodoPais* paisEncontrado = listaPaises.buscar(codPais);
    if (paisEncontrado != NULL) {
        listaPaises.mostrar(paisEncontrado);
    }else {
        cout << "El pais no existe." << endl;
    }
}

void buscarCiudad() {
    int codPais;
    int codCiudad;

    cout << "Digite el código del pais: ";
    cin >> codPais;
    if (!listaPaises.existe(codPais)){ // Primero validar que el pais exista
        cout << "El pais no existe" << endl;
        return;
    }

    cout << "Digite el codigo de la ciudad: ";
    cin >> codCiudad;

    NodoCiudad* ciudadEncontrado = listaCiudades.buscar(codPais, codCiudad); //ciudad va relacionada con pais
    if (ciudadEncontrado != NULL) {
        listaCiudades.mostrar(ciudadEncontrado);
    }
    else {
        cout << "La ciudad no existe en ese pais." << endl;
    }
}

void buscarPaciente() {
    int codPais;
    int codCiudad;
    int idPaciente;

    cout << "Digite el codigo del pais: ";
    cin >> codPais;
    cout << "Digite el codigo de la ciudad: ";
    cin >> codCiudad;

    if (!listaCiudades.existe(codPais, codCiudad)) { //valida que la ciudad exista
        cout << "La ciudad no existe en ese pais." << endl;
        return;
    }

    cout << "Digite el Id del paciente: ";
    cin >> idPaciente;
    NodoPaciente* pacienteEncontrado = tablaPacientes.buscar(idPaciente);
    if (pacienteEncontrado != NULL) {
        if (pacienteEncontrado->codPais == codPais && //Comparamos los datos guardados con los que se ingresaron
            pacienteEncontrado->codCiudad == codCiudad) 
        {
            tablaPacientes.mostrar(pacienteEncontrado);
        }
        else {
            cout << "El paciente no pertenece a esa ciudad." << endl;
        }
    }
    else {
        cout << "El paciente no existe." << endl;
    }
}

void buscarMedico() {
    int idEspecialidad;
    int idMedico;

    cout << "Digite el Id de la especialidad: ";
    cin >> idEspecialidad;
    if (!listaEspecialidades.existe(idEspecialidad)) { // Validar que la especialidad exista
        cout << "La especialidad no existe." << endl;
        return;
    }

    cout << "Digite el Id del medico: ";
    cin >> idMedico;
    NodoMedico* medicoEncontrado = tablaMedicos.buscar(idMedico);
    if (medicoEncontrado != NULL) {
        if (medicoEncontrado->idEspecialidad == idEspecialidad) { // Verificar que el medico pertenezca a la especialidad indicada
            tablaMedicos.mostrar(medicoEncontrado);
        }
        else {
            cout << "El medico no pertenece a esa especialidad." << endl;
        }
    }
    else {
        cout << "El medico no existe." << endl;
    }
}

void buscarEspecialidad() {
    int idEspecialidad;

    cout << "Id de la Especialidad: ";
    cin >> idEspecialidad;
    if (listaEspecialidades.existe(idEspecialidad)) {
        NodoEspecialidad* especialidadEncontrada = listaEspecialidades.buscar(idEspecialidad);
        listaEspecialidades.mostrar(especialidadEncontrada);
    }else{
        cout << "La especialidad no existe." << endl;
    }
}

void buscarCita() {
    int idPaciente;
    int idMedico;
    int idCita;

    cout << "Digite el Id del paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente)) { // Validar que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }

    cout << "Digite el Id del medico: ";
    cin >> idMedico;
    if (!tablaMedicos.existe(idMedico)) { // Validar que el medico exista
        cout << "El medico no existe." << endl;
        return;
    }

    cout << "Digite el Id de la cita: ";
    cin >> idCita;
    NodoCita* citaEncontrada = listaCitas.buscar(idCita);
    if (citaEncontrada != NULL) {
        if (citaEncontrada->idPaciente == idPaciente &&
            citaEncontrada->idMedico == idMedico) // Verificar que la cita corresponda al paciente y medico
        {
            listaCitas.mostrar(citaEncontrada);
        }
        else {
            cout << "La cita no corresponde al paciente y medico indicados." << endl;
        }
    }
    else {
        cout << "La cita no existe." << endl;
    }
}

void buscarHabitacion() {
    int idHabitacion;

    cout << "Id de la Habitacion: ";
    cin >> idHabitacion;
    if (listaHabitaciones.existe(idHabitacion)) {
        NodoHabitacion* habitacionEncontrada = listaHabitaciones.buscar(idHabitacion);
        listaHabitaciones.mostrar(habitacionEncontrada);
    }
    else {
        cout << "La habitacion no existe." << endl;
    }
}

void buscarHospitalizacionMenu(){
    int idPaciente;
    int idHabitacion;
    int idHospitalizacion;

    cout << "Digite el Id del paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente)){ // Validar que el paciente exista
        cout << "El paciente no existe." << endl;
        return;
    }

    cout << "Digite el Id de la habitacion: ";
    cin >> idHabitacion;
    if (!listaHabitaciones.existe(idHabitacion)){ // Validar que la habitacion exista
        cout << "La habitacion no existe." << endl;
        return;
    }

    cout << "Digite el Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    NodoHospitalizacion* hospitalizacionEncontrada = listaHospitalizaciones.buscar(idHospitalizacion);

    if (hospitalizacionEncontrada != NULL){
        if (hospitalizacionEncontrada->idPaciente == idPaciente &&    // Verificar que la hospitalizacion corresponda
            hospitalizacionEncontrada->idHabitacion == idHabitacion)  // al paciente y habitacion indicados
        {
            listaHospitalizaciones.mostrar(hospitalizacionEncontrada);
        }
        else{
            cout << "La hospitalizacion no corresponde al paciente y habitacion indicados." << endl;
        }
    }
    else{
        cout << "La hospitalizacion no existe." << endl;
    }
}

void modificarPais()
{
    int codPais;
    string nuevoNombre;
    cout << "Digite el codigo del pais: ";
    cin >> codPais;
    cin.ignore();
    NodoPais* pais = listaPaises.buscar(codPais);
    if (pais == NULL)
    {
        cout << "El pais no existe." << endl;
        return;
    }
    cout << "Nuevo nombre: ";
    getline(cin, nuevoNombre);
    pais->nombre = nuevoNombre; //actualiza el nombre
    cout << "Pais modificado correctamente." << endl;
}

void modificarCiudad()
{
    int codPais;
    int codCiudad;
    string nuevoNombre;
    cout << "Codigo del pais: ";
    cin >> codPais;
    if (!listaPaises.existe(codPais))
    {
        cout << "El pais no existe." << endl;
        return;
    }
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    NodoCiudad* ciudad = listaCiudades.buscar(codPais, codCiudad);

    if (ciudad == NULL)
    {
        cout << "La ciudad no existe." << endl;
        return;
    }
    cin.ignore();
    cout << "Nuevo nombre de la ciudad: ";
    getline(cin, nuevoNombre);
    ciudad->nombre = nuevoNombre; //actualiza nombre
    cout << "Ciudad modificada correctamente." << endl;
}

void modificarPaciente()
{
    int codPais;
    int codCiudad;
    int idPaciente;
    string telefono;
    string correo;
    cout << "Codigo del pais: ";
    cin >> codPais;
    cout << "Codigo de la ciudad: ";
    cin >> codCiudad;
    if (!listaCiudades.existe(codPais, codCiudad))
    {
        cout << "La ciudad no existe." << endl;
        return;
    }
    cout << "Id del paciente: ";
    cin >> idPaciente;
    NodoPaciente* paciente = tablaPacientes.buscar(idPaciente);
    if (paciente == NULL)
    {
        cout << "El paciente no existe." << endl;
        return;
    }
    if (paciente->codPais != codPais || paciente->codCiudad != codCiudad)
    {
        cout << "El paciente no pertenece a esa ciudad." << endl;
        return;
    }
    cin.ignore();
    cout << "Paciente modificado correctamente." << endl;
}

void modificarMedico()
{
    int idEspecialidad;
    int idMedico;
    string telefono;
    string correo;
    cout << "Id de especialidad: ";
    cin >> idEspecialidad;
    if (!listaEspecialidades.existe(idEspecialidad))
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    NodoMedico* medico = tablaMedicos.buscar(idMedico);
    if (medico == NULL)
    {
        cout << "El medico no existe." << endl;
        return;
    }
    if (medico->idEspecialidad != idEspecialidad)
    {
        cout << "El medico no pertenece a esa especialidad." << endl;
        return;
    }
    cin.ignore();
    cout << "Nuevo telefono: ";
    getline(cin, telefono);
    cout << "Nuevo correo: ";
    getline(cin, correo);
    medico->telefono = telefono; //actualiza telefono
    medico->correo = correo; //actualiza correo
    cout << "Medico modificado correctamente." << endl;
}
void modificarEspecialidad()
{
    int idEspecialidad;
    string descripcion;
    cout << "Id de especialidad: ";
    cin >> idEspecialidad;
    cin.ignore();
    NodoEspecialidad* especialidad = listaEspecialidades.buscar(idEspecialidad);
    if (especialidad == NULL)
    {
        cout << "La especialidad no existe." << endl;
        return;
    }
    cout << "Nueva descripcion: ";
    getline(cin, descripcion);
    especialidad->descripcion = descripcion; //actualiza descripcion
    cout << "Especialidad modificada correctamente." << endl;
}

void modificarCita()
{
    int idPaciente;
    int idMedico;
    int idCita;
    string motivo;
    int estado;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente))
    {
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id del medico: ";
    cin >> idMedico;
    if (!tablaMedicos.existe(idMedico))
    {
        cout << "El medico no existe." << endl;
        return;
    }
    cout << "Id de la cita: ";
    cin >> idCita;
    NodoCita* cita = listaCitas.buscar(idCita);
    if (cita == NULL)
    {
        cout << "La cita no existe." << endl;
        return;
    }
    if (cita->idPaciente != idPaciente || cita->idMedico != idMedico)
    {
        cout << "Los datos no coinciden." << endl;
        return;
    }
    cin.ignore();
    cout << "Nuevo motivo: ";
    getline(cin, motivo);
    cout << "Nuevo estado: ";
    cin >> estado;
    cita->motivo = motivo; //actualiza motivo
    cita->estado = estado; //actualiza estado
    cout << "Cita modificada correctamente." << endl;
}
void modificarHabitacion()
{
    int idHabitacion;
    int estado;
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    NodoHabitacion* habitacion = listaHabitaciones.buscar(idHabitacion);
    if (habitacion == NULL)
    {
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Nuevo estado: ";
    cin >> estado;
    habitacion->estado = estado; //actualiza estado
    cout << "Habitacion modificada correctamente." << endl;
}

void modificarHospitalizacion()
{
    int idPaciente;
    int idHabitacion;
    int idHospitalizacion;
    string motivo;
    cout << "Id del paciente: ";
    cin >> idPaciente;
    if (!tablaPacientes.existe(idPaciente))
    {
        cout << "El paciente no existe." << endl;
        return;
    }
    cout << "Id de la habitacion: ";
    cin >> idHabitacion;
    if (!listaHabitaciones.existe(idHabitacion))
    {
        cout << "La habitacion no existe." << endl;
        return;
    }
    cout << "Id de la hospitalizacion: ";
    cin >> idHospitalizacion;
    NodoHospitalizacion* hospitalizacion = listaHospitalizaciones.buscar(idHospitalizacion);
    if (hospitalizacion == NULL)
    {
        cout << "La hospitalizacion no existe." << endl;
        return;
    }
    if (hospitalizacion->idPaciente != idPaciente || hospitalizacion->idHabitacion != idHabitacion)
    {
        cout << "Los datos no coinciden." << endl;
        return;
    }
    cin.ignore();
    cout << "Nuevo motivo: ";
    getline(cin, motivo);
    hospitalizacion->motivo = motivo; //actualiza motivo
    cout << "Hospitalizacion modificada correctamente." << endl;
}

//----------Menú------------
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

void menuBusquedas(){
    int opcion;
    do{
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
    do
    {
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

void menuMantenimiento() {
    int opcion;
    do {
        cout << "\n===== MANTENIMIENTO DE LA BASE DE DATOS =====" << endl;
        cout << "1. Inserciones" << endl;
        cout << "2. Busquedas" << endl;
        cout << "3. Modificaciones" << endl;
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

