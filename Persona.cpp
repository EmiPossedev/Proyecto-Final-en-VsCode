/// Includes necesarios para la implementación de la clase Persona
#include "Persona.h"
#include <string>

/// Implementación de los métodos de la clase Persona

// Métodos para el nombre
void Persona::setNombre(string nuevoNombre) {
    nombre = nuevoNombre;
}
string Persona::getNombre() {
    return nombre;
}

// Métodos para el apellido
void Persona::setApellido(string nuevoApellido){
    apellido = nuevoApellido;
}
string Persona::getApellido(){
    return apellido;
}

// Métodos para el DNI
void Persona::setDni(int nuevoDni){
    dni = nuevoDni;
}
int Persona::getDni(){
    return dni;
}

// Métodos para el mail
void Persona::setMail(string nuevoMail){
    mail = nuevoMail;
}
string Persona::getMail() {
    return mail;
}

// Métodos para el teléfono
void Persona::setTelefono(int nuevoTelefono) {
    telefono = nuevoTelefono;
}
int Persona::getTelefono() {
    return telefono;
}

// Métodos para la fecha de nacimiento
void Persona::setFechaDeNacimiento(int nuevaFecha) {
    fechaDeNacimiento = nuevaFecha;
}
int Persona::getFechaDeNacimiento() {
    return fechaDeNacimiento;
}