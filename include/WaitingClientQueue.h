#ifndef WAITINGCLIENTQUEUE_H
#define WAITINGCLIENTQUEUE_H

#include "Queue.h"

// clase Cola de Espera de Clientes
class WaitingClientQueue : public Queue {
    private:
        int waitingTime; // tiempo de espera
        int clientsDispatched; // clientes despachados

	public:
        // constructor
		WaitingClientQueue();

		// desencolar
		void dequeue();

        // obtener clientes despachados
		int getClientsDispatched() const;

		// obtener tiempo de espera
		int getWaitingTime() const;

		// incrementar el tiempo de espera de cada cliente
		void updateWaitingTime();
};

#endif // WAITINGCLIENTQUEUE_H
