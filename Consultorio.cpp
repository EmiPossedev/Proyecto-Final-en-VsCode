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

// MÉTODO DESTRUCTOR
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

// FUNCIONES AUXILIARES
// Compara si coincide un turno con una fecha
bool coincide(const Turno &turno, const Fecha &fecha)
{
    return turno.fecha == fecha;
}
// Compara si coincide un turno con el string que puede ser el nombre del kinesiologo o la hora
bool coincide(const Turno &turno, const string &valor)
{
    return turno.hora == valor || turno.nombreKinesiologo == valor;
}

/// MÉTODOS BÁSICOS PARA AGREGAR/MODIFICAR DATOS

// Métodos BÁSICOS para KINESIÓLOGOS
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

// Métodos BÁSICOS para PACIENTES
void Consultorio::agregarPaciente(Paciente *paciente)
{
    pacientes.push_back(paciente);
}

vector<Paciente *> Consultorio::getPacientes() const
{
    return pacientes;
}

// MÉTODOS PARA LOS TURNOS(buscar, consultar, agregar, cancelar, reprogramar, ordenar)
// Método para obtener los turnos
vector<Turno> Consultorio::getTurnos() const
{
    return turnos;
}

vector<Turno> Consultorio::getTurnosPorFecha(const Fecha &fecha)
{
    return getTurnosPor(fecha);
}

vector<Turno> Consultorio::getTurnosPorHora(const string &hora)
{
    return getTurnosPor(hora);
}

vector<Turno> Consultorio::getTurnosPorKinesiologo(const string &nombreKinesio)
{
    return getTurnosPor(nombreKinesio);
}

// Agregar un turno
void Consultorio::agregarTurno(const Turno &turno)
{
    turnos.push_back(turno);
}
// Cancelar un turno
void Consultorio::cancelarTurno(const string &nombrePacienteBuscado, const Fecha &fecha, const string &hora)
{
    for (auto it = turnos.begin(); it != turnos.end(); it++)
    {
        // sobrecargamos el operator==
        if (it->nombrePaciente == nombrePacienteBuscado && it->fecha == fecha && it->hora == hora)
        {
            turnos.erase(it);
            return;
        }
    }
}

// Reprogramar un turno
void Consultorio::reprogramarTurno(const string &nombrePaciente, const Fecha &fechaVieja, const string &horaVieja, const Fecha &fechaNueva, const string &horaNueva)
{
    for (auto &turno : turnos)
    {
        // Buscar el turno original
        if (turno.nombrePaciente == nombrePaciente && turno.fecha == fechaVieja && turno.hora == horaVieja)
        {
            if (!verificarDisponibilidadKinesiologo(turno.nombreKinesiologo, fechaNueva, horaNueva))
            {
                cout << "Error: El kinesiologo " << turno.nombreKinesiologo << " ya tiene un turno a esa hora nueva." << endl;
                return;
            }

            if (turno.requiereCamilla)
            {
                if (!verificarDisponibilidadCamilla(fechaNueva, horaNueva))
                {
                    cout << "Error: No hay camillas disponibles en el nuevo horario." << endl;
                    return;
                }
            }
            if (turno.requiereGimnasio)
            {
                if (!verificarDisponibilidadGimnasio(fechaNueva, horaNueva))
                {
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

// Ordenar los turnos
void Consultorio::ordenarTurnos()
{
    sort(turnos.begin(), turnos.end());
}

/// MÉTODOS PARA VERIFICAR DISPONIBILIDAD DE LOS RECURSOS

// Disponibilidad del Kinesiólogo
bool Consultorio::verificarDisponibilidadKinesiologo(const string &nombreKinesio, const Fecha &fecha, const string &hora)
{
    for (const auto &turno : turnos)
    {
        if (turno.nombreKinesiologo == nombreKinesio && turno.fecha == fecha && turno.hora == hora)
        {
            if (turno.estadoDelTurno != "Cancelado")
            {
                return false;
            }
        }
    }
    return true;
}

// Disponibilidad de Camillas
bool Consultorio::verificarDisponibilidadCamilla(const Fecha &fecha, const string &hora)
{
    int camillasOcupadas = 0;
    for (const auto &turno : turnos)
    {
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereCamilla && turno.estadoDelTurno != "Cancelado")
        {
            camillasOcupadas++;
        }
    }
    if (camillasOcupadas < cantCamillas)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Disponibilidad del Gimnasio
bool Consultorio::verificarDisponibilidadGimnasio(const Fecha &fecha, const string &hora)
{
    int gimnasioOcupado = 0;

    for (const auto &turno : turnos)
    {
        if (turno.fecha == fecha && turno.hora == hora && turno.requiereGimnasio && turno.estadoDelTurno != "Cancelado")
        {
            gimnasioOcupado++;
        }
    }

    if (gimnasioOcupado < capacidadGimnasio)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// MÉTODOS DE BÚSQUEDA para Kinesios y Pacientes por nombre y apellido

// MÉTODOS PARA PACIENTES
Paciente *Consultorio::buscarPacientePorNombre(const string &nombre)
{
    for (Paciente *p : pacientes)
    {
        if (p->getNombre() == nombre)
        {
            return p;
        }
    }
    return nullptr;
}
Paciente *Consultorio::buscarPacientePorApellido(const string &apellido)
{
    for (Paciente *p : pacientes)
    {
        if (p->getApellido() == apellido)
        {
            return p;
        }
    }
    return nullptr;
}
// MÉTODOS PARA KINESIÓLOGOS
Kinesiologo *Consultorio::buscarKinesiologoPorNombre(const string &nombre)
{
    for (Kinesiologo *k : kinesiologos)
    {
        if (k->getNombre() == nombre)
        {
            return k;
        }
    }
    return nullptr;
}
Kinesiologo *Consultorio::buscarKinesiologoPorApellido(const string &apellido)
{
    for (Kinesiologo *k : kinesiologos)
    {
        if (k->getApellido() == apellido)
        {
            return k;
        }
    }
    return nullptr;
}

// MÉTODOS DE ELIMINACIÓN de pacientes y kinesiologos de los vectores de Consultorio
void Consultorio::eliminarPacientePorNombre(const string &nombrePaciente)
{
    Paciente *p = buscarPacientePorNombre(nombrePaciente);
    if (p != nullptr)
    {
        pacientes.erase(find(pacientes.begin(), pacientes.end(), p));
        delete p;
    }
}
// no funcionaba ya que era un copy paste del de paciente

// void Consultorio::eliminarKinesiologoPorNombre(const string &nombreKinesio)
// {
//     Kinesiologo *k = buscarPacientePorNombre(nombrePaciente);
//     if (p != nullptr)
//     {
//         pacientes.erase(find(pacientes.begin(), pacientes.end(), p));
//         delete p;
//     }
// }

// CORRECTO
void Consultorio::eliminarKinesiologoPorNombre(const string &nombreKinesio)
{
    // ahora si buysca un kinesiologo
    Kinesiologo *k = buscarKinesiologoPorNombre(nombreKinesio);

    if (k != nullptr)
    {
        // 2. Busco en vector KINESIOLOGOS
        auto it = find(kinesiologos.begin(), kinesiologos.end(), k);
        if (it != kinesiologos.end())
        {
            delete *it;
            kinesiologos.erase(it); // y borro del vector correcto
        }
    }
}
// Paciente con pago pendiente
vector<Paciente *> Consultorio::getPacientesConPagoPendiente() const
{
    vector<Paciente *> deudores;
    for (Paciente *p : pacientes)
    {
        if (!p->getSesionesPagas())
        {
            deudores.push_back(p);
        }
    }
    return deudores;
}

/// MÉTODOS DE ARCHIVOS BINARIOS

// Método para guardar/cargar los pacientes en un archivo binario
void Consultorio::guardarPacientes(const string &nombreArchivo)
{
    fstream bin(nombreArchivo, ios::binary | ios::out);
    if (!bin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para escritura.");
    }
    for (size_t i = 0; i < pacientes.size(); i++)
    {
        RegistroPaciente RegPaciente;
        strncpy(RegPaciente.nombre, pacientes[i]->getNombre().c_str(), 59);     // 59 porque el caracter 60 es para el \0 del c_string
        strncpy(RegPaciente.apellido, pacientes[i]->getApellido().c_str(), 59); // lo mismo para el apellido
        strncpy(RegPaciente.diagnostico, pacientes[i]->getDiagnostico().c_str(), 99);
        strncpy(RegPaciente.observaciones, pacientes[i]->getObservaciones().c_str(), 199);
        strncpy(RegPaciente.obraSocial, pacientes[i]->getObraSocial().c_str(), 49);
        RegPaciente.telefono = pacientes[i]->getTelefono();
        RegPaciente.fechaDeInicio = pacientes[i]->getFechaDeInicio();
        RegPaciente.cantSesionesTotales = pacientes[i]->getCantSesionesTotales();
        RegPaciente.cantSesionesRealizadas = pacientes[i]->getCantidadSesionesRealizadas();
        RegPaciente.sesionesPagas = pacientes[i]->getSesionesPagas();
        bin.write(reinterpret_cast<char *>(&RegPaciente), sizeof(RegistroPaciente));
    }
    bin.close();
    cout << "Pacientes guardados correctamente en: " << nombreArchivo << endl;
}

void Consultorio::cargarPacientes(const string &nombreArchivo)
{
    fstream bin(nombreArchivo, ios::binary | ios::in);
    if (!bin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para lectura.");
    }
    RegistroPaciente RegPaciente;
    while (bin.read(reinterpret_cast<char *>(&RegPaciente), sizeof(RegistroPaciente))))
        {
            Paciente *p = new Paciente();
            // ahora tengo que convertur el RegistroPaciente a Paciente
            p->setNombre(string(RegPaciente.nombre));
            p->setApellido(string(RegPaciente.apellido));
            p->setTelefono(RegPaciente.telefono);
            p->setFechaDeInicio(RegPaciente.fechaDeInicio);
            p->setDiagnostico(string(RegPaciente.diagnostico));
            p->setObraSocial(string(RegPaciente.obraSocial));
            p->setCantSesionesTotales(RegPaciente.cantSesionesTotales);
            p->setCantidadSesionesRealizadas(RegPaciente.cantSesionesRealizadas);
            p->setObservaciones(string(RegPaciente.observaciones));
            // El atributo sesiones pagas se maneja con los métodos de marcarComoPagado y marcarComoPendiente
            if (RegPaciente.sesionesPagas)
            {
                p->marcarComoPagado();
            }
            else
            {
                p->marcarComoPendiente();
            }
            pacientes.push_back(p);
        }
    bin.close();
    cout << "Pacientes cargados correctamente desde: " << nombreArchivo << endl;
}

// guardarKinesiologos / cargarKinesiologos
void Consultorio::guardarKinesiologos(const string &nombreArchivo)
{
    fstream bin(nombreArchivo, ios::binary | ios::out);
    if (!bin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para escritura.");
    }
    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        RegistroKinesiologo RegKinesio;
        strncpy(RegKinesio.nombre, kinesiologos[i]->getNombre().c_str(), 59);     // 59 porque el caracter 60 es para el \0 del c_string
        strncpy(RegKinesio.apellido, kinesiologos[i]->getApellido().c_str(), 59); // lo mismo para el apellido
        RegKinesio.telefono = kinesiologos[i]->getTelefono();
        strncpy(RegKinesio.especialidad, kinesiologos[i]->getEspecialidad().c_str(),99);
        RegKinesio.matricula = kinesiologos[i]->getMatricula();
        RegKinesio.cantidadPacientesAtendidos = kinesiologos[i]->getCantidadPacientesAtendidos();
        bin.write(reinterpret_cast<char *>(&RegKinesio), sizeof(RegistroKinesiologo));
    }
    bin.close();
    cout << "Kinesiólogos guardados correctamente en: " << nombreArchivo << endl;
}

void Consultorio::cargarKinesiologos(const string &nombreArchivo)
{
    fstream bin(nombreArchivo, ios::binary | ios::in);
    if (!bin.is_open())
    {
        throw runtime_error("No se pudo abrir el archivo para lectura.");
    }
    RegistroKinesiologo RegKinesio;
    while (bin.read(reinterpret_cast<char *>(&RegKinesio), sizeof(RegistroKinesiologo))))
        {
            Kinesiologo *k = new Kinesiologo();
            // ahora tengo que convertur el RegistroPaciente a Paciente
            k->setNombre(string(RegKinesio.nombre));
            k->setApellido(string(RegKinesio.apellido));
            k->setTelefono(RegKinesio.telefono);
            k->setEspecialidad(string(RegKinesio.especialidad));
            k->setMatricula(RegKinesio.matricula);
            k->setCantPacientesAtendidos(RegKinesio.cantPacientesAtendidos);
            kinesiologos.push_back(k);
        }
    bin.close();
    cout << "Kinesiólogos cargados correctamente desde: " << nombreArchivo << endl;
}

// guardarTurnos / cargarTurnos

// guardarTodosDatos / cargarTodosDatos
