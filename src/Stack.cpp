#include "Stack.h"

// constructor
Stack::Stack() {
	erase();
}

// vacia una pila
void Stack::erase() {
	myTop = nullptr;
	myLength = 0;
}

// agregar valor a pila
void Stack::push(ShoppingCart element) {
	myTop = new Node(element, myTop);
	myLength++;
}

// eliminar valor del tope
void Stack::pop() {
	Node *ptr = myTop;
	myTop = myTop->next;
	delete ptr;
	myLength--;
}

// obtener elemento el tope
ShoppingCart Stack::top() {
	return myTop->element;
}

// determina si esta vacio
bool Stack::isEmpty() const {
	return myTop == nullptr;
}

// obtener longitud de pila
int Stack::getLength() const {
	return myLength;
}
