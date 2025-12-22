#include <iostream>
#include "Consultorio.h"
using namespace std;

// Función para leer fecha cómodamente
Fecha pedirFecha() {
    Fecha f;
    cout << "   Dia: "; cin >> f.dia;
    cout << "   Mes: "; cin >> f.mes;
    cout << "   Anio: "; cin >> f.anio;
    return f;
}

//LOGICA PACIENTES
void registrarPaciente(Consultorio &sistema) {
    
    //Crear el paciente nuevo en memoria
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

    //Pedir teléfono
    cout << "Ingrese Telefono (solo numeros): ";
    cin >> numeroAux;
    nuevoP->setTelefono(numeroAux);

    // La Fecha (es un struct, hay que llenarlo parte por parte)
    cout << "Fecha de Inicio " << endl;
    cout << "Dia: "; cin >> fechaAux.dia;
    cout << "Mes: "; cin >> fechaAux.mes;
    cout << "Anio: "; cin >> fechaAux.anio;
    
    nuevoP->setFechaDeInicio(fechaAux);

    //(Diagnóstico y Obra Social)
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

void listarPacientes(Consultorio &sistema) {
    
    // Obtenemos la copia de la lista de pacientes
    vector<Paciente*> lista = sistema.getPacientes();

    cout << "LISTADO DE PACIENTES" << endl;

    if (lista.empty() == true) {
        cout << "No hay pacientes registrados en el sistema." << endl;
        return; 
    }

    for (size_t i = 0; i < lista.size(); i++) {
        
       
        Paciente *p = lista[i];
        cout << i  << " " << p->getApellido() << " " << p->getNombre();
        
        // Agregamos info extra útil separada por guiones
        cout << " Obra social" << p->getObraSocial();
        cout << " Sesiones: " << p->getCantidadSesionesRealizadas() << " " << p->getCantSesionesTotales();
        
      
        cout << endl; 
    }
    
    cout << "Suiguiente " << endl;
}

//LOGICA PARA BUSCAR Y GESTIONAR PACIENTE CON SU SUB MENU

// Creamos estas funciones de los menus para tener mas ordenado el main
void menuPacientes(Consultorio &sistema) {
    // Aca armamos la implementación del menú de pacientes
    int opcion;
    do{
        cout<<" GESTIONAR PACIENTES "<<endl;
        cout<<"1. Registrar nuevo paciente"<<endl;
        cout<<"2. Ver lista de pacientes (Nombres)"<<endl;
        cout<<"3. Buscar y gestionar paciente por nombre"<<endl; //si encontramos nos vamos a otra funcion para hacer las gestiones especificas por paciente
        cout<<"0. Volver al menu principal"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion;

        switch(opcion){
            case 1:
               registrarPaciente(sistema); // llamamos a la función para registrar un paciente
                break;
            case 2:
                listarPacientes(sistema); // llamamos a la función para listar los pacientes
                break;
            case 3:
                // Lógica para buscar y gestionar paciente
                break;
            case 0:
                cout<<"Volver al menu principal"<<endl;
                break;
            default:
                cout<<"No funciono, intente nuevamente."<<endl;
                break;
        }
    }
    while(opcion != 0);
}

void menuKinesiologos(Consultorio &sistema) {
    // Aca armamos la implementación del menú de kinesiologos
    int opcion;
    do{
        cout<<" GESTIONAR KINESIOLOGOS "<<endl;
        cout<<"1. Registrar nuevo kinesiologo"<<endl;
        cout<<"2. Ver lista de kinesiologos (Nombres)"<<endl;
        cout<<"3. Buscar y gestionar kinesiologo por nombre"<<endl; //nuevamente fucniones aux para manejar todo por kinesiologo
        cout<<"0. Volver al menu principal"<<endl;
        cout<<"Ingrese una opcion: ";
        cin>>opcion; // leemos la opción del usuario

        switch(opcion){
            case 1:
                // Lógica para registrar nuevo kinesiologo

                break;
            case 2:
                // Lógica para ver lista de kinesiologos
                break;
            case 3:
                // Lógica para buscar y gestionar kinesiologo
                break;
            case 0:
                cout<<"Volviendo al menu principal..."<<endl;
                break;
            default:
                cout<<"Opcion invalida, intente nuevamente."<<endl;
                break;
        }
    }
    while(opcion != 0);
}

void menuTurnos(Consultorio &sistema)
{
    int opcion;
    do {
        cout << "GESTION DE TURNOS " << endl; //todas funciones aux por cada meno en cada case
        cout << "1. Reservar nuevo Turno " << endl; //reservar turno
        cout << "2. Ver agenda " << endl; //ver todos los turnos
        cout << "3. Modificar Turno " << endl; //reprogramar turno
        cout << "4. Cancelar Turno " << endl; //cancelar turno
        cout << "0. Volver" << endl;
        cout << "Opcion: ";
        cin >> opcion; // leemos la opción del usuario

        switch (opcion) {
            case 1:
            //necesitamos fuinciones aux
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

/// Utilizamos el main para probar todas las clases  
int main(){

    Consultorio sistema;
    sistema.cargarTodosDatos(); // Carga los datos al iniciar el programa

    int opcion;
    do {
        cout << " SISTEMA DE GESTION DE CONSULTORIO " << endl;
        cout << "1. Gestionar Pacientes" << endl;
        cout << "2. Gestionar Kinesiologos" << endl;
        cout << "3. Gestionar Turnos" << endl;
        cout << "0. Guardar y salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion; // leemos la opción del usuario

        switch(opcion) {
            case 1:
                menuPacientes(sistema); // mostramos las opciones del menú de los pacientes
                break;
            case 2:
                menuKinesiologos(sistema); // mostramos las opciones del menú de los kinesiologos
                break;
            case 3:
                menuTurnos(sistema); // mostramos el menú de los turnos
                break;
            case 0:
                sistema.guardarTodosDatos(); // guardamos los datos antes de salir
                cout << "Datos guardados, salir del sistema." << endl;
                break;
            default:
                cout << "No funciono, intente nuevamente." << endl;
                break;
        }
    } while(opcion != 0);

    return 0;
}