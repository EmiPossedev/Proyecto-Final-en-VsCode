#ifndef KINESIOLOGO_H
#define KINESIOLOGO_H

/// Includes necesarios para la definición de la clase Kinesiologo
#include "Persona.h"
#include <string>
using namespace std;

// Registro para Kinesiologo
struct RegistroKinesiologo
{
    // Datos heredados de Persona
    char nombre[50];
    char apellido[50];
    int telefono;
    // Datos de la clase kinesiologo
    char especialidad[50];
    int matricula;
    int cantidadPacientesAtendidos;
};

/// Creacion de la clase Kinesiologo que hereda de Persona
class Kinesiologo : public Persona
{
private:
    int matricula;
    string especialidad;
    int cantidadPacientesAtendidos;
public:
    // Métodos para obtener los datos del kinesiologo y/o modificarlos
    string getEspecialidad() const;
    void modificarEspecialidad(const string &modificacion);
    int getCantidadPacientesAtendidos() const;
    void modificarCantPacientesAtendidos(const int &cant);
    int getMatricula() const;
    void modificarMatricula(int n);
};

#endif