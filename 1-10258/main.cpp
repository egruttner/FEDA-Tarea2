/*
1.- Nombre: Erich Germán Grüttner Díaz
2.- Online Judge ID:	1597479
3.- Sentencia de autoría: el código entregado ha sido generado personalmente, en base a la investigación realizada
4.- Análisis asintótico de la solución para el peor caso

4.1. Costo (en notación O) del tiempo:
El ciclo principal while (casos--) ejecuta el código interno una vez por cada caso.
En el peor caso, tiene una complejidad de O(casos).

El ciclo interno while (cin.peek() != '\n' && cin.peek() != EOF) se ejecuta hasta que se encuentra un salto de línea o se alcanza el final del archivo.
En el peor caso, su complejidad es O(n), donde n es el número total de líneas de entrada en un caso.

El ciclo for dentro del ciclo interno realiza operaciones adicionales, pero su complejidad total está limitada por la complejidad del ciclo while.
Por lo tanto, se puede considerar que el ciclo interno domina la complejidad.

La función sort se utiliza para ordenar los equipos según el criterio personalizado.
En el peor caso, tiene una complejidad de O(n log n), donde n es el número total de equipos.

El ciclo for que muestra los resultados se ejecuta para cada equipo con envío realizado, lo que tiene una complejidad de O(101) en el peor caso.

Por lo tanto, la complejidad del tiempo en el peor caso se puede aproximar a O(casos * n log n),
donde n es el número total de líneas de entrada en un caso.

4.2.- Costo de espacio:
Se utilizan varias estructuras de datos para almacenar el input de entrada y los resultados.
El uso de memoria está limitado por la cantidad máxima de equipos y líneas de entrada en un caso.

La estructura "resultado" se almacena para cada equipo, lo que requiere un espacio de O(101) en el peor caso.

El vector concursantes se utiliza para almacenar las líneas de entrada para cada equipo,
lo que también requiere un espacio adicional dependiendo del número total de líneas de entrada.

Por lo tanto, el costo de espacio en el peor caso está limitado por O(101 + n), donde n es el número total de líneas de entrada en un caso.

5.- Referencias de código:

//Uso de struct
https://www.w3schools.com/cpp/cpp_structs.asp

//Custom sort
https://www.studytonight.com/cpp-programs/cpp-custom-sort-method-for-stl-pair-template-program

*/

/* LIBRERIAS */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* ESTRUCTURAS */
//Información recibida por cada línea del caso
struct linea_ingreso{
  int problema;
  int tiempo;
  char resultado; //Puede ser: ‘C’, ‘I’, ‘R’, ‘U’ or ‘E’. Correct, Incorrect, clarification Request, Unjudged and Erroneous submission. 
                  //Los últimos 3 no afectan al puntaje
};

//Salida del problema. Se considera además un flag de envio_realizado para que sirva de indicador para comenzar a medir el tiempo
struct resultado {
  int id;
  int cant_resueltos;
  int tiempo;
  bool envio_realizado;
  //Constructor-Inicializador
  resultado() : cant_resueltos(0),
                tiempo(0),
                envio_realizado(false) 
                {}
};

/* FUNCIONES */
bool ordenCustom(const resultado &a, const resultado &b) 
{
  /* Permite ordenar el vector de resultados con el siguiente criterio:
  1.- Ordena por cantidad de problemas resueltos
  2.- Si hay empate, gana el con menos tiempo de penalización
  3.- Si hay empate, gana el que tenga el envío realizado
  4.- Si el empate persiste, se ordena por id dentro del equipo
  */
  if (a.cant_resueltos == b.cant_resueltos) 
  {
    if (a.tiempo == b.tiempo) 
    {
      if (a.envio_realizado == b.envio_realizado) 
      {
        return a.id < b.id;
      }
      return a.envio_realizado;
    }
    return a.tiempo < b.tiempo;
  }
  return a.cant_resueltos > b.cant_resueltos;
}



int main() {
  
  /* VARIABLES */
  int casos; //Cantidad de casos a evaluar, ingresado en input
  int id_concursante;
  linea_ingreso tmp;
  bool envio_realizado;
  
  //INPUT DE CASOS
  scanf("%d",&casos);
  getchar();  //Salto de carro por formato de Input
  getchar();  //Salto de carro por formato de Input

  //LOOP PRINCIPAL
  while (casos--) //Para cada caso realiza el proceso. Los casos generan soluciones independientes
  { 
    //Por cada caso reinicia las estructuras que almacenarán la info temporal
    resultado teams[101]; //Vector de estructuras de tipo resultado, tamaño 101 
    vector<linea_ingreso> concursantes[101];

    //Inicializa el vector de resultado. Crea 100 registros aunque se usen o no.
    for (int i = 0; i < 101; i++)
      teams[i].id = i;

    //Ciclo mientras no se acabe el archivo (EOF) o mientas no se
    //encuentre un salto de carro, lo que significaría un nuevo caso
    while (cin.peek() != '\n' && cin.peek() != EOF) 
    {
      //Lee la información de la lína de input
      cin >> id_concursante >> tmp.problema >> tmp.tiempo >> tmp.resultado;
      getchar(); 

      //Marca como envío realizado para ese concursante
      teams[id_concursante].envio_realizado = true;

      //Si el input de la línea viene con resultado Correcto...
      if (tmp.resultado == 'C') {
        envio_realizado = false;
        //...busca en el "caché" de inputs si para ese problema ya había información de entrega correcta, si es así
        //marca como "envio_realizado" para no alterar la cuenta de tiempo
        for (int i = 0, cant_concursantes = concursantes[id_concursante].size(); i < cant_concursantes; i++) {
          if (concursantes[id_concursante][i].problema == tmp.problema && concursantes[id_concursante][i].resultado == 'C') {
            envio_realizado = true;
            break;
          }
        }

        //Si no se encontró "envío realizado" para ese concursante, entonces es un nuevo problema resuelto
        //Aumenta la cantidad de resueltos
        //Aumenta el tiempo de penalización en base al Input
        //Si para ese problema ya tenía la marca 'I' entonces aumentar valor de penalización por tiempo
        if (!envio_realizado) { 
          teams[id_concursante].cant_resueltos += 1;
          teams[id_concursante].tiempo += tmp.tiempo;
          //...busca en el "caché" de inputs si para ese problema ya había información de entrega incorrecta para aumentar la penalización
          for (int i = 0, cant_concursantes = concursantes[id_concursante].size(); i < cant_concursantes; i++) {
            if (concursantes[id_concursante][i].problema == tmp.problema && concursantes[id_concursante][i].resultado == 'I') {
              teams[id_concursante].tiempo += 20;
            }
          }
        }
      }

      //Agrega al caché la línea de registro
      concursantes[id_concursante].push_back(tmp);

    }
    //Fin de ingreso de Input

    getchar(); //Salto de carro para marcar el término

    //Ordena el resultado de acuerdo a lo especificado en la función ordenCustom
    sort(teams, teams + 101, ordenCustom);

    //Muestra el resultado. Solamente considera los que tienen envío realizado
    for (int i = 0; i < 101; i++) {
      if (teams[i].envio_realizado == false) break;

      cout << teams[i].id << " " << teams[i].cant_resueltos << " " << teams[i].tiempo << endl;
    }
    
    //Si es el final del caso, agrega un salto de carro al output final
    if (casos)  cout << endl;
  }
}