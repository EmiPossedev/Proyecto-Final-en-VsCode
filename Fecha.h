#ifndef FECHA_H
#define FECHA_H
#include <iostream>

using namespace std;

struct Fecha
{
    int dia;
    int mes;
    int anio;

    // Sobrecarga del operador < (Para que el sort funcione solo)
    // Compara Años, luego Meses, luego Días.
    bool operator<(const Fecha &f) const
    {
        if (anio != f.anio)
            return anio < f.anio;
        if (mes != f.mes)
            return mes < f.mes;
        return dia < f.dia;
    }

    // 2. Sobrecarga del operador == (Para buscar turnos por fecha)
    bool operator==(const Fecha &f) const
    {
        return dia == f.dia && mes == f.mes && anio == f.anio;
    }

    // 3. Sobrecarga del operador != (Para saber si son distintas)
    bool operator!=(const Fecha &f) const
    {
        return !(*this == f);
    }
};

// Sobrecarga del operador <<
//  Esto permite hacer: cout << turno.fecha;
//  y salga impreso  "25/10/2023" automáticamente.
ostream &operator<<(std::ostream &os, const Fecha &f);

#endif