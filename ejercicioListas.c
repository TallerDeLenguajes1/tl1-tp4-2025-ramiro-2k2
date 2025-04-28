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
void MoverTareas(Nodo **pendientes, Nodo **realizadas);
Nodo* BuscarPorID(Nodo *lista, int id);
Nodo* BuscarPorPalabra(Nodo *lista, char *palabra);
void LiberarLista(Nodo *lista);

int main() {
    srand(time(NULL));

    Nodo *pendientes = CrearListaVacia();
    int opcion;
    int idActual = 1000; // Comienza en 1000
    int buscarID;
char buscarPalabra[50];
Nodo *resultado;

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
    Nodo *realizadas = CrearListaVacia();

// muevo las tareas de una lista a la otra
MoverTareas(&pendientes, &realizadas);

//muestro como quedo la lista pendiente

printf("Lista de Pendientes:\n");
MostrarTareas(pendientes);

//muestro la orta lista

printf("Lista de realizadas:\n");
MostrarTareas(realizadas);




printf("Ingrese el ID que desea buscar:\n ");
fflush(stdin);
scanf("%d", &buscarID);

// Buscar en pendientes
resultado = BuscarPorID(pendientes, buscarID);
if (resultado != NULL) {
    printf("Tarea encontrada en pendientes: %s\n", resultado->T.Descripcion);
} else {
    // Buscar en realizadas
    resultado = BuscarPorID(realizadas, buscarID);
    if (resultado != NULL) {
        printf("Tarea encontrada en realizadas: %s\n", resultado->T.Descripcion);
    } else {
        printf("Tarea no encontrada.\n");
    }
}

printf("Ingrese palabra clave:\n ");
fflush(stdin);
gets(buscarPalabra);

// Buscar en pendientes
resultado = BuscarPorPalabra(pendientes, buscarPalabra);
if (resultado != NULL) {
    printf("Tarea encontrada en pendientes: %s\n", resultado->T.Descripcion);
} else {
    // Buscar en realizadas
    resultado = BuscarPorPalabra(realizadas, buscarPalabra);
    if (resultado != NULL) {
        printf("Tarea encontrada en realizadas: %s\n", resultado->T.Descripcion);
    } else {
        printf("Tarea no encontrada.\n");
    }
}


LiberarLista(pendientes);
LiberarLista(realizadas);

    return 0;
}
//creo el primer nodo vacio apuntado a null
Nodo* CrearListaVacia() {
    return NULL;
}
// para insertar un nodo lo aputn star al nuevo nodo y a ese mismo lo apunto a star
void InsertarNodo(Nodo **Start, Nodo *nuevoNodo) {
    nuevoNodo->Siguiente = *Start;
    *Start = nuevoNodo;
}
// aqui  creo un nodo tarea y le doy el malloc y uso buff para guardar la cadena
Nodo* CrearTarea(int id) {
    Nodo *nueva = (Nodo *)malloc(sizeof(Nodo));
   

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



// para mover las tareas de una lista a la otrea
void MoverTareas(Nodo **pendientes, Nodo **realizadas) {
    Nodo *actual = *pendientes;
    Nodo *anterior = NULL;
    int respuesta;

    while (actual != NULL) {
        printf("\nTarea ID: %d\n", actual->T.TareaID);
        printf("Descripcion: %s\n", actual->T.Descripcion);
        printf("Duracion: %d minutos\n", actual->T.Duracion);

        printf("¿ Se realizo esta tarea? \n1: Si  \n0: No ");
        fflush(stdin);
        scanf("%d", &respuesta);

        if (respuesta == 1) {
            // Mover a lista de realizadas
            Nodo *mover = actual;

            // Actualizar la lista de pendientes
            if (anterior == NULL) {
                // El primer nodo fue realizado
                *pendientes = actual->Siguiente;
            } else {
                anterior->Siguiente = actual->Siguiente;
            }

            // Insertar en realizadas
            InsertarNodo(realizadas, mover);

            // Avanzar al siguiente
            actual = (anterior == NULL) ? *pendientes : anterior->Siguiente;
        }
        else {
            // No se movió la tarea
            anterior = actual;
            actual = actual->Siguiente;
        }
    }
}


// busco
Nodo* BuscarPorID(Nodo *lista, int id) {
    Nodo *aux = lista;
    while (aux != NULL) {
        if (aux->T.TareaID == id) {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}


Nodo* BuscarPorPalabra(Nodo *lista, char *palabra) {
    Nodo *aux = lista;
    while (aux != NULL) {
        if (strstr(aux->T.Descripcion, palabra) != NULL) {
            return aux;
        }
        aux = aux->Siguiente;
    }
    return NULL;
}

void LiberarLista(Nodo *lista) {
    Nodo *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->Siguiente;
        free(aux->T.Descripcion); // liberar la descripción
        free(aux);                // liberar el nodo
    }
}