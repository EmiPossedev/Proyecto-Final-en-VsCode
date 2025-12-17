#include <ctime>


// Funcion para obtener la fecha actual en formato entero
int obtenerFechaActual() {
    //acá obtengo los segundos que pasaron desde el 01/01/1970
    time_t t = time(0); // time_t es un tipo de dato para guardar fechas
    tm* tiempo = localtime(&t); // localtime transforma la variable time_t en un struct legible
    return (tiempo->tm_year + 1900) * 10000 + 
           (tiempo->tm_mon + 1) * 100 + 
           tiempo->tm_mday;
}
