/// Includes para la implementación de la clase Consultorio
#include "Consultorio.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

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
        if (it->nombrePaciente == nombrePacienteBuscado && 
            it->fecha == fecha && // En minúsculas
            it->hora == hora)     // En minúsculas
        {
            turnos.erase(it);
            return; 
        }
    }  
} 

