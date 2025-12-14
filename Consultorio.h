#include "Persona.h"
#include "Kinesiologo.h"
#include "Paciente.h"
#include <string>
#include <vector>
using namespace std;

/// Definición de la clase Consultorio
class Consultorio {
    private: 
        vector<Kinesiologo> kinesiologos;
        vector<Paciente> pacientes;
    public:
        // Métodos para agregar y obtener kinesiologos y pacientes
        void agregarKinesiologo(const Kinesiologo &kinesiologo);
        vector<Kinesiologo> getKinesiologos() const;
        void agregarPaciente(const Paciente &paciente);
        vector<Paciente> getPacientes() const;


        // Otros métodos, como por ejemplo métodos de búsqueda
        Paciente buscarPacientePorDni(int dni);
        Paciente buscarPacientePorNombre(const string &nombre);
        Paciente buscarPacientePorApellido(const string &apellido);
        Paciente buscarPacientePorApellidoYNombre(const string &apellido, const string &nombre);
        Paciente buscarPacientePorTelefono(int telefono);
        Paciente buscarPacientePorMail(const string &mail);
        Paciente buscarPacientePorFechaDeNacimiento(int fechaDeNacimiento);
        
        // Métodos de eliminación
        void eliminarPacientePorDni(int dni);
        void eliminarPacientePorNombre(const string &nombre);
        void eliminarPacientePorApellido(const string &apellido);
        void eliminarPacientePorApellidoYNombre(const string &apellido, const string &nombre);
        void eliminarPacientePorTelefono(int telefono);
        void eliminarPacientePorMail(const string &mail);
        void eliminarPacientePorFechaDeNacimiento(int fechaDeNacimiento);
};