#ifndef CLIENT_H
#define CLIENT_H

#include "ShoppingCart.h"
#include "Timer.h"

// clase Cliente
class Client {
    private:
        int ID; // identificador
        int arrivalTime; // tiempo de llegada
        int shoppingTime; // tiempo de compras
        int departureTime; // tiempo de salida
        ShoppingCart shoppingCart; // carrito
        Timer waitingTime; // tiempo de espera

	public:
        // constructor
		Client(
			int = 0, 
			int = 0, 
			int = 0, 
			int = 0, 
			int = 0, 
			ShoppingCart = ShoppingCart()
		);

        // constructor a partir de otro Cliente
		Client(const Client &);

		// obtener ID
		int getID() const;

		// establecer ID
		void setID(int);

		// obtener tiempo de llegada
		int getArrivalTime() const;

		// establecer tiempo de llegada
		void setArrivalTime(int);

		// obtener tiempo de compras
        int getShoppingTime() const;

		// establecer tiempo de compras
		void setShoppingTime(int);

		// obtener tiempo de espera
		int getWaitingTime() const;

		// establecer tiempo de espera
		void setWaitingTime(int);

		// incrementar tiempo de espera
		void incrementWaitingTime();

		// obtener tiempo de salida
		int getDepartureTime() const;

		// establecer tiempo de salida
		void setDepartureTime(int);

		// obtener carrito
        ShoppingCart getShoppingCart() const;

		// establecer carrito
		void setShoppingCart(ShoppingCart);
};

#endif // CLIENT_H
