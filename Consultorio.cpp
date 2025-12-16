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

// Métodos Básicos para agregar/modificar datos
void Consultorio::agregarKinesiologo(Kinesiologo *kinesiologo)
{
    kinesiologos.push_back(kinesiologo);
}

vector<Kinesiologo *> Consultorio::getKinesiologos() const
{
    return kinesiologos;
}

void Consultorio::agregarPaciente(Paciente *paciente)
{
    pacientes.push_back(paciente);
}

vector<Paciente *> Consultorio::getPacientes() const
{
    return pacientes;
}

void Consultorio::agregarTurno(const Turno &turno)
{
    turnos.push_back(turno);
}

vector<Turno> Consultorio::getTurnos() const
{
    return turnos;
}
