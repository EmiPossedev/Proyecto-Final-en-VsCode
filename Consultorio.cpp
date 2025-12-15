/// Includes para la implementación de la clase Consultorio
#include "Consultorio.h"
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

// ========== MÉTODOS BÁSICOS ==========

void Consultorio::agregarKinesiologo(Kinesiologo *kinesiologo)
{
    kinesiologos.push_back(kinesiologo);
}

vector<Kinesiologo *> Consultorio::getKinesiologos() const
{
    return kinesiologos;
}

void Consultorio::agregarPaciente(Paciente *paciente)
{
    pacientes.push_back(paciente);
}

vector<Paciente *> Consultorio::getPacientes() const
{
    return pacientes;
}

void Consultorio::agregarTurno(const Turno &turno)
{
    turnos.push_back(turno);
}

vector<Turno> Consultorio::getTurnos() const
{
    return turnos;
}

// ========== MÉTODOS DE BÚSQUEDA ==========

Paciente *Consultorio::buscarPacientePorDni(int dni)
{
    for (size_t i = 0; i < pacientes.size(); i++)
    {
        if (pacientes[i]->getDni() == dni)
        {
            return pacientes[i];
        }
    }
    return nullptr;
}

Paciente *Consultorio::buscarPacientePorNombre(const string &nombre)
{
    for (size_t i = 0; i < pacientes.size(); i++)
    {
        if (pacientes[i]->getNombre() == nombre)
        {
            return pacientes[i];
        }
    }
    return nullptr;
}

Paciente *Consultorio::buscarPacientePorApellido(const string &apellido)
{
    for (size_t i = 0; i < pacientes.size(); i++)
    {
        if (pacientes[i]->getApellido() == apellido)
        {
            return pacientes[i];
        }
    }
    return nullptr;
}

// ========== MÉTODOS DE ELIMINACIÓN ==========

void Consultorio::eliminarPacientePorDni(int dni)
{
    for (size_t i = 0; i < pacientes.size(); i++)
    {
        if (pacientes[i]->getDni() == dni)
        {
            delete pacientes[i]; // Liberar memoria
            pacientes.erase(pacientes.begin() + i);
            return;
        }
    }
}

void Consultorio::eliminarKinesiologoPorDni(int dni)
{
    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        if (kinesiologos[i]->getDni() == dni)
        {
            delete kinesiologos[i]; // Liberar memoria
            kinesiologos.erase(kinesiologos.begin() + i);
            return;
        }
    }
}

// ========== GUARDAR EN ARCHIVOS BINARIOS ==========

void Consultorio::guardarPacientes(const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad = pacientes.size();
        archivo.write((char *)&cantidad, sizeof(int));

        for (size_t i = 0; i < pacientes.size(); i++)
        {
            RegistroPaciente reg;
            // Copiar strings a char[] usando strncpy
            strncpy(reg.nombre, pacientes[i]->getNombre().c_str(), 49);
            reg.nombre[49] = '\0';
            strncpy(reg.apellido, pacientes[i]->getApellido().c_str(), 49);
            reg.apellido[49] = '\0';
            reg.dni = pacientes[i]->getDni();
            strncpy(reg.mail, pacientes[i]->getMail().c_str(), 49);
            reg.mail[49] = '\0';
            reg.telefono = pacientes[i]->getTelefono();
            reg.fechaDeNacimiento = pacientes[i]->getFechaDeNacimiento();

            archivo.write((char *)&reg, sizeof(RegistroPaciente));
        }
        archivo.close();
    }
}

void Consultorio::guardarKinesiologos(const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad = kinesiologos.size();
        archivo.write((char *)&cantidad, sizeof(int));

        for (size_t i = 0; i < kinesiologos.size(); i++)
        {
            RegistroKinesiologo reg;
            strncpy(reg.nombre, kinesiologos[i]->getNombre().c_str(), 49);
            reg.nombre[49] = '\0';
            strncpy(reg.apellido, kinesiologos[i]->getApellido().c_str(), 49);
            reg.apellido[49] = '\0';
            reg.dni = kinesiologos[i]->getDni();
            strncpy(reg.mail, kinesiologos[i]->getMail().c_str(), 49);
            reg.mail[49] = '\0';
            reg.telefono = kinesiologos[i]->getTelefono();
            reg.fechaDeNacimiento = kinesiologos[i]->getFechaDeNacimiento();
            strncpy(reg.especialidad, kinesiologos[i]->getEspecialidad().c_str(), 49);
            reg.especialidad[49] = '\0';
            reg.cantidadPacientesAtendidos = kinesiologos[i]->getCantidadPacientesAtendidos();

            archivo.write((char *)&reg, sizeof(RegistroKinesiologo));
        }
        archivo.close();
    }
}

void Consultorio::guardarTurnos(const string &nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad = turnos.size();
        archivo.write((char *)&cantidad, sizeof(int));

        for (size_t i = 0; i < turnos.size(); i++)
        {
            RegistroTurno reg;
            reg.codigoTurno = turnos[i].codigoTurno;
            reg.dniPaciente = turnos[i].dniPaciente;
            reg.dniKinesiologo = turnos[i].dniKinesiologo;
            strncpy(reg.fecha, turnos[i].fecha.c_str(), 14);
            reg.fecha[14] = '\0';
            strncpy(reg.hora, turnos[i].hora.c_str(), 9);
            reg.hora[9] = '\0';
            strncpy(reg.estadoDelTurno, turnos[i].estadoDelTurno.c_str(), 19);
            reg.estadoDelTurno[19] = '\0';
            strncpy(reg.observaciones, turnos[i].observaciones.c_str(), 199);
            reg.observaciones[199] = '\0';

            archivo.write((char *)&reg, sizeof(RegistroTurno));
        }
        archivo.close();
    }
}

// ========== CARGAR DESDE ARCHIVOS BINARIOS ==========

void Consultorio::cargarPacientes(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad;
        archivo.read((char *)&cantidad, sizeof(int));

        // Limpiar vector actual
        for (size_t i = 0; i < pacientes.size(); i++)
        {
            delete pacientes[i];
        }
        pacientes.clear();

        for (int i = 0; i < cantidad; i++)
        {
            RegistroPaciente reg;
            archivo.read((char *)&reg, sizeof(RegistroPaciente));

            Paciente *paciente = new Paciente();
            paciente->setNombre(string(reg.nombre));
            paciente->setApellido(string(reg.apellido));
            paciente->setDni(reg.dni);
            paciente->setMail(string(reg.mail));
            paciente->setTelefono(reg.telefono);
            paciente->setFechaDeNacimiento(reg.fechaDeNacimiento);

            pacientes.push_back(paciente);
        }
        archivo.close();
    }
}

void Consultorio::cargarKinesiologos(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad;
        archivo.read((char *)&cantidad, sizeof(int));

        // Limpiar vector actual
        for (size_t i = 0; i < kinesiologos.size(); i++)
        {
            delete kinesiologos[i];
        }
        kinesiologos.clear();

        for (int i = 0; i < cantidad; i++)
        {
            RegistroKinesiologo reg;
            archivo.read((char *)&reg, sizeof(RegistroKinesiologo));

            Kinesiologo *kinesiologo = new Kinesiologo();
            kinesiologo->setNombre(string(reg.nombre));
            kinesiologo->setApellido(string(reg.apellido));
            kinesiologo->setDni(reg.dni);
            kinesiologo->setMail(string(reg.mail));
            kinesiologo->setTelefono(reg.telefono);
            kinesiologo->setFechaDeNacimiento(reg.fechaDeNacimiento);
            kinesiologo->setEspecialidad(string(reg.especialidad));
            kinesiologo->setCantidadPacientesAtendidos(reg.cantidadPacientesAtendidos);

            kinesiologos.push_back(kinesiologo);
        }
        archivo.close();
    }
}

void Consultorio::cargarTurnos(const string &nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary);
    if (archivo.is_open())
    {
        int cantidad;
        archivo.read((char *)&cantidad, sizeof(int));

        turnos.clear();

        for (int i = 0; i < cantidad; i++)
        {
            RegistroTurno reg;
            archivo.read((char *)&reg, sizeof(RegistroTurno));

            Turno turno;
            turno.codigoTurno = reg.codigoTurno;
            turno.dniPaciente = reg.dniPaciente;
            turno.dniKinesiologo = reg.dniKinesiologo;
            turno.fecha = string(reg.fecha);
            turno.hora = string(reg.hora);
            turno.estadoDelTurno = string(reg.estadoDelTurno);
            turno.observaciones = string(reg.observaciones);

            turnos.push_back(turno);
        }
        archivo.close();
    }
}

// ========== GUARDAR/CARGAR TODO ==========

void Consultorio::guardarTodosDatos()
{
    guardarPacientes("pacientes.dat");
    guardarKinesiologos("kinesiologos.dat");
    guardarTurnos("turnos.dat");
}

void Consultorio::cargarTodosDatos()
{
    cargarPacientes("pacientes.dat");
    cargarKinesiologos("kinesiologos.dat");
    cargarTurnos("turnos.dat");
}