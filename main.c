#include "hashmap.h"
#include "list.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BARRA "-------------------------------------------------------"

// Se definen las estructuras de datos y TDA usadas en el programa.
typedef struct Tarea Tarea;

typedef struct {
  char data[21];
} precedencia;

struct Tarea {
  char nombre[31];
  int prioridad;
  bool completada;
  List *precedencia;
};

void RegistrarTarea(HashMap *map, int prioridad, char *tarea, int *contTareas) {
  Tarea *i = (Tarea *)malloc(sizeof(Tarea));
  strcpy(i->nombre, tarea);
  i->prioridad = prioridad;
  insertMap(map, strdup(tarea), i);
  (*contTareas)++;
}

void Precedencia(HashMap *map, char *tarea1, char *tarea2) {

  Pair *i = searchMap(map, tarea2);
  if (((Tarea *)i->value)->precedencia == NULL) {
    ((Tarea *)i->value)->precedencia = createList();
  }
  Pair *j = searchMap(map, tarea1);
  if (j == NULL) {
    printf("La tarea %s no existe\n", tarea2);
    return;
  }
  pushBack(((Tarea *)i->value)->precedencia, j->key);
}

void mostrarTareas(HashMap *map,int contTareas) { // Se muestran todas las tareas del mapa con sus
                      // respectivos precedentes en caso de que los posea.
  Pair *a = firstMap(map);
  if (a == NULL) { // Validacion de que hayan tareas que mostrar
    printf("No se ha ingresado ninguna tarea\n");
    return;
  }
  // Se crean 2 valor copia, para no modificar el mapa real.
  Tarea **tareasAux = malloc(sizeof(Tarea) * contTareas);
  int *indiaux = malloc(sizeof(int) * contTareas);
  int i = 0;
/*
  while (a != NULL) {//Se ingresan los datos a la copia.
    Tarea *T = (Tarea*)a->value;
    tareasAux[i] = T;
    indiaux[i] = i;
    i++;

    a = nextMap(map);
  }
  //Se ordenan los elementos del arreglo copia a traves de un bubblesort
  for (int i = 1; i < contTareas; i++) {
  int j = i;
  while (j > 0 && tareasAux[indiaux[j - 1]]->prioridad >
  tareasAux[indiaux[j]]->prioridad) { int aux = indiaux[j]; indiaux[j] =
  indiaux[j - 1]; indiaux[j - 1] = aux; j--;
    }
  }*/

  printf("|Tarea  |Prioridad  |Precedentes  |\n");
  int cont = 1;
  while (a != NULL) {
    int cont2 = 0;
    Tarea *o = (Tarea *)a->value;
    printf("%d. %s (Prioridad: %d)", cont, o->nombre, o->prioridad);

    if (firstList(o->precedencia) != NULL) {
      for (char *x = firstList(o->precedencia); x != NULL;
           x = nextList(o->precedencia)) {
        if (cont2 == 0) {
          printf("- Precedente: %s", x);
          cont2++;
        } else {
          printf(", %s", x);
        }
      }
    }
    printf("\n");
    cont++;
    a = nextMap(map);
  }
}

void borrarTarea(HashMap *map, char *tarea,int *contTareas) { // Funcion que se encarga de marcar como completa una tarea y borrarla del mapa.                        
  Pair *i = searchMap(map, tarea);
  char respuesta[2];
  if (((Tarea *)i->value)->precedencia != NULL) {
    printf("¿estás seguro que desea eliminar la tarea?");//En caso de tener precedencia se hace unapregunta para confirmar su uso.
    scanf(" %[^\n]s", respuesta);
    printf("%s\n", respuesta);
    if (strcmp(respuesta, "n") == 0)
      return;
    if(strcmp(respuesta,"s")==0)
      eraseMap(map, tarea);

  for(Pair *a=firstMap(map); a!= NULL;a=nextMap(map)){ 
    List *o=((Tarea *)a->value)->precedencia;

    if (firstList(o) != NULL) { // Se comprueba si la tarea es precedente a otra. Si es asi, se
                // borrara de las listas ajenas en las que se encuentra.

      for (char *j = firstList(o); j != NULL;j = nextList(o)) {
        if (strcmp(j, tarea)==0) {
          popCurrent(o);
        }
      }
    }
  }
    return;
  }
  eraseMap(map, tarea);

  for(Pair *a=firstMap(map); a!= NULL;a=nextMap(map)){ 
    List *o=((Tarea *)a->value)->precedencia;

    if (firstList(o) != NULL) { // Se comprueba si la tarea es precedente a otra. Si es asi, se
                // borrara de las listas ajenas en las que se encuentra.

      for (char *j = firstList(o); j != NULL;j = nextList(o)) {
        if (strcmp(j, tarea)==0) {
          popCurrent(o);
        }
      }
    }
  }
}

void mostrarMenu() { // Función que se encarga de desplegar el menu cada vez que
                     // se ingresa al programa.
  puts(BARRA);
  printf("                   Administrador de prioridades\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer "
         "precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar "
         "tarea como completada\n0. Salir\n");
  puts(BARRA);
}

int main() {
  HashMap *map = createMap(50);
  char tarea1[31];
  char tarea2[31];
  int prioridad;
  unsigned short numIngresado;
  char nombreArchivo[31];
  int largoName;
  int contTareas = 0;

  while (true) {
    mostrarMenu();

    scanf("%hu", &numIngresado);

    while (numIngresado > 6 || numIngresado < 0) {
      printf("Ingrese un número válido \n");
      scanf("%hu", &numIngresado);
    }

    if (numIngresado == 0) {
      printf("\n");
      puts(BARRA);
      printf("                  FIN DEL PROGRAMA\n");
      puts(BARRA);
      return 0;
    }
    if (numIngresado == 1) {
      printf("Ingrese el nombre de la tarea\n");
      scanf(" %[^\n]", tarea1);
      largoName = strlen(tarea1);

      while (largoName > 31 || largoName < 1) {
        printf("Ingrese un nombre válido (hasta 30 caracteres)\n");
        scanf(" %[^\n]", tarea1);
        largoName = strlen(tarea1);
      }
      printf("Ingrese la prioridad de la tarea\n");
      scanf(" %i", &prioridad);

      RegistrarTarea(map, prioridad, tarea1, &contTareas);
    }
    if (numIngresado == 2) {
      printf("Ingrese el nombre de la primer tarea\n");
      scanf(" %[^\n]s", tarea1);
      printf("Ingrese el nombre de la segunda tarea\n");
      scanf(" %[^\n]s", tarea2);
      Precedencia(map, tarea1, tarea2);
    }
    if (numIngresado == 3) {
      mostrarTareas(map, contTareas);
    }
    if (numIngresado == 4) {
      printf("Ingrese el nombre de la tarea completada\n");
      scanf(" %[^\n]s", tarea1);
      borrarTarea(map, tarea1, &contTareas);
    }
    if (numIngresado == 5) {
      printf("Funcion no terminada\n");
      BetterCallSaul();
    }
  }
}