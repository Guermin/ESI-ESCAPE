#include "partida.h"
#include <stdio.h>


EstadoPartida partida_crear(const char *nombre_jugador, int id_sala_inicio) {
    EstadoPartida nueva_partida;
    nueva_partida.num_salas = 0;
    nueva_partida.num_conexiones = 0;
    nueva_partida.num_objetos = 0;
    nueva_partida.num_puzzles = 0;
    nueva_partida.jugador_actual = jugador_crear(nombre_jugador, id_sala_inicio);
    return nueva_partida; 
}



void partida_destruir(EstadoPartida *p) {
    jugador_destruir(&(p->jugador_actual));
}

int partida_anadir_sala(EstadoPartida *p, Sala s) {
    int exito = 0;
    if (p->num_salas < MAX_SALAS_PARTIDA) {
        p->salas[p->num_salas] = s;
        p->num_salas = p->num_salas + 1;
        exito = 1;
    }
    return exito;
}



int partida_anadir_conexion(EstadoPartida *p, Conexion c) {
    int exito = 0;
    if (p->num_conexiones < MAX_CONEXIONES_PARTIDA) {
        p->conexiones[p->num_conexiones] = c;
        p->num_conexiones = p->num_conexiones + 1;
        exito = 1;
    }
    return exito;
}


int partida_anadir_objeto(EstadoPartida *p, Objeto obj) {
    int exito = 0;
    if (p->num_objetos < MAX_OBJETOS_PARTIDA) {
        p->objetos[p->num_objetos] = obj;
        p->num_objetos = p->num_objetos + 1;
        exito = 1;
    }
    return exito;
}



int partida_anadir_puzzle(EstadoPartida *p, Puzzle puz) {
    int exito = 0;
    if (p->num_puzzles < MAX_PUZZLES_PARTIDA) {
        p->puzzles[p->num_puzzles] = puz;
        p->num_puzzles = p->num_puzzles + 1;
        exito = 1;
    }
    return exito;
}



Sala* partida_obtener_sala(EstadoPartida *p, int id) {
    Sala* encontrada = NULL;
    int i = 0;
    while (i < p->num_salas && encontrada == NULL) {
        if (p->salas[i].id == id) encontrada = &(p->salas[i]);
        i++;
    }
    return encontrada;
}




Conexion* partida_obtener_conexion(EstadoPartida *p, int id) {
    Conexion* encontrada = NULL;
    int i = 0;
    while (i < p->num_conexiones && encontrada == NULL) {
        if (p->conexiones[i].id == id) encontrada = &(p->conexiones[i]);
        i++;
    }
    return encontrada;
}




Objeto* partida_obtener_objeto(EstadoPartida *p, int id) {
    Objeto* encontrado = NULL;
    int i = 0;
    while (i < p->num_objetos && encontrado == NULL) {
        if (p->objetos[i].id == id) encontrado = &(p->objetos[i]);
        i++;
    }
    return encontrado;
}



Puzzle* partida_obtener_puzzle(EstadoPartida *p, int id) {
    Puzzle* encontrado = NULL;
    int i = 0;
    while (i < p->num_puzzles && encontrado == NULL) {
        if (p->puzzles[i].id == id) encontrado = &(p->puzzles[i]);
        i++;
    }
    return encontrado;
}