#include "conexiones.h"
#include <string.h>
#include <stdio.h>



/**
 * @brief Crea e inicializa una nueva estructura de tipo Conexion.
 * * @param id      Identificador único de la conexión (debe ser >= 0).
 * @param nombre  Cadena de caracteres con el nombre de la conexión (no debe ser NULL).
 * @param origen  Identificador de la sala de origen (debe ser >= 0).
 * @param destino Identificador de la sala de destino (debe ser >= 0).
 * @param activa  Estado inicial de la conexión (1 = Abierta, 0 = Bloqueada).
 * @param id_obj  ID del objeto necesario para abrir la conexión (-1 si no necesita objeto).
 * @param id_puz  ID del puzle necesario para abrir la conexión (-1 si no necesita puzle).
 * * @return Conexion La estructura inicializada con los valores proporcionados.
 */
Conexion conexion_crear(int id, const char *nombre, int origen, int destino, int activa, int id_obj, int id_puz) {
    Conexion nueva_conexion;
    nueva_conexion.id = id;
    nueva_conexion.id_sala_origen = origen; 
    nueva_conexion.id_sala_destino = destino; 
    nueva_conexion.activa = activa; 
    nueva_conexion.id_objeto_necesario = id_obj; 
    nueva_conexion.id_puzzle_necesario = id_puz; 
    
    strncpy(nueva_conexion.nombre, nombre, MAX_NOMBRE_CONEXION - 1);
    nueva_conexion.nombre[MAX_NOMBRE_CONEXION - 1] = '\0'; 
    
    return nueva_conexion; 
}

/**
 * @brief Intenta desbloquear una conexión utilizando un objeto específico.
 * * @param c         Puntero a la conexión válida que se desea abrir.
 * @param id_objeto Identificador del objeto que el jugador intenta usar (debe ser >= 0).
 * * @return int 1 si el id del objeto coincide con la cerradura (pone 'activa' a 1). 0 en caso contrario.
 */
int conexion_intentar_abrir_objeto(Conexion *c, int id_objeto) {
    int exito = 0; 
    if (c->activa == 1) { 
        exito = 1;
    } else if (c->id_objeto_necesario != -1 && c->id_objeto_necesario == id_objeto) { 
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}

/**
 * @brief Intenta desbloquear una conexión tras resolver un puzle.
 * * @param c         Puntero a la conexión válida que se desea abrir.
 * @param id_puzzle Identificador del puzle que se ha resuelto (debe ser >= 0).
 * * @return int 1 si el id del puzle coincide (pone 'activa' a 1). 0 en caso contrario.
 */
int conexion_intentar_abrir_puzzle(Conexion *c, int id_puzzle) {
    int exito = 0;
    if (c->activa == 1) {
        exito = 1;
    } else if (c->id_puzzle_necesario != -1 && c->id_puzzle_necesario == id_puzzle) {
        c->activa = 1; 
        exito = 1;
    }
    return exito; 
}