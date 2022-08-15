#ifndef DELTALIST_H
#define DELTALIST_H

#include "Client.h"
#include "Queue.h"

// clase Lista Delta
class DeltaList {
	private:
		// estructura Nodo
		struct Node {
			Client element; // elemento a almacenar
			int waitingTime; // tiempo de espera
			Node *next; // siguiente

			// constructor
			Node(
			    Client ELEMENT,
			    int WAITING_TIME,
			    Node *NEXT_PTR = nullptr
			) : element(ELEMENT), waitingTime(WAITING_TIME), next(NEXT_PTR) { }
		};

		Node *head; // cabecera
		Node *tail; // cola
		Node *current; // actual
		int done; // realizados
		int length; // longitud

	public:
		// constructor
		DeltaList();

		// constructor a partir de otra lista
		DeltaList(DeltaList &);

		// descructor
		~DeltaList();

		// inserta elemento
		void insert(Client, int);

		// elimina elemento de una posicion determinada
		bool erase(int);

		// decrementa lista a tiempo constante
		Queue decrement(int);

		// determina si esta vacia
		bool isEmpty() const;

		// obtener longitud
		int getLength() const;

		// obtener realizados
		int getDone() const;

		// determina si el primer elemento tiene espera = 0
		bool isDone() const;

		// obtener nodo inicial
		Node* start() {
			return (current = head);
		}

		// obtener nodo siguiente
		Node* nextNode() {
			return (current = current->next);
		}

		// obtener nodo actual
		Node* currentNode() const {
			return current;
		}
};

#endif // DELTALIST_H
