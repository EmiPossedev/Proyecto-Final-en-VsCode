#include "Paciente.h"


// Métodos para la fecha de inicio
int Paciente::getFechaDeInicio() const
{
    return fechaDeInicio;
}
void Paciente::setFechaDeInicio(const int &nuevaFechaInicio)
{
    fechaDeInicio = nuevaFechaInicio;
}
// Métodos para el diágnostico
string Paciente::getDiagnostico() const
{
    return diagnostico;
}
void Paciente::setDiagnostico(const string nuevoDiagnostico)
{
    diagnostico = nuevoDiagnostico;
}

// Métodos para la obra social
string Paciente::getObraSocial() const
{
    return obraSocial;
}

void Paciente::setObraSocial(const string &nuevaObraSocial)
{
    obraSocial = nuevaObraSocial;
}

// Métodos para las sesiones totales
int Paciente::getCantSesionesTotales() const
{
    return cantSesionesTotales;
}
void Paciente::setCantSesionesTotales(const int &nuevaCant)
{
    cantSesionesTotales = nuevaCant;
}

// Método para la cantidad de sesiones realizadas
int Paciente::getCantidadSesionesRealizadas() const
{
    return cantSesionesRealizadas;
}

// Método para observaciones
string Paciente::getObservaciones() const
{
    return observaciones;
}
void Paciente::agregarObservaciones(const string &nuevaObservacion)
{
    if (observaciones.empty()){
        observaciones = nuevaObservacion;
    } else {
        observaciones += '\n' + nuevaObservacion; // \n es el caracter que indica salto de línea
    }
}
void borrarObservaciones()
{
    observaciones = ""; // vacío las observaciones
}

// Métodos para sesiones pendientes/pagas
bool Paciente::getSesionesPagas() const
{
    return sesionesPagas;
}

void Paciente::marcarComoPendiente()
{
    sesionesPagas = false;
}

void Paciente::MarcarComoPago()
{
    sesionesPagas = true;
}

// Métodos para descontar sesiones realizadas o reintregarlas si se cancela un turno
void Paciente::descontarSesionDelTotal()
{
    cantSesionesTotales = cantSesionesTotales - 1;
}

void Paciente::reintegrarSesionRealizada()
{
    cantSesionesRealizadas = cantSesionesRealizadas + 1;
}
hola posse