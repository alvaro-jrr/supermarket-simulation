#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Simulation.h"
#include "utils.h"
using namespace std;

// constructor
Simulation::Simulation() {
	// inicializar variables
	timer.set(0);
	clientsReceived = 0;
	clientsCompleted = 0;
	clientsTotalTime = 0;
	clientMaxTime = 0;

	// pedir y leer tiempo de simulacion
	timeLimit = getNumberFrom("Tiempo de Simulacion (s): ", 0);

	// pedir y leer tiempo minimo de llegadas
	timeMinBetweenClientArrival = getNumberFrom(
        "Tiempo Min. entre Llegadas de Clientes (s): ",
        0
    );

	// pedir y leer tiempo maximo de llegadas
	timeMaxBetweenClientArrival = getNumberFrom(
        "Tiempo Max. entre Llegadas de Clientes (s): ",
        timeMinBetweenClientArrival + 1
    );

	// pedir y leer tiempo minimo que tarda un cliente en comprar
	timeMinClientShopping = getNumberFrom(
        "Tiempo Min. que tarda un Cliente en Comprar (s): ",
        0
    );

	// pedir y leer tiempo maximo que tarda un cliente en comprar
	timeMaxClientShopping = getNumberFrom(
        "Tiempo Max. que tarda un Cliente en Comprar (s): ",
        timeMinClientShopping + 1
    );

	// pedir y leer tiempo de atencion para cada cajero
	for (int cashier = 0; cashier < CASHIERS; cashier++) {
        string label = "Tiempo de Atencion de Caja ";
        label += to_string(cashier + 1);
        label += " (s): ";

        // pedir y leer tiempo de atencion
		int serviceTime = getNumberFrom(label, 0);

		// establecer tiempo de atencion
		cashiersSystem[cashier].setServiceTime(serviceTime);

		// inicializar longitud total para cajero n
		cashiersQueueTotalLength[cashier] = 0;

		// inicializar longitud maxima para cajero n
		cashiersQueueMaxLength[cashier] = 0;
	}

	// inicializar pila de carritos
	for (int cart = 1; cart <= SHOPPING_CARTS; cart++) {
		ShoppingCart shoppingCart(cart);
		shoppingCarts.push(shoppingCart);
	}

	// inicializar generador de numeros aleatorios
	long seed = long(time(0));
	srand(seed);
}

// obtener cola de cajero mas corta
int Simulation::getShortestCashierQueue() {
	int shortest = 0;
	int shortestLength = cashiersSystem[shortest].getWaitingQueueLength();

	// contar persona en cajero
	if (!cashiersSystem[shortest].isCashierFree()) shortestLength++;

	// recorrer cada cola
	for (int cashier = 1; cashier < CASHIERS; cashier++) {
		int currentLength = cashiersSystem[cashier].getWaitingQueueLength();

		// contar persona en cajero
		if (!cashiersSystem[cashier].isCashierFree()) currentLength++;

		// actualizar mas corta
		if (currentLength < shortestLength) {
			shortest = cashier;
			shortestLength = currentLength;
		}
	}

	return shortest;
}

// actualizar tiempos
void Simulation::update() {
    // actualizar sistemas de cajeros
    for (int cashier = 0; cashier < CASHIERS; cashier++) {
        cashiersSystem[cashier].update();
    }

	// actualizar tiempos de espera para cola de espera de carritos
	if (!shoppingCartsQueue.isEmpty()) shoppingCartsQueue.updateWaitingTime();
}

// verificar longitud de colas de espera de cajeros
void Simulation::checkForCashiersQueueLength() {
	// recorrer cada cola de cajero
	for (int cashier = 0; cashier < CASHIERS; cashier++) {
		int currentLength = cashiersSystem[cashier].getWaitingQueueLength();

		// sumar longitud actual a total
		cashiersQueueTotalLength[cashier] += currentLength;

		// actualizar longitud maxima
		if (currentLength > cashiersQueueMaxLength[cashier]) {
			cashiersQueueMaxLength[cashier] = currentLength;
		}
	}
}

// verificar si hay nuevo cliente
void Simulation::checkForNewClient(int &timeRemaining) {
	if (timeRemaining > 0) {
		timeRemaining--;
	} else {
		int clientID = clientsReceived + 1;

		// generar tiempo de compras aleatorio
		int shoppingTime = getRandom(
            timeMinClientShopping,
            timeMaxClientShopping
        );

		// crear nuevo cliente y agregar a espera por carrito
		Client newClient(clientID, timer.get(), shoppingTime);
		newClient.setWaitingTime(0);
		shoppingCartsQueue.enqueue(newClient);

		// aumentar numero de clientes
		clientsReceived++;

		// establecer nuevo tiempo restante
		timeRemaining = getRandom(
            timeMinBetweenClientArrival,
            timeMaxBetweenClientArrival
        );
	}
}

// dar carritos a clientes y enviar de compras
void Simulation::checkForAvailableCarts() {
	while(!shoppingCartsQueue.isEmpty() && !shoppingCarts.isEmpty()) {
		// obtener cliente y asignar carrito
		Client client = shoppingCartsQueue.front();
		client.setShoppingCart(shoppingCarts.top());

		// desapilar carrito y sacar cliente de cola
		shoppingCarts.pop();
		shoppingCartsQueue.dequeue();

		// enviar cliente de compras
		clientsShopping.insert(client, client.getShoppingTime());
	}
}

// verificar si hay clientes por pagar
void Simulation::checkForClientsToPay() {
	Queue clientsToPay = clientsShopping.decrement(1);

	// asignar clientes a colas de cajeros mas cortas
	while(!clientsToPay.isEmpty()) {
		// obtener cliente
		Client clientToPay = clientsToPay.front();
		int shortestServerQueue = getShortestCashierQueue();

		// establecer tiempo de espera a 0
		clientToPay.setWaitingTime(0);

		// encolar a cola de cajero
		cashiersSystem[shortestServerQueue].pushClientToWaitingQueue(clientToPay);

		// eliminar de cola de clientes por pagar
		clientsToPay.dequeue();
	}
}

// verificar si hay cajeros disponibles
void Simulation::checkForAvailableCashier() {
	// recorrer cada cajero y su respectiva cola
	for (int cashier = 0; cashier < CASHIERS; cashier++) {
		// si cajero esta libre
		if (cashiersSystem[cashier].isCashierFree()) {
            // obtener cliente actual
            Client *currentClient = cashiersSystem[cashier].getCurrentClient();

            // si hay cliente
            if (currentClient) {
                // eliminar e ir a cola de salida
                cashiersSystem[cashier].unsetCurrentClient();
                clientsLeaving.enqueue(*currentClient);
            }

            // si cola de espera no esta vacia
            if (!cashiersSystem[cashier].isWaitingQueueEmpty()) {
                // obtener siguiente y devolver carrito
                Client *nextClient = cashiersSystem[cashier].getNextClient();
                shoppingCarts.push(nextClient->getShoppingCart());

                // atender siguiente
                cashiersSystem[cashier].serviceNextClient();
            }
		}
	}
}

// verificar si hay clientes saliendo
void Simulation::checkForClientsLeaving() {
	while(!clientsLeaving.isEmpty()) {
		// obtener cliente por salir
		Client clientLeaving = clientsLeaving.front();

		// establecer tiempo de salida
		clientLeaving.setDepartureTime(timer.get());

		// obtener tiempo total de cliente
		int totalTime = clientLeaving.getDepartureTime()
		                - clientLeaving.getArrivalTime();

		// establecer tiempo maximo
		if (totalTime > clientMaxTime) clientMaxTime = totalTime;

		// agegar a tiempo total de clientes
		clientsTotalTime += totalTime;

		// sumar a clientes completados
		clientsCompleted++;

		// sacar cliente
		clientsLeaving.dequeue();
	}
}

// mostrar estado actual
void Simulation::displayState() {
	cout << "# Estado\n" << endl;

	// mostrar tiempo actual
	cout << left << setw(WIDTH) << "Tiempo Actual"
	     << timer.get() << "s" << endl;

	// recorrer cajeros
	for (int cashier = 0; cashier < CASHIERS; cashier++) {
		string label = "Personas en Cola de Caja ";
		label += to_string(cashier + 1);

		// mostrar personas en espera
		cout << setw(WIDTH) << label
		     << cashiersSystem[cashier].getWaitingQueueLength();

		// mostrar cliente siendo atendido
		Client *currentClient = cashiersSystem[cashier].getCurrentClient();

		if (!cashiersSystem[cashier].isCashierFree()) {
			cout << " (Atendiendo a Cliente " << currentClient->getID() << ")";
		}

		cout << endl;
	}

	// mostrar carritos ocupados
	cout << setw(WIDTH) << "Carritos Ocupados"
	     << SHOPPING_CARTS - shoppingCarts.getLength() << endl;

	// mostrar cantidad de personas en espera de carrito
	cout << setw(WIDTH) << "En Espera de Carrito"
	     << shoppingCartsQueue.getLength() << endl;
}

// mostrar estadisticas
void Simulation::displayStatistics() const {
	// configuracion de salidas
	cout << left << fixed << setprecision(2);

	// mostrar estadisticas generales del supermecado
	cout << "# Supermercado\n" << endl;

	cout << setw(WIDTH) << "Tiempo Promedio de Clientes"
	     << getAverage(clientsTotalTime, clientsCompleted) << "s" << endl;

	cout << setw(WIDTH) << "Tiempo Maximo de Cliente"
	     << clientMaxTime << "s\n" << endl;

	// mostrar estadisticas generales de la cola de carritos
	cout << "# Carritos\n" << endl;

	cout << setw(WIDTH) << "Tiempo Total de Espera"
	     << shoppingCartsQueue.getWaitingTime() << "s" << endl;

    cout << setw(WIDTH) << "Tiemo de Espera Promedio"
         << getAverage(
            shoppingCartsQueue.getWaitingTime(),
            shoppingCartsQueue.getClientsDispatched()
         ) << "s\n" << endl;

	// mostrar estadisticas de colas de caja
	cout << "# Colas de Cajas\n" << endl;

	for (int cashier = 0; cashier < CASHIERS; cashier++) {
		// mostrar cola de caja
		cout << "- Cola de Caja " << cashier + 1 << endl;

		// mostrar longitud promedio
		cout << setw(WIDTH) << "Longitud Promedio"
		     << getAverage(cashiersQueueTotalLength[cashier], timeLimit)
		     << endl;

		// mostrar longitud maxima
		cout << setw(WIDTH) << "Longitud Maxima"
		     << cashiersQueueMaxLength[cashier] << "\n" << endl;
	}

	// mostrar estadisticas de cada caja y global
	cout << "# Cajas\n" << endl;

	int totalWaitingTime = 0;
	int totalClientsServiced = 0;
	int totalQueueClientsDispatched = 0;

	for (int cashier = 0; cashier < CASHIERS; cashier++) {
		// obtener clientes que salieron de cola
		int queueClientsDispatched =
			cashiersSystem[cashier].getClientsDispatchedByWaitingQueue();

        // obtener tiempo de espera total
        int queueWaitingTime = cashiersSystem[cashier].getWaitingTime();

		// obtener clientes atendidos en cajero
		int cashierClientsServiced =
			cashiersSystem[cashier].getClientsServicedByCashier();

		// mostrar caja
		cout << "- Caja " << cashier + 1 << endl;

		// mostrar clientes atendidos
		cout << setw(WIDTH) << "Clientes Atendidos"
		     << cashierClientsServiced << endl;

		// mostrar tiempo promedio
		cout << setw(WIDTH) << "Tiempo de Espera Promedio"
             << getAverage(queueWaitingTime, queueClientsDispatched) << "s\n"
             << endl;

		// sumar tiempo de espera de cola de cajero al total
		totalWaitingTime += queueWaitingTime;

		// sumar clientes atendidos en cola al total
		totalQueueClientsDispatched += queueClientsDispatched;

		// sumar clientes atendidos al total
		totalClientsServiced += cashierClientsServiced;
	}

	cout << "- Global" << endl;

	cout << setw(WIDTH) << "Clientes Atendidos"
	     << totalClientsServiced << endl;

	cout << setw(WIDTH) << "Tiempo de Espera Promedio"
	     << getAverage(totalWaitingTime, totalQueueClientsDispatched)
	     << "s" << endl;
}

// ejecutar simulacion
void Simulation::run() {
	int arrivalTimeRemaining = getRandom(
        timeMinBetweenClientArrival,
        timeMaxBetweenClientArrival
    );

	// limpiar pantalla
	clearConsole();

	// realizar simulacion dentro de tiempo limite
	while(timer.get() < timeLimit) {
        // mostrar estado actual
		displayState();

		// actualizar sistemas y cola de espera de carritos
		update();

		// verificar longitud de colas de espera de cajeros
		checkForCashiersQueueLength();

		// verificar si un cliente llega
		checkForNewClient(arrivalTimeRemaining);

		// dar carrito a clientes y enviar de compras
		checkForAvailableCarts();

		// enviar cliente a linea de espera de una cajero
		checkForClientsToPay();

		// enviar cliente de cola de espera a cajero
		checkForAvailableCashier();

		// sacar clientes del supermercado
		checkForClientsLeaving();

		// incrementar tiempo
		timer.increment();

		// limpiar pantalla y dormir proceso por 1 segundo
		sleepFor(1);
		clearConsole();
	}

	displayStatistics(); // mostrar estadisticas
	cout << endl;
	displayState(); // mostrar estado final
}
