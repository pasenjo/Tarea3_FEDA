#ifndef ___hashADT___
#define ___hashADT___

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// Nos basamos en el código creado en ayudantía, pero modificando levemente, agregando la pseudoclase
// datos, que consiste en un par, de primera componente un string y segunda componente un 
// vector. Esta es nuestra estructura para guardar los datos.

static const int hash_primos[] = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157};


typedef std::pair<std::string, std::vector<std::string>> datos;

class hashADT{

// virtual: todas las funciones hash que vaya a implementar dentro de esta clase abstracta,
	// debe realizar SÍ O SÍ estas operaciones (no es necesario definirlas)
	// 
	public:
		//
		virtual bool insert(datos) = 0;
		virtual bool borrar(std::string) = 0;
		virtual int buscar(std::string) = 0;
	private:
		virtual void resize() = 0;
		virtual int hash_foo(std::string) = 0;



};



#endif
