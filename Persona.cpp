/// Includes necesarios para la implementación de la clase Persona
#include "Persona.h"
#include <string>

/// Implementación de los métodos de la clase Persona

// Métodos para el nombre
void Persona::setNombre(const string &nuevoNombre)
{
    nombre = nuevoNombre;
}
string Persona::getNombre() const
{
    return nombre;
}

// Métodos para el apellido
void Persona::setApellido(const string &nuevoApellido)
{
    apellido = nuevoApellido;
}
string Persona::getApellido() const
{
    return apellido;
}

// Métodos para el teléfono
void Persona::setTelefono(const std::string &nuevoTelefono)
{
    telefono = nuevoTelefono;
}
std::string Persona::getTelefono() const
{
    return telefono;
}
