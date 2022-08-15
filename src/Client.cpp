#include "Client.h"

// constructor
Client::Client(
	int ID, 
	int arrivalTime, 
	int shoppingTime, 
	int waitingTime, 
	int departureTime,
	ShoppingCart shoppingCart
) {
	setID(ID);
	setArrivalTime(arrivalTime);
	setShoppingTime(shoppingTime);
	setWaitingTime(waitingTime);
	setDepartureTime(departureTime);
	setShoppingCart(shoppingCart);
}

// constructor a partir de otro Cliente
Client::Client(const Client &client) {
	setID(client.getID());
	setArrivalTime(client.getArrivalTime());
	setShoppingTime(client.getShoppingTime());
	setWaitingTime(client.getWaitingTime());
	setDepartureTime(client.getDepartureTime());
	setShoppingCart(client.getShoppingCart());
}

// obtener ID
int Client::getID() const {
	return ID;
}

// establecer ID
void Client::setID(int ID) {
	this->ID = ID;
}

// obtener tiempo de llegada
int Client::getArrivalTime() const {
	return arrivalTime;
}

// establecer tiempo de llegada
void Client::setArrivalTime(int arrivalTime) {
	if (arrivalTime >= 0) {
		this->arrivalTime = arrivalTime;
	}
}

// obtener tiempo de compras
int Client::getShoppingTime() const {
	return shoppingTime;
}

// establecer tiempo de compras
void Client::setShoppingTime(int shoppingTime) {
	if (shoppingTime >= 0) {
		this->shoppingTime = shoppingTime;
	}
}

// obtener tiempo de espera
int Client::getWaitingTime() const {
	return waitingTime.get();
}

// establecer tiempo de espera
void Client::setWaitingTime(int waitingTime) {
	this->waitingTime.set(waitingTime);
}

// incrementar tiempo de espera
void Client::incrementWaitingTime() {
	waitingTime.increment();
}

// obtener tiempo de salida
int Client::getDepartureTime() const {
	return departureTime;
}

// establecer tiempo de salida
void Client::setDepartureTime(int departureTime) {
	if (departureTime >= 0) {
		this->departureTime = departureTime;
	}
}

// obtener carrito
ShoppingCart Client::getShoppingCart() const {
	return shoppingCart;
}

// establecer carrito
void Client::setShoppingCart(ShoppingCart shoppingCart) {
	this->shoppingCart = shoppingCart;
}
