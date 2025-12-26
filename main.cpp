#include <iostream>
#include <vector>
#include "Consultorio.h"
#include "Utils.h"
#include "menu.h"
using namespace std;



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
            case 1: {
                menuPacientes(sistema); // mostramos las opciones del menú de los pacientes
                break;
            }
            case 2: {
                menuKinesiologos(sistema); // mostramos las opciones del menú de los kinesiologos
                break;
            }
            case 3: {
                menuTurnos(sistema); // mostramos el menú de los turnos
                break;
            }
            case 0: {
                sistema.guardarTodosDatos(); // guardamos los datos antes de salir
                cout << "Datos guardados, salir del sistema." << endl;
                break;
            }
            default: {
                cout << "No funciono, intente nuevamente." << endl;
                break;
            }
        }
    } while(opcion != 0);

    return 0;
}
