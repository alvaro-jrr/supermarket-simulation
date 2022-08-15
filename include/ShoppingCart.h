#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

// clase Carrito de Compras
class ShoppingCart {
	private:
		int ID; // identificador

	public:
		// constructor
		ShoppingCart(int = 0);

		// constructor a partir de otro carrito
		ShoppingCart(const ShoppingCart &);

		// establecer ID
		void setID(int);

		// obtener ID
		int getID() const;
};

#endif // SHOPPINGCART_H
