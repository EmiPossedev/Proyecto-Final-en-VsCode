#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

/// Necesitamos una manera de transformar los datos de las personas en registros para guardarlos en archivos binarios
struct registro_persona
{
    char nombre[50];
    char apellido[50];
    int telefono;
};

/// Definición de la clase Persona
class Persona
{
private:
    string nombre;
    string apellido;
    int telefono;

public:
    void setNombre(string nombreyApellido);
    string getNombre();
    void setApellido(string apellido);
    string getApellido();
    void setTelefono(int telefono);
    int getTelefono();
};

#endif
