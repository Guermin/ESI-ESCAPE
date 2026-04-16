#ifndef JUGADORES_H
#define JUGADORES_H

#include "inventario.h"

#define MAX_NOMBRE_JUGADOR 50

typedef struct {
    char nombre[MAX_NOMBRE_JUGADOR];
    int id_sala_actual;              
    Inventario mochila;              
} Jugador;

/* PRE: 'nombre' no es NULL. POST: Crea el jugador con mochila vacía dinámica. */
Jugador jugador_crear(const char *nombre, int id_sala_inicio);

/* PRE: 'j' válido. POST: Actualiza sala actual del jugador. */
int jugador_mover(Jugador *j, int id_nueva_sala);

/* Funciones puente que delegan la lógica al módulo de inventario */
int jugador_recoger_objeto(Jugador *j, int id_objeto);
int jugador_soltar_objeto(Jugador *j, int id_objeto);
int jugador_tiene_objeto(Jugador j, int id_objeto);

/* PRE: 'j' válido. POST: Libera la memoria del inventario interno. */
void jugador_destruir(Jugador *j);

#endif
