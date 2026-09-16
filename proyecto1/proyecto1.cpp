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
        codCiudad = stoi(campo);
        getline(datos, campo, ';');
        codPais = stoi(campo);
        getline(datos, correo);
        if (listaCiudades.existe(codPais, codCiudad) && !tablaPacientes.existe(id)) //valida ciudad y paciente
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
        if (tablaPacientes.existe(paciente) && tablaMedicos.existe(medico) && !listaCitas.existe(id)) //valida paciente, medico y cita
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
        if (tablaPacientes.existe(paciente) && listaHabitaciones.existe(habitacion) && !listaHospitalizaciones.existe(id)) //valida paciente, habitacion y hospitalizacion
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