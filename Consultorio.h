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
    char nombreKinesio[50];
    char nombrePaciente[50];
    char fecha[15];          // Formato DD/MM/AAAA
    char hora[10];           // Formato HH:MM
    char estadoDelTurno[20]; // Programado, Cancelado, Completado
    bool requiereCamilla;
    bool requiereGimnasio;
    char observaciones[200];
};

// Y este struct turno me deja trabajar los datos en memoria
struct Turno
{
    string nombreKinesiologo;
    string nombrePaciente;
    string fecha; // Formato DD/MM/AAAA
    string hora;  // Formato HH:MM
    bool requiereCamilla;
    bool requiereGimnasio;
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
    int cantCamillas = 5;
    int capacidadGimnasio = 5;

public:

    // Método constructor y método destructor
    Consultorio(){}
    ~Consultorio();
    // Métodos para agregar y obtener kinesiologos y pacientes
    void agregarKinesiologo(Kinesiologo *kinesiologo);
    vector<Kinesiologo *> getKinesiologos() const;
    void agregarPaciente(Paciente *paciente);
    vector<Paciente *> getPacientes() const;

    // Métodos para la gestión de los turnos
    vector<Turno> getTurnos() const;
    void agregarTurno(const Turno &turno);
    void cancelarTurno(const string &nombrePaciente, const string &fecha, const string &hora);
    void reprogramarTurno(const string &nombrePaciente, const string &fechaVieja, const string &horaVieja, const string &fechaNueva, const string &horaNueva);
    vector<Turno> getTurnosPorFecha(const string &fecha);
    vector<Turno> getTurnosPorHora(const string &hora);
    vector<Turno> getTurnosDeKinesiologo(const string &nombreKinesio);

    // Métodos para verificar la disponibilidad de los recursos para poder agendar el turno
    bool verificarDisponibilidadKinesiologo(const string &kinesiologo, const string &fecha, const string &hora);
    bool verificarDisponibilidadCamilla(const string &fecha, const string &hora);
    bool verificarDisponibilidadGimnasio(const string &fecha, const string &hora);

    // Métodos de búsqueda de pacientes
    Paciente *buscarPacientePorNombre(const string &nombre);
    Paciente *buscarPacientePorApellido(const string &apellido);

    // Métodos de eliminación
    void eliminarPacientePorDni(int dni);
    void eliminarKinesiologoPorDni(int dni);

    // Método de alerta al kinesiologo de que le tienen que pagar
    vector<Paciente*> getPacientesConPagoPendiente() const;

    /// Métodos con archivos binarios

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