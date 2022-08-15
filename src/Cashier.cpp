#include "Cashier.h"

// constructor
Cashier::Cashier(int serviceTime) {
	setFree();
	setServiceTime(serviceTime);
    unsetCurrentClient();
	clientsServiced = 0;
}

// determinar si el cajero esta libre
bool Cashier::isFree() const {
	return status == FREE;
}

// establecer el estatus del cajero a ocupado
void Cashier::setBusy() {
	status = BUSY;
}

// establecer el estatus del cajero a libre
void Cashier::setFree() {
	status = FREE;
}

// obtener tiempo de atencion
int Cashier::getServiceTime() const {
	return serviceTime;
}

// establecer tiempo de atencion
void Cashier::setServiceTime(int serviceTime) {
	if (serviceTime >= 0) {
		this->serviceTime = serviceTime;
	}
}

// obtener tiempo restante
int Cashier::getTimeRemaining() const {
	return timeRemaining.get();
}

// reestablecer tiempo restante
void Cashier::resetTimeRemaining() {
    timeRemaining.set(getServiceTime());
}

// decrementar tiempo restante
void Cashier::decrementTimeRemaining() {
    if (timeRemaining.get() > 0) {
        timeRemaining.decrement();

        // si no hay tiempo restante, aumentar clientes atendidos
        if (timeRemaining.get() == 0) {
            clientsServiced++;
        }
    }
}

// obtener clientes atendidos
int Cashier::getClientsServiced() const {
    return clientsServiced;
}

// establecer cliente actual
void Cashier::setCurrentClient(Client currentClient) {
	this->currentClient = new Client(currentClient);
}

// eliminar cliente actual
void Cashier::unsetCurrentClient() {
    currentClient = nullptr;
}

// obtener cliente actual
Client* Cashier::getCurrentClient() const {
	return currentClient;
}
