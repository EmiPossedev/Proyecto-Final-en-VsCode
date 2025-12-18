/// Includes para la implementación de la clase Consultorio
#include "Consultorio.h"
#include "Persona.h"
#include "Paciente.h"
#include "Kinesiologo.h"
#include "Fecha.h"
#include "Utils.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm> // para que funcione el sort

// Método Destructor
Consultorio::~Consultorio()
{
    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        delete kinesiologos[i];
    }

    for (size_t i = 0; i < pacientes.size(); i++)
    {
        delete pacientes[i];
    }
}

/// Métodos Básicos para agregar/modificar datos

// Métodos básicos para kinesiólogos
void Consultorio::agregarKinesiologo(Kinesiologo *kinesiologo)
{
    kinesiologos.push_back(kinesiologo);
}
void Consultorio::eliminarKinesiologo(Kinesiologo *kinesiologo)
{
    delete kinesiologo;
}
vector<Kinesiologo *> Consultorio::getKinesiologos() const
{
    return kinesiologos;
}

// Métodos para pacientes
void Consultorio::agregarPaciente(Paciente *paciente)
{
    pacientes.push_back(paciente);
}

vector<Paciente *> Consultorio::getPacientes() const
{
    return pacientes;
}

// Métodos para turnos
vector<Turno> Consultorio::getTurnos() const
{
    return turnos;
}

// Métodos de búsqueda de turnos
// Busca todos los turnos de una fecha específica
vector<Turno> Consultorio::getTurnosPorFecha(const Fecha &fecha)
{
    vector<Turno> encontrados;

    for (const auto &turno : turnos) {
        // operator== en Fecha.h
        if (turno.fecha == fecha) {
            encontrados.push_back(turno);
        }
    }
    return encontrados;
}

// Busca todos los turnos de una hora específica
vector<Turno> Consultorio::getTurnosPorHora(const string &hora) {
    vector<Turno> encontrados;
    for (const auto &turno : turnos){
        if (turno.hora == hora) {
            encontrados.push_back(turno);
        }
    }
    return encontrados;
}

// Busca todos los turnos de un kinesiólogo específico
vector<Turno> Consultorio::getTurnosDeKinesiologo(const string &nombreKinesio){
    vector<Turno> encontrados;
    for (const auto &turno : turnos){
        if (turno.nombreKinesiologo == nombreKinesio) {
            encontrados.push_back(turno);
        }
    }
    return encontrados;
}

void Consultorio::agregarTurno(const Turno &turno){
    turnos.push_back(turno);
}

void Consultorio::cancelarTurno(const string &nombrePacienteBuscado, const Fecha &fecha, const string &hora){
    for (auto it = turnos.begin(); it != turnos.end(); it++){
        //sobrecargamos el operator==
        if (it->nombrePaciente == nombrePacienteBuscado && it->fecha == fecha &&  it->hora == hora)
        {
            turnos.erase(it);
            return;
        }
    }
}

// Disponibilidad del Kinesiólogo
bool Consultorio::verificarDisponibilidadKinesiologo(const string &nombreKinesio, const Fecha &fecha, const string &hora){
    for (const auto &turno : turnos){
        if (turno.nombreKinesiologo == nombreKinesio && turno.fecha == fecha && turno.hora == hora){
            if (turno.estadoDelTurno != "Cancelado"){
                return false;
            }
        }
    }
    return true;
}

// Disponibilidad de Camillas
bool Consultorio::verificarDisponibilidadCamilla(const Fecha &fecha, const string &hora){
    int camillasOcupadas = 0;
    for (const auto &turno : turnos){
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereCamilla && turno.estadoDelTurno != "Cancelado"){
            camillasOcupadas++;
        }
    }
    if (camillasOcupadas < cantCamillas){
        return true;
    }
    else{
        return false;
    }
}

// Métodos de búsqueda por nombre y apellido
Paciente *Consultorio::buscarPacientePorApellido(const string &apellido){
    for(Paciente* p : pacientes){
        if(p->getApellido() == apellido){
            return p;
        }
    }
    return nullptr; //No existe
}
Paciente *Consultorio::buscarPacientePorNombre(const string &nombre)
{
    for(Paciente* p : pacientes){
        if(p->getNombre() == nombre){
            return p;
        }
    }
    return nullptr;
}


//Disponibilidad del Gimnasio
bool Consultorio::verificarDisponibilidadGimnasio(const Fecha &fecha, const string &hora)
{
    int gimnasioOcupado = 0;

    for (const auto &turno : turnos){
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereGimnasio && turno.estadoDelTurno != "Cancelado"){
            gimnasioOcupado++;
        }
    }

    if (gimnasioOcupado < capacidadGimnasio){
        return true;
    }else{
        return false;
    }
}

void Consultorio::reprogramarTurno(const string &nombrePaciente, const Fecha &fechaVieja, const string &horaVieja, const Fecha &fechaNueva, const string &horaNueva)
{
    for (auto &turno : turnos) {
        // Buscar el turno original
        if (turno.nombrePaciente == nombrePaciente && turno.fecha == fechaVieja && turno.hora == horaVieja){
            if (!verificarDisponibilidadKinesiologo(turno.nombreKinesiologo, fechaNueva, horaNueva)){
                cout << "Error: El kinesiologo " << turno.nombreKinesiologo << " ya tiene un turno a esa hora nueva." << endl;
                return;
            }

            if (turno.requiereCamilla){
                if (!verificarDisponibilidadCamilla(fechaNueva, horaNueva)) {
                    cout << "Error: No hay camillas disponibles en el nuevo horario." << endl;
                    return;
                }
            }
            if (turno.requiereGimnasio){
                if (!verificarDisponibilidadGimnasio(fechaNueva, horaNueva)) {
                    cout << "Error: El gimnasio esta lleno en el nuevo horario." << endl;
                    return;
                }
            }

            // Actualización de datos
            turno.fecha = fechaNueva; 
            turno.hora = horaNueva;
            turno.estadoDelTurno = "Reprogramado";

            cout << "El turno se logro reprogramar" << endl;
            return;
        }
    }

    cout << "Error" << endl;
}

void Consultorio::ordenarTurnos()
{
    sort(turnos.begin(), turnos.end());
}