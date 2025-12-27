#include "Consultorio.h" 
#include "submenu.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

/// LÓGICA PARA PACIENTES
void registrarPaciente(Consultorio &sistema){

    // Crear el paciente nuevo en memoria
    Paciente *nuevoP = new Paciente();

    // Variables auxiliares para leer los datos
    string textoAux;
    int numeroAux;
    Fecha fechaAux;

    cout << "REGISTRAR NUEVO PACIENTE" << endl;
    cout << "-Ingrese nombre y apellido por separado-" << endl;
    cout << "Ingrese Nombre: ";
    getline(cin, textoAux);
    nuevoP->setNombre(textoAux);

    cout << "Ingrese Apellido: ";
    getline(cin, textoAux);
    nuevoP->setApellido(textoAux);

    // Pedir teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> textoAux;
    nuevoP->setTelefono(textoAux);

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
    // Y luego lo guardo en mi archivo binario
    sistema.guardarPacientes("pacientes.dat");

    cout << "Paciente registrado con exito! " << endl;
}

void listarPacientes(Consultorio &sistema){

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
        cout << i+1 << ". " << p->getApellido() << " " << p->getNombre() << ". ";

        // Mostramos su obra social y la cantidad de sesiones que lleva
        cout << " Obra social: " << p->getObraSocial() << ". ";
        cout << " Sesiones: " << p->getCantidadSesionesRealizadas() << "/" << p->getCantSesionesTotales() << ".";
        cout << endl;
    }
    cout << "-Siguiente-" << endl;
}

void gestionarPaciente(Consultorio &sistema, Paciente *p){
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
        case 1:{
            string nuevoNombre;
            cout << "Ingrese el nombre: ";
            getline(cin, nuevoNombre);
            p->setNombre(nuevoNombre);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 2:{
            string nuevoApellido;
            cout << "Ingrese el apellido: ";
            getline(cin, nuevoApellido);
            p->setApellido(nuevoApellido);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 3:{
            string nuevoTelefono;
            cout << "Ingrese el teléfono: ";
            cin >> nuevoTelefono;
            p->setTelefono(nuevoTelefono);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 4:{
            string nuevaObraSocial;
            cout << "Ingrese la obra social: ";
            getline(cin, nuevaObraSocial);
            p->setObraSocial(nuevaObraSocial);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 5:
        {
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
                sistema.guardarPacientes("pacientes.dat");
            }
            else
            {
                p->borrarObservaciones();
                string observaciones;
                cout << "Ya se borraron todas las observaciones. Ingrese las nuevas observaciones: ";
                getline(cin, observaciones);
                p->setObservaciones(observaciones);
                sistema.guardarPacientes("pacientes.dat");
            }
            break;
        }
        case 0: {
            cout << "Volver al menú principal" << endl;
            break;
        }
        default: {
            cout << "No funciono, intente nuevamente." << endl;
            break;
        }
        }
    } while (opcion != 0);
}

/// LÓGICA PARA KINESIOLOGOS
void listarKinesiologos(const Consultorio &sistema){
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

void registrarkinesiologo(Consultorio &sistema){
    
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
    cout << "Ingrese apellido: ";
    getline(cin, textoAux);
    k->setApellido(textoAux);
    // Pido el teléfono
        cout << "Ingrese Telefono (solo numeros): ";
        cin >> textoAux;
        k->setTelefono(textoAux);
    cin.ignore(); // porque mi última lectura fue con un cin y la prox va a ser un getline
    // Pido especialidad
    cout << "Ingrese Especialidad (ej: Traumatologia, Deportiva): "; getline(cin, textoAux);
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

void gestionarKinesiologo(Consultorio &sistema ,Kinesiologo *k){
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
        case 1:{
            string nuevoNombre;
            cout << "Ingrese el nombre: "; getline(cin,nuevoNombre);
            k->setNombre(nuevoNombre);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 2: {
            string apellido;
            cout << "Ingrese el apellido: "; getline(cin, apellido);
            k->setApellido(apellido);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 3: {
            string nuevoTel;
            cout << "Ingrese el telefono: "; cin >> nuevoTel;
            k->setTelefono(nuevoTel);
            sistema.guardarPacientes("pacientes.dat");
            break;
        }
        case 4: {
            int subOpcionEspecialidad;
            cout << "1. Agregar una especialidad nueva" << endl;
            cout << "2. Borrar la/s especialiadad/es anterior/es y agregar una/s nueva/s " << endl;
            cin >> subOpcionEspecialidad;
            cin.ignore();
            if(subOpcionEspecialidad == 1){
                string nuevaEspecialidad;
                cout << "Ingrese la nueva especialidad: "; getline(cin, nuevaEspecialidad);
                k->setEspecialidad(nuevaEspecialidad);
                sistema.guardarKinesiologos("kinesiologos.dat");
            } else {
                k->borrarEspecialidad();
                string nuevaEspecialiadad;
                cout << "Ya se borraron las especialidades. Ingrese la/s nueva/s especialidad/es: "; getline(cin, nuevaEspecialiadad);
                k->setEspecialidad(nuevaEspecialiadad);
                sistema.guardarKinesiologos("kinesiologos.dat");
            }
            break;
        }
        case 5: {
            int nuevaMatricula;
            cout << "Ingrese la nueva matrícula: "; cin >> nuevaMatricula;
            k->setMatricula(nuevaMatricula);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 6: {
            int nuevaCant;
            cout << "Ingrese la nueva cantidad de pacientes atendidos: "; cin >> nuevaCant;
            k->setCantPacientesAtendidos(nuevaCant);
            sistema.guardarKinesiologos("kinesiologos.dat");
            break;
        }
        case 0: {
            cout << "Volver al menú principal" << endl;
            break;
        }
        default: {
            cout << "No funcionó, intente nuevamente" << endl;
            break;
        }
        }
    } while (opcion != 0);
}

/// LÓGICA PARA TURNOS
void reservarTurno(Consultorio &sistema){
	cout<<"RESERVAR TURNO"<<endl;
	cin.ignore();
	
	string nombrePac, apellidoPac;
	cout << "Ingrese el nombre del paciente: ";
	getline(cin, nombrePac);
	cout << "Ingrese el apellido del paciente: ";
    getline(cin, apellidoPac);
	if(sistema.buscarPacientePorNombreYapellido(nombrePac,apellidoPac) == nullptr){
		cout << "Error: No se encontro un paciente con ese nombre y apellido." << endl;
		return;
	}
	
	string nombreKine, apellidoKine;
	cout << "Ingrese el nombre del kinesiologo: ";
	getline(cin, nombreKine);
	cout << "Ingrese el nombre del kinesiologo: ";
    getline(cin, apellidoKine);
	if(sistema.buscarKinesiologoPorNombreYapellido(nombreKine,apellidoKine) == nullptr){
		cout << "Error: No se encontro un kinesiologo con ese nombre y apellido." << endl;
		return;
	}
	
	Turno nuevoT;
	nuevoT.nombrePaciente = nombrePac;
	nuevoT.nombreKinesiologo = nombreKine;
	cout << "Ingrese la fecha del turno: " << endl;
	cout << "Dia: "; cin >> nuevoT.fecha.dia;
	cout << "Mes: "; cin >> nuevoT.fecha.mes;
	cout << "Anio: "; cin >> nuevoT.fecha.anio;
	
	cout<<"Ingrese la hora del turno (formato HH:MM): ";
	cin>>nuevoT.hora;
	
	char respuesta;
	cout << "Requiere Camilla? (s/n): "; cin >> respuesta;
	// Si pone 's' o 'S', es true. Si no, false.
	nuevoT.requiereCamilla = (respuesta == 's' || respuesta == 'S');
	
	cout << "Requiere Gimnasio? (s/n): "; cin >> respuesta;
	nuevoT.requiereGimnasio = (respuesta == 's' || respuesta == 'S');
	
	nuevoT.estadoDelTurno = "Programado"; 
	
	cin.ignore();
	cout << "Observacion para el turno: "; 
	getline(cin, nuevoT.observaciones);
	
	// Validar Kinesiologo
	if (sistema.verificarDisponibilidadKinesiologo(nombreKine, nuevoT.fecha, nuevoT.hora) == false) {
		cout << ">>> Error: El Kinesiologo ya tiene un turno a esa hora." << endl;
		return;
	}
	
	// Validar Camilla (Solo si la pidió)
	if (nuevoT.requiereCamilla == true) {
		if (sistema.verificarDisponibilidadCamilla(nuevoT.fecha, nuevoT.hora) == false) {
			cout << ">>> Error: No hay camillas disponibles a esa hora (Todas ocupadas)." << endl;
			return;
		}
	}
	
	// Validar Gimnasio (Solo si lo pidió)
	if (nuevoT.requiereGimnasio == true) {
		if (sistema.verificarDisponibilidadGimnasio(nuevoT.fecha, nuevoT.hora) == false) {
			cout << ">>> Error: El gimnasio está lleno a esa hora." << endl;
			return;
		}
	}
	
	sistema.agregarTurno(nuevoT);
	cout << "TURNO AGENDADO CON EXITO" << endl;
	
}

void verAgenda(Consultorio &sistema) {
	// Ordenar la agenda cronológicamente
	sistema.ordenarTurnos();
	
	// Obtener la lista
	vector<Turno> lista = sistema.getTurnos();
	
	cout << " AGENDA DE TURNOS " << endl;
	
	// Verificar si está vacía
	if (lista.empty()) {
		cout << "No hay turnos registrados en la agenda." << endl;
		return;
	}
	
	for (size_t i = 0; i < lista.size(); i++) {
		
		Turno t = lista[i];
		
		cout << i+1  << ". ";
		
		// Formato de fecha [DD/MM/AAAA - HH:MM]
		cout << "[" << t.fecha.dia << "/" << t.fecha.mes << "/" << t.fecha.anio << " - " << t.hora << "] ";
		
		// Datos de las personas
		cout << "Paciente: " << t.nombrePaciente << " Kinesiólogo: " << t.nombreKinesiologo;
		
		// Estado y Extras
		cout << " (" << t.estadoDelTurno << ")";
		
		if (t.requiereCamilla) cout << " [Cam]";
		if (t.requiereGimnasio) cout << " [Gim]";
		
		cout << endl; 
	}
	cout << "Siguiente" << endl;
}

void modificarTurno(Consultorio &sistema) {
	cout << "REPROGRAMAR TURNO " << endl;
	
	cin.ignore(); 
	
	// Pedimos los datos para encontrar el turno viejo
	string nombrePac;
	cout << "Ingrese el nombre del Paciente: ";
	getline(cin, nombrePac);
	
	Fecha fechaVieja;
	string horaVieja;
	
	cout << "Datos del Turno ACTUAL (El que quiere cambiar) " << endl;
	cout << "Dia: "; cin >> fechaVieja.dia;
	cout << "Mes: "; cin >> fechaVieja.mes;
	cout << "Anio: "; cin >> fechaVieja.anio;
	cout << "Hora actual (HH:MM): "; cin >> horaVieja;
	
	// Pedimos los datos para el nuevo horario
	Fecha fechaNueva;
	string horaNueva;
	
	cout << " Datos del NUEVO Horario " << endl;
	cout << "Nuevo Dia: "; cin >> fechaNueva.dia;
	cout << "Nuevo Mes: "; cin >> fechaNueva.mes;
	cout << "Nuevo Anio: "; cin >> fechaNueva.anio;
	cout << "Nueva Hora (HH:MM): "; cin >> horaNueva;
	
	sistema.reprogramarTurno(nombrePac, fechaVieja, horaVieja, fechaNueva, horaNueva);
}

void cancelarTurno(Consultorio &sistema) {
	cout << " CANCELAR TURNO " << endl;
	
	cin.ignore();
	
	// Pedimos los datos para identificar el turno
	string nombrePac;
	cout << "Ingrese el nombre del Paciente: ";
	getline(cin, nombrePac);
	
	Fecha fecha;
	string hora;
	
	cout << " Datos del Turno a ELIMINAR " << endl;
	cout << "Dia: "; cin >> fecha.dia;
	cout << "Mes: "; cin >> fecha.mes;
	cout << "Anio: "; cin >> fecha.anio;
	cout << "Hora (HH:MM): "; cin >> hora;
	
	cin.ignore();
	
	char respuesta;
	cout << "¿Estas seguro que queres cancelar este turno? (s/n): ";
	cin >> respuesta;
	
	if (respuesta == 's' || respuesta == 'S') {
		sistema.cancelarTurno(nombrePac, fecha, hora);
		cout << " Turno cancelado con exito " << endl;
	} else {
		cout << " Operacion cancelada. El turno sigue activo." << endl;
	}
}
