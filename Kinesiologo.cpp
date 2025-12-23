#include "Kinesiologo.h"

string Kinesiologo::getEspecialidad() const
{
    return especialidad;
}

int Kinesiologo::getCantidadPacientesAtendidos() const
{
    return cantidadPacientesAtendidos;
}

/// Métodos para modificar los datos del kinesiólogo faltantes

void Kinesiologo::setEspecialidad(const string &nuevaEspecialidad)
{
    if (especialidad.empty()){
        especialidad = nuevaEspecialidad;
    } else {
        especialidad += '\n' + nuevaEspecialidad; // \n es el caracter que indica salto de línea
    }
}

void Kinesiologo::borrarEspecialidad()
{
    especialidad = ""; // vacío sus especialidades
}

void Kinesiologo::setCantPacientesAtendidos(const int &cant)
{
    cantidadPacientesAtendidos = cant;
}

int Kinesiologo::getMatricula() const
{
    return matricula;
}

void Kinesiologo::setMatricula(int n)
{
    matricula = n;
}