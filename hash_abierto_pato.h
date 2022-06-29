#ifndef __hashitoAbierto__
#define __hashitoAbierto__


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


		virtual bool insert(datos dato){
			
			float alpha_plus = (float)(size + 1) / hash_primos[real_size];


			if(alpha_plus > 0.5){
				resize();
			}
			int index = hash_foo(dato.first) % hash_primos[real_size];
			(*hash)[index].push_back(dato);

			size++;

			return true;

		}


		virtual bool borrar(std::string str){
			int index = buscar(str);
			if(index == -1){
				return false;
			}

			return true;
		}

		virtual int buscar(std::string str){
			int index = hash_foo(str) % hash_primos[real_size];

			 for(int i=0;i<(*hash)[index].size();i++){
			 	if(str.compare((*hash)[index][i].first)==0){
			 		return index;
			 	}
			 }

			 return -1;
		}
		// virtual void print();
	
	private:

		int real_size;
		int size;
		std::vector<std::vector<datos>> *hash;
		
		virtual void resize(){
			
			// Creo una nueva tabla
			// std::vector<std::list<std::string>> *aux(hash_primos[real_size + 1]);

			std::vector<std::vector<datos>> *aux = new std::vector<std::vector<datos>>(hash_primos[real_size + 1]); 

			// Recorrer la tabla vieja
			for(int i = 0; i < hash_primos[real_size]; i++){
				if(!(*hash).empty()){

					for(int j=0; j<(*hash)[i].size(); j++){
						int index = hash_foo((*hash)[i][j].first)  % hash_primos[real_size+1] ;
						(*aux)[index].push_back((*hash)[i][j]);
					}
					
				}
			}

			real_size++;
			delete hash;
			hash = aux;

		}


		virtual int hash_foo(std::string str){
			int hash_value = 0;

			for(int i = 1; i <= str.size(); i++)
				hash_value += str[i - 1] * i;

			return hash_value;
		}

};


#endif
