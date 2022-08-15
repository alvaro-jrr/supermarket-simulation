#include <iostream>
#include <string>
#include "Simulation.h"
#include "utils.h"
using namespace std;

int main() {
    // opciones
    string options[] = {
        "Iniciar",
        "Salir"
    };

    int optionsLength = 2;

    // estado del programa
    bool shouldContinue = true;

    do {
        cout << "----- Simulacion de Supermercado -----\n" << endl;

        // mostrar opciones
        displayOptions(options, optionsLength);
        cout << endl;

        // pedir y leer opcion
        int option = getOption("Opcion: ", 1, optionsLength);
        cout << endl;

        // ejecutar accion de acuerdo a opcion elegida
        switch(option) {
            case 1: {
                // pedir parametros
                Simulation S;
                cout << endl;

                // ejecutar simulacion
                S.run();
                cout << endl;
                break;
            }

            case 2:
                shouldContinue = false;
                break;

            default:
                cout << "Opcion invalida" << endl;
        }

        cout << endl;
    } while(shouldContinue);

	return 0;
}
