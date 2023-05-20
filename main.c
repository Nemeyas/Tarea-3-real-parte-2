#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "hashmap.h"
#define BARRA "-------------------------------------------------------"

//Se definen las estructuras de datos y TDA usadas en el programa.
typedef struct Tarea Tarea;

typedef struct{
  char data[21];
}precedencia;

struct Tarea{
  char nombre[31];
  int prioridad;
  bool completada;
  List* precedencia;
};

void RegistrarTarea(HashMap* map,int prioridad, char *tarea){
  Tarea *i=(Tarea*) malloc(sizeof(Tarea));
  strcpy(i->nombre, tarea);
  i->prioridad=prioridad;
  insertMap(map, strdup(tarea), i);
}

void Precedencia(HashMap* map, char *tarea1, char *tarea2){
  Pair* i=searchMap(map, tarea2);
  if(((Tarea *)i->value)->precedencia==NULL){
    ((Tarea *)i->value)->precedencia = createList();
  }
  Pair* j=searchMap(map, tarea1);
  if(j==NULL){
    printf("La tarea %s no existe\n", tarea2);
    return;
  }
  pushBack(((Tarea *)i->value)->precedencia, j->key);
}

void mostrarTareas(HashMap* map){
  Pair *a = firstMap(map);
  if(a == NULL){
    printf("No se ha ingresado ninguna tarea\n");
    return;
  }
  printf("|Tarea  |Prioridad  |Precedentes  |\n");
  int cont = 1;
  while(a != NULL){
    int cont2 = 0;
    Tarea *o = (Tarea*)a->value;
    printf("%d. %s (Prioridad: %d)", cont, o->nombre, o ->prioridad);

    if(firstList(o -> precedencia) != NULL){
      for(char *i = firstList(o ->precedencia) ; i != NULL ; i = nextList(o -> precedencia)){
        if(cont2 == 0){
          printf("- Precedente: %s",i);
          cont2++;
        }
        else{
          printf(", %s",i);
        }
      }
    }
    printf("\n");
    cont++;
    a = nextMap(map);
  }
} 

void borrarTarea(HashMap* map, char *tarea){
  Pair* i=searchMap(map, tarea);
  char respuesta[2];
  bool valido=false;
  if(((Tarea *)i->value)->precedencia!=NULL){
    printf("¿estás seguro que desea eliminar la tarea? [y/n]");
    scanf(" %[^\n]", respuesta);
    printf("%s\n", respuesta);
    while (valido==false){
      printf("Ingrese una de las 2 opciones [y/n] \n");
      scanf(" %[^\n]", respuesta);
      if(strcmp(respuesta, "y") ==0){
        valido=true;
      }
      if(strcmp(respuesta, "n") !=0){
        valido=true;
      }
    }
    if(strcmp(respuesta, "n")==0) return;
  }
  if(strcmp(respuesta, "y")==0){ 
  Pair *a = firstMap(map);
  while(a != NULL){
    int cont2 = 0;
    Tarea *o = (Tarea*)a->value;

    if(firstList(o -> precedencia) != NULL){
      for(char *j = firstList(o ->precedencia) ; j != NULL ; j = nextList(o -> precedencia)){
        if(strcmp(j, ((Tarea *)i->value)->nombre)){ 
          j=NULL;
          cont2++;
        }
      }
    }
    a = nextMap(map);
  }
  free(i);
  i=NULL;
  }
}

void mostrarMenu() {//Función que se encarga de desplegar el menu cada vez que se ingresa al programa.
  puts(BARRA);
  printf("                   Administrador de prioridades\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. Agregar tarea\n2. Establecer precedencia entre tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada\n5. Cargar datos de tareas desde un archivo de texto\n0. Salir\n\n");
  puts(BARRA);
}

int main(){
  HashMap* map= createMap(50);
  char tarea1[31];
  char tarea2[31];
  int prioridad;
  unsigned short numIngresado;
  char nombreArchivo[31];
  int largoName;

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
      
      RegistrarTarea(map, prioridad, tarea1);
    }
    if (numIngresado == 2) {
      printf("Ingrese el nombre de la primer tarea\n");
      scanf(" %[^\n]s", tarea1);
      printf("Ingrese el nombre de la segunda tarea\n");
      scanf(" %[^\n]s", tarea2);
      Precedencia(map, tarea1, tarea2);
    }
    if (numIngresado == 3) {
      mostrarTareas(map);
    }
    if (numIngresado == 4) {
      printf("Ingrese el nombre de la tarea completada\n");
      scanf(" %[^\n]", tarea1);
      borrarTarea(map,tarea1);
    }
    if (numIngresado == 5) {
      printf("Escriba el nombre del archivo\n");
      scanf(" %[^\n]", nombreArchivo);
      setbuf(stdout, NULL);

      FILE *archivo = fopen(nombreArchivo,"rt");
      if (archivo == NULL) {
        printf("* Error al abrir el archivo.\n");
      } 
      else{
        //importar(heap, archivo);
        printf("* Archivo importado con éxito\n");
      }
    }
  }
}