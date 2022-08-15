#include "ShoppingCart.h"

// constructor
ShoppingCart::ShoppingCart(int ID) {
	setID(ID);
}

// constructor a partir de otro carrito
ShoppingCart::ShoppingCart(const ShoppingCart &shoppingCart) {
    setID(shoppingCart.getID());
}

// establecer ID
void ShoppingCart::setID(int ID) {
	this->ID = ID;
}

// obtener ID
int ShoppingCart::getID() const {
	return ID;
}
