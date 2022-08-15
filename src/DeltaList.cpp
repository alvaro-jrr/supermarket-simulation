#include "DeltaList.h"

// constructor
DeltaList::DeltaList() {
	head = tail = current = nullptr;
	done = length = 0;
}

// constructor a partir de otra lista
DeltaList::DeltaList(DeltaList &deltaList) {
	head = tail = current = nullptr;
	done = length = 0;

	// apuntar a inicio de lista
	Node *iptr = deltaList.start();

	while(iptr) {
        // insertar en lista
		insert(iptr->element, iptr->waitingTime);

		// avanzar apuntador
        iptr = deltaList.nextNode();
	}
}

// destructor
DeltaList::~DeltaList() {
	// eliminar cada nodo
	while(!isEmpty()) {
		current = head;
		head = head->next;
		delete current;
	}

	tail = nullptr;
	length = 0;
}

// inserta elemento
void DeltaList::insert(Client element, int waitingTime) {
	Node *np = new Node(element, waitingTime); // nuevo proceso
	Node *ap = nullptr; // anterior
	Node *cp = head; // cabecera

	// restar tiempo de nuevo proceso con respecto a los anteriores
	while(cp && np->waitingTime >= cp->waitingTime) {
		np->waitingTime -= cp->waitingTime;
		ap = cp;
		cp = cp->next;
	}

	// cola apunta a nuevo proceso si esta vacio
	if (isEmpty()) tail = np;

	// colocar nuevo proceso antes de cp
	np->next = cp;

	// si cp != nullptr, restar tiempo de espera con el tiempo de nuevo proceso
	if (cp) cp->waitingTime -= np->waitingTime;

	if (ap) {
		// agregar despues del anterior a nuevo proceso
		ap->next = np;
	} else {
		// posicionar nuevo proceso en la cabecera
		head = np;
	}

	// si cola tiene un elemento siguiente, actualizar cola
	if (tail->next) tail = tail->next;

	// aumentar longitud
	length++;
}

// elimina elemento de una posicion determinada
bool DeltaList::erase(int index) {
	// FALSE si indice esta fuera de rango
	if (index < 1 || index > length) return false;

	// apuntadores
	Node *prevPtr = head;
	Node *ptr = head;

	// indice de iteraciones
	int i = 1;

	// recorrer hasta llegar a la posicion
	while(i < index && ptr) {
		ptr = ptr->next;
		prevPtr = i == 1 ? prevPtr : prevPtr->next;
		i++;
	}

	// FALSE si apuntador es nulo
	if (!ptr) return false;

	if (ptr == head && ptr == tail) {
		// un solo elemento en cola
		head = tail = current = nullptr;
	} else if (ptr == head) {
		// primer elemento
		head = head->next;
		head->waitingTime += ptr->waitingTime;
	} else if (ptr == tail) {
		// ultimo elemento
		tail = prevPtr;
		prevPtr->next = nullptr;
	} else {
		// elemento intermedio
		ptr->next->waitingTime += ptr->waitingTime;
		prevPtr->next = ptr->next;
	}

	// eliminar elemento
	delete ptr;
	length--;

	return true;
}

// decrementa lista a tiempo constante
Queue DeltaList::decrement(int time) {
	Node *cp = head;
	Queue elementsDone;

	while(cp) {
		if (cp->waitingTime >= time) {
			// restar a proceso actual el tiempo
			cp->waitingTime -= time;
			break;
		}

		// restar a tiempo el proceso actual y establecer en 0
		time -= cp->waitingTime;
		cp->waitingTime = 0;
		elementsDone.enqueue(cp->element);

		// apuntar al siguiente
		cp = cp->next;

		// cabecera apunta al siguiente actual
		head = cp;
		done++;
		length--;
	}

	return elementsDone;
}

// determina si esta vacia
bool DeltaList::isEmpty() const {
	return head == nullptr;
}

// obtener longitud
int DeltaList::getLength() const {
	return length;
}

// obtener cantidad de realizados
int DeltaList::getDone() const {
	return done;
}

// determina si el primer elemento tiene espera = 0
bool DeltaList::isDone() const {
	return head && head->waitingTime == 0;
}
