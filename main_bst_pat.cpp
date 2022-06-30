#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include "arbolBinarioBusqueda.h"

using namespace std;



// Creamos funciones para leer los datos
// funcion para leer datos y separar csv obtenida de
// https://www.geeksforgeeks.org/split-string-substrings-using-delimiter/


vector<string> splitStrings(string str, char dl){
    string word = ""; 
 
    // to count the number of split strings
    int num = 0;
 
    // adding delimiter character at the end
    // of 'str'
    str = str + dl;
 
    // length of 'str'
    int l = str.size();
 
    // traversing 'str' from left to right
    vector<string> substr_list;
    for (int i = 0; i < l; i++) {
 
        // if str[i] is not equal to the delimiter
        // character then accumulate it to 'word'
        if (str[i] != dl)
            word = word + str[i];
 
        else {
 
            // if 'word' is not an empty string,
            // then add this 'word' to the array
            // 'substr_list[]'
            if ((int)word.size() != 0)
                substr_list.push_back(word);
 
            // reset 'word'
            word = "";
        }
    }
 
    // return the splitted strings
    return substr_list;
}





typedef std::pair<std::string, std::vector<std::string>> datos;
using namespace std;

// CREAREMOS AQUÍ LA CLASE ÁRBOL BINARIO DE BÚSQUEDA


// ---- Metodos Clase Nodo ---- //

// Constructor nodo raiz
Nodo::Nodo(datos str){   // O(1)

	izq = NULL;
	der = NULL;
	padre = NULL;
	this -> str = str;
}


// Constructor Nodo no raiz
Nodo::Nodo(datos str, Nodo *padre){   // O(1)

	izq = NULL;
	der = NULL;
	this -> padre = padre;
	this -> str = str;
}

// Destructor
Nodo::~Nodo(){      // O(1)

	delete izq;
	delete der;
}



// ---- Metodos Clase ArbolBinarioBusqueda ---- //

// Constructor
ArbolBinarioBusqueda::ArbolBinarioBusqueda(){   // O(1)
	raiz = NULL;
}

// Destructor
ArbolBinarioBusqueda::~ArbolBinarioBusqueda(){   // O(1)
	// Eliminar todos los nodos hacia abajo (implementar, soy flojo)
	delete raiz;
}

// Publico: Insertar un valor en el arbol
bool ArbolBinarioBusqueda::insertar(datos dato){     // O(log(n))

	if(raiz == NULL){
		raiz = new Nodo(dato);
		return true;
	}

	return insertar(dato, raiz);
}

// Privado: Insertar un nodo no raiz solo si n !=NULL
bool ArbolBinarioBusqueda:: insertar(datos dato, Nodo *n){   // O(log(n))

	// ---- Caso base principal
	// Si el valor está repetido, no se inserta el nodo
	if(dato.first == n -> str.first){
		return false;
	}

	// Si el valor a insertar es menor al del nodo, hacia la izquierda
	if(dato.first < n -> str.first){

		// Si el hijo izquierdo esta vacio, insertar
		if(n -> izq == NULL){
			n -> izq = new Nodo(dato, n);
			return true;
		}

		// Si no está vacio, bajar a la izquierda e intentar insertar
		return insertar(dato, n -> izq);
	}

	// Si el valor a insertar es mayor al del nodo, hacia la derecha
	if(n -> der == NULL){
		n -> der = new Nodo(dato, n);
		return true;
	}

	return insertar(dato, n -> der);
}


// Public: busca el valor en el arbol, retorna NULL si no existe
Nodo *ArbolBinarioBusqueda::buscar(string str){       // O(log(n))
	
	return buscar(str, raiz);
}


// Private: busca el valor en un nodo, si no es, baja hasta llegar a una hoja
Nodo *ArbolBinarioBusqueda::buscar(string str, Nodo *n){    // O(log(n))

	// ---- Casos Base ---- //
	
	// Si es una hoja o raiz, el valor no existe
	if(n == NULL)
		return NULL; 
	
	// Si encontramos el valor, retornar direccion del nodo
	if(n -> str.first == str)
		return n;

	// ---- Casos Recursivos ---- //
	if(str < n -> str.first)
		return buscar(str, n -> izq);

	return buscar(str, n -> der);
} 

// Public: Imprimir arbol inOrder
void ArbolBinarioBusqueda::inOrder(){    // O(n)

	cout << "In Order:" << endl;
	inOrder(raiz);
	cout << endl;
}

// Private: Imprimir nodo inOrder
void ArbolBinarioBusqueda::inOrder(Nodo *n){  // O(n)
	
	// ---- Caso Base
	// Si llegamos a una hoja, no seguir bajando
	if(n == NULL)
		return;
	inOrder(n -> izq);
	std::cout << n -> str.first << " ";
	inOrder(n -> der);
}


// Public: Retorna el nodo mayor del arbol (analogo para el menor)
Nodo *ArbolBinarioBusqueda::mayor(Nodo* n){    // O(log(n))

	if(n == NULL)
		return NULL;

	Nodo *iterador = n;
	while(iterador -> der != NULL)
		iterador = iterador -> der;

	return iterador;
}

int main(){

	int n;
	ArbolBinarioBusqueda arbol;

	std::cout << "Cantidad de nodos a insertar: ";
	std::cin >> n;

		// Abrimos el archivo y lo leemos
	ifstream my_file;
	my_file.open("universities_followers_2022.csv");
	char dl = ';';
	string line;	
	int cont = 0;
	getline(my_file,line);

	vector<string> linestring;



	clock_t final_time;
	double total_time;
	clock_t start_time = clock();
	

	for(int i = 0; i < n; i++){

		string line;
		getline(my_file, line);

		linestring = splitStrings(line,dl);

		
		datos par;

		vector<string> vectorfile;

		// tengamos que en linestring:
		// 0: university
		// 1: user_id
		// 2: user_name
		// 3: number_tweets
		// 4: friends_count
		// 5: followers_count
		// 6: created_at

		// el vector del type dato tiene tamaño no definido
		// editado 27/6 22:41  



		vectorfile.push_back(linestring[0]); //second[0]
		vectorfile.push_back(linestring[2]); //second[1]
		vectorfile.push_back(linestring[3]); //second[2]
		vectorfile.push_back(linestring[4]); //second[3]
		vectorfile.push_back(linestring[5]);
		vectorfile.push_back(linestring[6]);

		par = make_pair(linestring[1],vectorfile);

		arbol.insertar(par);

	}

	final_time=clock();
	total_time = ((double)(final_time - start_time)) / CLOCKS_PER_SEC;


	cout << "Tiempo de inserción de " << n+1 << " datos: " << total_time << endl;



	// arbol.inOrder();
		
	return 0;
}
