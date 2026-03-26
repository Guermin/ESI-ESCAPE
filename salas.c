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


int sala_añadir_objeto(Sala *s, int id_objeto) {
    int exito = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && exito == 0) {
        if (s->id_objetos[i] == -1) { 
            s->id_objetos[i] = id_objeto;
            exito = 1;
        }
        i++;
    }
    return exito;
}

int sala_quitar_objeto(Sala *s, int id_objeto) {
    int exito = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && exito == 0) {
        if (s->id_objetos[i] == id_objeto) {
            s->id_objetos[i] = -1; 
            exito = 1;
        }
        i++;
    }
    return exito;
}

int sala_tiene_objeto(Sala s, int id_objeto) {
    int encontrado = 0, i = 0;
    while (i < MAX_OBJETOS_SALA && encontrado == 0) {
        if (s.id_objetos[i] == id_objeto) encontrado = 1;
        i++;
    }
    return encontrado;
}

int sala_añadir_puzzle(Sala *s, int id_puzzle) {
    int exito = 0, i = 0;
    while (i < MAX_PUZZLES_SALA && exito == 0) {
        if (s->id_puzzles[i] == -1) {
            s->id_puzzles[i] = id_puzzle;
            exito = 1;
        }
        i++;
    }
    return exito;
}

int sala_tiene_puzzle(Sala s, int id_puzzle) {
    int encontrado = 0, i = 0;
    while (i < MAX_PUZZLES_SALA && encontrado == 0) {
        if (s.id_puzzles[i] == id_puzzle) encontrado = 1;
        i++;
    }
    return encontrado;
}