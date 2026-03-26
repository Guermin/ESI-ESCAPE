#ifndef CONEXIONES_H
#define CONEXIONES_H

#define MAX_NOMBRE_CONEXION 50

typedef struct {
    int id;
    char nombre[MAX_NOMBRE_CONEXION];
    int id_sala_origen;
    int id_sala_destino;
    int activa; // 1 = Abierta, 0 = Bloqueada
    int id_objeto_necesario; // -1 si no necesita objeto
    int id_puzzle_necesario; // -1 si no necesita puzle
} Conexion;

/* * PRE:  'id', 'origen', y 'destino' >= 0. 'nombre' no es NULL.
 * POST: Devuelve una Conexion inicializada. 
 */
Conexion conexion_crear(int id, const char *nombre, int origen, int destino, int activa, int id_obj, int id_puz);

#endif