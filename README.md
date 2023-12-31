# MUIC - DPS - Laboratorio 1

## ejemplo1.c

Follow the instructions explained in the beginning of file ejemplo1.c for compiling with gcc and g++ (you can try also clang). 

								COMPILAR CON GCC
EJEMPLO 1 - ESTANDAR C11

En primer lugar, se observa que se está utilizando R que es trata de una cadena cruda. La cadena cruda es una característica de C++11 y de los estandares suguientes que se utiliza para crear literales de cadena que no interpretan \n o \t. 
En este caso, el compilador no lo está reconociendo ya que estamos compilando el código como C11 y no como C++11. Para solucionarlo, he cambiado la linea que ocasiona el error por: const char* s1 =” foo (Hello World) foo”

Depues, se observa que se está produciendo un error en una funcion de tipo void debido a que en su interior se encuentra la sentencia return 1 que indica que devuelve un 1, lo que es contraditorio. Para solucionarlo, he transformado el return en un printf. 

Además, teniendo en cuenta lo que se ha dicho en clase, la función gets ha sido desaconsejada y se ha eliminado del estandar C11 debido a problemas de seguridad relacionados con la falta de control en el tamaño de los datos. En lugar de gets se recomienda utilizar fgets para leer la entrada de forma segura ya que permite especificar el tamaño máximo del buffer que se va a leer. Por ello, he reemplazado gets por fgets para que no se sopbrepase el tamaño. 

En este codigo, existen varias variables que no se utilizan, por ello he comentado todas aquellas declaraciones de variables que no se usan para evitar errores o warnings de tipo unused variable. 

El puntero slash debe ser inicializado a null para que compile sin warnings ni errores. En caso de GCC++ será inicializado a nullptr en lugar de NULL.  

								COMPILAR CON GCC++ 

Partiendo del codigo corregido anterior, veremos lo que ocurre cuando compilamos con GCC++
						
EJEMPLO 1 - ESTANDAR GCC++11

El primer error que se puede observar es que estamos intenntando modificar una cadena que es una constante en una funcion que se llama "get_dirname". El problema es que la funcion strrchr devuelve un puntero de tipo const cgar porque no permite modificar el contenido de la cadena y por eso no puedo modificar la cadena que está siendo apuntada por pathname.  Para solucionar este problema he copiado la cadena y así puedo trabajar con la copia en lugar de modificar la cadena original. La funcion queda de la siguiente manera:
 
 			const char *get_dirname(const char *pathname) {
 			char *path_copia = strdup (pathname); //copiamos la cadena 
  			char *slash;
			//slash = strrchr(pathname, '/');
 			if (slash) {
    			*slash = '\0'; /* Undefined behavior */
  			}
  			const char *result = strdup(path_copia);
  			free(path_copia);
  			return result;
			}
 
 El siguiente error que aparece tiene que ver con la linea: 
 							char *ptr_char  = "new string literal";  
Esto se debe a que estamos intentando asignar una cadena que esta declarada como una constante a un puntero que es de tipo char. Para solucionar este error he declarado ptr_char como un puntero constante. 
Al transformarlo en un puntero constante no podré modificarla posteriormente, por ello para modificarla se debe hacer una copia de la cadena en el bufer. 

El siguiente error se debe a que no está inicialiazo el puntero slash. Por ello lo inicializamos de esta manera: char *slash = nullptr;

En ambos casos, aparece un ultimo warning al compilar unused parameter que indica que la variable argc no se utiliza en la funcion main. 


## ejemplo2.c. Program Instrumentation

Find the memory errors presented in file ejemplo2 using gcc instrumentation option **AddressSanitizer (ASan)**.
Explain in this file each error.


PRACTICA STRINGS - REBECA RADÍO 

								COMPILAR CON GCC 

EJEMPLO 2 - ESTANDAR C11

El primer error que se debe corregir se encuentra en la función OptionThree() ya que se está 
intentando usar un puntero "s" con la función printf despues de haber liberado su espacio en memoria con la sentencia free(s). 
Para solucionar este error, he asignado el valor null a "s" y de esta forma sigue teniendo el espacio en memoria pero su valor es null. 
Además, según el estandar 11, es aconsejable utilizar strncpy en lugar de strcpy, la diferencia está en el numero de argumentos ya que utilizando strncpy se debe indicar tambien el numero de caracteres que se quiere copiar. Lo solucionamos introduciendo el maximo de caracteres de la cadena. 

La siguiente cuestión a solucionar tiene que ver con la misma funcion, pero con strcpy. LO que ocurre es que estamos intentando copiar una cadena en "s" que es un puntero nulo. Por ello aparece el error argument 1 null where non-null expected. 
Para solucionar esto, asignamos antes de utilizarlo memoria valida nuevamente y de esta forma ya se puede copiar. 


Ahora, lo que se debe corregir se encuentra en la funcion optionFour(), y de nuevo corresponde con la funcionalidad strcpy nuevamente. Ocurre lo mismo que en el caso anterior pero en este caso tenemos una reserva de memoria de 18 caracteres que es exactamente la longitud de la cadena. 
Por ello, como hemos puesto que es exactamente la longitud de la cadena, aparece un warning ya que si metemos la longitud exacta la funcion strncpy no añade el caracter de terminación \0. Para solucionar esto, ponemos una reserva de espacio de memoria de 20 caracteres y copiamos la cadena de 18 caracteres maximo. De esta forma se añade el caracter nulo de terminacion \0 y no sale ningun warning. 

La función strcpy debe ser sustituida por strncpy en el resto del codigo, es decir, en las funciones OPtionOne() y OPtionTwo(). 

								COMPILAR CON GCC++

Al compilar el ejemplo 2 con GCC++11, no se muestra ningun error. 


								
