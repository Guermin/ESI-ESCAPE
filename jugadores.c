#include "jugadores.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Crea e inicializa un nuevo jugador.
 * * @param nombre         Cadena de caracteres con el nombre del jugador.
 * @param id_sala_inicio Identificador de la sala donde empezará el jugador.
 * * @return Jugador La estructura del jugador inicializada con su nombre, sala y mochila vacía.
 */
Jugador jugador_crear(const char *nombre, int id_sala_inicio) {
    Jugador nuevo_jugador;
    
    strncpy(nuevo_jugador.nombre, nombre, MAX_NOMBRE_JUGADOR - 1);
    nuevo_jugador.nombre[MAX_NOMBRE_JUGADOR - 1] = '\0';//Aseguramos que la cadena termine correctamente
    nuevo_jugador.id_sala_actual = id_sala_inicio;
    nuevo_jugador.mochila = inventario_crear();
    
    return nuevo_jugador; 
}

/**
 * @brief Actualiza la posición del jugador moviéndolo a una nueva sala.
 * * @param j             Puntero al jugador que se va a mover.
 * @param id_nueva_sala Identificador de la sala de destino.
 * * @return int Devuelve 1 indicando que el movimiento ha sido exitoso.
 */
int jugador_mover(Jugador *j, int id_nueva_sala) {
    j->id_sala_actual = id_nueva_sala;
    return 1; 
}

/**
 * @brief Añade un objeto al inventario (mochila) del jugador.
 * * @param j         Puntero al jugador que recoge el objeto.
 * @param id_objeto Identificador del objeto a recoger.
 * * @return int Devuelve el resultado de inventario_añadir (típicamente 1 si hay éxito, 0 si falla).
 */
int jugador_recoger_objeto(Jugador *j, int id_objeto) {
    int exito = inventario_añadir(&(j->mochila), id_objeto); 
    return exito; 
}

/**
 * @brief Elimina un objeto del inventario (mochila) del jugador.
 * * @param j         Puntero al jugador que suelta el objeto.
 * @param id_objeto Identificador del objeto a soltar.
 * * @return int Devuelve el resultado de inventario_quitar (típicamente 1 si hay éxito, 0 si falla).
 */
int jugador_soltar_objeto(Jugador *j, int id_objeto) {
    int exito = inventario_quitar(&(j->mochila), id_objeto);
    return exito; 
}

/**
 * @brief Comprueba si el jugador lleva un objeto concreto en su mochila.
 * * @param j         Estructura del jugador a comprobar.
 * @param id_objeto Identificador del objeto buscado.
 * * @return int 1 si el jugador tiene el objeto, 0 en caso contrario.
 */
int jugador_tiene_objeto(Jugador j, int id_objeto) {
    int lo_tiene = inventario_tiene(j.mochila, id_objeto); //Solo comprobamos si un jugador tiene o no el objeto
    return lo_tiene; 
}

/**
 * @brief Libera la memoria y los recursos asociados al jugador.
 * * @param j Puntero al jugador a destruir.
 */
void jugador_destruir(Jugador *j) {
    inventario_destruir(&(j->mochila));
}