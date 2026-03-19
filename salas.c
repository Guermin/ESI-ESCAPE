#include "salas.h"
#include <stdio.h>
#include <string.h>


Sala sala_crear(int id, const char *nombre, const char *descripcion, TipoSala tipo){
    Sala nueva_sala;

    nueva_sala.id = id;
    nueva_sala.tipo = tipo; //Asignación de datos

    strcpy(nueva_sala.nombre, nombre);
    strcpy(nueva_sala.descripcion, descripcion);

    for (int i = 0; i < MAX_OBJETOS_SALA; i++){
        nueva_sala.id_objetos[i] = -1;
    }

    for (int i = 0; i < MAX_PUZZLES_SALA; i++){
        nueva_sala.id_puzzles[i] = -1;
    }

    return nueva_sala;
}

void sala_mostrar_info(Sala sala){
    printf("\n===================================\n");
    printf("LUGAR: %s\n", sala.nombre);
    printf("====================================\n");
    printf("%s\n\n", sala.descripcion);
}