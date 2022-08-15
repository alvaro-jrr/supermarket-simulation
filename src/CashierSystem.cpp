#include "CashierSystem.h"

// constructor
CashierSystem::CashierSystem() { }

// agregar cliente a cola de espera
void CashierSystem::pushClientToWaitingQueue(Client client) {
	waitingQueue.enqueue(client);
}

// obtener cliente actual
Client* CashierSystem::getCurrentClient() {
	return cashier.getCurrentClient();
}

// eliminar cliente actual
void CashierSystem::unsetCurrentClient() {
	cashier.unsetCurrentClient();
}

// obtener cliente siguiente
Client* CashierSystem::getNextClient() {
	if (!waitingQueue.isEmpty()) {
		return new Client(waitingQueue.front());
	}

	return nullptr;
}

// obtener si esta vacia cola de espera
bool CashierSystem::isWaitingQueueEmpty() const {
	return waitingQueue.isEmpty();
}

// obtener clientes despachados de cola de espera
int CashierSystem::getClientsDispatchedByWaitingQueue() const {
	return waitingQueue.getClientsDispatched();
}

// obtener longitud de cola de espera
int CashierSystem::getWaitingQueueLength() const {
	return waitingQueue.getLength();
}

// obtener tiempo de espera en cola
int CashierSystem::getWaitingTime() const {
    return waitingQueue.getWaitingTime();
}

// obtener si esta libre
bool CashierSystem::isCashierFree() const {
	return cashier.isFree();
}

// establecer tiempo de atencion
void CashierSystem::setServiceTime(int serviceTime) {
	cashier.setServiceTime(serviceTime);
}

// obtener clientes atendidos por cajero
int CashierSystem::getClientsServicedByCashier() const {
    return cashier.getClientsServiced();
}

// atender cliente
void CashierSystem::serviceNextClient() {
	if (!waitingQueue.isEmpty()) {
		// obtener siguiente cliente en cola
		Client nextClient = waitingQueue.front();
		waitingQueue.dequeue();

		// establecer cliente actual y reiniciar tiempo restante
		cashier.setBusy();
		cashier.setCurrentClient(nextClient);
		cashier.resetTimeRemaining();
	}
}

// actualizar sistema
void CashierSystem::update() {
	// si cola de espera no esta vacia
	if (!waitingQueue.isEmpty()) {
		// actualizar tiempos de espera
		waitingQueue.updateWaitingTime();
	}

	// si esta ocupado
	if (!cashier.isFree()) {
		cashier.decrementTimeRemaining();

		// si acabo tiempo de atencion, establecer como libre
		if (cashier.getTimeRemaining() == 0) cashier.setFree();
	}
}
