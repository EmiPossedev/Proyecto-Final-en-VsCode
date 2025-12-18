#include "Fecha.h"
using namespace std;

ostream &operator<<(ostream &os, const Fecha &f)
{
    os << f.dia << "/" << f.mes << "/" << f.anio;
    return os;
}