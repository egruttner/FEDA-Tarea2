/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso

4.1. Costo (en notación O) del tiempo:

El ciclo while(casos--) se ejecuta "casos" veces. Dentro de este ciclo, se realizan operaciones de lectura,
inserción y acceso en los vectores y colas, así como operaciones de comparación y asignación.
En general, el tiempo de ejecución del ciclo depende de la cantidad de casos, la cantidad de autos
y la capacidad máxima del ferry.

Las operaciones de inserción y acceso en las colas tienen un costo de O(1) amortizado en promedio.

Las operaciones de inserción y acceso en los vectores tienen un costo de O(1) en promedio.

Las operaciones de comparación y asignación tienen un costo de O(1).

En resumen, el tiempo de ejecución del algoritmo es proporcional al número total de autos
y la capacidad máxima del ferry, es decir, O(cant_autos * capacidadMaxima).


4.2. Costo de espacio:

El uso de espacio en el programa se debe principalmente a los vectores y las colas utilizadas para almacena
la información de los autos y los tiempos totales.

El tamaño de los vectores tiempoTotal y lados depende de la cantidad de autos, es decir, O(cant_autos).

El espacio utilizado por las colas lados[0] y lados[1] también depende de la cantidad de autos,
pero cada cola puede contener un máximo de cant_autos elementos. Por lo tanto, el espacio utilizado
por cada cola es O(cant_autos).

Finalmente, el costo de espacio del algoritmo es proporcional al número de autos, es decir, O(cant_autos).

5.- Referencias de código:

Implementación/uso de queue
https://www.techiedelight.com/es/queue-implementation-cpp/#:~:text=Implementación%20de%20queues%20en%20C,enqueue%20%2C%20dequeue%20%2C%20y%20peek%20.


*/

/* LIBRERIAS */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main(void)
{
  
  //VARIABLES
  int casos;

  scanf("%d",&casos); //Lee cantidad de casos

	while(casos--)
	{
		//Input
		//n = capacidad de Ferry para llevar autos
		//t = tiempo de viaje
		//m = cantidad de líneas a procesar = cantidad de autos
		
		int capacidadMaxima;
		int tiempoViaje;
		int cant_autos;

		//Lee encabezado de caso
		cin >> capacidadMaxima >> tiempoViaje >> cant_autos;

		//Vector para guardar el tiempo total para cada auto
		vector<int> tiempoTotal(cant_autos);
		
		//Vector de colas para almacenar el movimiento en cada lado
		vector< queue<int> > lados(2); //lados[0] = izquierda, lados[1] = derecha
		
		//Lee información de cada auto
		for(int i = 0; i < cant_autos; ++i)
		{
			int tiempo;
			string lado;

			//Lee información de tiempo y lado
			cin >> tiempo >> lado;

			if(lado == "left")
			{
				lados[0].push(i); //Si la dirección es left, se guarda en lados[0] que representa izquierda
			}
			else
			{
				lados[1].push(i); //Si la dirección es right, se guarda en lados[1] que representa derecha
			}

			//Almacena el tiempo para ese auto en el vector totalizador
			tiempoTotal[i] = tiempo;
		}

		
		int lado = 0; //El Ferry parte de la izquierda, es decir 0
		int tiempo = 0;

		//COMIENZA EL VIAJE
		//Mientres queden autos para ser transportados (en el lado izquierdo o derecho)
		while(!lados[0].empty() || !lados[1].empty())
		{
			//Por cada viaje de Ferry
			int tiempoSiguienteLlegada = 0;
			int cargaActual = 0;

			if(lados[0].empty())
				//Si no quedan autos en el lado izquierdo, toma el tiempo del auto de la orilla derecha
				tiempoSiguienteLlegada = tiempoTotal[lados[1].front()];
			else
			{
				if(lados[1].empty())
					//Si no quedan autos en el lado derecho, toma el tiempo del auto de la orilla izquieda
					tiempoSiguienteLlegada = tiempoTotal[lados[0].front()];
				else
					//Si quedan autos en los dos lados
					//obtiene el tiempo mínimo entre el auto de la izquierda y el auto de la derecha
					tiempoSiguienteLlegada = min(tiempoTotal[lados[0].front()], tiempoTotal[lados[1].front()]);
			}

			//Calcula el tiempo de espera máximo entre el tiempo transporte y el de la siguiente llegada
			tiempo = max(tiempo, tiempoSiguienteLlegada);

			//Realiza la carga al Ferry si se cumplen las siguientes condiciones
			//- No esté vacío el lado evaluado (variable lado)
			//- El tiempo total del auto en la orilla actual (variable lado) es menor que el tiempo de llegada
			//- El ferry no esté lleno
			while(  !lados[lado].empty() && 
                    tiempoTotal[lados[lado].front()] <= tiempo && 
                    cargaActual < capacidadMaxima)
			{
				++cargaActual; //Se aumenta la carga del ferry
				tiempoTotal[lados[lado].front()] = tiempo + tiempoViaje; //carga el tiempo de llegada + viaje
				lados[lado].pop(); //Saca el registro del lado porque ya se subió al ferry!!!
			}

			tiempo = tiempo + tiempoViaje; //Se acumula el tiempo

			//Cambia de lado
			if (lado==0)
			{
				lado=1; //Derecho
			}
			else
			{
				lado=0; //Izquierdo
			}

		}

		//Muestra tiempos para cada auto
		for(int i = 0; i < cant_autos; ++i)
		{
			cout << tiempoTotal[i] << endl;
		}

     	//Agrega un salto de carro al final de los casos
        if(casos) cout << endl;
	}	

}