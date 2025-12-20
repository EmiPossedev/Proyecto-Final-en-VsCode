#ifndef PERSONA_H
#define PERSONA_H

#include <string>
using namespace std;

/// Necesitamos una manera de transformar los datos de las personas en registros para guardarlos en archivos binarios
struct registro_persona
{
    char nombre[60];
    char apellido[60];
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
virtual ~Persona() {} // Destructor virtual para herencia segura

    void setNombre(string nombreyApellido);
    string getNombre() const;
    void setApellido(string apellido);
    string getApellido() const;
    void setTelefono(int telefono);
    int getTelefono() const;
};

#endif
