#ifndef CASHIER_H
#define CASHIER_H

#include "Client.h"
#include "Timer.h"

// clase Cajero
class Cashier {
	private:
		enum STATUS { BUSY, FREE };
		STATUS status; // estatus
		int serviceTime; // tiempo de atencion
		int clientsServiced; // clientes atendidos
		Timer timeRemaining; // tiempo restante
		Client *currentClient; // cliente actual

	public:
		// constructor
		Cashier(int = 0);

		// determinar si el cajero esta libre
		bool isFree() const;

		// establecer el estatus del cajero a ocupado
		void setBusy();

		// establecer el estatus del cajero a libre
		void setFree();

		// obtener tiempo de atencion
		int getServiceTime() const;

		// establecer tiempo de atencion
		void setServiceTime(int);

		// obtener tiempo restante
		int getTimeRemaining() const;

		// reestablecer tiempo restante
		void resetTimeRemaining();

		// decrementar tiempo restante
		void decrementTimeRemaining();

		// obtener clientes atendidos
		int getClientsServiced() const;

		// establecer cliente actual
		void setCurrentClient(Client);

		// eliminar cliente actual
		void unsetCurrentClient();

		// obtener cliente actual
		Client* getCurrentClient() const;
};

#endif // CASHIER_H
