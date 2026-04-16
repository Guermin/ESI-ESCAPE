#ifndef FICHEROS_H
#define FICHEROS_H

#include "partida.h"

/* PRE:  'p' es un puntero válido. Los ficheros .txt existen y cumplen el formato.
 * POST: Carga las entidades, extrae sus IDs numéricos, y las asigna a las salas correspondientes. Devuelve 1 si todas las cargas tienen éxito, o 0 si falta algún fichero. 
 */
int ficheros_cargar_todo(EstadoPartida *p);

/* PRE:  'p' es un puntero válido.
 * POST: Crea o sobreescribe "Partida.txt" con el formato exigido en la especificación. Devuelve 1 en caso de éxito y 0 en fallo de apertura de fichero. 
 */
int ficheros_guardar_partida(EstadoPartida *p);

/* PRE:  'p' es un puntero válido y el tablero base ya está cargado.
 * POST: Lee el archivo "Partida.txt" y restaura la sala actual, inventario, estado de conexiones y puzles. Devuelve 1 en éxito y 0 si no encuentra el archivo.
 */
int ficheros_cargar_partida(EstadoPartida *p);



#endif