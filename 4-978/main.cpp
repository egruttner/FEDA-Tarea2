/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso
4.1. Costo (en notación O) del tiempo:

El ciclo while(casos--) se ejecuta "casos" veces. En cada iteración, se realizan operaciones de lectura,
inserción y extracción en las colas de prioridad. Las operaciones de inserción y extracción tienen un costo
logarítmico en función del número de elementos en la cola. 
Por lo tanto, el costo total de este ciclo es O(casos * (sg + sb) * log(sg + sb)), donde sg es la cantidad de 
Lemmings verdes y sb es la cantidad de Lemmings azules en cada caso.
* Según https://en.cppreference.com/w/cpp/container/priority_queue
A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element,
at the expense of logarithmic insertion and extraction.

Dentro del ciclo while(!l_azules.empty() && !l_verdes.empty()), hay un ciclo for que se ejecuta b veces en cada iteración.
En cada iteración del ciclo, se realizan operaciones de inserción y extracción en las colas de prioridad,
lo que tiene un costo logarítmico en función del número de elementos en la cola.
Por lo tanto, el costo total de este ciclo es O(b * log(sg + sb)),
donde sg es la cantidad de Lemmings verdes y sb es la cantidad de Lemmings azules en cada caso.

Por lo tanto, el costo total del algoritmo sería O(casos * (sg + sb) * log(sg + sb) + b * log(sg + sb)),
donde:
- casos es el número de casos a procesar
- sg es la cantidad de Lemmings verdes
- sb es la cantidad de Lemmings azules
- b es el número de batallas en cada caso.

4.2. Costo de espacio:

El uso de espacio en el programa se debe principalmente a las colas de prioridad (priority_queue),
los vectores y las variables locales.

En el peor caso, el número de elementos en cada cola de prioridad es igual a la cantidad total de Lemmings verdes
y Lemmings azules en todos los casos.

Por lo tanto, el costo de espacio del algoritmo es proporcional al número total de Lemmings verdes
y Lemmings azules en todos los casos, es decir, O(sg + sb).


5.- Referencias de código:

Implementación/uso de queue
https://www.techiedelight.com/es/queue-implementation-cpp/#:~:text=Implementación%20de%20queues%20en%20C,enqueue%20%2C%20dequeue%20%2C%20y%20peek%20.

*/

/* LIBRERIAS */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() 
{
    /* VARIABLES */
    int casos; //Número de casos a procesar
    int b; //Número de batallas - Battlefields
    int sg; //Cantidad de Lemmings verdes
    int sb; //Cantidad de Lemmings azules
    int aux_poder; //Auxiliar para lectura de poder de cada Lemming

    //Lee cantidad de casos a procesar
    scanf("%d",&casos);
    while(casos--)
    {
        //Lee número de batallas y cantidad de lemmings verdes y azules
        cin >> b >> sg >> sb;

        priority_queue<int> l_verdes; //Cola de prioridad para guardar lemmings verdes
        priority_queue<int> l_azules; //Cola de prioridad para guardar lemmings azules
        
        //A continuación se lee toda la info de lemmings verdes
        //y se almacena en la cola correspondiente
        while(sg--)
        {
            cin >> aux_poder;
            l_verdes.push(aux_poder);
        }

        //A continuación se lee toda la info de lemmings azules
        //y se almacena en la cola correspondiente
        while(sb--)
        {
            cin >> aux_poder;
            l_azules.push(aux_poder);
        }

        //BATALLA!!!
        //MIENTRAS QUEDEN SOLDADOS PARA PELEAR
        while(!l_azules.empty() && !l_verdes.empty())
        {
            //Vectores para almacenar los soldados verdes y azules que quedaron
            vector<int> quedanVerdes;
            vector<int> quedanAzules; 

            //Loop por todas las batallas (b) mientras queden soldados verdes y azules para pelear
            for(int i=0;i<b && !l_verdes.empty() && !l_azules.empty();i++)
            {
                //Toma un soldado de cada frente
                int topeVerde = l_verdes.top();
                int topeAzul = l_azules.top();
                l_verdes.pop();
                l_azules.pop();

                if(topeVerde-topeAzul>0) //GANA EL VERDE
                {
                    quedanVerdes.push_back(topeVerde-topeAzul);
                }

                if(topeAzul-topeVerde>0) //GANA EL AZUL
                {
                    quedanAzules.push_back(topeAzul-topeVerde);
                }
            }

            //Guarda los lemmings azules que sobraron de la batalla en el registro total de cada color
            for(int i : quedanAzules)
            {
                l_azules.push(i);
            } 
            for(int i : quedanVerdes)
            {
                l_verdes.push(i);
            } 
        }

        //Si no quedan solados para pelear, ambos murieron:
        if(l_azules.empty() && l_verdes.empty())
        {
            cout<< "green and blue died" << endl; 
        } 
        else if(l_azules.empty())   //Si no quedan más soldados azules, ganan los verdes
        {
            cout << "green wins" << endl;
            while(!l_verdes.empty()){
                    cout << l_verdes.top() << endl;
                    l_verdes.pop();
            }
        }
        else //ELSE Si no quedan más soldados verdes, ganan los azules
        {
            cout << "blue wins" << endl;
            while(!l_azules.empty()){
                    cout << l_azules.top() << endl;
                    l_azules.pop();
            }
        }

        //Agrega un salto de carro al final de los casos
        if(casos) cout << endl;
    }
}