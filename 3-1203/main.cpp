/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso
4.1. Costo (en notación O) del tiempo:

La lectura inicial de los registros y la construcción de la cola de prioridad tienen un costo lineal en relación con el número de registros.
En el peor caso, se leen todos los registros antes de encontrar el carácter "#", por lo que el costo es O(N),
donde N es el número total de registros.

El ciclo while(k--) se ejecuta k veces, donde k es el número de queries que se considerarán.
En cada iteración, se realiza una operación de extracción y una operación de inserción en la cola de prioridad,
ambas operaciones tienen un costo logarítmico en función del número de elementos en la cola.
Por lo tanto, el costo total de este bucle es O(k * log N), donde N es el número total de registros.
* Según https://en.cppreference.com/w/cpp/container/priority_queue
A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element,
at the expense of logarithmic insertion and extraction.

Por lo tanto, el costo total del algoritmo es O(N + k * log N), donde N es el número total de registros
y k es el número de queries que se considerarán.

4.2. Costo de espacio:

El espacio utilizado por la cola de prioridad depende del número de registros en la entrada. 

En el peor caso, donde se leen todos los registros antes de encontrar el carácter "#",
el número de elementos en la cola es igual al número total de registros.
Por lo tanto, el costo de espacio de la cola de prioridad es O(N).

El espacio adicional utilizado por las variables locales y las lecturas de entrada
también es insignificante en comparación con la cola de prioridad mencionada anteriormente.

En general, el costo de espacio del algoritmo es proporcional al número total de registros en la entrada, es decir, O(N).

5.- Referencias de código:

Explicación de cola de prioridad
https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/

Explicación de make_pair
https://www.educative.io/answers/how-to-use-the-makepair-function-in-cpp

*/


/* LIBRERIAS */
#include <iostream>
#include <queue>
using namespace std;

int main() 
{
  /* VARIABLES */
  string registro;
  int q_num;  //Número de query
  int period; //Tiempo
  int k;      //Cantidad de queries a ejecutar
  
  priority_queue< pair< pair<int, int>, int> > cola_proridad;
  //Ejemplo de par: < <200,2004>, 200>

  pair< pair<int, int>, int> aux_tiempo;


  //Carga toda la info previa
  cin >> registro;
  while (registro!="#") //Lee mientras no salda un #
  {
      cin >> q_num >> period; //Lee input en formato establecido

      //Se guarda input en cola de prioridad
      //Se guardan negativos para invertir el orden
      cola_proridad.push(make_pair(make_pair(-period, -q_num), -period));

      //Lee un nuevo registro
      cin >> registro;
  }

  //Lee k para hacer loop
  cin >> k; //Número de queries que se considerarán
  while(k--) 
  {
      aux_tiempo = cola_proridad.top(); //Se rescata el valor en aux_tiempo
      cola_proridad.pop(); //Se quita el registro
      cout << -aux_tiempo.first.second << '\n'; //Se imprime negativo para que se imprima positivo, en este caso el q_num
      
      //Al sacarlo se considera ejecutado, pero volverá a ejecutarse en el siguiente periodo
      //es por eso que se debe aumentar su registro de tiempo y volver a ingresar a la cola de prioridad
      aux_tiempo.first.first += aux_tiempo.second;
      cola_proridad.push(aux_tiempo);
  }
}