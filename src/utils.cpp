#include <iostream>
#include <cstdlib>
#include <chrono>
#include <limits>
#include <thread>
#include "utils.h"
using namespace std;

// desplegar opciones
void displayOptions(string *options, int size) {
    int option;

    // mostrar opcion con su numero correspondiente
    for (option = 0; option < size; option++) {
        cout << option + 1 << ") " << options[option] << endl;
    }
}

// obtener numero
int getNumber(string label) {
	int number;

	do {
		// si fallo entrada
		if (cin.fail()) {
			cin.clear(); // manejar fallo de entrada
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignorar linea
			cout << "Entrada invalida\n" << endl;
		}

		cout << label;
		cin >> number;
	} while(cin.fail());

	return number;
}

// obtener numero desde un numero
int getNumberFrom(string label, int min) {
	int number;

	number = getNumber(label);

	while(number < min) {
		cout << "Numero debe ser mayor o igual que " << min << "\n" << endl;
		number = getNumber(label);
	}

	return number;
}

// obtener opcion
int getOption(string label, int min, int max) {
    int option;

    do {
        option = getNumber(label);
    } while(option < min || option > max);

    return option;
}

// obtener numero aleatorio en un rango
int getRandom(int min, int max) {
	return min + rand() % ((max + 1) - min);
}

// obtener promedio
double getAverage(double numerator, double denominator) {
	return denominator ? numerator / denominator : 0;
}

// limpiar consola
void clearConsole() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif // _WIN32
}

// dormir proceso por n segundos
void sleepFor(int seconds) {
	this_thread::sleep_for(chrono::seconds(seconds));
}
