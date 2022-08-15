#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <string>

// desplegar opciones
void displayOptions(std::string *, int);

// obtener numero
int getNumber(std::string);

// obtener numero desde un numero minimo
int getNumberFrom(std::string, int = 0);

// obtener opcion
int getOption(std::string, int, int);

// obtener numero aleatorio en un rango
int getRandom(int, int);

// obtener promedio
double getAverage(double, double);

// limpiar consola
void clearConsole();

// dormir proceso por n segundos
void sleepFor(int = 0);

#endif // UTILS_H_INCLUDED
