#ifndef __hashitoAbierto__
#define __hashitoAbierto__

// Nos basamos en el código creado en ayudantía, modificado a las necesidades del problema:
// Similar a lo descrito en hash_ADT.h, tenemos la pseudo estructura datos que nos ayudará
// a manipular de mejor manera los datos dados para el problema y le lectura del archivo


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "hashADT.h"


typedef std::pair<std::string, std::vector<std::string>> datos;

class TablaHash_abierta: public hashADT{
	
	public:
		TablaHash_abierta(){
			real_size = 0;
			size = 0;
			hash = new std::vector<std::vector<datos>>(hash_primos[0]);
		}


		~TablaHash_abierta(){
			delete hash;
		}

		// Al insertar datos, debemos ingresar toda una linea del archivo csv, por lo que su input es del tipo datos
		virtual bool insert(datos dato){
			// verificamos si se sobrepasa el factor de carga para hacer o no resize
			float alpha_plus = (float)(size + 1) / hash_primos[real_size];


			if(alpha_plus > 0.5){
				resize();
			}
			
			// Hacemos hashing de la clave primaria, enlazando al índice correspondiente un nuevo dato
			int index = hash_foo(dato.first) % hash_primos[real_size];
			(*hash)[index].push_back(dato);

			size++;

			return true;

		}


		// para borrar un dato, solo ingresamos la clave asociada al dato que queremos borrar
		virtual bool borrar(std::string str){
			int index = buscar(str);
			if(index == -1){
				return false;
			}

			return true;
		}

		// para buscar un dato, solo ingresamos la clave del dato que queremos buscar. Retornará el índice de la tabla
		// hash en la que el dato se encuentra si es que lo encuentra. Caso contrario, se devolverá un cero
		virtual int buscar(std::string str){
			int index = hash_foo(str) % hash_primos[real_size];

			 for(int i=0;i<(*hash)[index].size();i++){
			 	if(str.compare((*hash)[index][i].first)==0){
			 		return index;
			 	}
			 }

			 return -1;
		}
	
	private:

		int real_size;
		int size;
		std::vector<std::vector<datos>> *hash;
		
		virtual void resize(){
			
			// Creo una nueva tabla

			std::vector<std::vector<datos>> *aux = new std::vector<std::vector<datos>>(hash_primos[real_size + 1]); 

			// Recorrer la tabla vieja
			for(int i = 0; i < hash_primos[real_size]; i++){
				if(!(*hash).empty()){
					// debemos copiar la tabla antigua a aux 
					for(int j=0; j<(*hash)[i].size(); j++){
						int index = hash_foo((*hash)[i][j].first)  % hash_primos[real_size+1] ;
						(*aux)[index].push_back((*hash)[i][j]);
					}
					
				}
			}
			
// 			borramos la tabla en desuso, y solo nos QUEDAMOS CON NUESTRA NUEVA TABLA: LA TABLA DEFINITIVA
			real_size++;
			delete hash;
			hash = aux;

		}

		
// 		fUNCIÓN hASH: es la misma (mala) función creaeda en ayudantía: la dejé pues era más ilustrativa para mostrar diferencias significativas
// 	para comparar. Más funciones hash se pueden encontrar en internet, en sitios web como http://www.partow.net/programming/hashfunctions/index.html
		virtual int hash_foo(std::string str){
			int hash_value = 0;

			for(int i = 1; i <= str.size(); i++)
				hash_value += str[i - 1] * i;

			return hash_value;
		}

};


#endif
