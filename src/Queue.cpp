#include "Queue.h"

// constructor
Queue::Queue() {
	myFront = myBack = nullptr;
	myLength = 0;
}

// constructor a partir de otra cola
Queue::Queue(const Queue &src) {
	myFront = myBack = nullptr;
	myLength = 0;

	if (!src.isEmpty()) {
		myFront = myBack = new Node(src.front());
		Node *srcPtr = src.myFront->next;

		while(srcPtr) {
			myBack->next = new Node(srcPtr->element);
			myBack = myBack->next;
			srcPtr = srcPtr->next;
			myLength++;
		}
	}
}

// destructor
Queue::~Queue() {
	erase();
}

// vaciar
void Queue::erase() {
	Node *prev;

	while(myFront) {
		prev = myFront;
		myFront = myFront->next;
		delete prev;
	}

	myLength = 0;
}

// determinar si esta vacio
bool Queue::isEmpty() const {
	return myFront == nullptr;
}

// obtener longitud
int Queue::getLength() const {
	return myLength;
}

// encolar elemento
void Queue::enqueue(Client element) {
	Node *newPtr = new Node(element);

	if (isEmpty()) {
		myFront = myBack = newPtr;
	} else {
		myBack->next = newPtr;
		myBack = newPtr;
	}

	myLength++;
}

// desencolar
void Queue::dequeue() {
	if (!isEmpty()) {
		Node *ptr = myFront;
		myFront = myFront->next;
		delete ptr;

		// si cola esta vacia
		if (myFront == nullptr) myBack = nullptr;

		myLength--;
	}
}

// obtener frente
Client Queue::front() const {
	if (!isEmpty()) return myFront->element;

	Client *temp = new(Client);
	Client garbage = *temp; // basura
	delete temp;

	return garbage;
}
