

// función principal

#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <stdio.h>
#include "hashADT.h"

#include "hash_cerrado_pato.h"


typedef std::pair<std::string, std::vector<std::string>> datos;
using namespace std;


vector<string> splitStrings(string str, char dl)
{
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







int main(){
	ifstream my_file;
	my_file.open("universities_followers_2022.csv");
	char dl = ';';
	string line;	
	int cont = 0;

	int tol; // cuantos serán leídos
	cout << "Ingrese cantidad de datos a leer: ";
	cin >> tol;
	tol=tol-1;
	getline(my_file,line);;

	vector<string> linestring;
	// cout << "UniversityID  UserID " << endl; 



	clock_t final_time;
	double total_time;
	clock_t start_time = clock();
	



	TablaHash_cerrada hash;

	while(my_file.good()){
		if (cont>tol) break;
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
		// editado 24/6 22:02  
		
		
		vectorfile.push_back(linestring[0]); //second[0]
		vectorfile.push_back(linestring[2]); //second[1]
		vectorfile.push_back(linestring[3]); //second[2]
		vectorfile.push_back(linestring[4]); //second[3]
		vectorfile.push_back(linestring[5]);
		vectorfile.push_back(linestring[6]);

		// Si el primer valor del par es un 1, entonces la clave será User_ID. Si es un 2, entonces la clave será
		// User_Name
		par = make_pair(linestring[1],vectorfile);
		


		// cout << "User Name: " << par.first << " " << endl;

		// cout << "university: " << par.second[0] << endl;
		// for(int i=0; i<4; i++){
			// cout << par.second[i+1] << endl1
		// }

		// cout << "User ID: " << par.second[1] << endl;;
		// cout << "Number Tweets: " << par.second[2] << endl;
		// cout << "Friends Count: " << par.second[3] << endl;
		// cout << "Followers Count: " << par.second[4] << endl;
		// cout << "Created At: " << par.second[5] << endl;

		

		hash.insert(par);



		cont = cont + 1; 




	}

	final_time=clock();
	total_time = ((double)(final_time - start_time)) / CLOCKS_PER_SEC;


	cout << "Tiempo de inserción de " << tol+1 << " datos: " << total_time << endl;



	bool busqueda=0;
	cout << "¿Desea hacer una búsqueda? ";
	cin >> busqueda;

	while(busqueda == 1){
		string str;
		cout << "ingrese ID a buscar: ";
		cin >> str;
		cout << "Posición de " << str << " en tabla hash: " << hash.buscar(str) << endl;
		cout << "Si deseas buscar otro usuario, ingresa 1; caso contrario, un cero: ";
		cin >> busqueda;
	}

	cout << "Tiempo de inserción de " << tol+1 << " datos: " << total_time << endl;


	cout << "Tamaño de la tabla hash: " << sizeof(hash) << endl;
	// std::cout << "Posicion elemento \"renormalizando\": " << hash.buscar("renormalizado") << "\n";



	my_file.close();
	return 0; 
}
