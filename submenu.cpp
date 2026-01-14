#include "Consultorio.h"
#include "submenu.h"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

/// LÓGICA PARA PACIENTES
void registrarPaciente(Consultorio &sistema)
{

    // Crear el paciente nuevo en memoria
    Paciente *p = new Paciente();

    // Variables auxiliares para leer los datos
    string textoAux;
    int numeroAux;
    Fecha fechaAux;

    cout << "REGISTRAR NUEVO PACIENTE" << endl;
    cout << "-Ingrese nombre y apellido por separado-" << endl;
    cout << "Ingrese Nombre: ";
    cin.ignore();
    getline(cin, textoAux);
    p->setNombre(textoAux);

    cout << "Ingrese Apellido: ";
    getline(cin, textoAux);
    p->setApellido(textoAux);
    cout << "Ingrese dni: ";
    cin >> textoAux;
    
    // Verificar si el DNI ya existe
    bool dniValido = false;
    while (!dniValido) {
        bool existe = false;
        for (const auto &pac : sistema.getPacientes()) {
            if (pac->getDni() == textoAux) {
                existe = true;
                break;
            }
        }
        if (existe) {
            cout << "Error: Ya existe un paciente con ese DNI. Ingrese otro: ";
            cin >> textoAux;
        } else {
            dniValido = true;
        }
    }
    
    p->setDni(textoAux);

    // Pedir teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> textoAux;
    p->setTelefono(textoAux);

    // La Fecha (es un struct, hay que llenarlo parte por parte)
    cout << "Fecha de Inicio " << endl;
    
    bool fechaCorrecta = false;
    
    do {
        cout << "Dia(DD): ";
        cin >> fechaAux.dia;
        
        cout << "Mes(MM): ";
        cin >> fechaAux.mes;
        
        cout << "Anio(AAAA): ";
        cin >> fechaAux.anio;

        // Llamamos a la función de validación
        if (esFechaValida(fechaAux.dia, fechaAux.mes, fechaAux.anio)) {
            fechaCorrecta = true; // Salimos del bucle
        } else {
            cout << "ERROR: Fecha invalida " << endl;
            cout << "Por favor, ingrese la fecha nuevamente " << endl;
        }

    } while (fechaCorrecta == false);

    p->setFechaDeInicio(fechaAux);

    // (Diagnóstico y Obra Social)
    cin.ignore();

    cout << "Ingrese Diagnostico: ";
    getline(cin, textoAux);
    p->setDiagnostico(textoAux);

    cout << "Ingrese Obra Social: ";
    getline(cin, textoAux);
    p->setObraSocial(textoAux);

    cout << "Cantidad de sesiones totales asignadas: ";
    cin >> numeroAux;
    p->setCantSesionesTotales(numeroAux);

    // Configuramos valores por defecto (empieza con 0 hechas y no pagó aún)
    p->setCantidadSesionesRealizadas(0);
    p->marcarComoPendiente(); // Por defecto debe plata

    // Guardar en el consultorio
    sistema.agregarPaciente(p);
    // Y luego lo guardo en mi archivo binario
    sistema.guardarPacientes("pacientes.dat");

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
        cout << setw(3) << right << (i) << ". "
             << setw(25) << left << p->getApellido() + " " + p->getNombre() << ". "
             << setw(12) << left << "Dni: " + p->getDni() << ". "
             << setw(12) << left << "Tel: " + p->getTelefono() << ". "
             << setw(20) << left << "Obra social: " + p->getObraSocial() << ". "
             << setw(10) << left << "Sesiones: " + to_string(p->getCantidadSesionesRealizadas()) + "/" + to_string(p->getCantSesionesTotales()) << ".";
        cout << endl;
    }
    cout << "-Siguiente-" << endl;
    cout << endl;
}

void gestionarPaciente(Consultorio &sistema, Paciente *p)
{
    int opcion;
    do
    {
        // Muestro los datos primero, y luego ofrezco modificarlos o utilizarlos para otra cosa
        cout << "GESTION DEL PACIENTE: " << p->getNombre() << " " << p->getApellido() << endl;
        cout << "Dni: " << p->getDni() << endl;
        cout << "telefono: " << p->getTelefono() << endl;
        cout << "Obra social: " << p->getObraSocial() << endl;
        cout << "Cantidad de Sesiones Totales: " << p->getCantSesionesTotales() << endl;
        cout << "Cantidad de Sesiones Realizadas: " << p->getCantidadSesionesRealizadas() << endl;
        cout << "Observaciones: " << p->getObservaciones() << endl;
        if (p->getSesionesPagas())
        {
            cout << "Estado de sesiones: Sesiones pagas" << endl;
        }
        else
        {
            cout << "Estado de sesiones: Falta pagar las sesiones" << endl;
        }
        cout << "¿ QUE MODIFICACIONES DESEA REALIZAR ?" << endl
             << "1. Modificar el nombre del paciente" << endl
             << "2. Modificar el apellido del paciente" << endl
             << "3. Modificar el dni del paciente" << endl
             << "4. Modificar el telefono del paciente" << endl
             << "5. Modificar la obra social del paciente" << endl
             << "6. Modificar la cantidad de sesiones totales del paciente" << endl
             << "7. Modificar las observaciones del paciente" << endl
             << "8. Marcar sesiones como pagas" << endl
             << "9. Marcar sesiones como pendientes de pago" << endl
             << "10. Borrar paciente" << endl
             << "0. Regresar al menu principal" << endl;

        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(); // limpio el buffer porque uso getline en algunos casos
        switch (opcion)
        {
        case 1: // Modificar nombre
        {
            string nuevoNombre;
            cout << "Ingrese el nombre: ";
            getline(cin, nuevoNombre);
            p->setNombre(nuevoNombre);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 2: // Modificar apellido
        {
            string nuevoApellido;
            cout << "Ingrese el apellido: ";
            getline(cin, nuevoApellido);
            p->setApellido(nuevoApellido);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 3: // Modificar DNI
        {
            string nuevoDni;
            cout << "Ingrese el nuevo DNI: ";
            cin >> nuevoDni;
            p->setDni(nuevoDni);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 4: // Modificar teléfono
        {
            string nuevoTelefono;
            cout << "Ingrese el telefono: ";
            cin >> nuevoTelefono;
            p->setTelefono(nuevoTelefono);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 5: // Modificar obra social
        {
            string nuevaObraSocial;
            cout << "Ingrese la obra social del paciente: ";
            getline(cin, nuevaObraSocial);
            p->setObraSocial(nuevaObraSocial);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 6: // Modificar cantidad de sesiones totales
        {
            int nuevaCant;
            cout << "Ingrese la nueva cantidad de sesiones totales: ";
            cin >> nuevaCant;
            p->setCantSesionesTotales(nuevaCant);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 7: // Modificar observaciones
        {
            int subOpcionDelMenu;
            cout << "Ingrese " << endl;
            cout << "1. Si desea agregar observaciones nuevas." << endl;
            cout << "2. Si desea borrar las observaciones viejas y agregar unas nuevas." << endl;
            do
            {
                cin >> subOpcionDelMenu;
                if (subOpcionDelMenu == 1)
                {
                    string observaciones;
                    cout << "Ingrese las observaciones a agregar: ";
                    cin.ignore();
                    getline(cin, observaciones);
                    p->setObservaciones(observaciones);
                    sistema.guardarPacientes("pacientes.dat");
                }
                else if (subOpcionDelMenu == 2)
                {
                    p->borrarObservaciones();
                    string observaciones;
                    cout << "Ya se borraron todas las observaciones. Ingrese las nuevas observaciones: ";
                    getline(cin, observaciones);
                    p->setObservaciones(observaciones);
                    sistema.guardarPacientes("pacientes.dat");
                }
                else
                {
                    cout << "Ingrese una opción válida por favor." << endl;
                }
            } while (subOpcionDelMenu != 1 && subOpcionDelMenu != 2);
            break;
        }
        case 8: // Marcar sesiones como pagas
        {
            p->marcarComoPagado();
            sistema.guardarPacientes("pacientes.dat");
            cout << "Las sesiones del paciente han sido marcadas como pagadas." << endl;
            break;
        }
        case 9: // Marcar sesiones como pendientes de pago
        {
            p->marcarComoPendiente();
            sistema.guardarPacientes("pacientes.dat");
            cout << "Las sesiones del paciente han sido marcadas como pendientes de pago." << endl;
            break;
        }
        case 10: // Borrar paciente
        {
            sistema.eliminarPacientePorDni(p->getDni());
            sistema.guardarPacientes("pacientes.dat");
            cout << "Paciente eliminado del sistema." << endl;
            break;
        }
        case 0:
        {
            cout << "Volver al menu principal" << endl;
            break;
        }
        default:
        {
            cout << "No funciono, intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 0);
}

void gestionarPacientePorIndice(Consultorio &sistema, const vector<Paciente *> &pacientes, size_t indice) {
    if (indice < pacientes.size()) {
        Paciente *p = pacientes[indice];
        gestionarPaciente(sistema, p);
    } else {
        cout << "Índice inválido. Por favor, intente nuevamente." << endl;
    }
}

/// LÓGICA PARA KINESIOLOGOS
void listarKinesiologos(const Consultorio &sistema)
{
    // Obtenemos la copia de la lista de kinesiologos
    vector<Kinesiologo *> kinesiologos = sistema.getKinesiologos();
    sort(kinesiologos.begin(), kinesiologos.end());

    if (kinesiologos.empty())
    {
        cout << "No hay kinesiólogos registrados en el sistema." << endl;
        return;
    }

    for (size_t i = 0; i < kinesiologos.size(); i++)
    {
        Kinesiologo *k = kinesiologos[i];
        if (k == nullptr) continue; // Evitar punteros nulos
        cout << setw(3) << right << (i + 1) << ". "
             << setw(25) << left << (k->getApellido() + ", " + k->getNombre()) << ". "
             << setw(12) << left << "Dni: " << k->getDni() << " "
             << setw(12) << left << "Telefono: " << k->getTelefono() << " "
             << setw(30) << left << "Especialidad: " << k->getEspecialidad() << " "
             << setw(20) << left << "Matricula: " << to_string(k->getMatricula()) << endl;
    }
    cout << endl << "-Siguiente-" << endl << endl;
}

void registrarkinesiologo(Consultorio &sistema)
{

    // Crear el kinesiologo nuevo en memoria
    Kinesiologo *k = new Kinesiologo();

    // Variables auxiliares para leer los datos
    string textoAux;
    int numeroAux;

    cout << "REGISTRAR NUEVO KINESIOLOGO" << endl;
    cout << "-Ingrese nombre y apellido por separado-" << endl;
    cout << "Ingrese nombre: ";
    getline(cin, textoAux);
    k->setNombre(textoAux);

    // Pido el apellido
    cout << "Ingrese Apellido: ";
    getline(cin, textoAux);
    k->setApellido(textoAux);

    // Pido el dni
    cout << "Ingrese dni: ";
    cin >> textoAux;
    
    // Verificar si el DNI ya existe
    bool dniValido = false;
    while (!dniValido) {
        bool existe = false;
        for (const auto &kin : sistema.getKinesiologos()) {
            if (kin->getDni() == textoAux) {
                existe = true;
                break;
            }
        }
        if (existe) {
            cout << "Error: Ya existe un kinesiólogo con ese DNI. Ingrese otro: ";
            cin >> textoAux;
        } else {
            dniValido = true;
        }
    }
    
    k->setDni(textoAux);

    // Pido el teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> textoAux;
    k->setTelefono(textoAux);
    cin.ignore(); // porque mi ultima lectura fue con un cin y la prox va a ser un getline

    // Pido especialidad
    cout << "Ingrese Especialidad (ej: Traumatologia, Deportiva): ";
    getline(cin, textoAux);
    k->setEspecialidad(textoAux);

    // Pido el nro de matrícula
    cout << "Ingrese Numero de Matricula: ";
    cin >> numeroAux;
    k->setMatricula(numeroAux);
    k->setCantPacientesAtendidos(0);

    // Luego lo pusheo en mi vector de kinesiologos
    sistema.agregarKinesiologo(k);
    // Y lo guardo en mi archivo binario
    sistema.guardarKinesiologos("kinesiologos.dat");

    cout << "Kinesiologo registrado con exito" << endl;
}

void gestionarKinesiologo(Consultorio &sistema, Kinesiologo *k)
{
    int opcion;
    do
    {
        // Muestro los datos primero, y luego ofrezco modificarlos o utilizarlos para otra cosa
        cout << "GESTION DEL KINESIOLOGO: " << k->getNombre() << " " << k->getApellido() << endl;
        cout << "Dni: " << k->getDni() << ". "
             << "Telefono: " << k->getTelefono() << ". "
             << "Especialidad: " << k->getEspecialidad() << ". "
             << "Matrícula: " << k->getMatricula()
             << "Cantidad de pacientes atendidos: " << k->getCantidadPacientesAtendidos() << endl;

        cout << "¿ QUE MODIFICACIONES DESEA REALIZAR ?" << endl
             << "1. Modificar el nombre del kinesiologo" << endl
             << "2. Modificar el apellido del kinesiolgo" << endl
             << "3. Modificar el DNI" << endl
             << "4. Modificar el telefono" << endl
             << "5. Modificar la especialidad" << endl
             << "6. Modificar la matrícula" << endl
             << "7. Modificar la cantidad de pacientes atendidos" << endl
             << "8. Borrar este kinesiologo" << endl
             << "0. Regresar al menu principal"
             << endl;
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            string nuevoNombre;
            cout << "Ingrese el nombre: ";
            getline(cin, nuevoNombre);
            k->setNombre(nuevoNombre);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 2:
        {
            string apellido;
            cout << "Ingrese el apellido: ";
            getline(cin, apellido);
            k->setApellido(apellido);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 3:
        {
            string nuevoDni;
            cout << "Ingrese el nuevo DNI: ";
            cin >> nuevoDni;
            k->setDni(nuevoDni);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 4:
        {
            string nuevoTel;
            cout << "Ingrese el telefono: ";
            cin >> nuevoTel;
            k->setTelefono(nuevoTel);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 5:
        {
            int subOpcionEspecialidad;
            cout << "1. Agregar una especialidad nueva" << endl;
            cout << "2. Borrar la/s especialidad/es anterior/es y agregar una/s nueva/s" << endl;
            do
            {
                cin >> subOpcionEspecialidad;
                cin.ignore();
                if (subOpcionEspecialidad == 1)
                {
                    string nuevaEspecialidad;
                    cout << "Ingrese la nueva especialidad: ";
                    getline(cin, nuevaEspecialidad);
                    k->setEspecialidad(nuevaEspecialidad);
                    sistema.guardarKinesiologos("kinesiologos.dat");
                }
                else if (subOpcionEspecialidad == 2)
                {
                    k->borrarEspecialidad();
                    string nuevaEspecialidad;
                    cout << "Ya se borraron las especialidades. Ingrese la/s nueva/s especialidad/es: ";
                    getline(cin, nuevaEspecialidad);
                    k->setEspecialidad(nuevaEspecialidad);
                    sistema.guardarKinesiologos("kinesiologos.dat");
                }
                else
                {
                    cout << "Ingrese una opción válida por favor." << endl;
                }
            } while (subOpcionEspecialidad != 1 && subOpcionEspecialidad != 2);
            break;
        }
        case 6:
        {
            int nuevaMatricula;
            cout << "Ingrese la nueva matrícula: ";
            cin >> nuevaMatricula;
            k->setMatricula(nuevaMatricula);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 7:
        {
            int nuevaCant;
            cout << "Ingrese la nueva cantidad de pacientes atendidos: ";
            cin >> nuevaCant;
            k->setCantPacientesAtendidos(nuevaCant);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 8:
        {
            string dniKine;
            cout << "Ingrese el dni del kinesiologo a eliminar: ";
            cin >> dniKine;
            sistema.eliminarKinesiologoPorDni(dniKine);
            break;
        }
        case 0:
        {
            cout << "Volver al menu principal" << endl;
            break;
        }
        default:
        {
            cout << "No funcionó, intente nuevamente" << endl;
            break;
        }
        }
    } while (opcion != 0);
}

void gestionarKinesiologoPorIndice(Consultorio &sistema, const vector<Kinesiologo *> &encontrados, size_t indice) {
    if (indice < encontrados.size()) {
        Kinesiologo *k = encontrados[indice];
        gestionarKinesiologo(sistema, k);
    } else {
        cout << "Indice invalido. Por favor, intente nuevamente." << endl;
    }
}

/// LÓGICA PARA TURNOS
void reservarTurno(Consultorio &sistema)
{
    cout << "RESERVAR TURNO" << endl;
    cin.ignore();

    string nombrePac, apellidoPac, dniPaciente;
    cout << "Ingrese el nombre del paciente: ";
    getline(cin, nombrePac);
    cout << "Ingrese el apellido del paciente: ";
    getline(cin, apellidoPac);
    cout << "Ingrese el dni del paciente: ";
    cin >> dniPaciente;
    Paciente *paciente = sistema.buscarPacientePorDni(dniPaciente);
    if (paciente == nullptr)
    {
        cout << "Error: No se encontro un paciente con ese dni." << endl;
        return;
    }

    string nombreKine, apellidoKine, dniKine;
    cout << "Ingrese el nombre del kinesiologo: ";
    cin.ignore();
    getline(cin, nombreKine);
    cout << "Ingrese el dni del kinesiólogo: ";
    cin >> dniKine;
    if (sistema.buscarKinesiologoPorDni(dniKine) == nullptr)
    {
        cout << "Error: No se encontro un kinesiologo con ese dni." << endl;
        return;
    }

    Turno nuevoT;
    nuevoT.nombrePaciente = nombrePac;
    nuevoT.nombreKinesiologo = nombreKine;
    nuevoT.dniKinesiologo = dniKine;
    nuevoT.dniPaciente = dniPaciente;
    cout << "Ingrese la fecha del turno: " << endl;
    cout << "Dia(formato DD): ";
    cin >> nuevoT.fecha.dia;
    cout << "Mes(formato MM): ";
    cin >> nuevoT.fecha.mes;
    cout << "Anio(formato AAAA): ";
    cin >> nuevoT.fecha.anio;

    cout << "Ingrese la hora del turno (formato HH:MM): ";
    cin >> nuevoT.hora;

    char respuesta;
    cout << "Requiere Camilla? (s/n): ";
    cin >> respuesta;
    // Si pone 's' o 'S', es true. Si no, false.
    nuevoT.requiereCamilla = (respuesta == 's' || respuesta == 'S');

    cout << "Requiere Gimnasio? (s/n): ";
    cin >> respuesta;
    nuevoT.requiereGimnasio = (respuesta == 's' || respuesta == 'S');

    nuevoT.estadoDelTurno = "Programado";

    cin.ignore();
    cout << "Observacion para el turno: ";
    getline(cin, nuevoT.observaciones);

    // Validar Kinesiologo
    if (sistema.verificarDisponibilidadKinesiologo(dniKine, nuevoT.fecha, nuevoT.hora) == false)
    {
        cout << ">>> Error: El Kinesiologo ya tiene un turno a esa hora." << endl;
        return;
    }

    // Validar Camilla (Solo si la pidió)
    if (nuevoT.requiereCamilla == true)
    {
        if (sistema.verificarDisponibilidadCamilla(nuevoT.fecha, nuevoT.hora) == false)
        {
            cout << ">>> Error: No hay camillas disponibles a esa hora (Todas ocupadas)." << endl;
            return;
        }
    }

    // Validar Gimnasio (Solo si lo pidió)
    if (nuevoT.requiereGimnasio == true)
    {
        if (sistema.verificarDisponibilidadGimnasio(nuevoT.fecha, nuevoT.hora) == false)
        {
            cout << ">>> Error: El gimnasio está lleno a esa hora." << endl;
            return;
        }
    }

    sistema.agregarTurno(nuevoT);
    // Actualizar sesiones del paciente
    paciente->setCantidadSesionesRealizadas(paciente->getCantidadSesionesRealizadas() + 1);
    sistema.guardarPacientes("pacientes.dat");
    cout << "TURNO AGENDADO CON EXITO. Sesiones realizadas actualizadas." << endl;
}

void verAgenda(Consultorio &sistema)
{
    // Ordenar la agenda cronológicamente
    sistema.ordenarTurnos();

    // Obtener la lista
    vector<Turno> lista = sistema.getTurnos();

    cout << " AGENDA DE TURNOS " << endl;

    // Verificar si está vacía
    if (lista.empty())
    {
        cout << "No hay turnos registrados en la agenda." << endl;
    }
    else
    {
        for (size_t i = 0; i < lista.size(); i++)
        {
            Turno t = lista[i];

            cout << setw(3) << right << (i + 1) << ". "
                 // Formato de fecha [DD/MM/AAAA - HH:MM]
                 << setw(20) << left << "[" << t.fecha.dia << "/" << t.fecha.mes << "/" << t.fecha.anio << " - " << t.hora << "] "
                 << setw(25) << left << "Paciente: " << t.nombrePaciente
                 << setw(25) << left << " Kinesiólogo: " << t.nombreKinesiologo
                 << setw(15) << left << " (" << t.estadoDelTurno << ")";
            if (t.requiereCamilla)
            {
                cout << " [Cam]";
            }
            if (t.requiereGimnasio)
            {
                cout << " [Gim]";
            }
            cout << "Observaciones: " << t.observaciones << endl;
        }
    }
    cout << "Siguiente" << endl;
}


void modificarTurno(Consultorio &sistema)
{
    cout << "REPROGRAMAR TURNO " << endl;

    cin.ignore();

    // Pedimos los datos para encontrar el turno viejo
    string dniPaciente;
    cout << "Ingrese el DNI del Paciente: ";
    cin >> dniPaciente;
    Fecha fechaVieja;
    string horaVieja;

    cout << "Datos del Turno ACTUAL (El que quiere cambiar) " << endl;
    cout << "Hora del turno a reprogramar(HH:MM): ";
    cin >> horaVieja;
    cout << "Dia: ";
    cin >> fechaVieja.dia;
    cout << "Mes: ";
    cin >> fechaVieja.mes;
    cout << "Anio: ";
    cin >> fechaVieja.anio;
    

    // Pedimos los datos para el nuevo horario
    Fecha fechaNueva;
    string horaNueva;

    cout << " Datos del NUEVO Horario " << endl;
    cout << "Nuevo Dia: ";
    cin >> fechaNueva.dia;
    cout << "Nuevo Mes: ";
    cin >> fechaNueva.mes;
    cout << "Nuevo Anio: ";
    cin >> fechaNueva.anio;
    cout << "Nueva Hora (HH:MM): ";
    cin >> horaNueva;

    sistema.reprogramarTurno(dniPaciente, horaVieja, fechaVieja, fechaNueva, horaNueva);
}

void cancelarTurno(Consultorio &sistema)
{
    cout << " CANCELAR TURNO " << endl;

    cin.ignore();

    // Pedimos los datos para identificar el turno
    string dniPac;
    cout << "Ingrese el DNI del Paciente: ";
    getline(cin, dniPac);

    Fecha fecha;
    string hora;

    cout << " Datos del Turno a ELIMINAR " << endl;
    cout << "Dia: ";
    cin >> fecha.dia;
    cout << "Mes: ";
    cin >> fecha.mes;
    cout << "Anio: ";
    cin >> fecha.anio;
    cout << "Hora (HH:MM): ";
    cin >> hora;

    cin.ignore();

    char respuesta;
    cout << "¿Estas seguro que queres cancelar este turno? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S')
    {
        sistema.cancelarTurno(dniPac, fecha, hora);
        // Actualizar sesiones del paciente
        Paciente *paciente = sistema.buscarPacientePorDni(dniPac);
        if (paciente != nullptr)
        {
            int realizadas = paciente->getCantidadSesionesRealizadas();
            if (realizadas > 0)
                paciente->setCantidadSesionesRealizadas(realizadas - 1);
            sistema.guardarPacientes("pacientes.dat");
        }
        cout << " Turno cancelado con exito y sesiones actualizadas." << endl;
    }
    else
    {
        cout << " Operacion cancelada. El turno sigue activo." << endl;
    }
}
