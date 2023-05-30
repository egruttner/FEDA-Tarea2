/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso

4.1. Costo (en notación O) del tiempo:

El ciclo while(cant_casos--) se ejecuta "cant_casos" veces.
Dentro de este ciclo, se realizan operaciones de lectura, inserción y acceso en el mapa "resultado",
que tiene una complejidad promedio de O(log N), donde N es el tamaño del mapa.
* https://en.cppreference.com/w/cpp/container/map
std::map is a sorted associative container that contains key-value pairs with unique keys.
Keys are sorted by using the comparison function Compare. Search, removal,
and insertion operations have logarithmic complexity.
Maps are usually implemented as Red–black trees.

Además, se realiza una operación de ordenamiento en el vector procesa, lo cual tiene un costo de O(1) en este caso,
ya que el tamaño del vector es constante (5 elementos).
Por lo tanto, el costo total de este bucle es O(cant_casos * log N), donde N es el tamaño del mapa resultado.

Dentro del ciclo while (iterador != resultado.end()), se recorre el mapa "resultado" utilizando un iterador.
La iteración se realiza una vez para cada elemento del mapa, por lo que el costo de este ciclo es proporcional
al tamaño del mapa, es decir, O(N), donde N es el tamaño del mapa resultado.

Finalmente, el costo total del algoritmo es O(cant_casos * log N + N),
donde:
- cant_casos es la cantidad de casos a procesar
- N es el tamaño del mapa "resultado".

4.2. Costo de espacio:

El uso de espacio en el programa se debe principalmente al mapa resultado, el vector procesa y las variables locales.

En el peor caso, el tamaño del mapa puede ser igual al número total de casos procesados, es decir, cant_casos.
Por lo tanto, el costo de espacio del mapa resultado es O(cant_casos).

El espacio utilizado por el vector "procesa" es constante, ya que tiene un tamaño fijo de 5 elementos.

El espacio adicional utilizado por las variables locales es insignificante en comparación con el mapa "resultado".

En general, el costo de espacio del algoritmo es proporcional al número de casos a procesar, es decir, O(cant_casos).


5.- Referencias de código:

FROSH -> "Mechón"

Explicación de mapa
https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/

https://aprende.olimpiada-informatica.org/index.php/cpp-map


*/

/* LIBRERIAS */
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {

    /* VARIABLES */
    int cant_casos;
    int c1,c2,c3,c4,c5; //cursos
    int combinacion_popular;
    int cantidad_alumnos;
    map<vector<int>,int> resultado;

    scanf("%d",&cant_casos); //Lee cantidad de casos

    while(cant_casos>0)
    {
        resultado.clear(); //Limpia todos los elementos del mapa
        combinacion_popular = 0;

        while(cant_casos--)
        {
            //Lee info de caso
            cin >> c1 >> c2 >> c3 >> c4 >> c5;

            //Carga vector con información
            vector<int> procesa;
            procesa.push_back(c1);
            procesa.push_back(c2);
            procesa.push_back(c3);
            procesa.push_back(c4);
            procesa.push_back(c5);
            
            //Al ordenar el vector se puede visualizar mejor si es una combinación única
            sort(procesa.begin(),procesa.end());

            //El vector ordenado queda como índice del mapa resultado
            resultado[procesa] = resultado[procesa] + 1;
            //Si no existe la combinación parte, por defecto, con 0 y se le suma 1 para visualización
            //Si ya está la combinación la hace aumentar

            //Revisa si ha salido una combinación "más popular" y la actualiza
            combinacion_popular = max(combinacion_popular,resultado[procesa]);  

        }

        cantidad_alumnos = 0; //Inicializa

        //Recorre el mapa resultado con un iterador
        map<vector<int>,int>::iterator iterador = resultado.begin();
        while (iterador != resultado.end())
        {
            //Si la combinación seleccionada seleccionada por un alumno es la más popular, aumenta conteo de alumnos
            if(iterador->second == combinacion_popular) cantidad_alumnos++;
            ++iterador;
        }
        
        cout << cantidad_alumnos * combinacion_popular << endl;

        //Busca si hay más casos a procesar
        scanf("%d",&cant_casos);
        getchar();  //Salto de carro por formato de Input
    }
}