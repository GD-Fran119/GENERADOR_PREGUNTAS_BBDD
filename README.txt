
# REQUERIMIENTOS:

	- Sistema operativo Linux (no importa la arquitectura)

	- Sistema operativo que siga el estandar POSIX, en su defecto


# ACLARACIONES A LA HORA DE COMPILAR EL PROGRAMA:

	- Usar la siguiente linea para compilar:
		g++ main.cpp funciones.hpp -o TEST

		Si hay problemas, añadir la opcion -std=gnu++14:
			g++ -std=gnu++14 main.cpp funciones.hpp -o TEST

		Si persisten los problemas, contactar con el desarrollador


	- Usar el comando make:

		make

		make help (para saber los destinos que se pueden usar)


# ACLARACIONES ANTES DE EJECUTAR EL PROGRAMA:

	- Los directorios, al igual que el fichero <config.conf> donde esten los ficheros de las preguntas deben
		estar en la misma carpeta que desde donde se ejecuta al programa. No existe opcion para especificar la
		ruta a estos directorios


	- El nombre de los directorios debe seguir el siguiente formato:

		Tema_n donde n es el numero del tema (Tema_1, Tema_2, ...)

		No deben faltar directorios en la secuencia 1, 2, 3, ..., n; podria fallar el script <config.sh>


	- Los ficheros deben ser nombrados de la siguiente forma:
		
		n.txt donde n es el numero del fichero (1.txt, 2.txt, ...)

		Al igual que con los directorios, no deben faltar numeros entre [1, n]

		La numeracion de los ficheros de un directorio es independiente de la numeracion de otro.
		Explicacion: se puede dar el siguiente caso:

			Tema_1/1.txt Tema_2/1.txt

	- Los ficheros deben estar estructurados de la siguente manera:

		\\ linea 1 -> pregunta

		// lineas de la 2 a la 5 (ambas inclusive) -> respuestas

		\\ linea 6 -> numero de la respuesta correcta

		// linea 7 -> vacia (salto de linea o '\n' de la linea 6)

		Ejemplo:

			1	¿Cual es la funcion del gestor de la base de datos?
			2	Respuesta 1
			3	Respuesta 2
			4	Respuesta 3
			5	Respuesta 4
			6	2
			7

			En este caso la respuesta correcta seria "Respuesta 2" (linea 3)



	- Antes de ejecutar el programa, se debe ejecutar <config.sh>

		(asegurarse de que tiene los permisos necesarios chmod u+x) para generar el fichero <config.conf>,
		que recoge la cantidad de carpetas que hay con preguntas y el numero de ficheros que tiene
		cada carpeta. No modificar a mano el fichero <config.conf>

		No hace falta borrar el fichero <config.conf> si se producen cambios en los ficheros de los
		directorios, ejecute <config.sh> para volver a generarlo

		Si se usa <config.sh> y no existen directorios del tipo 'Tema_n', se generara el fichero de
		configuracion, pero al ejecutar el programa saltara un fallo. Asegurarse de que existe, al menos,
		un directorio (Tema_1)


# ACLARACIONES A LA HORA DE EJECUTAR EL PROGRAMA:

	- Usar la opcion -h para conocer las opciones existentes


# DUDAS O PROBLEMAS:

	- Contactar con el desarrollador
