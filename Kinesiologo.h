/// Includes necesarios para la definición de la clase Kinesiologo
#include "Persona.h"
#include <string>
using namespace std;

// Registro para Kinesiologo
struct RegistroKinesiologo {
    char nombre[50];
    char apellido[50];
    int dni;
    char mail[50];
    int telefono;
    int fechaDeNacimiento;
    char especialidad[50];
    char diaSemana[20];
    int horaInicio;
    int horaFin;
    int cantidadPacientesAtendidos;
};



/// Creacion de la clase Kinesiologo que hereda de Persona
class Kinesiologo : public Persona {

private:
    string especialidad;
    int horaInicioJornada;
    int horafinJornanda;
    int cantidadPacientesAtendidos;
public:
    string getEspecialidad() const;
    void modificarEspecialidad(string modif);
    int getCantidadPacientesAtendidos() const;
    void modificarCantPacientesAtendidos
    int getHoraInicioJornada() const;
    void modificarInicioJornada(int nuevaHoraInicio);
    int getHoraFinJornada() const;
    void modificarFinJornada(int nuevaHoraFin);

    

};