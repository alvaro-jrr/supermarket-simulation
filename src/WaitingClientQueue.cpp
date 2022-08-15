#include "WaitingClientQueue.h"

// constructor
WaitingClientQueue::WaitingClientQueue() : Queue() {
	waitingTime = 0;
    clientsDispatched = 0;
}

// desencolar
void WaitingClientQueue::dequeue() {
	Client client = front();
	waitingTime += client.getWaitingTime();

    // agregar a clientes despachados
    clientsDispatched++;

	// desencolar elemento
	Queue::dequeue();
}


// obtener clientes despachados
int WaitingClientQueue::getClientsDispatched() const {
    return clientsDispatched;
}

// obtener tiempo de espera
int WaitingClientQueue::getWaitingTime() const {
    return waitingTime;
}

// incrementar el tiempo de espera de cada cliente
void WaitingClientQueue::updateWaitingTime() {
	Queue auxQueue;
	Client auxClient;

	// encolar elementos en cola auxiliar
	while(!isEmpty()) {
		// obtener cliente, aumentar tiempo y agregar a cola auxiliar
		auxClient = front();
		auxClient.incrementWaitingTime();
		auxQueue.enqueue(auxClient);

		// desencolar elemento
		Queue::dequeue();
	}

	// encolar elementos a cola original
	while(!auxQueue.isEmpty()) {
		// obtener cliente y agregar a cola original
		auxClient = auxQueue.front();
		enqueue(auxClient);

		// desencolar
		auxQueue.dequeue();
	}
}
