#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>

/*
	void print_help();

	Desc:
		prints the available options

	return:
		void
*/

void print_help(){
	std::cout << "\tAYUDA:\n\n"
			  << "  -h          imprime esta ayuda\n"
			  << "  -t numero   especifica el tema a trabajar, por defecto -1 (todos)\n"
			  << "  -n numero   numero de preguntas a responder, por defecto: 10, min: 1, max: 30\n"
			  << "\nNota: no hace falta especificar ninguna opcion para usar el programa.\n"
			  << "      Si se usan las opciones -t o -n, se deben emplear solo una vez\n"
			  << "      Si se usan mas de una vez (cualquiera de ellas) el programa acaba\n";
}

/*
	std::vector<std::pair<int, int>> read_config(int &numero_temas);

	Desc:
		gets the number of lessons and stores its value in numero_temas
		makes a vector with the lessons and their questions

		Example:
			vector[0].first -> number of lesson (1 'cause vector[0] is "Tema_1")
			vector[0].second -> number of questions (files 1.txt, 2.txt, etc)
								inside the directory Tema_<vector[n].first> (Tema_1)

	return:
		vector with the lessons and their questions
*/

std::vector<std::pair<int, int>> read_config(int &numero_temas){
	
	std::ifstream file("config.conf");

	file >> numero_temas;

	if(not file){
		std::cout << "Fallo en el fichero \"config.conf\", no tiene el formato corecto\n"
				  << "Fin del programa\n";
		exit(EXIT_FAILURE);
	}
	if(numero_temas == 0){
		std::cout << "Fallo en el fichero \"config.conf\", no existen directorios Tema_*\n"
				  << "Fin del programa\n";
		exit(EXIT_FAILURE);
	}

	std::vector<std::pair<int, int>> devolusion;

	for(int i = 0; i < numero_temas; ++i){
		
		int a, b;
		file >> a >> b;

		if(not file){
			std::cout << "Fallo en el fichero \"config.conf\", no tiene el formato corecto\n"
					  << "Fin del programa\n";
			exit(EXIT_FAILURE);
		}

		devolusion.push_back(std::pair<int, int>(a, b));

	}
	return devolusion;
}

/*
	bool is_number(std::string numero);

	Desc:
		checks if a string (numero) is 0 or a positive number

	return:
		True: numero == (0 or a positive number)
		False: any other case
*/

bool is_number(std::string numero){

	if(not numero.size()) return false; //Size == 0

	for(auto aux : numero)
		if(aux < '0' or aux > '9') return false;

	return true;
}

/*
	void check(int tema_dir, int numero_veces, int tema_max);

	Desc:
		checks if tema_dir is in [-1(default), tema_max] and numero_veces is in [1, 30];
		finishes the program if the conditions above are false

	return:
		void
*/

void check(int tema_dir, int numero_veces, int tema_max){
	
	if(tema_dir > tema_max or tema_dir == 0){
		std::cout << "Numero de tema especificado (-t " << tema_dir << ") no permitido\n"
				  << "Debe estar en [1, " << tema_max << "]\n"
				  << "Fin del programa\n";
		exit(EXIT_FAILURE);
	}

	if (numero_veces > 30 or numero_veces < 1){
		std::cout << "Numero de veces especificado (-n " << numero_veces << ") no permitido\n"
				  << "Debe estar en [1, 30]\n"
				  << "Fin del programa\n";
		exit(EXIT_FAILURE);
	}
}

/*
	std::vector <std::pair <std::string, bool>> read_file(std::string name_file)

	Desc:
		reads the questions from the file, mixes the answers by making them randomly positioned
		if the format of the file "name_file" is incorrect, the program ends

	return:
		std::vector <std::pair <std::string, bool>>

		vector[0].first -> Question
		vector[1].first -> Randomly inserted answer 1
		vector[2].first -> Randomly inserted answer 2
		vector[3].first -> Randomly inserted answer 3
		vector[4].first -> Randomly inserted answer 4

		vector.second -> bool : if true, it means vector.first is the correct answer

*/

std::vector <std::pair <std::string, bool>> read_file(std::string name_file){

	std::ifstream file(name_file);
	
	if(not file.is_open()){
		std::cout << "Fallo al abrir el fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	std::pair <std::string, bool> linea1("", false), linea2("", false), linea3("", false),
								  linea4("", false), linea5("", false);
	int respuesta;

	if(not std::getline(file, linea1.first, '\n')){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	if(not std::getline(file, linea2.first, '\n')){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	if(not std::getline(file, linea3.first, '\n')){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	if(not std::getline(file, linea4.first, '\n')){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	if(not std::getline(file, linea5.first, '\n')){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	if(not (file >> respuesta)){
		std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
		exit(EXIT_FAILURE);
	}

	switch(respuesta){
		case 1:{
			linea2.second = true;
		}break;
		case 2:{
			linea3.second = true;
		}break;
		case 3:{
			linea4.second = true;
		}break;
		case 4:{
			linea5.second = true;
		}break;
		default:{
			std::cout << "Fallo en el formato del fichero: " + name_file + "\nFin del programa\n";
			exit(EXIT_FAILURE);
		}break;
	}

	std::vector <std::pair <std::string, bool>> retornasion;

	//Insertar las respuestas en orden aleatorio

	if(rand() % 2) retornasion.push_back(linea2);
	else retornasion.insert(retornasion.begin(), linea2);

	if(rand() % 2) retornasion.push_back(linea3);
	else retornasion.insert(retornasion.begin(), linea3);

	if(rand() % 2) retornasion.push_back(linea4);
	else retornasion.insert(retornasion.begin(), linea4);

	if(rand() % 2) retornasion.push_back(linea5);
	else retornasion.insert(retornasion.begin(), linea5);

	//Inserta la pregunta al inicio del vector;

	retornasion.insert(retornasion.begin(), linea1);

	file.close();

	return retornasion;
}

/*
	void test(int tema_dir, int numero_veces);

	Desc:
		provides the correct answer(if the chosen answer is incorrect)
		and calculates the result (Mark1 | Mark 2) see main.cpp

	return:
		void
*/

void test(int tema_dir, int numero_veces, std::vector<std::pair<int, int>> config, int numero_temas){
	
	std::string directorio = "Tema_" + (tema_dir == -1 ? "" : std::to_string(tema_dir) + "/");
	int copy = numero_veces, corectas = 0;
	
	std::string fichero;

	std::vector<std::pair<std::string, bool>> pregunta;
	
	auto print_question = [&]() -> void{
		std::cout << pregunta[0].first << "\n";
		for(int i = 1; i < 5; ++i)
			std::cout << i << ".- " << pregunta[i].first << "\n";
		std::cout << "Opcion: ";
	};

	auto print_correct_answer = [&]() -> void{
		std::cout << "Respuesta correcta: ";
		for(auto aux : pregunta)
			if(aux.second)
				std::cout << aux.first << "\n\n";
	};

	auto print_results = [&]() -> void {
		std::cout << "\n==================== RESULTADO ====================\n"
				  << "\nCorrectas | Incorrectas | Total | Nota 1 |   Nota 2"
				  << "\n\n    "
				  //Correctas e incorrectas
				  << corectas << "            " << numero_veces - corectas << "          "
				  //Total
				  << numero_veces << "      "
				  //Nota 1
				  << float(corectas) * 10.0 / float(numero_veces) << "/" << 10
				  << "      "
				  //Nota 2
				  << (float(corectas) * 10.0 / float(numero_veces)) -
				  float(numero_veces - corectas) * 10 / (numero_veces * 3)
				  << "/" << 10
				  << "\n===================================================\n";
	};

	int respuesta;
	std::string ans;
	
	if(directorio == "Tema_"){
		for(int i = 0; i < copy; ++i){
			
			int temasion = rand() % numero_temas + 1;
			std::string directorio_copia = directorio + std::to_string(temasion) + "/";
			
			fichero = std::to_string(rand() % config[temasion - 1].second + 1) + ".txt";
			pregunta = read_file(directorio_copia+fichero);

			//BORRAR ESTA LINEA, IMPRIME FICHERO DE LA PREGUNTA
			std::cout << directorio_copia+fichero << std::endl;
			print_question();

			std::getline(std::cin, ans, '\n');

			if(not is_number(ans) or std::stoi(ans) > 4){
				std::cout << "INCORRECTO\n";
					print_correct_answer();
			}
			else{
				respuesta = std::stoi(ans);
				if(pregunta[respuesta].second){
					std::cout << "CORRECTO\n\n";
					corectas++;
				}
				else{
					std::cout << "INCORRECTO\n";
					print_correct_answer();
				}
			}
		}
	}
	else{
		for(int i = 0; i < copy; ++i){

			fichero = std::to_string(rand() % config[tema_dir - 1].second + 1) + ".txt";
			pregunta = read_file(directorio+fichero);

			//BORRAR ESTA LINEA, IMPRIME FICHERO DE LA PREGUNTA
			std::cout << directorio+fichero << std::endl;
			print_question();

			std::getline(std::cin, ans, '\n');

			if(not is_number(ans) or std::stoi(ans) > 4){
				std::cout << "INCORRECTO\n";
					print_correct_answer();
			}
			else{
				respuesta = std::stoi(ans);
				if(pregunta[respuesta].second){
					std::cout << "CORRECTO\n\n";
					corectas++;
				}
				else{
					std::cout << "INCORRECTO\n";
					print_correct_answer();
				}
			}

		}
	}


	print_results();
}
