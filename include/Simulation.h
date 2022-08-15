#ifndef SIMULATION_H
#define SIMULATION_H

#include "Stack.h"
#include "DeltaList.h"
#include "WaitingClientQueue.h"
#include "Timer.h"
#include "CashierSystem.h"
#include <string>

// clase Simulacion
class Simulation {
	private:
        // Constantes
        static const int WIDTH = 45; // ancho para impresion de resultados
        static const int CASHIERS = 3; // numero de cajeros
        static const int SHOPPING_CARTS = 20; // numero de carritos

        // Parametros
        int timeLimit; // tiempo limite
        int timeMinBetweenClientArrival; // tiempo minimo entre llegadas
        int timeMaxBetweenClientArrival; // tiempo maximo entre llegadas
        int timeMinClientShopping; // tiempo minimo de compras
        int timeMaxClientShopping; // tiempo maximo de compras

        // Temporizador
        Timer timer;

        // Estructuras de Datos
        Stack shoppingCarts; // carritos de compra
        DeltaList clientsShopping; // clientes de compras
        WaitingClientQueue shoppingCartsQueue; // cola de espera de carritos
        CashierSystem cashiersSystem[CASHIERS]; // sistema de cajeros
        Queue clientsLeaving; // clientes saliendo

        // Variables para Estadisticas
        int clientsReceived; // clientes que llegaron
        int clientsCompleted; // clientes completados (llegaron y salieron)
        int clientsTotalTime; // tiempo total de clientes
        int clientMaxTime; // tiempo maximo de un cliente
        int cashiersQueueTotalLength[CASHIERS]; // longitud total de colas de espera
        int cashiersQueueMaxLength[CASHIERS]; // longitud maxima de colas de espera

        // obtener cola de cajero mas corta
        int getShortestCashierQueue();

	public:
        // constructor
		Simulation();

		// actualizar tiempos
		void update();

		// verificar longitud de colas de espera de cajeros
		void checkForCashiersQueueLength();

		// verificar si hay nuevo cliente
		void checkForNewClient(int &);

		// dar carritos a clientes y enviar de compras
		void checkForAvailableCarts();

		// verificar si hay clientes por pagar
		void checkForClientsToPay();

		// verificar si hay cajeros disponibles
		void checkForAvailableCashier();

        // verificar si hay clientes saliendo
		void checkForClientsLeaving();

		// mostrar estado actual
		void displayState();

        // mostrar estadisticas
		void displayStatistics() const;

		// ejecutar simulacion
		void run();
};

#endif // SIMULATION_H
