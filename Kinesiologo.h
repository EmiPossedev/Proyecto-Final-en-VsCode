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
    // Datos propios del kinesiologo
    char especialidad[50];
    int cantidadPacientesAtendidos;
};

/// Creacion de la clase Kinesiologo que hereda de Persona
class Kinesiologo : public Persona
{
private:
    string especialidad;
    int cantidadPacientesAtendidos;
public:
    string getEspecialidad() const;
    void modificarEspecialidad(const string &modificacion);
    int getCantidadPacientesAtendidos() const;
    void modificarCantPacientesAtendidos(const int &cant);
};