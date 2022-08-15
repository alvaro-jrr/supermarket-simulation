#ifndef CASHIERSYSTEM_H
#define CASHIERSYSTEM_H

#include "Cashier.h"
#include "WaitingClientQueue.h"

// clase Sistema de Cajero
class CashierSystem {
    private:
        Cashier cashier; // cajero
        WaitingClientQueue waitingQueue; // cola de espera

    public:
        // constructor
        CashierSystem();

        // agregar cliente a cola de espera
        void pushClientToWaitingQueue(Client);

        // obtener cliente actual
        Client* getCurrentClient();

        // eliminar cliente actual
        void unsetCurrentClient();

        // obtener cliente siguiente
        Client *getNextClient();

        // obtener si esta vacia cola de espera
        bool isWaitingQueueEmpty() const;

        // obtener clientes despachados de cola de espera
        int getClientsDispatchedByWaitingQueue() const;

        // obtener longitud de cola de espera
        int getWaitingQueueLength() const;

        // obtener tiempo de espera en cola
        int getWaitingTime() const;

        // obtener si cajero esta libre
        bool isCashierFree() const;

        // establecer tiempo de atencion
        void setServiceTime(int);

        // obtener clientes atendidos por cajero
        int getClientsServicedByCashier() const;

        // atender siguiente cliente
        void serviceNextClient();

        // actualizar sistema
        void update();
};

#endif // CASHIERSYSTEM_H
