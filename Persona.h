#include <string>
using namespace std;

/// Necesitamos una manera de transformar los datos de las personas en registros para guardarlos en archivos binarios
struct registro_persona {
    char nombre[50];
    char apellido[50];
    char telefono[50];
    char mail[50];
    char direccion[50];
    char dni[10];
};

/// Definición de la clase Persona
class Persona{
private:
    string nombre;
    string apellido;
    int dni;
    string mail;
    int telefono;
    int fechaDeNacimiento; // Formato AAAAMMDD
public:
    void setNombre(string nombreyApellido);
    string getNombre();
    void setApellido(string apellido);
    string getApellido();
    int getDni();
    void setDni(int dni);
    void setMail(string mail);
    string getMail();
    void setTelefono(int telefono);
    int getTelefono();
    string ValidarDatos();
    void setFechaDeNacimiento(int fechaDeNacimiento);
    int getFechaDeNacimiento();
};



