/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso

4.1. Costo (en notación O) del tiempo:

El ciclo while(cin >> texto) se ejecuta hasta que no haya más texto que leer.
Dentro de este ciclo, se realiza un ciclo for que recorre el texto caracter por caracter
y realiza operaciones de inserción en una lista en función de los caracteres encontrados.
La inserción en una lista en la posición actual del "puntero" tiene un costo de O(1).

Por lo tanto, el tiempo de ejecución del algoritmo es proporcional al tamaño del texto de entrada,
es decir, O(m), donde m es el tamaño del texto.
Sin embargo, en el peor caso se debe considerar que lleguen n cantidad de líneas de texto,
por lo tanto debiera ser O(n * m), donde:
- n cantidad de líneas de texto
- m tamaño del texto

4.2. Costo de espacio:

El uso de espacio en el programa se debe principalmente a la lista textoProcesado utilizada para almacenar
el texto una vez revisado y procesado.

El tamaño de la lista "textoProcesado" depende del tamaño del texto de entrada,
por lo que el costo de espacio es proporcional al tamaño del texto, es decir, O(n), donde n es el tamaño del texto.

5.- Referencias de código:

Uso de listas
https://www.geeksforgeeks.org/list-cpp-stl/

*/


/* LIBRERIAS */
#include <iostream>
#include <list>

using namespace std;

int main(void)
{
	//VARIABLES
	string texto;

	while(cin >> texto) //Mientras exista texto que leer
	{
		list<char> textoProcesado; //Lista donde se almacenará el texto una vez revisado y procesado

		list<char>::iterator puntero = textoProcesado.end(); //"Puntero" donde se escribe, parte apuntando al final
		
		//Recorre texto caracter por caracter, hasta largo del texto
		for(int i = 0; i < texto.length(); ++i)
		{
			//Casos en función del caracter evaluacdo del string
			switch(texto[i])
			{
				case '[':
					puntero = textoProcesado.begin(); //Si encuentra '[' puntero va al principio
				break;
				case ']':
					puntero = textoProcesado.end(); //Si encuentra ']' puntero va al final
				break;
				default:	//Si no es ninguna de la anteriores agrega caracter donde apunte el "puntero"
					textoProcesado.insert(puntero, texto[i]);
			}
		}

		//Recorre lista textoProcesado como output del programa, utilizando un iterador para la lista
		for(list<char>::iterator i = textoProcesado.begin(); i != textoProcesado.end(); ++i)
		{
			cout << *i; //Se imprime el valor aputnado por el iterador
		}

		cout << endl;

	}

}