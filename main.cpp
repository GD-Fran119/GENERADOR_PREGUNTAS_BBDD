#include <unistd.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <map>

#include "funciones.hpp"

/*

	Options:

		-h          for help
		-t number   for choosing the lesson, if not selected it generates questions fom all the lessons
		-n number   how many questions do u wanna answer? Default: 10, min: 1, max: 30
		
				Correct | Incorrect | Total | Mark 1 | Mark 2
						|			|		|		 |
				   7    |     3     |  10   |  7/10  |  6/10

				Mark 2:
					Incorrects : -0.33 (-1 / number of incorrect answers)

*/

static int numero_temas;


//For debugging
void print_vector(std::vector<std::pair<int, int>> v){
	std::cout << numero_temas << '\n';
	for(auto aux : v) std::cout << aux.first << " " << aux.second << '\n';

	exit(EXIT_SUCCESS);
}
//

int main(int argc, char **argv){
	
	srand(time(NULL));
	
	bool help = false, tema_especifico = false, numero = false;
	std::string tema_number, numero_number;
	int tema_dir = -1, numero_veces = 1;

	char c;
	opterr = 0;

	while((c = getopt(argc, argv, "ht:n:")) != -1){
		
		switch(c){
			
			case 'h':{
				help = true;
			} break;
			
			case 't':{
				if(not tema_especifico){
					tema_especifico = true;
					tema_number = optarg;
				}
				else{
					std::cout << "Doble opcion -t encontrada. Fin del programa\n";
					exit(EXIT_FAILURE);
				}
			} break;
			
			case 'n':{
				if(not numero){
					numero = true;
					numero_number = optarg;
				}
				else{
					std::cout << "Doble opcion -n encontrada. Fin del programa\n";
					exit(EXIT_FAILURE);
				}
			} break;
			
			case '?':{
				
				switch(optopt){
				
					case 't':{
						std::cout << "Falta argumento para la opcion -t. Fin del programa\n";
						exit(EXIT_FAILURE);
					} break;
				
					case 'n':{
						std::cout << "Falta argumento para la opcion -n. Fin del programa\n";
						exit(EXIT_FAILURE);
					} break;
				
					default:{
						std::cout << "Opcion no valida encontrada. Fin del programa\n";
						exit(EXIT_FAILURE);
					} break;
				}
			} break;
			default:{
				std::cout << "Fallo importante en getopt(). Fin del programa\n";
				exit(EXIT_FAILURE);
			} break;
		}
	}

	if(help){
		print_help();
		exit(EXIT_SUCCESS);
	}

	std::ifstream file("config.conf");
	std::vector<std::pair<int, int>> vectorsito_config;

	if(not file.is_open()){
		std::cout << "Fichero \"config.conf\" no encontrado. Ejecute \"config.sh\" para generarlo\n";
		exit(EXIT_FAILURE);
	}
	else{
		file.close();
		vectorsito_config = read_config(numero_temas);
	}

	//Debug
	//print_vector(vectorsito_config);
	//

	if(tema_especifico){
		if(is_number(tema_number))
			tema_dir = std::stoi(tema_number);
		else{
			std::cout << "Argumento de -t (" + tema_number + ") no numerico. Fin del programa\n";
			exit(EXIT_FAILURE);
		}
	}

	if(numero){
		
		if(is_number(numero_number))
			numero_veces = std::stoi(numero_number);
		else{
			std::cout << "Argumento de -n (" + numero_number + ") no numerico. Fin del programa\n";
			exit(EXIT_FAILURE);
		}
	}

	check(tema_dir, numero_veces, numero_temas);

	test(tema_dir, numero_veces, vectorsito_config, numero_temas);

	exit(EXIT_SUCCESS);

}
