#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MIN_DURACION 10
#define MAX_DURACION 100

typedef struct {
    int TareaID; // autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 – 100
} Tarea;

typedef struct Nodo {
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

// Funciones
Nodo* CrearListaVacia();
void InsertarNodo(Nodo **Start, Nodo *nuevoNodo);
Nodo* CrearTarea(int id);
void MostrarTareas(Nodo *Start);

int main() {
    srand(time(NULL));

    Nodo *pendientes = CrearListaVacia();
    int opcion;
    int idActual = 1000; // Comienza en 1000

    printf("CARGA DE TAREAS:\n");

    do {
        Nodo *nuevaTarea = CrearTarea(idActual);
        InsertarNodo(&pendientes, nuevaTarea);
        idActual++;

        printf("¿Desea ingresar otra tarea? \n1: Si \n0: No ");
        fflush(stdin);
        scanf("%d", &opcion);
        

    } while (opcion != 0);

    printf("\nLISTADO DE TAREAS PENDIENTES:\n");
    MostrarTareas(pendientes);

    return 0;
}

Nodo* CrearListaVacia() {
    return NULL;
}

void InsertarNodo(Nodo **Start, Nodo *nuevoNodo) {
    nuevoNodo->Siguiente = *Start;
    *Start = nuevoNodo;
}

Nodo* CrearTarea(int id) {
    Nodo *nueva = (Nodo *)malloc(sizeof(Nodo));
    if (nueva == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    nueva->T.TareaID = id;

    char buff[100];
    printf("Ingrese descripcion de la tarea: ");
    fflush(stdin);
    gets(buff);
   

    nueva->T.Descripcion = (char *)malloc(strlen(buff) + 1);
    strcpy(nueva->T.Descripcion, buff);

    nueva->T.Duracion = (rand() % (MAX_DURACION - MIN_DURACION + 1)) + MIN_DURACION;

    nueva->Siguiente = NULL;

    return nueva;
}

void MostrarTareas(Nodo *Start) {
    Nodo *aux = Start;
    while (aux != NULL) {
        printf("ID: %d - Descripcion: %s - Duracion: %d minutos\n",
               aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
        aux = aux->Siguiente;
    }
}
