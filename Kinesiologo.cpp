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

void Kinesiologo::setEspecialidad(const string &modificacion)
{
    especialidad = modificacion;
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