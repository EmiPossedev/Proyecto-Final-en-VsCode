/// Includes necesarios para la definición de la clase Kinesiologo
#include "Persona.h"
#include <string>
using namespace std;

// Creo un struct para el horario de atencion del kinesiologo
struct HorarioAtencion {
    string diaSemana; // Lunes, Martes, etc.
    int horaInicio; // Formato 24hs
    int horaFin;    // Formato 24hs
};
/// Creacion de la clase Kinesiologo que hereda de Persona
class Kinesiologo : public Persona {
private:
    string especialidad;
    HorarioAtencion horario;
    int cantidadPacientesAtendidos;
public:
    
};