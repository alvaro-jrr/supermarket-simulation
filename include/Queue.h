#ifndef QUEUE_H
#define QUEUE_H

#include "Client.h"

// clase Cola
class Queue {
	private:
		// estructura Nodo
		struct Node {
			Client element; // elemento
			Node *next; // siguiente

			// constructor
			Node(Client ELEMENT, Node *NEXT_PTR = nullptr)
				: element(ELEMENT), next(NEXT_PTR) { }
		};

		Node *myFront; // apuntador al frente
		Node *myBack; // apuntador al final
		int myLength; // tamanio de cola

	public:
		// constructor
		Queue();

		// constructor a partir de otra cola
		Queue(const Queue &);

		// destructor
		~Queue();

		// vaciar
		void erase();

		// determinar si esta vacio
		bool isEmpty() const;

		// obtener longitud
		int getLength() const;

		// encolar elemento
		void enqueue(Client);

		// desencolar
		void dequeue();

		// obtener frente
		Client front() const;
};

#endif // QUEUE_H
