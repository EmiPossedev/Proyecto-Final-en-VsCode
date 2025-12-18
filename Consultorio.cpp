/// Includes para la implementación de la clase Consultorio
#include "Consultorio.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream> 
#include <algorithm> // para que funcione sort
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
// Fíjate que el parámetro ahora es 'const Fecha &fecha'
void Consultorio::cancelarTurno(const string &nombrePacienteBuscado, const Fecha &fecha, const string &hora)
{
    for (auto it = turnos.begin(); it != turnos.end(); it++) 
    {
        // Gracias a que sobrecargamos el operator== en Fecha.h, 
        // esta comparación (it->fecha == fecha) funciona automático.
        if (it->nombrePaciente == nombrePacienteBuscado && 
            it->fecha == fecha && 
            it->hora == hora)     
        {
            turnos.erase(it);
            return; 
        }
    }  
} 

// Verificación 1: Disponibilidad del Kinesiólogo 
// Cambio: parámetro fecha ahora es tipo Fecha
bool Consultorio::verificarDisponibilidadKinesiologo(const string &nombreKinesio, const Fecha &fecha, const string &hora)
{
    for (const auto &turno : turnos)
    {
        if (turno.nombreKinesiologo == nombreKinesio && turno.fecha == fecha && turno.hora == hora)
        {
            if (turno.estadoDelTurno != "Cancelado") 
            {
                return false; 
            }
        }
    }
    return true; 
}

// Verificación 2: Disponibilidad de Camillas 
bool Consultorio::verificarDisponibilidadCamilla(const Fecha &fecha, const string &hora)
{
    int camillasOcupadas = 0;

    for (const auto &turno : turnos)
    {
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereCamilla && turno.estadoDelTurno != "Cancelado")
        {
            camillasOcupadas++;
        }
    }

    if (camillasOcupadas < cantCamillas)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// Verificación 3: Disponibilidad del Gimnasio 
bool Consultorio::verificarDisponibilidadGimnasio(const Fecha &fecha, const string &hora)
{
    int gimnasioOcupado = 0;

    for (const auto &turno : turnos)
    {
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereGimnasio && turno.estadoDelTurno != "Cancelado")
        {
            gimnasioOcupado++;
        }
    }

    if (gimnasioOcupado < capacidadGimnasio)
    {
        return true; 
    }
    else
    {
        return false; 
    }
}

// Cambio: fechaVieja y fechaNueva ahora son tipo Fecha
void Consultorio::reprogramarTurno(const string &nombrePaciente, const Fecha &fechaVieja, const string &horaVieja, const Fecha &fechaNueva, const string &horaNueva)
{
    for (auto &turno : turnos)
    {
        // Buscar el turno original (Compara fechas usando Fecha.h)
        if (turno.nombrePaciente == nombrePaciente &&
            turno.fecha == fechaVieja &&
            turno.hora == horaVieja)
        {
            
            // Verificaciones (pasamos los objetos Fecha a las funciones)
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

            if (turno.requiereGimnasio)
            {
                if (!verificarDisponibilidadGimnasio(fechaNueva, horaNueva))
                {
                    cout << "Error: El gimnasio esta lleno en el nuevo horario." << endl;
                    return;
                }
            }

            // Actualización de datos
            turno.fecha = fechaNueva; // Copia los 3 ints (día, mes, año)
            turno.hora = horaNueva;
            turno.estadoDelTurno = "Reprogramado"; 
            
            cout << "El turno ha sido reprogramado correctamente." << endl;
            return; 
        }
    }

    cout << "Error: No se encontro el turno original para reprogramar." << endl;
}

// ¡FALTABA ESTE! Agregalo para que funcione el ordenamiento
void Consultorio::ordenarTurnos()
{
    // Como definimos el operator< dentro del struct Turno (en el .h)
    // sort ya sabe qué hacer mágicamente.
    sort(turnos.begin(), turnos.end());
}