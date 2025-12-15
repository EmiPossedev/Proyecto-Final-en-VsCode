#include "Persona.h"
#include "Kinesiologo.h"
#include "Paciente.h"
#include "Registros.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Este struct sirve para guardar en archivo binario (usando char)
struct RegistroTurno
{
    int codigoTurno;
    int dniPaciente;
    int dniKinesiologo;
    char fecha[15];          // Formato DD/MM/AAAA
    char hora[10];           // Formato HH:MM
    char estadoDelTurno[20]; // Programado, Cancelado, Completado
    char observaciones[200];
};

// Y este struct turno me deja trabajar los datos en memoria
struct Turno
{
    int codigoTurno;
    int dniPaciente;
    int dniKinesiologo;
    string fecha;          // Formato DD/MM/AAAA
    string hora;           // Formato HH:MM
    string estadoDelTurno; // Programado, Cancelado, Completado
    string observaciones;
};

/// Definición de la clase Consultorio
class Consultorio
{

private:
    vector<Kinesiologo *> kinesiologos;
    vector<Paciente *> pacientes;
    vector<Turno> turnos;

public:
    // Métodos para agregar y obtener kinesiologos y pacientes
    void agregarKinesiologo(Kinesiologo *kinesiologo);
    vector<Kinesiologo *> getKinesiologos() const;
    void agregarPaciente(Paciente *paciente);
    vector<Paciente *> getPacientes() const;

    // Métodos para turnos
    void agregarTurno(const Turno &turno);
    vector<RegistroTurno> getTurnos() const;

    // Métodos de búsqueda de pacientes
    Paciente *buscarPacientePorNombre(const string &nombre);
    Paciente *buscarPacientePorApellido(const string &apellido);

    // Métodos de eliminación
    void eliminarPacientePorDni(int dni);
    void eliminarKinesiologoPorDni(int dni);

    // Métodos con archivos binarios

    // Guardar datos en archivos binarios
    void guardarPacientes(const string &nombreArchivo);
    void guardarKinesiologos(const string &nombreArchivo);
    void guardarTurnos(const string &nombreArchivo);

    // Cargar datos desde archivos binarios
    void cargarPacientes(const string &nombreArchivo);
    void cargarKinesiologos(const string &nombreArchivo);
    void cargarTurnos(const string &nombreArchivo);

    // Guardar/cargar todo de una vez
    void guardarTodosDatos();
    void cargarTodosDatos();
};