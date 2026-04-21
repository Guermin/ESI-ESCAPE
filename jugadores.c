#include "jugadores.h"
#include <stdio.h>
#include <string.h>

Jugador jugador_crear(const char *nombre, int id_sala_inicio) {
    Jugador nuevo_jugador;
    
    strncpy(nuevo_jugador.nombre, nombre, MAX_NOMBRE_JUGADOR - 1);
    nuevo_jugador.nombre[MAX_NOMBRE_JUGADOR - 1] = '\0';//Aseguramos que la cadena termine correctamente
    nuevo_jugador.id_sala_actual = id_sala_inicio;
    nuevo_jugador.mochila = inventario_crear();
    
    return nuevo_jugador; 
}

int jugador_mover(Jugador *j, int id_nueva_sala) {
    j->id_sala_actual = id_nueva_sala;
    return 1;  //Devolvemos siempre 1 porque si se llega a esta función significa que te puedes mover
}

int jugador_recoger_objeto(Jugador *j, int id_objeto) {
    //pasamos una dirección de memoria porque el inventario puede incrementar
    int exito = inventario_añadir(&(j->mochila), id_objeto); 
    return exito; 
}

int jugador_soltar_objeto(Jugador *j, int id_objeto) {
    int exito = inventario_quitar(&(j->mochila), id_objeto);
    return exito; 
}

int jugador_tiene_objeto(Jugador j, int id_objeto) {
    int lo_tiene = inventario_tiene(j.mochila, id_objeto); //Solo comprobamos si un jugador tiene o no el objeto
    return lo_tiene; 
}

void jugador_destruir(Jugador *j) {
    inventario_destruir(&(j->mochila));
}