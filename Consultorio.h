#include "Persona.h"
#include "Kinesiologo.h"
#include "Paciente.h"
#include <string>

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
};