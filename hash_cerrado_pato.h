#ifndef __hashito__
#define __hashito__

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "hashADT.h"


typedef std::pair<std::string, std::vector<std::string>> datos;
class TablaHash_cerrada: public hashADT{
	
	public:
		// ---- Metodos ----//
		//
		// Constructor
		TablaHash_cerrada(){     // O(n)
			size = 0; // cantidad de elementos en la tabla hash
			real_size = 0; // tiene que ver con el vector de primos dados en ADT
			alpha = 0; //factor de carga: indica que qué tan llena está una tabla hash (funciona como tolerancia)
			
			hash = new std::vector<std::pair<char,datos > >(hash_primos[0]);

			for(int i = 0; i < hash_primos[real_size]; i++){
				(*hash)[i].first = 'v';
			}

		}

		// Destructor
		~TablaHash_cerrada(){     // O(1)
			delete hash;
		}

		// Insertar un elemento si no está repetido
		virtual bool insert(datos par){    // O(n)    o(1)

			int index = hash_foo(par.first) % hash_primos[real_size];
			float alpha_plus = (float)(size + 1) / hash_primos[real_size];   // Revisar si sobrepasa el factor de carga
			
			// Si lo sobrepasa, resize
			if(alpha_plus > 0.5){
				resize();		
			}
			
			
			// Verificar si hay colisión
			while((*hash)[index].first == 'o'){
				index = (index + 1) % hash_primos[real_size];
			}
		
			// Cuando encuentre un espacio, lo inserta
			(*hash)[index].first = 'o';
			(*hash)[index].second = par; // inserta un vector

			size++;
			
			return true;
		}


		// O(n)   o(1)
		virtual bool borrar(std::string str){    // Borrar un elemento si es que existe en la tabla hash

			
			int index = buscar(str) % hash_primos[real_size];   // Obtenemos el indice del string en la tabla

			// Si buscar devuelve -1, es porque el elemento no esta, por ende no se puede borrar
			// Retornamos false
			if(index == -1)
				return false;
			
			// Si lo encuentra, cambiamos el estado 'o' (ocupado) a 'b' (borrado)
			(*hash)[index].first = 'b';
			return true;
		}

		
		// O(n)   o(1)
		virtual int buscar(std::string str){     // Devuelve la posicion del elemento
			
			int index = hash_foo(str);     // Obtenemos el indice del string

			// Verificar colisiones
			while((*hash)[index].first != 'v'){
				//
				// Si nos encontramos con un espacio borrado, saltar al siguiente
				if((*hash)[index].first == 'b'){
					index = (index + 1) % hash_primos[real_size];
					continue;
				}
				
				// Si es un espacio ocupado, comparar strings
				if(str.compare((*hash)[index].second.first) == 0){
					return index;
				}
					

				index = (index + 1) % hash_primos[real_size];
			}


			// Si llegamos a este punto, es porque nos encontramos un vacio y el elemento no esta en la tabla
			// Retornamos -1 como señal de no encontrarlo
			return -1;
		}



	private:
		// ---- Atributos ---- //
		float alpha;            							// Factor de carga
		int real_size;										// Indice en el arreglo de tamaños de la tabla hash
		int size;                							// Elementos en la tabla hash
		// std::vector<std::pair<char, std::string>> *hash;    // Vector dinamico que actua como tabla hash
		std::vector< std::pair<char, datos > > *hash;


		// 	dentro de este par, primero tenemos un char, que es el estado de cada celda, y la segunda componente es un par
		// 		este par, en su primera componente guarda un string que vendría siendo el ID, y la segunda componente es un vector que guadará la info correspondiente


		// ---- Metodos ----/
		// O(n)
		virtual void resize(){
			std::vector< std::pair<char, datos > > *aux = new std::vector< std::pair<char, datos > >(hash_primos[real_size + 1]);
			for(int i = 0; i < hash_primos[real_size]; i++){
				if((*hash)[i].first == 'o'){
					(*aux)[i].first = 'o';
					(*aux)[i].second = (*hash)[i].second;
				}
				else{
					std::vector<std::string> sisi;
					(*aux)[i].first = 'v';
					(*aux)[i].second = std::make_pair("_",sisi);
				}
			}


			this -> real_size++;
			this -> alpha = (float)size / hash_primos[real_size];
			delete hash;
			this -> hash = aux;



		}


		// O(1)
		virtual int hash_foo(std::string str){       // Funcion de hash que se aplicará a los elementos
			
			int hash_value = 0;

			// tamdato = 
			// La funcion hash devuelve la sumatoria de cada caracter en ascii multiplicado por su posicion en el arreglo
			// Inventada por mi, no es una buena funcion hash, es solo con fines demostrativos
			for(int i = 1; i <= str.size(); i++)
				hash_value += str[i - 1] * i;

			return hash_value;
		}
};


#endif
