/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso

4.1. Costo (en notación O) del tiempo:
La lectura inicial de la cantidad de carros tiene un costo de tiempo constante, O(1).
El ciclo exterior while que lee los casos de prueba se ejecuta hasta que se encuentre un encabezado con 0 carros.
El número total de iteraciones de este ciclo depende del número de casos de prueba en la entrada, pero asumiendo que 
el número total de casos de prueba es N, el costo de este ciclo es O(N).

El ciclo interior while que lee los carros dentro de cada caso de prueba se ejecuta hasta que se encuentre un carro con valor 0.
El número total de iteraciones de este bucle depende de la cantidad de carros en cada caso de prueba, pero en el peor caso,
donde no se encuentra un carro con valor 0, el número de iteraciones es igual a la cantidad de carros.
Por lo tanto, el costo de este ciclo es O(M), donde M es la suma de la cantidad de carros en todos los casos de prueba.

El ciclo for que lee la información de los carros y los guarda en la cola de carros tiene un costo lineal
en relación con la cantidad de carros, por lo que su costo es O(M).

El ciclo while que recorre la cola de carros tiene un costo en función de la cantidad de carros y la cantidad de elementos en la estación.
En el peor caso, donde todos los carros están en la cola y la estación está vacía, el número de iteraciones es igual a M.
Por lo tanto, el costo de este bucle es O(M).

Por lo tanto, el costo total del algoritmo es O(N * M),
donde N es el número de casos de prueba y M es la suma de la cantidad de carros en todos los casos de prueba.

4.2. Costo de espacio:
El uso de espacio en el programa se debe principalmente a las estructuras de datos utilizadas.
El espacio utilizado por las estructuras de pila (stack) y cola (queue) depende de la cantidad de carros en cada caso de prueba.

El espacio adicional utilizado por las variables locales y las lecturas de entrada también es insignificante
en comparación con las estructuras de datos mencionadas anteriormente.

En general, el costo de espacio del algoritmo es proporcional a la cantidad total de carros en todos los casos de prueba,
es decir, O(M).

5.- Referencias de código:

Uso de stack
https://es.wikibooks.org/wiki/Programación_en_C%2B%2B/Librería_Estándar_de_Plantillas/Pilas#:~:text=C%2B%2B%20stack%20estándar&text=La%20Libreria%20estándar%20de%20plantillas,cinco%20métodos%20y%20dos%20constructores.

Uso de queue
https://www.techiedelight.com/es/queue-implementation-cpp/#:~:text=Implementación%20de%20queues%20en%20C,enqueue%20%2C%20dequeue%20%2C%20y%20peek%20.

*/

/* LIBRERIAS */ 
#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

int main() {

    /* VARIABLES */ 
    int cantidad_carros;

    scanf("%d",&cantidad_carros);
    while(cantidad_carros != 0) //Lee hasta que en el encabezado de carros aparezca un 0
    {
        int carro;
        scanf("%d",&carro); //Lee carro

        while(carro != 0)   //Lee hasta que venga un carro con valor 0
        { 
            stack<int> estacion;        //Estructura de pila para simular estación
            queue<int> cola_carros;     //Estructura de cola para simular cola de carros a evaluar
            
            //Guarda (push) el valor del primer carro en la cola
            cola_carros.push(carro);

            //Inicializa variable que lleva el control de la posición actual del carro
            int posicion_carro = 1;

            //Lee la información de carros y la guarda en la cola de carros
            for(int i=1;i<cantidad_carros;i++)
            {
                scanf("%d",&carro);
                cola_carros.push(carro);
            }

            //Recorre la cola de carros mientras queden carros
            while(!cola_carros.empty())
            {
                if( estacion.empty() ||
                    estacion.top() != cola_carros.front())
                {
                    //Si la estación queda vacía o el carro tope de la estación no es el mismo de la cola de carros
                    //valida que la posición del carro no sea mayor que la cantidad de carros
                    //en ese caso sale del loop
                    if(posicion_carro > cantidad_carros) break;
                    //sino aumenta la posición del carro y guarda en la estación
                    estacion.push(posicion_carro++);
                } 
                else 
                {
                    //Se elimina un carro desde la cola de carros y desde la estación
                    cola_carros.pop();
                    estacion.pop();
                }
            }

            //Después de procesar, revisa si quedaron o no carros
            if (cola_carros.empty())
            {
                //Si no quedaron carros, SI es factible la maniobra, por lo que se devuelve "Yes"
                cout << "Yes" << endl;
            }
            else
            {
                //Si quedaron carros, NO es factible la maniobra, por lo que se devuelve "No"
                cout << "No" << endl;
            }

            //Lee el siguiente carro
            scanf("%d",&carro);
        }
        cout << endl;

        //Vuelve a leer la cantidad de carros
        scanf("%d",&cantidad_carros);

    }
}