#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <vector>
#include "Fecha.h"
#include "Consultorio.h"
#include "Paciente.h"
#include "Kinesiologo.h"
#include <ctime>

/// FUNCIONES AUXILIARES

// Funcion para obtener la fecha actual en formato entero
int obtenerFechaActual()
{
    // acá obtengo los segundos que pasaron desde el 01/01/1970
    time_t t = time(0);         // time_t es un tipo de dato para guardar fechas
    tm *tiempo = localtime(&t); // localtime transforma la variable time_t en un struct legible
    return (tiempo->tm_year + 1900) * 10000 +
           (tiempo->tm_mon + 1) * 100 +
           tiempo->tm_mday;
}

// Función para leer fecha cómodamente
Fecha pedirFecha()
{
    Fecha f;
    cout << "   Dia: ";
    cin >> f.dia;
    cout << "   Mes: ";
    cin >> f.mes;
    cout << "   Anio: ";
    cin >> f.anio;
    return f;
}

// LOGICA PACIENTES
void registrarPaciente(Consultorio &sistema)
{

    // Crear el paciente nuevo en memoria
    Paciente *nuevoP = new Paciente();

    // Variables auxiliares para leer los datos
    string textoAux;
    int numeroAux;
    Fecha fechaAux;

    cout << "REGISTRAR NUEVO PACIENTE" << endl;
    // Usamos cin.ignore() al principio por si quedó basura del menú anterior
    cin.ignore();

    cout << "Ingrese Nombre: ";
    getline(cin, textoAux);
    nuevoP->setNombre(textoAux);

    cout << "Ingrese Apellido: ";
    getline(cin, textoAux);
    nuevoP->setApellido(textoAux);

    // Pedir teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> numeroAux;
    nuevoP->setTelefono(numeroAux);

    // La Fecha (es un struct, hay que llenarlo parte por parte)
    cout << "Fecha de Inicio " << endl;
    cout << "Dia: ";
    cin >> fechaAux.dia;
    cout << "Mes: ";
    cin >> fechaAux.mes;
    cout << "Año: ";
    cin >> fechaAux.anio;

    nuevoP->setFechaDeInicio(fechaAux);

    // (Diagnóstico y Obra Social)
    cin.ignore();

    cout << "Ingrese Diagnostico: ";
    getline(cin, textoAux);
    nuevoP->setDiagnostico(textoAux);

    cout << "Ingrese Obra Social: ";
    getline(cin, textoAux);
    nuevoP->setObraSocial(textoAux);

    cout << "Cantidad de sesiones totales asignadas: ";
    cin >> numeroAux;
    nuevoP->setCantSesionesTotales(numeroAux);

    // Configuramos valores por defecto (empieza con 0 hechas y no pagó aún)
    nuevoP->setCantidadSesionesRealizadas(0);
    nuevoP->marcarComoPendiente(); // Por defecto debe plata

    // Guardar en el consultorio
    sistema.agregarPaciente(nuevoP);

    cout << "Paciente registrado con exito! " << endl;
}

void listarPacientes(Consultorio &sistema)
{

    // Obtenemos la copia de la lista de pacientes
    vector<Paciente *> pacientes = sistema.getPacientes();

    cout << "LISTADO DE PACIENTES" << endl;

    if (pacientes.empty() == true)
    {
        cout << "No hay pacientes registrados en el sistema." << endl;
        return;
    }

    for (size_t i = 0; i < pacientes.size(); i++)
    {

        Paciente *p = pacientes[i];
        cout << i << " " << p->getApellido() << " " << p->getNombre();

        // Mostramos su obra social y la cantidad de sesiones que lleva
        cout << " Obra social" << p->getObraSocial();
        cout << " Sesiones: " << p->getCantidadSesionesRealizadas() << "/" << p->getCantSesionesTotales();
        cout << endl;
    }
    cout << "-Siguiente-" << endl;
}

// LOGICA PARA BUSCAR Y GESTIONAR PACIENTE CON SU SUB MENU
void gestionarPaciente(Paciente *p)
{
    int opcion;
    do
    {
        // Muestro los datos primero, y luego ofrezco modificarlos o utilizarlos para otra cosa
        cout << "GESTION DEL PACIENTE: " << p->getNombre() << " " << p->getApellido() << endl;
        cout << "Teléfono: " << p->getTelefono() << endl;
        cout << "Obra social: " << p->getObraSocial() << endl;
        cout << "Cantidad de Sesiones Totales: " << p->getCantSesionesTotales() << endl;
        cout << "Cantidad de Sesiones Realizadas: " << p->getCantidadSesionesRealizadas() << endl;
        cout << "Observaciones: " << p->getObservaciones() << endl;
        if (p->getSesionesPagas())
        {
            cout << "Sesiones pagas" << endl;
        }
        else
        {
            cout << "Falta pagar las sesiones" << endl;
        }
        cout << "¿ QUE MODIFICACIONES DESEA REALIZAR ?" << endl 
        << "1. Modificar el nombre del paciente" << endl
        << "2. Modificar el apellido del paciente" << endl
        << "3. Modificar el teléfono del paciente" << endl
        << "4. Modificar la obra social del paciente" << endl
        << "5. Modificar la cantidad de sesiones totales del paciente" << endl
        << "6. Modificar las observaciones del paciente" << endl
        << "0. Regresar al menú principal" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(); // limpio el buffer porque uso getline en algunos casos
        switch (opcion)
        {
        case 1:
            string nuevoNombre;
            cout << "Ingrese el nombre: ";
            getline(cin, nuevoNombre);
            p->setNombre(nuevoNombre);
            break;
        case 2:
            string nuevoApellido;
            cout << "Ingrese el apellido: ";
            getline(cin, nuevoApellido);
            p->setApellido(nuevoApellido);
            break;
        case 3:
            int nuevoTelefono;
            cout << "Ingrese el teléfono: ";
            cin >> nuevoTelefono;
            p->setTelefono(nuevoTelefono);
            break;
        case 4:
            string nuevaObraSocial;
            cout << "Ingrese la obra social: ";
            getline(cin, nuevaObraSocial);
            p->setObraSocial(nuevaObraSocial);
            break;
        case 5:
            int subOpcionObservaciones;
            cout << "1. Agregar observaciones" << endl
            << "2. Borrar observaciones anteriores y anotar nuevas observaciones" << endl;
            cin >> subOpcionObservaciones;
            cin.ignore(); // limpio el buffer después de haber usado el cin en vez de getline
            if (subOpcionObservaciones == 1)
            {
                string observaciones;
                cout << "Ingrese las observaciones a agregar: ";
                getline(cin, observaciones);
                p->setObservaciones(observaciones);
            }
            else
            {
                p->borrarObservaciones();
                string observaciones;
                cout << "Ya se borraron todas las observaciones. Ingrese las nuevas observaciones: ";
                getline(cin, observaciones);
                p->setObservaciones(observaciones);
            }
            break;
        case 0:
            cout << "Volver al menú principal" << endl;
            break;
        default:
            cout << "No funciono, intente nuevamente." << endl;
            break;
        }
    } while (opcion != 0);
}
// Lógica Kinesiólogo
void registrarkinesiologo(Consultorio &sistema)
{
    Kinesiologo *k = new Kinesiologo();
    string textoAux;
    int numeroAux;
    // Pido el nombre
    cout << "REGISTRAR NUEVO KINESIOLOGO" << end1;
    cin.ignore();
    cout << "Ingrese nombre: ";
    getline(cin, textoAux);
    k->setNombre(textoAux);
    // Pido el apellido
    cout << "Ingrese apellido: ";
    getline(cin, textoAux);
    k->setApellido(textoAux);
    // Pido el teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> numeroAux;
    k->setTelefono(numeroAux);
    cin.ignore(); // porque mi última lectura fue con un cin y la prox va a ser un getline
    // Pido especialidad
    cout << "Ingrese Especialidad (ej: Traumatologia, Deportiva): "; getline(cin, textoAux);
    k->setEspecialidad(textoAux);
    // Pido el nro de matrícula
    cout << "Ingrese Numero de Matricula: ";
    cin >> numeroAux;
    k->setMatricula(numeroAux);
    k->setCantPacientesAtendidos(0);
    // Y luego lo pusheo en mi vector de kinesiologos
    sistema.agregarKinesiologo(k);
    cout << "Kinesiologo registrado con exito" << endl;
}

void listarKinesiologo(const Consultorio &consultorio)
{
    // Obtenemos la copia de la lista de kinesiologos
    vector<Kinesiologo *> kinesiologos = sistema.getKinesiologos();

    cout << "LISTADO DE KINESIOLOGOS" << endl;

    if (kinesiologos.empty() == true)
    {
        cout << "No hay kinesiologos registrados en el sistema." << endl;
        return;
    }

    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        Kinesiologo *k = kinesiologos[i];
        cout << i + 1 << ". " << k->getApellido() << " " << k->getNombre();
        cout << "Tel: " << k->getTelefono() << endl;
        cout << "Especialidad: " << k->getEspecialidad() << endl;
        cout << endl;
    }
    cout << "-Siguiente-" << endl;
}

void gestionarKinesiologo(Kinesiologo *k)
{
    int opcion;
    do
    {
        // Muestro los datos primero, y luego ofrezco modificarlos o utilizarlos para otra cosa
        cout << "GESTION DEL KINESIOLOGO: " << k->getNombre() << " " << k->getApellido() << endl;
        cout << "Teléfono: " << k->getTelefono();
        cout << "Especialidad: " << k->getEspecialidad() << endl;
        cout << "Matrícula: " << k->getMatricula() << endl;
        cout << "Cantidad de pacientes atendidos: " << k->getCantidadPacientesAtendidos() << endl;
        cout << "¿ QUE MODIFICACIONES DESEA REALIZAR ?" << endl
        << "1. Modificar el nombre del kinesiologo" << endl
        << "2. Modificar el apellido del kinesiolgo" << endl
        << "3. Modificar el telefono" << endl
        << "4. Modificar la especialidad" << endl
        << "5. Modificar la matrícula" << endl
        << "6. Modificar la cantidad de pacientes atendidos" << endl;
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
            string nombre;
            cout << "Ingrese el nombre: "; getline(cin, nombre);
            k->setNombre(nombre);
            break;
        case 2:
            string apellido;
            cout << "Ingrese el apellido: "; getline(cin, apellido);
            k->setApellido(apellido);
            break;
        case 3:
            int nuevoTel;
            cout << "Ingrese el telefono: "; cin >> nuevoTel;
            k->setTelefono(nuevoTel);
            break;
        case 4:
            int subOpcionEspecialidad;
            cout << "1. Agregar una especialidad nueva" << endl
            << "2. Borrar la/s especialiadad/es anterior/es y agregar una/s nueva/s " << endl;
            cin >> subOpcionEspecialidad;
            if(subOpcionEspecialidad == 1){
                string nuevaEspecialidad;
                cout << "Ingrese la nueva especialidad: "; getline(cin, nuevaEspecialidad);
                k->setEspecialidad(nuevaEspecialidad);
            } else {
                k->borrarEspecialidad();
                string nuevaEspecialiadad;
                cout << "Ya se borraron las especialidades. Ingrese la/s nueva/s especialidad/es: "; getline(cin, nuevaEspecialiadad);
                k->setEspecialidad(nuevaEspecialiadad);
            }
            break;
        case 5:
            int nuevaMatricula;
            cout << "Ingrese la nueva matrícula: "; cin >> nuevaMatricula;
            k->setMatricula(nuevaMatricula);
            break;
        case 6:
            int nuevaCant;
            cout << "Ingrese la nueva cantidad de pacientes atendidos: "; cin >> nuevaCant;
            k->setCantPacientesAtendidos(nuevaCant);
            break;
        case 0:
            cout << "Volver al menú principal" << endl;
            break;
        default:
            cout << "No funcionó, intente nuevamente" << endl;
            break;
        }
    } while (opcion != 0)
}
// CREAMOS ESTAS FUNCIONES DE LOS MENUS PARA TENER MAS ORDENADO EL MAIN
void menuPacientes(Consultorio &sistema)
{
    // Aca armamos la implementación del menú de pacientes
    int opcion;
    do
    {
        cout << " GESTIONAR PACIENTES " << endl;
        cout << "1. Registrar nuevo paciente" << endl;
        cout << "2. Ver lista de pacientes (Nombres)" << endl;
        cout << "3. Buscar y gestionar paciente por nombre y apellido" << endl; // si encontramos nos vamos a otra funcion para hacer las gestiones especificas por paciente
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        switch (opcion)
        {
        case 1:
            registrarPaciente(sistema); // llamamos a la función para registrar un paciente
            break;
        case 2:
            listarPacientes(sistema); // llamamos a la función para listar los pacientes
            break;
        case 3:
            string nombre, apellido;
            cout << "Nombre del paciente buscado: ";
            getline(cin, nombre);
            cout << "Apellido del paciente buscado: ";
            getline(cin, apellido)
                Paciente *p = buscarPacientePorNombreYapellido(nombre, apellido);
            gestionarPaciente(p);
            break;
        case 0:
            cout << "Volver al menu principal" << endl;
            break;
        default:
            cout << "No funciono, intente nuevamente" << endl;
            break;
        }
    } while (opcion != 0);
}

void menuKinesiologos(Consultorio &sistema)
{
    // Acá armamos la implementación del menú de kinesiologos
    int opcion;
    do
    {
        cout << " GESTIONAR KINESIOLOGOS " << endl;
        cout << "1. Registrar nuevo kinesiologo" << endl;
        cout << "2. Ver lista de kinesiologos (Nombres)" << endl;
        cout << "3. Buscar y gestionar kinesiologo por nombre y apellido" << endl; // nuevamente fucniones aux para manejar todo por kinesiologo
        cout << "0. Volver al menu principal" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; // leemos la opción del usuario
        cin.ignore();
        switch (opcion)
        {
        case 1:
            registrarkinesiologo(sistema);

            break;
        case 2:
            listarKinesiologos(sistema);
            break;
        case 3:
            string nombre, apellido;
            cout << "Nombre del paciente buscado: ";
            getline(cin, nombre);
            cout << "Apellido del paciente buscado: ";
            getline(cin, apellido);
            Kinesiologo *k = buscarKinesiologoPorNombreYapellido(nombre, apellido);
            gestionarKinesiologo(k);
            break;
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida, intente nuevamente." << endl;
            break;
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
            // necesitamos funciones aux
            menuReservarTurno(sistema);
            break;
        case 2:

            menuListarTurnos(sistema);
            break;
        case 3:
            // Lógica de Reprogramación
            break;
        case 4:
            // Lógica de Cancelación
            break;
        }
    } while (opcion != 0);
}