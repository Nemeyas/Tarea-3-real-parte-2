#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define BARRA "-------------------------------------------------------"



void mostrarMenu() {//Función que se encarga de desplegar el menu cada vez que se ingresa al programa.
  puts(BARRA);
  printf("                   Administrador de prioridades\n");
  puts(BARRA);
  printf("\nSeleccione una opción:\n\n1. 1. Agregar tarea\n2. Establecer precedencia entre   tareas\n3. Mostrar tareas por hacer\n4. Marcar tarea como completada\n5. Deshacer última acción\n6. Cargar datos de tareas desde un archivo de texto\n0. Salir\n\n");
  puts(BARRA);
}

int main(){;
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
      
      //RegistrarTarea(map, prioridad, tarea1);
    }
    if (numIngresado == 2) {
      printf("Ingrese el nombre de la primer tarea\n");
      scanf(" %[^\n]s", tarea1);
      printf("Ingrese el nombre de la segunda tarea\n");
      scanf(" %[^\n]s", tarea2);
      //Precedencia(tarea1, tarea2);
    }
    if (numIngresado == 3) {
      //mostrarTareas(heap);
    }
    if (numIngresado == 4) {
      printf("Ingrese el nombre de la tarea completada\n");
      scanf(" %[^\n]", tarea1);
      //borrarTarea(heap,tarea1);
    }
    if (numIngresado == 5) {
      //deshacer(heap);
    }
    if (numIngresado == 6) {
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