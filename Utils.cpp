#include "Utils.h"
#include <ctime>
#include <iostream>
using namespace std;

int obtenerFechaActual()
{
    time_t t = time(0);
    tm *tiempo = localtime(&t);
    return (tiempo->tm_year + 1900) * 10000 +
           (tiempo->tm_mon + 1) * 100 +
           tiempo->tm_mday;
}

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
