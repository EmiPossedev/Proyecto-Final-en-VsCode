#include "Fecha.h"
using namespace std;

bool esBisiesto(int anio) {
   // Es bisiesto si es divisible por 4, excepto si es divisible por 100 (salvo que sea por 400)
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

bool esFechaValida(int dia, int mes, int anio) {
    // Validar año 
    if (anio < 1900 || anio > 2100) return false;

    // Validar mes
    if (mes < 1 || mes > 12) return false;

    // Definir días por mes
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Si es bisiesto, febrero tiene 29
    if (esBisiesto(anio)) {
        diasEnMes[2] = 29;
    }

    // Validar día
    if (dia < 1 || dia > diasEnMes[mes]) return false;

    return true;
}

ostream &operator<<(ostream &os, const Fecha &f)
{
    os << f.dia << "/" << f.mes << "/" << f.anio;
    return os;
}