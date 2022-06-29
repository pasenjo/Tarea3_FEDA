#ifndef ARBOLBINARIOBUSQUEDA_H
#define ARBOLBINARIOBUSQUEDA_H

#include <iostream>



//  árbol modificado para las necesidades del problema.
// definimos la pseudoestructura datos como un par, de 
// primera entrada un string, acompañada de un vector de strings
typedef std::pair<std::string, std::vector<std::string>> datos;


class Nodo{

	public:
		datos str;
		Nodo *izq;
		Nodo *der;
		Nodo *padre;
		Nodo(datos str);            	 // Constructor valor raiz
		Nodo(datos str, Nodo *padre);	 // Constructor nodo no raiz
		~Nodo();                     	 // Destructor
};

class ArbolBinarioBusqueda{
	public:
		ArbolBinarioBusqueda();       // Constructor
		~ArbolBinarioBusqueda();      // Destructor
		bool insertar(datos dato);     // No acepta valores repetidos
		Nodo *buscar(std::string valor);      // Si no existe, return null
		void inOrder();

	private:
		Nodo *raiz;                             // ptr a primer nodo
		bool insertar(datos dato, Nodo *n);      // Insertar un nodo en el nodo *n
		Nodo *buscar(std::string str, Nodo *n);       // Buscar valor en el nodo *n
		void inOrder(Nodo *n);                  // Recorrido inOrder desde el nodo *n
		Nodo *mayor(Nodo *n);                   // Retorna el nodo de mayor valor
};

#endif