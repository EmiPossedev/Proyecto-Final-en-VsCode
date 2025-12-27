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
    char nombre[60];
    char apellido[60];
    char telefono[20];
    char dni[10];
    // Datos de la clase kinesiologo
    char especialidad[100];
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
    void setEspecialidad(const string &modificacion);
    void borrarEspecialidad();
    int getCantidadPacientesAtendidos() const;
    void setCantPacientesAtendidos(const int &cant);
    int getMatricula() const;
    void setMatricula(int n);
};

#endif