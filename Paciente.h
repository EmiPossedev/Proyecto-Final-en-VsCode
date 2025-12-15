#include "Persona.h"
#include <string>
using namespace std;

// Registro para guardar en archivo binario (incluye datos de Persona + Paciente)
struct RegistroPaciente
{
    // Datos heredados de Persona
    char nombre[50];
    char apellido[50];
    int telefono;
    // Datos propios de Paciente
    int fechaDeInicio;
    char diagnostico[100];
    char obraSocial[50];
    int cantidadSesionesRealizadas;
    char observaciones[200];
    bool sesionesPagas;
};

class Paciente : public Persona
{
private:
    int fechaDeInicio;
    string diagnostico;
    string obraSocial; // mencionar si tiene o viene en forma particular
    int cantidadSesionesRealizadas;
    string observaciones;
    bool sesionesPagas;

public:
    // Getters
    int getFechaDeInicio() const;
    string getDiagnostico() const;
    string getObraSocial() const;
    int getCantidadSesionesRealizadas() const;
    string getObservaciones() const;
    bool getSesionesPagas() const;

    // Setters
    void setFechaDeInicio(int fecha);
    void setDiagnostico(const string &diag);
    void setObraSocial(const string &obra);
    void setCantidadSesionesRealizadas(int cantidad);
    void setObservaciones(const string &obs);
    void setSesionesPagas(bool pagas);
};