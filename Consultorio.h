#ifndef CONSULTORIO_H
#define CONSULTORIO_H
#include "Fecha.h"
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
    Fecha fecha;          // Usamos el struct Fecha definido en Fecha.h
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
    Fecha fecha; 
    string hora;  // Formato HH:MM
    bool requiereCamilla;
    bool requiereGimnasio;
    string estadoDelTurno; // Programado, Cancelado, Completado
    string observaciones;

    // Necesitamos esto para que ordenarTurnos() sepa qué hacer.
    // Como ahora 'fecha' ya sabe compararse sola.
    bool operator<(const Turno &b) const {
        if (fecha != b.fecha) {
            return fecha < b.fecha; // Usa la lógica de tu Fecha.h
        }
        return hora < b.hora; // Si es el mismo día, desempata por hora
    }

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
    // Antes: const string &fecha -> Ahora: const Fecha &fecha
    void cancelarTurno(const string &nombrePaciente, const Fecha &fecha, const string &hora);
    
    // Aquí cambiamos fechaVieja y fechaNueva a tipo Fecha
    void reprogramarTurno(const string &nombrePaciente, const Fecha &fechaVieja, const string &horaVieja, const Fecha &fechaNueva, const string &horaNueva);
    
    void ordenarTurnos(); 
    
    // Búsqueda por fecha ahora recibe un objeto Fecha
    vector<Turno> getTurnosPorFecha(const Fecha &fecha);
    
    vector<Turno> getTurnosPorHora(const string &hora);
    vector<Turno> getTurnosDeKinesiologo(const string &nombreKinesio);

    // Métodos de verificación (También actualizados a Fecha)
    bool verificarDisponibilidadKinesiologo(const string &kinesiologo, const Fecha &fecha, const string &hora);
    bool verificarDisponibilidadCamilla(const Fecha &fecha, const string &hora);
    bool verificarDisponibilidadGimnasio(const Fecha &fecha, const string &ho
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

#endif