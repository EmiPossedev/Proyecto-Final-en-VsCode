#ifndef PACIENTE_H
#define PACIENTE_H
#include "Fecha.h"
#include "Persona.h"
#include <string>
using namespace std;

// Registro para guardar en archivo binario (incluye datos de Persona + Paciente)
struct RegistroPaciente
{
    // Datos heredados de Persona
    char nombre[50];
    char apellido[50];
    int telefono;
    // Datos propios de Paciente
    Fecha fechaDeInicio;
    char diagnostico[100];
    char obraSocial[50];
    int cantSesionesTotales;
    int cantSesionesRealizadas;
    char observaciones[200];
    bool sesionesPagas;
};

class Paciente : public Persona
{
private:
    Fecha fechaDeInicio;
    string diagnostico;
    string obraSocial; // mencionar si tiene o viene en forma particular
    int cantSesionesTotales; // la cantidad de sesiones totales asignadas para el tratamiento
    int cantSesionesRealizadas; // las que se vayan realizando, se van a ir descontando de las totales
    string observaciones;
    bool sesionesPagas;

public:
    // Métodos para obtener y modificar los datos del paciente(en inglés es más corto)
    // Obtener y modificar la fecha de inicio del paciente
    Fecha getFechaDeInicio() const;
    void setFechaDeInicio(const Fecha &nuevaFechaInicio);
    // Obtener y modificar el diágnostico del paciente
    string getDiagnostico() const;
    void setDiagnostico(const string &nuevoDiagnostico); 
    // Obtener y modificar la obra social del paciente
    string getObraSocial() const;
    void setObraSocial(const string &nuevaObraSocial);
    // Obtener y modificar las sesiones totales que le corresponden al paciente
    int getCantSesionesTotales() const;
    void setCantSesionesTotales(const int &nuevaCant);
    // Solo un método para saber las sesiones realizadas y no para modificarlas porque
    // esa lógica la manejan otros métodos, si alguien las modifica podría romper la lógica del sistema
    int getCantidadSesionesRealizadas() const;
    void setCantidadSesionesRealizadas(const int &nuevaCant);
    // Obtener y modificar las observaciones del paciente
    string getObservaciones() const;
    void agregarObservaciones(const string &nuevaObservacion);
    void borrarObservaciones();
    // Métodos para las sesiones pagas y pendientes
    bool getSesionesPagas() const;
    void marcarComoPendiente();
    void marcarComoPago();
    
    // Métodos para las cancelación de turnos de los pacientes
    void descontarSesionDelTotal(); // descontar la sesion si se agendó un turno
    void reintegrarSesionRealizada(); // reintegrar la sesion si se canceló el turno
};

#endif