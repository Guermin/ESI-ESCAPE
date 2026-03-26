#ifndef PARTIDA_H
#define PARTIDA_H
#include "salas.h"
#include "conexiones.h"
#include "puzzles.h"
#include "objetos.h"
#include "jugadores.h"

#define MAX_SALAS_PARTIDA 6
#define MAX_CONEXIONES_PARTIDA 12
#define MAX_OBJETOS_PARTIDA 4
#define MAX_PUZZLES_PARTIDA 4

typedef struct {
    Sala salas[MAX_SALAS_PARTIDA];
    int num_salas;                   
    
    Conexion conexiones[MAX_CONEXIONES_PARTIDA];
    int num_conexiones;
    
    Objeto objetos[MAX_OBJETOS_PARTIDA];
    int num_objetos;
    
    Puzzle puzzles[MAX_PUZZLES_PARTIDA];
    int num_puzzles;
    
    Jugador jugador_actual;          
} EstadoPartida;

/* PRE:  'nombre_jugador' no es NULL. 
 * POST: Tablero vacío, todos los contadores a 0, jugador creado e inicializado. 
 */
EstadoPartida partida_crear(const char *nombre_jugador, int id_sala_inicio);


/* PRE:  'p' puntero válido.
 * POST: Libera los elementos dinámicos que existen en la partida.
 */
void partida_destruir(EstadoPartida *p);

/* Funciones de inserción, devuelve 1 en caso de exito, o 0 en caso de que supere el limite establecido en las macros. */
int partida_añadir_sala(EstadoPartida *p, Sala s);
int partida_añadir_conexion(EstadoPartida *p, Conexion c);
int partida_añadir_objeto(EstadoPartida *p, Objeto obj);
int partida_añadir_puzzle(EstadoPartida *p, Puzzle puz);

/* Funciones de búsqueda, devuelven el puntero en memoria del elemento, o null en caso de que no exista. */
Sala* partida_obtener_sala(EstadoPartida *p, int id);
Conexion* partida_obtener_conexion(EstadoPartida *p, int id);
Objeto* partida_obtener_objeto(EstadoPartida *p, int id);
Puzzle* partida_obtener_puzzle(EstadoPartida *p, int id);



#endif