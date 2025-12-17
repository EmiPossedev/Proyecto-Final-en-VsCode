/// Includes para la implementación de la clase Consultorio
#include "Consultorio.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream> 

// Método Destructor
Consultorio::~Consultorio()
{
    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        delete kinesiologos[i];
    }

    for (size_t i = 0; i < pacientes.size(); i++)
    {
        delete pacientes[i];
    }
}

/// Métodos Básicos para agregar/modificar datos

// Métodos básicos para kinesiólogos
void Consultorio::agregarKinesiologo(Kinesiologo *kinesiologo)
{
    kinesiologos.push_back(kinesiologo);
}
void Consultorio::eliminarKinesiologo(Kinesiologo *kinesiologo)
{
    delete kinesiologo;
}
vector<Kinesiologo *> Consultorio::getKinesiologos() const
{
    return kinesiologos;
}

// Métodos para pacientes
void Consultorio::agregarPaciente(Paciente *paciente)
{
    pacientes.push_back(paciente);
}

vector<Paciente *> Consultorio::getPacientes() const
{
    return pacientes;
}

// Métodos para turnos
vector<Turno> Consultorio::getTurnos() const
{
    return turnos;
}

void Consultorio::agregarTurno(const Turno &turno)
{
    turnos.push_back(turno);
}

void Consultorio::cancelarTurno(const string &nombrePacienteBuscado, const string &fecha, const string &hora)
{
    for (auto it = turnos.begin(); it != turnos.end(); it++) //tenias auto i, no auto it;
    {
        if (it->nombrePaciente == nombrePacienteBuscado and 
            it->fecha == fecha and // En minúsculas
            it->hora == hora)     // En minúsculas
        {
            turnos.erase(it);
            return; 
        }
    }  
} 


// Verificación 1: Disponibilidad del Kinesiólogo 
bool Consultorio::verificarDisponibilidadKinesiologo(const string &nombreKinesio, const string &fecha, const string &hora)
{
    for (const auto &turno : turnos)
    {
        // Si el kinesiólogo ya tiene turno ese día a esa hora...
        if (turno.nombreKinesiologo == nombreKinesio and turno.fecha == fecha and turno.hora == hora)
        {
            if (turno.estadoDelTurno != "Cancelado") 
            {
                return false; 
            }
        }
    }
    return true; // Está libre
}

// Verificación 2: Disponibilidad de Camillas 
bool Consultorio::verificarDisponibilidadCamilla(const string &fecha, const string &hora)
{
    int camillasOcupadas = 0;

    for (const auto &turno : turnos)
    {
        // Buscamos turnos a la misma hora que usen camilla
        if (turno.fecha == fecha and  turno.hora == hora and turno.requiereCamilla and turno.estadoDelTurno != "Cancelado")
        {
            camillasOcupadas++;
        }
    }

    if (camillasOcupadas < cantCamillas)
    {
        return true; // Hay lugar
    }
    else
    {
        return false; // Todo lleno
    }
}

// Verificación 3: Disponibilidad del Gimnasio 
bool Consultorio::verificarDisponibilidadGimnasio(const string &fecha, const string &hora)
{
    int gimnasioOcupado = 0;

    for (const auto &turno : turnos)
    {
        // Buscamos turnos a la misma hora que usen el gimnasio
        if (turno.fecha == fecha and turno.hora == hora and turno.requiereGimnasio and turno.estadoDelTurno != "Cancelado")
        {
            gimnasioOcupado++;
        }
    }

    // Verificamos límite (capacidadGimnasio está definida en el .h como 5)
    if (gimnasioOcupado < capacidadGimnasio)
    {
        return true; // Hay lugar
    }
    else
    {
        return false; // Todo lleno
    }
}

void Consultorio::reprogramarTurno(const string &nombrePaciente, const string &fechaVieja, const string &horaVieja, const string &fechaNueva, const string &horaNueva)
{
    for (auto &turno : turnos)
    {
        // Buscar el turno que coincida con paciente, fecha vieja y hora vieja
        if (turno.nombrePaciente == nombrePaciente and
            turno.fecha == fechaVieja and
            turno.hora == horaVieja)
        {
           
            // Verificar si el MISMO kinesiólogo está libre en el nuevo horario
            if (!verificarDisponibilidadKinesiologo(turno.nombreKinesiologo, fechaNueva, horaNueva))
            {
                cout << "Error: El kinesiologo " << turno.nombreKinesiologo << " ya tiene un turno a esa hora nueva." << endl;
                return; 
            }

            if (turno.requiereCamilla)
            {
                if (!verificarDisponibilidadCamilla(fechaNueva, horaNueva))
                {
                    cout << "Error: No hay camillas disponibles en el nuevo horario." << endl;
                    return;
                }
            }

            // Verificar recursos (Gimnasio) SOLO si el turno original usaba gimnasio
            if (turno.requiereGimnasio)
            {
                if (!verificarDisponibilidadGimnasio(fechaNueva, horaNueva))
                {
                    cout << "Error: El gimnasio esta lleno en el nuevo horario." << endl;
                    return;
                }
            }
            // Si todas las verificaciones pasan, de 10
            turno.fecha = fechaNueva;
            turno.hora = horaNueva;
            turno.estadoDelTurno = "Reprogramado"; 
            
            cout << "El turno ha sido reprogramado correctamente." << endl;
            return; 
        }
    }

    // Si termina el for y no retornó, es que no encontró el turno viejo
    cout << "Error: No se encontro el turno original para reprogramar." << endl;
}