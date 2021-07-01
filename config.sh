
#Cuenta los directorios que existen en el directorio desde el que se llama al script
let temas=$(ls | egrep "Tema_[0123456789]+" | wc -l)

#Si no hay directorios con el nombre en el formato requerido
#Salta error
if [ $temas -eq 0 ]; then

	echo "No existen en este directorio las carpetas \"Tema_*\" pertinentes"

	if [ -e config.conf ]; then
		rm config.conf
	fi

#Si encuentra al menos 1 directorio que cumple el formato
else

	echo $temas > config.conf

	#Por cada carpeta cuenta los ficheros que contiene y tienen el formato de nombre requerido
	#No compueba si faltan ficheros en la secuencia 1..$numero_ficheros
	for i in $(seq $temas); do

		#Si existe el directorio cuenta TODOS los ficheros
		if [ -d "Tema_$i" ]; then

			let numero_ficheros=$(ls "Tema_$i" | egrep "^[123456789][0123456789]*\.txt$" | wc -l)
			echo "$i $numero_ficheros" >> config.conf

		#Si hay algun directorio que falta en la secuencia 1..$temas
		#Sale del bucle y elimina el fichero config.conf si se estuviese generando
		else

			echo "No se encontro la carpeta Tema_$i"

			if [ -e config.conf ]; then
				rm config.conf
			fi

			break
		fi
	done

fi

#Si se ha generado el fichero de configuracion, avisa por pantalla
if [ -e config.conf ]; then
	echo "Generado config.conf"

#Si no se ha generado el fichero de configuracion, avisa por pantalla
else
	echo "No se genero el fichero config.conf."
	echo "Consulte \"README.txt\" para conocer el formato de directorios y ficheros"
fi
