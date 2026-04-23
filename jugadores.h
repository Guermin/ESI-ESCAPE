#ifndef JUGADORES_H
#define JUGADORES_H

#include "inventario.h"

#define MAX_NOMBRE_JUGADOR 50

typedef struct {
    char nombre[MAX_NOMBRE_JUGADOR];
    int id_sala_actual;              
    Inventario mochila;              
} Jugador;

Jugador jugador_crear(const char *nombre, int id_sala_inicio);

int jugador_mover(Jugador *j, int id_nueva_sala);

int jugador_recoger_objeto(Jugador *j, int id_objeto);

int jugador_soltar_objeto(Jugador *j, int id_objeto);

int jugador_tiene_objeto(Jugador j, int id_objeto);

void jugador_destruir(Jugador *j);

#endif
