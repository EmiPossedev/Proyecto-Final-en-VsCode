#include "menu.h"
#include "submenu.h"
#include <iostream>
#include <string>
using namespace std;

void menuPacientes(Consultorio &sistema)
{
    // Aca armamos la implementación del menú de pacientes
    int opcion;
    do
    {
        cout << " MENU PACIENTES " << endl;
        cout << "1. Registrar nuevo paciente" << endl;
        cout << "2. Ver lista de pacientes (Nombres)" << endl;
        cout << "3. Filtrar y gestionar pacientes por nombre y apellido" << endl;
        cout << "4. Buscar y gestionar paciente por dni" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
        {
            registrarPaciente(sistema); // llamamos a la función para registrar un paciente
            break;
        }
        case 2:
        {
            listarPacientes(sistema); // llamamos a la función para listar los pacientes
            break;
        }
        case 3:
        {
            string nombre, apellido;
            cout << "NOMBRE completo del paciente buscado: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "APELLIDO completo del paciente buscado: ";
            getline(cin, apellido);
            vector<Paciente *> encontrados = sistema.filtrarPorNombreApellidoPaciente(nombre, apellido);
            if (encontrados.empty())
            {
                cout << "No se encontraron pacientes con ese nombre y apellido." << endl;
            }
            else
            {
                cout << "Pacientes encontrados:" << endl;
                for (size_t i = 0; i < encontrados.size(); i++)
                {
                    Paciente *p = encontrados[i];
                    {
                        cout << i << ". " << p->getApellido() + ", " + p->getNombre() << ". DNI: " << p->getDni() << endl;
                    }
                }
                cout << "Ingrese el numero del paciente que desea gestionar: ";
                size_t indice;
                cin >> indice;
                gestionarPacientePorIndice(sistema, encontrados, indice);
            }
            break;
        }
        case 4:
        {
            string dniBuscado;
            cout << "Dni del paciente buscado: ";
            cin >> dniBuscado;
            Paciente *p = sistema.buscarPacientePorDni(dniBuscado);
            if (p == nullptr)
            {
                cout << "No se encontró un paciente con ese dni." << endl;
            }
            else
            {
                gestionarPaciente(sistema, p);
            }
            break;
        }
        case 0:
        {
            cout << "Volver al menu principal" << endl;
            break;
        }
        default:
        {
            cout << "No funciono, intente nuevamente" << endl;
            break;
        }
        }
    } while (opcion != 0);
}

void menuKinesiologos(Consultorio &sistema)
{
    // Acá armamos la implementación del menú de kinesiologos
    int opcion;
    do
    {
        cout << " MENU KINESIOLOGOS " << endl;
        cout << "1. Registrar nuevo kinesiologo" << endl;
        cout << "2. Ver lista de kinesiologos (Nombres)" << endl;
        cout << "3. Filtrar y gestionar kinesiologos por nombre y apellido" << endl;
        cout << "4. Buscar y gestionar kinesiologo por dni" << endl; // nuevamente fucniones aux para manejar todo por kinesiologo
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; // leemos la opción del usuario
        cin.ignore();
        switch (opcion)
        {
        case 1:
        {
            registrarkinesiologo(sistema);
            break;
        }
        case 2:
        {
            listarKinesiologos(sistema);
            break;
        }
        case 3:
        {
            string nombreBuscado, apellidoBuscado;
            cout << "Nombre del kinesiologo buscado: ";
            getline(cin, nombreBuscado);
            cout << "Apellido del kinesiologo buscado: ";
            getline(cin, apellidoBuscado);
            vector<Kinesiologo *> encontrados = sistema.filtrarPorNombreApellidoKinesiologo(nombreBuscado, apellidoBuscado);
            if (encontrados.empty())
            {
                cout << "No se encontraron kinesiologos con ese nombre y apellido." << endl;
            }
            else
            {
                cout << "Kinesiologos encontrados:" << endl;
                for (size_t i = 0; i < encontrados.size(); i++)
                {
                    Kinesiologo *k = encontrados[i];
                    {
                        cout << i << ". " << k->getApellido() + ", " + k->getNombre() << ", DNI: " << k->getDni() << endl;
                    }
                }
                cout << "Ingrese el número del kinesiologo que desea gestionar: ";
                size_t indice;
                cin >> indice;
                gestionarKinesiologoPorIndice(sistema, encontrados, indice);
            }
            break;
        }
        case 4:
        {
            string dniBuscado;
            cout << "Dni del kinesiologo buscado: ";
            cin >> dniBuscado;
            Kinesiologo *k = sistema.buscarKinesiologoPorDni(dniBuscado);
            if (k == nullptr)
            {
                cout << "No se encontró un kinesiologo con ese dni." << endl;
            }
            else
            {
                gestionarKinesiologo(sistema, k);
            }
            break;
        }
        case 0:
        {
            cout << "Volviendo al menu principal..." << endl;
            break;
        }
        default:
        {
            cout << "Opcion invalida, intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 0);
}

void menuTurnos(Consultorio &sistema)
{
    int opcion;
    do
    {
        cout << "GESTION DE TURNOS " << endl;       // todas funciones aux por cada meno en cada case
        cout << "1. Reservar nuevo Turno " << endl; // reservar turno
        cout << "2. Ver agenda " << endl;           // ver todos los turnos
        cout << "3. Modificar Turno " << endl;      // reprogramar turno
        cout << "4. Cancelar Turno " << endl;       // cancelar turno
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion; // leemos la opción del usuario

        switch (opcion)
        {
        case 1:
        {
            reservarTurno(sistema);
            break;
        }
        case 2:
        {
            verAgenda(sistema);
            break;
        }
        case 3:
        {
            modificarTurno(sistema);
            break;
        }
        case 4:
        {
            cancelarTurno(sistema);
            break;
        }
        case 0:
        {
            cout << "Volver al menu principal" << endl;
            break;
        }
        default:
        {
            cout << "Opcion invalida, intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 0);
}