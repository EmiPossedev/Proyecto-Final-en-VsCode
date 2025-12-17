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

void Consultorio::cancelarTurno(const stringPaciente &nombrePacienteBuscado, const string &fecha, const string &hora)
{
for (auto i = turnos.begin(); i != turnos.end(); i++) 
    {
        if (it->nombrePaciente == nombrePacienteBuscado && 
            it->Fecha == fecha && 
            it->Hora == hora)
        {
            turnos.erase(it);
            return; // el return solo sale de las funciones void :)
            // Lástima que lo aprendí tarde, así me ahorraba iteraciones innecesarias jajaj
        }
    }  
}

