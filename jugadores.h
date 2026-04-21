#ifndef JUGADORES_H
#define JUGADORES_H

#include "inventario.h"

#define MAX_NOMBRE_JUGADOR 50

typedef struct {
    char nombre[MAX_NOMBRE_JUGADOR];
    int id_sala_actual;              
    Inventario mochila;              
} Jugador;

/*  Cabecera: Jugador jugador_crear(const char *nombre, int id_sala_inicio)
    Precondición: 'nombre' no es NULL. 
    Postcondición: Crea el jugador con mochila vacía dinámica. */
Jugador jugador_crear(const char *nombre, int id_sala_inicio);

/*  Cabecera: int jugador_mover(Jugador *j, int id_nueva_sala)
    Precondición: 'j' válido. 
    Postcondición: Actualiza sala actual del jugador. */
int jugador_mover(Jugador *j, int id_nueva_sala);

/*  Funciones puente que delegan la lógica al módulo de inventario */
/*  Cabecera: int jugador_recoger_objeto(Jugador *j, int id_objeto)
    Precondición: j e id_objeto válidos
    Postcondición: Añade un objeto al inventario*/
int jugador_recoger_objeto(Jugador *j, int id_objeto);

/*  Cabecera: int jugador_soltar_objeto(Jugador *j, int id_objeto)
    Precondición: j e id_objeto válidos
    Postcondición: Elimina un objeto al inventario*/
int jugador_soltar_objeto(Jugador *j, int id_objeto);

/*  Cabecera: int jugador_tiene_objeto(Jugador *j, int id_objeto)
    Precondición: j e id_objeto válidos
    Postcondición:  Informa si el jugador tiene cierto objeto en elinventario*/
int jugador_tiene_objeto(Jugador j, int id_objeto);

/*  Cabecera: void jugador_destruir(Jugador *j)
    Precondición: 'j' válido. 
    Postcondición: Libera la memoria del inventario interno. */
void jugador_destruir(Jugador *j);

#endif
