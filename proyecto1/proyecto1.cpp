// Creado por: Arina Tarasova y Hilary Aguilar
// Proyecto Programado #1 - Estructuras de Datos

#include <iostream>
#include <fstream>
#include <string>

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
    int codCiudad;
    string correo;
    NodoPaciente* siguiente;

    NodoPaciente(int id, string nombrePaciente, string fecha, string tel, int ciudad, string email)
    {
        idPaciente = id;
        nombre = nombrePaciente;
        fechaNacimiento = fecha;
        telefono = tel;
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
    void insertar(int id, string nombre, string fecha, string telefono, int codCiudad, string correo)
    {
        int posicion = funcionHash(id);
        NodoPaciente* nuevo = new NodoPaciente(id, nombre, fecha, telefono, codCiudad, correo);
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
        else
        {
            NodoMedico* actual = tabla[posicion];
            while (actual->siguiente != NULL)
            {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevo;
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
};
