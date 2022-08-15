#ifndef STACK_H
#define STACK_H

#include "ShoppingCart.h"

// clase Pila
class Stack {
	private:
		// estructura Nodo
		struct Node {
			ShoppingCart element; // elemento
			Node *next; // siguiente

			// constructor
			Node(ShoppingCart ELEMENT, Node *NEXT_PTR = nullptr)
				: element(ELEMENT), next(NEXT_PTR) { }
		};

		Node *myTop; // apuntador al tope
		int myLength; // longitud

	public:
		// constructor
		Stack();

		// vacia una pila
		void erase();

		// agregar valor a pila
		void push(ShoppingCart);

		// eliminar valor del tope
		void pop();

		// obtener elemento el tope
		ShoppingCart top();

		// determina si esta vacio
		bool isEmpty() const;

		// obtener longitud de pila
		int getLength() const;
};

#endif // STACK_H
