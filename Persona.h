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
    void setNombre(const string &nombre);
    string getNombre() const;
    void setApellido(const string &apellido);
    string getApellido() const;
    void setTelefono(const int &telefono);
    int getTelefono() const;
    virtual ~Persona() {} // Destructor virtual por ser clase madre
};

#endif
