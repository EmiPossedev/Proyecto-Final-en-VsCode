#include <iostream>
#include "Consultorio.h"

using namespace std;

//creamos funciones para gestionar las opciones del menu, nos sirven para ordenar el codigo mejor

void menuPacientes(Consultorio &sistema);
void menuKinesiologos(Consultorio &sistema);
void menuTurnos(Consultorio &sistema);

int main(){

    Consultorio sistema;
    sistema.cargarTodosDatos(); // Carga los datos al iniciar el programa o no arranca

    int opcion;
    do {
        cout << " SISTEMA DE GESTION DE CONSULTORIO " << endl;
        cout << "1. Gestionar Pacientes" << endl;
        cout << "2. Gestionar Kinesiologos" << endl;
        cout << "3. Gestionar Turnos" << endl;
        cout << "0. Guardar y salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                menuPacientes(sistema);
                break;
            case 2:
                menuKinesiologos(sistema);
                break;
            case 3:
                menuTurnos(sistema);
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

// Implementamos las funciones de los menus para tener mas ordenado el main

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
                // Lógica para registrar nuevo paciente

                break;
            case 2:
                // Lógica para ver lista de pacientes
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
        cin>>opcion;

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
        cin >> opcion;

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