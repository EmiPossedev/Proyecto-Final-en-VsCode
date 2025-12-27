#ifndef CONSULTORIO_H
#define CONSULTORIO_H
#include "Fecha.h"
#include "Persona.h"
#include "Kinesiologo.h"
#include "Paciente.h"
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Este struct sirve para guardar en archivo binario (usando char)
struct RegistroTurno
{
    char dniKine[10];
    char nombreKinesio[60];
    char nombrePaciente[60];
    Fecha fecha;             // Usamos el struct Fecha definido en Fecha.h
    char hora[10];           // Formato HH:MM
    char estadoDelTurno[20]; // Programado, Cancelado, Completado
    bool requiereCamilla;
    bool requiereGimnasio;
    char observaciones[200];
};

// Y este struct Turno me deja trabajar los datos en memoria
struct Turno
{
    string dniKinesiologo;
    string nombreKinesiologo;
    string nombrePaciente;
    Fecha fecha;
    string hora; // Formato HH:MM
    bool requiereCamilla;
    bool requiereGimnasio;
    string estadoDelTurno; // Programado, Cancelado, Completado
    string observaciones;

    // Necesitamos esto para que ordenarTurnos() pueda hacer la comparacion
    // Como ahora fecha ya sabe compararse sola
    bool operator<(const Turno &Turno) const
    {
        if (fecha != Turno.fecha)
        {
            return fecha < Turno.fecha; // Usa la lógica de tu Fecha.h
        }
        return hora < Turno.hora; // Si es el mismo día, desempata por hora
    }
};

/// FUNCIONES AUXILIARES PARA PODER COMPARAR TURNOS POR FECHA, POR HORA Y POR KINESIOLOGOS
// Compara si un turno coincide con una fecha
bool coincide(const Turno &turno, const Fecha &fecha);
// Compara si un turno coincide con un string como Nombrekinesio o Hora
bool coincide(const Turno &turno, const string &valor);

/// Definición de la clase Consultorio
class Consultorio
{

private:
    vector<Kinesiologo *> kinesiologos;
    vector<Paciente *> pacientes;
    vector<Turno> turnos;
    int cantCamillas = 5;
    int capacidadGimnasio = 5;

public:
    // Método constructor y método destructor
    Consultorio() {}
    ~Consultorio();
    // Métodos para agregar/obtener pacientes
    void agregarKinesiologo(Kinesiologo *kinesiologo);
    vector<Kinesiologo *> getKinesiologos() const;

    // Métodos para agregar/obtener kinesiólogos
    void agregarPaciente(Paciente *paciente);
    vector<Paciente *> getPacientes() const;

    // Métodos para la gestión de los turnos
    vector<Turno> getTurnos() const;
    void agregarTurno(const Turno &turno);
    void cancelarTurno(const string &nombrePaciente, const Fecha &fecha, const string &hora);
    void reprogramarTurno(const string &nombrePaciente, const Fecha &fechaVieja, const string &horaVieja, const Fecha &fechaNueva, const string &horaNueva);
    void ordenarTurnos();

    // Función de búsqueda templatizada(funciona paragetTurnosPorFecha, getTurnosPorHora, getTurnosPorKinesiologo)
    template <typename T>
    vector<Turno> getTurnosPor(const T &valorBuscado)
    {
        vector<Turno> encontrados;
        for (size_t i = 0; i < turnos.size(); i++)
        {
            // la manera más simple encontré fue con una funcion auxiliar
            if (coincide(turnos[i], valorBuscado)) // coincide es una funcion sobrecargada(no sé si es lo más óptimo pero funciona jajjaj)
            {
                encontrados.push_back(turnos[i]);
            }
        }
        return encontrados;
    }

    // Métodos de verificación
    bool verificarDisponibilidadKinesiologo(const string &dniKine, const Fecha &fecha, const string &hora);
    bool verificarDisponibilidadCamilla(const Fecha &fecha, const string &hora);
    bool verificarDisponibilidadGimnasio(const Fecha &fecha, const string &hora);

    /// MÉTODOS DE BÚSQUEDA
    /* Estos no los vamos a utilizar
    Kinesiologo *buscarKinesiologoPorNombre(const string &nombre);
    Kinesiologo *buscarKinesiologoPorApellido(const string &apellido);
    Paciente *buscarPacientePorNombre(const string &nombre);
    Paciente *buscarPacientePorApellido(const string &apellido);
    */

    Kinesiologo *buscarKinesiologoPorDni(const string &dniBuscado);
    Paciente *buscarPacientePorDni(const string &dniBuscado);

    // Métodos de eliminación
    void eliminarPacientePorDni(const string &dniKine);
    void eliminarKinesiologoPorDni(const string &nombreKinesio);

    // Método de alerta al kinesiologo de que le tienen que pagar
    vector<Paciente *> getPacientesConPagoPendiente() const;

    /// Métodos con archivos binarios

    // Guardar datos en archivos binarios
    void guardarPacientes(const string &nombreArchivo);
    void guardarKinesiologos(const string &nombreArchivo);
    void guardarTurnos(const string &nombreArchivo);

    // Cargar datos desde archivos binarios
    void cargarPacientes(const string &nombreArchivo);
    void cargarKinesiologos(const string &nombreArchivo);
    void cargarTurnos(const string &nombreArchivo);

    // Guardar/cargar todo de una vez
    void guardarTodosDatos();
    void cargarTodosDatos();
};

#endif