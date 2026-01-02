
#ifndef SUBMENU_H
#define SUBMENU_H

#include <iostream>
#include <string>
#include "Consultorio.h"
using namespace std;

// LOGICA PACIENTES
void registrarPaciente(Consultorio &sistema);
void listarPacientes(Consultorio &sistema);
void gestionarPacientePorIndice(Consultorio &sistema, const vector<Paciente *> &encontrados, size_t indice);
void gestionarPaciente(Consultorio &sistema, Paciente *p); // lógica para buscar y gestionar paciente con su sub menu

/// LÓGICA PARA KINESIOLOGOS
void listarKinesiologos(const Consultorio &consultorio);
void registrarkinesiologo(Consultorio &sistema);
void gestionarKinesiologoPorIndice(Consultorio &sistema, const vector<Kinesiologo *> &encontrados, size_t indice);
void gestionarKinesiologo(Consultorio &sistema, Kinesiologo *k);

/// LÓGICA PARA TURNOS
void reservarTurno(Consultorio &sistema);
void verAgenda(Consultorio &sistema);
void modificarTurno(Consultorio &sistema);
void cancelarTurno(Consultorio &sistema);

#endif